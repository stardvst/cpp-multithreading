#include <iostream>
#include <thread>
#include <chrono>
#include <string>

using namespace std::literals;

void print(const std::string &str)
{
  for (int i = 0; i < 5; i++)
  {
    std::cout << str[0] << str[1] << str[2] << std::endl;
    std::this_thread::sleep_for(50ms);
  }
}

int main()
{
  std::thread t1{print, "abc"};
  std::thread t2{print, "def"};
  std::thread t3{print, "xyz"};

  t1.join();
  t2.join();
  t3.join();
}
