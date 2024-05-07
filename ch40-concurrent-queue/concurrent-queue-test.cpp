#include <iostream>
#include <future>
#include <string>
#include <chrono>
#include "concurrent-queue.h"

using namespace std::literals;

cq::concurrent_queue<std::string> conc_queue;

void writer()
{
  std::cout << "Writer calling push...\n";
  conc_queue.push("Populated");
  std::cout << "Writer returned from push...\n";
}

void reader()
{
  std::string data;

  std::this_thread::sleep_for(2s);

  try
  {
    std::cout << "Reader calling pop...\n";
    conc_queue.pop(data);
    std::cout << "Reader received data: " << data << "\n";
  }
  catch (const std::exception &e)
  {
    std::cerr << "Exception caught: " << e.what() << '\n';
  }
}

int main()
{
  auto w = std::async(std::launch::async, writer);
  auto r = std::async(std::launch::async, reader);
  r.wait();
  w.wait();
}
