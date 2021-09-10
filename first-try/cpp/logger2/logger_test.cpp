#include <fstream>
#include <iostream>

#include "logger.hpp"
#include "thread.hpp"
#include "singleton.hpp"

using namespace ilrd;

//Logger my_log;

void* Thread1Func(void* arg)
{
    Logger& my_log = *(Singleton<Logger>::Instance());
    (void)arg;
    my_log.Log(Logger::DEBUG, "Thread1: DEBUG, change severity to INFO");
    sleep(1);
    my_log.SetOutputSeverity(Logger::INFO);
    my_log.Log(Logger::DEBUG, "Thread1: DEBUG, I shouldn't be here!!!");
    sleep(9);
    my_log.Log(Logger::DEBUG, "Thread1: DEBUG, hello consule!");

    return NULL;
}

void* Thread2Func(void* arg)
{
    Logger& my_log = *(Singleton<Logger>::Instance());


    (void)arg;
    my_log.Log(Logger::INFO, "Thread2: INFO");
    sleep(1);
    my_log.Log(Logger::INFO, "Thread2: INFO, change severity to WARNING");
    sleep(1);
    my_log.SetOutputSeverity(Logger::WARNING);
    my_log.Log(Logger::INFO, "Thread2: INFO, I shouldn't be here!!!");
    sleep(8);
    my_log.Log(Logger::INFO, "Thread2: INFO, hello consule!");

    return NULL;
}

void* Thread3Func(void* arg)
{
    Logger& my_log = *(Singleton<Logger>::Instance());


    (void)arg;
    my_log.Log(Logger::WARNING, "Thread3: WARNING");
    sleep(1);
    my_log.Log(Logger::WARNING, "Thread3: WARNING");
    sleep(1);
    my_log.Log(Logger::WARNING, "Thread3: WARNING, change severity to ERROR");
    sleep(1);
    my_log.SetOutputSeverity(Logger::ERROR);
    my_log.Log(Logger::WARNING, "Thread3: WARNING, I shouldn't be here!!!");
    sleep(7);
    my_log.Log(Logger::WARNING, "Thread3: WARNING, hello consule!");

    return NULL;
}

void* Thread4Func(void* arg)
{
    Logger& my_log = *(Singleton<Logger>::Instance());


    (void)arg;
    my_log.Log(Logger::ERROR, "Thread4: ERROR");
    sleep(1);
    my_log.Log(Logger::ERROR, "Thread4: ERROR");
    sleep(1);
    my_log.Log(Logger::ERROR, "Thread4: ERROR");
    sleep(1);
    my_log.Log(Logger::ERROR, "Thread4: ERROR, change severity to DEBUG and Output to stdin");
    sleep(1);
    my_log.SetOutputSeverity(Logger::DEBUG);
    my_log.Log(Logger::ERROR, "Thread4: ERROR, I should be here");
    my_log.SetOutput(std::cout);
    sleep(6);
    my_log.Log(Logger::ERROR, "Thread4: ERROR, hello consule!");

    return NULL;
}

int main()
{   
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;

    Logger& my_log = *(Singleton<Logger>::Instance());
    
    std::ofstream file;
    file.open("test.log", std::ofstream::out | std::ofstream::app);

    my_log.SetOutput(file);
    my_log.SetOutputSeverity(Logger::DEBUG);

    pthread_create(&thread1, NULL, Thread1Func, NULL);
    pthread_create(&thread2, NULL, Thread2Func, NULL);
    pthread_create(&thread3, NULL, Thread3Func, NULL);
    pthread_create(&thread4, NULL, Thread4Func, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    my_log.Exit();

    return 0;
}