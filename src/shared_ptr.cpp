#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
 
using namespace std::chrono_literals;
 
struct Base
{
    Base() { std::cout << "Base::Base()\n"; }
 
    // 注意：此处非虚析构函数 OK
    ~Base() { std::cout << "Base::~Base()\n"; }
};
 
struct Derived : public Base
{
    Derived() { std::cout << "Derived::Derived()\n"; }
 
    ~Derived() { std::cout << "Derived::~Derived()\n"; }
};
 
void print(auto rem, std::shared_ptr<Base> const& sp)
{
    std::cout << rem << "\n\tget() = " << sp.get()
              << ", use_count() = " << sp.use_count() << '\n';
}
 
void thr(std::shared_ptr<Base> p)
{
    std::this_thread::sleep_for(987ms);
    std::shared_ptr<Base> lp = p; // 线程安全，虽然自增共享的 use_count
    {
        static std::mutex io_mutex;
        std::lock_guard<std::mutex> lk(io_mutex);
        print("线程中的局部指针:", lp);
    }
}
 
int main()
{
    std::shared_ptr<Base> p = std::make_shared<Derived>();
 
    print("创建共享的 Derived (为 Base 指针)", p);
 
    std::thread t1{thr, p}, t2{thr, p}, t3{thr, p};
    p.reset(); // 从 main 释放所有权
 
    print("在 3 个线程间共享所有权并从 main 释放所有权:", p);
 
    t1.join();
    t2.join();
    t3.join();
 
    std::cout << "线程全部已完成，最后一个删除了 Derived。\n";
}