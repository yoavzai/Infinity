#include <string>
#include <iostream>

#include "boost/shared_ptr.hpp"
#include "logger.hpp"
#include "singleton.hpp"
#include "reactor.hpp"
#include "stdin_cmd.hpp"

namespace ilrd
{

void ExitCmd::operator()()
{
    Logger* m_log = Singleton<Logger>::Instance();
    m_log->Log(Logger::ERROR, "'exit' pressed");

    m_reactor->Stop();
}

void PlusCmd::operator()()
{
    Logger* m_log = Singleton<Logger>::Instance();
    m_log->Log(Logger::ERROR, "'+' pressed");
  
    int cur_severity = (int)m_log->GetSeverity();

    if (cur_severity != (int)Logger::ERROR)
    {
        m_log->SetOutputSeverity((Logger::Severity)(cur_severity + 1));
    }
}

void MinusCmd::operator()()
{
    Logger* m_log = Singleton<Logger>::Instance();
    m_log->Log(Logger::ERROR, "'-' pressed");
  
    int cur_severity = (int)m_log->GetSeverity();

    if (cur_severity != (int)Logger::DEBUG)
    {
        m_log->SetOutputSeverity((Logger::Severity)(cur_severity - 1));
    }
}

boost::shared_ptr<StdinCmd> ExitCreator(Reactor* reactor_)
{
    boost::shared_ptr<StdinCmd> nc(new ExitCmd(reactor_));

    return nc;   
}

boost::shared_ptr<StdinCmd> PlusCreator(Reactor* reactor_)
{
    boost::shared_ptr<StdinCmd> nc(new PlusCmd(reactor_));

    return nc;
}

boost::shared_ptr<StdinCmd> MinusCreator(Reactor* reactor_)
{
    boost::shared_ptr<StdinCmd> nc(new MinusCmd(reactor_));

    return nc;
}

} // namespace ILRD