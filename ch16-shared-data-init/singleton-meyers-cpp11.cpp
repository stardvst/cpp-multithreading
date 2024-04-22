#include <iostream>
#include <vector>
#include <thread>

class Singleton
{
public:
  static Singleton *getInstance()
  {
    static Singleton instance;
    return &instance;
  }

protected:
  Singleton()
  {
    std::cout << "Initializng singleton\n";
  }

private:
  static Singleton *m_instance;
};

Singleton *Singleton::m_instance = nullptr;

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
