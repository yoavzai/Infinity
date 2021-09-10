#include <iosfwd>
#include <iostream>

#include "logger.hpp"

using std::endl;


Logger::Logger(Severity initialSeverity)
    : cur_severity(initialSeverity), output_ptr(&std::cerr)
{}

void Logger::Log(Severity msgSeverity, const char* msg)
{
    if (msgSeverity >= cur_severity)
    {
        *output_ptr << msg << endl;
    }
}

void Logger::Log(Severity msgSeverity, const std::string msg)
{
    if (msgSeverity >= cur_severity)
    {
        *output_ptr << msg << endl;
    }
}

void Logger::SetOutputSeverity(Severity OutputSeverity)
{
    cur_severity = OutputSeverity;
}
    
void Logger::SetOutput(std::ostream& output)
{
    output_ptr = &output;
}

