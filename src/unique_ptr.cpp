#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <locale>
#include <memory>
#include <stdexcept>
 
// 用于下面运行时多态演示的辅助类
struct B
{
    virtual ~B() = default;
 
    virtual void bar() { std::cout << "B::bar\n"; }
};
 
struct D : B
{
    D() { std::cout << "D::D\n"; }
    ~D() { std::cout << "D::~D\n"; }
 
    void bar() override { std::cout << "D::bar\n"; }
};
 
// 消费 unique_ptr 的函数能以值或以右值引用接收它
std::unique_ptr<D> pass_through(std::unique_ptr<D> p)
{
    p->bar();
    return p;
}
 
// 用于下面自定义删除器演示的辅助函数
void close_file(std::FILE* fp)
{
    std::fclose(fp);
}
 
// 基于 unique_ptr 的链表演示
struct List
{
    struct Node
    {
        int data;
        std::unique_ptr<Node> next;
    };
 
    std::unique_ptr<Node> head;
 
    ~List()
    {
        // 循环按顺序销毁各列表节点，默认析构函数将会递归调用其 `next` 指针的析构函数，
        // 这在足够大的链表上可能造成栈溢出。
        while (head)
        {
            auto next = std::move(head->next);
            head = std::move(next);
        }
    }
 
    void push(int data)
    {
        head = std::unique_ptr<Node>(new Node{data, std::move(head)});
    }
};
 
int main()
{
    std::cout << "1) 独占所有权语义演示\n";
    {
        // 创建一个（独占）资源
        std::unique_ptr<D> p = std::make_unique<D>();
 
        // 转移所有权给 `pass_through`，而它再通过返回值将所有权转移回来
        // std::unique_ptr<D> q = pass_through(std::move(p));
        std::unique_ptr<D> q = std::move(p);
 
        // p 现在是已被移动的“空”状态，等于 nullptr
        assert(!p);
    }
 
    std::cout << "\n" "2) 运行时多态演示\n";
    {
        // 创建派生类资源并通过基类指向它
        std::unique_ptr<B> p = std::make_unique<D>();
 
        // 动态派发如期工作
        p->bar();
    }
 
    std::cout << "\n" "3) 自定义删除器演示\n";
    std::ofstream("demo.txt") << 'x'; // 准备要读取的文件
    {
        using unique_file_t = std::unique_ptr<std::FILE, decltype(&close_file)>;
        unique_file_t fp(std::fopen("demo.txt", "r"), &close_file);
        if (fp)
            std::cout << char(std::fgetc(fp.get())) << '\n';
    } // `close_file()` 于此调用（若 `fp` 为空）
 
    std::cout << "\n" "4) 自定义 lambda 表达式删除器和异常安全性演示\n";
    try
    {
        std::unique_ptr<D, void(*)(D*)> p(new D, [](D* ptr)
        {
            std::cout << "由自定义删除器销毁...\n";
            delete ptr;
        });
 
        throw std::runtime_error(""); // `p` 若为普通指针则此处将泄漏
    }
    catch (const std::exception&)
    {
        std::cout << "捕获到异常\n";
    }
 
    std::cout << "\n" "5) 数组形式的 unique_ptr 演示\n";
    {
        std::unique_ptr<D[]> p(new D[3]);
    } // `D::~D()` 被调用 3 次
 
    std::cout << "\n" "6) 链表演示\n";
    {
        List wall;
        const int enough{1'000'000};
        for (int beer = 0; beer != enough; ++beer)
            wall.push(beer);
 
        // std::cout.imbue(std::locale("en_US.UTF-8"));
        std::cout << "墙上有 " << enough << " 瓶啤酒...\n";
    } // 销毁所有啤酒
}