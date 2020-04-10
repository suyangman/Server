#include "event_loop_thread.h"
#include "event_loop.h"

EventLoopThread::EventLoopThread()
{
}

EventLoopThread::~EventLoopThread()
{
  if (m_p_loop != nullptr)
  {
    m_p_loop->quit();
    m_thread.join();
  }
}

EventLoop* EventLoopThread::GetThreadLoop()
{
  EventLoop* loop = NULL;
  
  std::unique_lock<std::mutex> lck(m_mutex);
  while (m_p_loop == nullptr)
  {
    m_condition.wait(lck);
  }

  loop = m_p_loop;
  
  return loop;
}

void EventLoopThread::threadFunc()
{
  EventLoop loop;
  
  {
    std::unique_lock<std::mutex> lck(m_mutex);
    m_p_loop = &loop;
    m_condition.notify_all();
  }
  
  loop.loop();

  std::unique_lock<std::mutex> lck(m_mutex);
  m_p_loop = nullptr;
}

