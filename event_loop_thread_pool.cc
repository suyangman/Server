#include "event_loop_thread_pool.h"
#include "event_loop.h"
#include "event_loop_thread.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop* pBaseLoop) : m_p_base_loop(pBaseLoop)
{
}

EventLoopThreadPool::~EventLoopThreadPool()
{

}

void EventLoopThreadPool::DoSetThreadNum(int i_thread_nums)
{
  m_i_thread_nums = i_thread_nums;
}

void EventLoopThreadPool::DoStart()
{
  m_p_base_loop->assertInLoopThread();

  for (int i = 0; i < m_i_thread_nums; ++i)
  {
    EventLoopThread* t = new EventLoopThread();
    m_vec_threads.push_back(std::unique_ptr<EventLoopThread>(t));
    m_vec_thread_loops.push_back(t->GetThreadLoop());
  }
}

EventLoop* EventLoopThreadPool::GetNextLoop()
{
  m_p_base_loop->assertInLoopThread();
  EventLoop* loop = m_p_base_loop;

  if (!m_vec_thread_loops.empty())
  {
    loop = nullptr;
    while (loop == nullptr)
    {
      loop = m_vec_thread_loops[m_i_next_thread];
      ++m_i_next_thread;
      if (implicit_cast<size_t>(m_i_next_thread) >= m_vec_thread_loops.size())
      {
        m_i_next_thread = 0;
      }
    }
  }
  return loop;
}
