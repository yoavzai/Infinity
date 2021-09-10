#include <iosfwd>
#include <iostream>
#include <queue>
#include <string>

#include "waitable_queue.hpp"
#include "thread.hpp"

using std::queue;

namespace ilrd
{

class Logger
{
public:
    enum Severity {DEBUG, INFO, WARNING, ERROR};

    explicit Logger(Severity initialSeverity = DEBUG,
                    std::ostream* output = &std::cout,
                    size_t interval = 5); // interval for checking if Exit wanted

    ~Logger();
    void Log(Severity msgSeverity, const char* msg);
    void Log(Severity msgSeverity, const std::string msg);

    void SetOutputSeverity(Severity OutputSeverity);
    void SetOutput(std::ostream &output);
    void SetInterval(size_t interval);

    Severity GetSeverity() const;
    std::ostream* GetStream() const;
    size_t GetInterval() const;

    void Exit();

private:
    static void* WriteToFile(void* arg);

    pthread_mutex_t seters_mutex;
    Severity cur_severity;
    std::ostream* output_ptr;
    size_t m_interval;

    WaitableQueue< std::queue<std::string> > m_queue;
    bool stay_active;

    Thread m_writer;
};

} // namespace ILRD