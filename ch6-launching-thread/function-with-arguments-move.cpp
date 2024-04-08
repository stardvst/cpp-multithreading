#include <iostream>
#include <thread>
#include <string>

void f(std::string str)
{
  std::cout << "str in function: " << str << '\n';
}

int main(int argc, const char *argv[])
{
  std::string str{"abc"};
  std::cout << "str in main (before): " << str << '\n';

  std::thread t(f, std::move(str));
  t.join();

  std::cout << "str in main (after): " << str << '\n';
  return 0;
}
