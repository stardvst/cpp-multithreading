#pragma once

#include "../ch40-concurrent-queue/concurrent-queue_cv.h"
#include <thread>
#include <functional>
#include <vector>

using Func = std::function<void()>;

class threadPool
{
public:
  threadPool()
  {
    const unsigned threadCount = std::thread::hardware_concurrency();
    for (unsigned i = 0; i < threadCount; ++i)
      m_threads.push_back(std::thread{&threadPool::worker, this});
  }

  ~threadPool()
  {
    stop();
    for (auto &thread : m_threads)
      thread.join();
  }

  void submit(Func f)
  {
    m_tasks.push(f);
    m_cv.notify_all();
  }

private:
  void worker()
  {
    while (true)
    {
      Func task;
      {
        std::unique_lock lk{m_mutex};
        m_cv.wait(lk, [this]
                  { return !m_tasks.empty(); });
        m_tasks.pop(task);
      }

      if (!task)
        break;

      task();
    }
  }

  void stop()
  {
    for (unsigned i = 0; i < m_threads.size(); ++i)
      m_tasks.push(nullptr);
    m_cv.notify_all();
  }

  cq::concurrent_queue<Func> m_tasks{};
  std::vector<std::thread> m_threads{};

  std::mutex m_mutex{};
  std::condition_variable m_cv;
};
