#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

std::once_flag flag;

class Singleton
{
public:
  static Singleton *getInstance()
  {
    std::call_once(flag, []
                   { m_instance = new Singleton{}; });
    return m_instance;
  }

protected:
  Singleton()
  {
    std::cout << "Initializng singleton\n";
  }

private:
  static Singleton *m_instance;
  static std::mutex m_mutex;
};

Singleton *Singleton::m_instance = nullptr;
std::mutex Singleton::m_mutex;

void task()
{
  auto *s = Singleton::getInstance();
  std::cout << s << std::endl;
}

int main()
{
  std::vector<std::thread> threads;

  for (auto i = 0; i < 10; ++i)
    threads.push_back(std::thread{task});

  for (auto &thread : threads)
    thread.join();
}
