#pragma once
#include "nocopyable.h"
#include "functional"
#include "thread"
#include "mutex"
#include "condition_variable"

class EventLoop;

class EventLoopThread : noncopyable
{
 public:
  EventLoopThread();
  ~EventLoopThread();
  EventLoop* GetThreadLoop();

 private:
  void threadFunc();

  EventLoop* m_p_loop = nullptr;
  std::thread m_thread(threadFunc);
  std::mutex m_mutex;
  std::condition_variable m_condition;
};

