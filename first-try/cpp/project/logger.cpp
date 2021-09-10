#include <iosfwd>
#include <iostream>

#include "logger.hpp"

using std::endl;

namespace ilrd
{

void* Logger::WriteToFile(void* arg)
{
    Logger* logger = static_cast<Logger*>(arg);
    std::string to_log;

    while (logger->stay_active)
    {
        if (logger->m_queue.Pop(to_log, logger->m_interval))
        {
            *(logger->GetStream()) << to_log << endl;
        }
    }

    return NULL;
}

Logger::Logger(Severity initialSeverity, std::ostream* output, size_t interval)
    :   cur_severity(initialSeverity),
        output_ptr(output),
        m_interval(interval),
        stay_active(true),
        m_writer(WriteToFile, this)
{}

Logger::~Logger()
{
    m_writer.Join();
}

void Logger::Log(Severity msgSeverity, const char* msg)
{
    if (msgSeverity >= GetSeverity())
    {
        m_queue.Push(msg);
    }
}

void Logger::Log(Severity msgSeverity, const std::string msg)
{
    if (msgSeverity >= GetSeverity())
    {
        m_queue.Push(msg);
    }
}

void Logger::SetOutputSeverity(Severity OutputSeverity)
{
    pthread_mutex_lock(&seters_mutex);
    cur_severity = OutputSeverity;
    pthread_mutex_unlock(&seters_mutex);
}
    
void Logger::SetOutput(std::ostream& output)
{
    pthread_mutex_lock(&seters_mutex);
    output_ptr = &output;
    pthread_mutex_unlock(&seters_mutex);
}

void Logger::SetInterval(size_t interval)
{
    pthread_mutex_lock(&seters_mutex);
    m_interval = interval;
    pthread_mutex_unlock(&seters_mutex);
}

Logger::Severity Logger::GetSeverity() const
{
    return cur_severity; 
}

std::ostream* Logger::GetStream() const
{
    return output_ptr;    
}

size_t Logger::GetInterval() const
{
    return m_interval; 
}

void Logger::Exit()
{
    stay_active = false;
}

} // namespace ILRD