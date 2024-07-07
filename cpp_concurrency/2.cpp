#include <thread>
#include <iostream>
#include <chrono>
using namespace std;

void do_something(int& i) {
    ++i;
}

struct func {
    int& i;

    func(int& i_) : i(i_) {}


    // 在类中使用防函数 对（）方法重构

    void operator()() {
        for (unsigned j = 0; j < 1000000; ++j) {
            do_something(i);
        }
        // 尽管执行有很大耗时  但是交给系统管理后没有开销
        std::this_thread::sleep_for(std::chrono::milliseconds(100000000));
        cout << i <<endl;
    }
};

void oops() {

    int some_local_state = 0;
    // 类构建
    func my_func(some_local_state);
    // 异步调用函数 使类具备足够的生命周期
    std::thread my_thread(my_func);
    // 分离后 该线程退出只负责发送信号  回收资源交给init 1管理
    my_thread.detach();
}

int main() {
    oops();
}
