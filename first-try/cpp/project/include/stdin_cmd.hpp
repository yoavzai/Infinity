#ifndef _STDIN_CMD_
#define _STDIN_CMD_

#include "reactor.hpp"
#include "boost/shared_ptr.hpp"

namespace ilrd
{

class StdinCmd
{
public:
    StdinCmd(Reactor* reactor_) : m_reactor(reactor_) {};
    virtual void operator()() = 0;

    Reactor* m_reactor;
};

class ExitCmd : public StdinCmd
{
public:
    ExitCmd(Reactor* reactor_) : StdinCmd(reactor_) {};
    void operator()();
};

class PlusCmd : public StdinCmd
{
public:
    PlusCmd(Reactor* reactor_) : StdinCmd(reactor_) {};
    void operator()();
};

class MinusCmd : public StdinCmd
{
public:
    MinusCmd(Reactor* reactor_) : StdinCmd(reactor_) {};
    void operator()();
};

boost::shared_ptr<StdinCmd> ExitCreator(Reactor*);

boost::shared_ptr<StdinCmd> PlusCreator(Reactor*);

boost::shared_ptr<StdinCmd> MinusCreator(Reactor*);

} // namespace ILRD

#endif

