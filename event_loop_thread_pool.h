#pragma once
#include "noncopyable.h"
#include "memory"
#include "vector"

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool : noncopyable
{
public:
  EventLoopThreadPool(EventLoop* baseLoop);
  ~EventLoopThreadPool();

  void DoSetThreadNum(int i_thread_nums);   //设置线程数目
  void DoStart();                           //启动线程
  EventLoop* GetNextLoop();

private:
  //EveneLoop都是在堆上，析构的时候不需要delete
  EventLoop*  m_p_base_loop;
  int         m_i_thread_nums = 0;
  int         m_i_next_thread = 0;
  std::vector<std::unique_ptr<EventLoopThread>> m_vec_threads;
  std::vector<EventLoop*>   m_vec_thread_loops;
};