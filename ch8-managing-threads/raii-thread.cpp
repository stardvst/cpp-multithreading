#include <thread>
#include <iostream>

class threadGuard
{
public:
  explicit threadGuard(std::thread &&thread)
      : m_thread(std::move(thread))
  {
    std::cout << "creating guard\n";
  }

  threadGuard(const threadGuard &) = delete;
  threadGuard &operator=(const threadGuard &) = delete;

  ~threadGuard()
  {
    std::cout << "destroying guard\n";
    if (m_thread.joinable())
      m_thread.join();
  }

private:
  std::thread m_thread{};
};

int main()
{
  std::thread t([]
                { std::cout << "Hello from thread!\n"; });
  threadGuard tg{std::move(t)};

  try
  {
    std::cout << "in try\n";
    throw 1;
  }
  catch(...)
  {
    std::cerr << "in catch\n";
  }

  return 0;
}
