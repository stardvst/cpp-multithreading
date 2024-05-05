#include <iostream>
#include <algorithm>
#include <vector>
#include <execution>
#include <mutex>

std::mutex m;

int main()
{
  std::vector<int> v(2000);
  int count = 0;

  std::for_each(begin(v), end(v), [&](int &x)
                { x = ++count; });

  // std::for_each(std::execution::seq, begin(v), end(v), [&](int &x)
  //               { x = ++count; });

  // std::for_each(std::execution::unseq, begin(v), end(v), [&](int &x)
  //               {
  //                 std::lock_guard<std::mutex> guard(m);
  //                 x = ++count; });

  // std::for_each(std::execution::par, begin(v), end(v), [&](int &x)
  //               {
  //                 std::lock_guard<std::mutex> guard(m);
  //                 x = ++count; });

  // std::for_each(std::execution::par_unseq, begin(v), end(v), [&](int &x)
  //               {
  //                 std::lock_guard<std::mutex> guard(m);
  //                 x = ++count; });

  for (auto e : v)
    std::cout << e << ',';
}
