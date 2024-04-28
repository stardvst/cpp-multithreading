#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <string>

using namespace std::literals;

std::mutex mutex;
std::condition_variable cv;
std::string text{"Empty"};
bool done{false};

void reader()
{
  // acquire lock
  std::unique_lock lk{mutex};

  // unlocks the mutex, and
  // waits for cv to be notified
  cv.wait(lk, []
          { return done; });

  // mutex is locked again
  // wake up and use the new value
  std::cout << "Data is " << text << '\n';
}

void writer()
{
  std::cout << "Writing data...\n";

  {
    // lock the mutex
    std::lock_guard lg{mutex};

    // pretend to be busy
    std::this_thread::sleep_for(2s);

    // modify the data
    text = "Populated";
    done = true;
  }

  // mutex is now unlocked
  // notify the cv
  cv.notify_one();
}

int main()
{
  std::cout << "Data is " << text << '\n';

  // a problem with the code: lost wakeup
  std::thread write{writer};
  std::this_thread::sleep_for(500ms);
  std::thread read{reader};

  read.join();
  write.join();
}
