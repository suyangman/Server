#pragma once
#include "functional"

class EventLoop;

class CAcceptor
{
public:
  typedef std::function<void (int i_accept_fd)> ListenCallback;

  CAcceptor(EventLoop* pLoop);
  ~CAcceptor();
private:
  EventLoop*      m_p_base_loop   = nullptr;
  int		          m_fd_listen     = -1;        //listen socket
  int             m_fd_idle       = -1;
  ListenCallback  m_func_listen_callback;
};
