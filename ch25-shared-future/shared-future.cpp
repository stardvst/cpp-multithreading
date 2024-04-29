#include <iostream>
#include <thread>
#include <chrono>
#include <future>

using namespace std::literals;

void produce(std::promise<int> &promise)
{
  int x{42};
  std::cout << "The promise sets the shared state to " << x << '\n';
  std::this_thread::sleep_for(1s);

  promise.set_value(x);
}

void consume(std::shared_future<int> &future)
{
  std::cout << "The future calls get()...\n";

  int x = future.get();

  std::cout << "The future returns from get()\n";
  std::cout << "The answer is " << x << '\n';
}

int main()
{
  std::promise<int> p;
  std::shared_future sf1 = p.get_future();
  std::shared_future sf2{sf1};

  std::thread consumer1{consume, std::ref(sf1)};
  std::thread consumer2{consume, std::ref(sf2)};
  std::thread producer{produce, std::ref(p)};

  consumer1.join();
  consumer2.join();
  producer.join();
}
