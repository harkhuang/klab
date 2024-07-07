#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

void do_something(int &i) { ++i; }

struct func {
  int &i;
  // 函数方法构建  初始化的时候构建成员变量用于子程序构建
  func(int &i_) : i(i_) {}

  void operator()() {
    for (unsigned j = 0; j < 1000000; ++j) {
      do_something(i);
    }
    cout << i << endl;
  }
};

void do_something_in_current_thread() {
  std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}

void f() {
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread t(my_func);
  try {
    do_something_in_current_thread();
  } catch (...) {
    t.join();
    throw;
  }
  t.join();
}

int main() { f(); }
