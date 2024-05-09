#include <queue>
#include <mutex>
#include <thread>
#include <exception>

namespace cq
{

  class concurrent_queue_exception : public std::runtime_error
  {
  public:
    using std::runtime_error::runtime_error;
    concurrent_queue_exception() : std::runtime_error("Queue is empty") {}
  };

  template <class T>
  class concurrent_queue
  {
  public:
    concurrent_queue() = default;

    void push(T value)
    {
      std::lock_guard lg{m_mutex};
      m_queue.push(value);
      m_cv.notify_one();
    }

    void pop(T &value)
    {
      std::unique_lock lk{m_mutex};
      m_cv.wait(lk, [this]
                { return !m_queue.empty(); });

      value = m_queue.front();
      m_queue.pop();
    }

    bool empty() const
    {
      std::lock_guard lg{m_mutex};
      return m_queue.empty();
    }

  private:
    std::queue<T> m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_cv;
  };
}
