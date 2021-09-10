// gc+ shape.cpp line.cpp demo2.cpp -L. -lpoint -lglut_utils -Wl,-rpath,.

#include <vector>
#include <iostream>
#include <fstream>

#include "glut_utils.h"
#include "shape.hpp"
#include "point.hpp"
#include "serializer.hpp"

using namespace ilrd;

static void DrawFunction();
static int TimerFunction();

bool load_shapes = false;
int drawLine = 1;
double lineAngle = 0;
double manAngle = 2;
double manX = 0;
double manY = 0;

int main(int argc, char** argv)
{
    load_shapes = argc > 1;

    DrawInit(argc, argv, 1000, 1000, DrawFunction);
    DrawSetTimerFunc(TimerFunction, 75);

    DrawMainLoop();

    return 0;
}

void InitShapes(std::vector<Shape*>& vector)
{
    ShapeGroup* man  = new ShapeGroup;
    man->Add(new Circle(20, Point(0, 0), 0, COLOR_YELLOW));
    man->Add(new Rectangle(10, 100, Point(35, -10), 0, COLOR_WHITE));
    man->Add(new Rectangle(10, 80, Point(20, 170), 0, COLOR_WHITE));
    man->Add(new Rectangle(10, 80, Point(-20, 170), 0, COLOR_WHITE));
    man->Add(new Rectangle(50, 100, Point(0, 75) , 0, COLOR_WHITE));
    man->SetPos(Point(manX, manY));
    man->SetAngle(manAngle);

    vector.push_back(new Line(200, Point(500, 500),lineAngle));
    vector.push_back(new Line(200, Point(500, 500),lineAngle + 90));
    vector.push_back(new Line(150, Point(500, 575), 270, COLOR_WHITE));
    vector.push_back(new Line(1000, Point(500, 650), 0, COLOR_GREEN));
    //vector.push_back(man);

    std::fstream file;
    file.open("saved_data.txt", std::fstream::out);
    Serializer<Shape> serializer(file);

    serializer.Serialize(vector);

    file.close();
}

void LoadShapes(std::vector<Shape*>& vector)
{
    std::fstream file;
    file.open("saved_data.txt", std::fstream::in);
    Serializer<Shape> serializer(file);

    serializer.AddType<Line>(CreateLine);

    vector = serializer.Deserialize();
}

static void DrawFunction()
{
    std::vector<Shape*> vector;

    if(load_shapes)
    {
        LoadShapes(vector);
    }

    else
    {
        InitShapes(vector);    
    }
    
    for (std::vector<Shape*>::iterator iter = vector.begin();
                 iter != vector.end(); ++iter)
    {
        (*iter)->Draw();
    }
}

static int TimerFunction()
{
    lineAngle += 10;
    //manAngle += 0.1;
    manX += 10;
    manY += 5;

    if (manX > 1200)
    {
        manX = 0;
        manY = 0;
    }

    return 1;  /* draw */
}