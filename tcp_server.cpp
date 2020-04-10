#include "tcp_server.h"
#include "event_loop_thread_pool.h"
#include "acceptor.h"
#include "macrodefine.h"

CTCPServer::CTCPServer(EventLoop* pLoop)
{
    m_p_base_loop = pLoop;
    m_p_thread_pool = new(std::nothrow) EventLoopThreadPool(pLoop);
    VERIFY(m_p_thread_pool);
    m_p_acceptor = new(std::nothrow) CAcceptor(pLoop);
}

CTCPServer::~CTCPServer()
{

}

void CTCPServer::SetThreadNum(int i_thread_nums)
{
    m_p_thread_pool->DoSetThreadNum(i_thread_nums);
}

void CTCPServer::TcpServerStart()
{
    m_p_thread_pool->DoStart();
}