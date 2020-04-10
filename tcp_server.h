#pragma once
#include "nocopyable.h"
#include "memory"

class EventLoop;
class EventLoopThreadPool;
class CTCPServer : noncopyable
{
public:
    CTCPServer(EventLoop* pLoop);
    ~CTCPServer();

    void    SetThreadNum(int i_thread_nums);

    void	TcpServerStart();

	void	TcpServerStop();

protected:
private:
    EventLoop*                              m_p_base_loop   = nullptr;
    std::unique_ptr<EventLoopThreadPool>    m_p_thread_pool = nullptr;
    std::unique_ptr<CAcceptor>              m_p_acceptor    = nullptr;
};