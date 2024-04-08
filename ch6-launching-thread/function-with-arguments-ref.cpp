#include <iostream>
#include <thread>
#include <string>

struct A
{
  A() { std::cout << "A()\n"; }
  ~A() { std::cout << "~A()\n"; }
  A(const A &a) { std::cout << "A(const A &a)\n"; }
  A &operator=(const A &a) { std::cout << "A &oeprator=(const A &a)\n"; return *this; }
  A(A &&a) { std::cout << "A(A &&a)\n"; }
  A &operator=(A &&a) { std::cout << "A &oeprator=(A &&a)\n"; return *this; }
};

void hello(std::string &str)
{
  str = "xyz";
}

void world(const A &str)
{
}

int main(int argc, const char *argv[])
{
  std::string str{"abc"};
  std::cout << "s before thread: " << str << '\n';

  std::thread t1(hello, std::ref(str));
  t1.join();
  std::cout << "s after thread: " << str << '\n';

  A a;

  // the object will be passed by value (i.e. copied) in this case
  std::cout << "-> start of passing a without std::cref():\n";
  std::thread t2(world, a);
  t2.join();
  std::cout << "<- end of passing a without std::cref():\n";

  // the object will be passed by ref (i.e. not copied) in this case
  std::cout << "-> start of passing a with std::cref():\n";
  std::thread t3(world, std::cref(a));
  t3.join();
  std::cout << "<- end of passing a with std::cref():\n";

  return 0;
}
