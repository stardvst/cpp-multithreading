#include <queue>
#include <mutex>
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
    }

    void pop(T &value)
    {
      std::lock_guard lg{m_mutex};

      if (m_queue.empty())
        throw concurrent_queue_exception();

      value = m_queue.front();
      m_queue.pop();
    }

  private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
  };
}
