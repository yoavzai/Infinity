//#include <iostream>
#include <fstream>

#include "logger.hpp"

int main()
{
    Logger my_logger(Logger::INFO);
    std::ofstream myfile;
    myfile.open ("my_log.txt");

    my_logger.Log(Logger::INFO, "INFO");
    my_logger.Log(Logger::ERROR, "ERROR");

    my_logger.SetOutput(myfile);
    my_logger.SetOutputSeverity(Logger::ERROR);

    my_logger.Log(Logger::INFO, "INFO");
    my_logger.Log(Logger::ERROR, "ERROR");

    myfile.close();

    return 0;
}