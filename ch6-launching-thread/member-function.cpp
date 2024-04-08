#include <iostream>
#include <thread>
#include <string>

class greeter
{
public:
  void hello()
  {
    std::cout << "Hello, Thread!\n";
  }

  void world(const std::string &str)
  {
    std::cout << str << '\n';
  }
};

int main(int argc, const char *argv[])
{
  greeter g;

  std::thread t(&greeter::hello, &g);
  t.join();

  std::string str{"Hello, World!"};
  std::thread t2(&greeter::world, &g, std::cref(str));
  t2.join();

  return 0;
}
