#include <iostream>
#include <memory>
 
struct MyObj
{
    MyObj() { std::cout << "构造 MyObj\n"; }
 
    ~MyObj() { std::cout << "析构 MyObj\n"; }
};
 
struct Container : std::enable_shared_from_this<Container> // 注: 公开继承
{
    std::shared_ptr<MyObj> memberObj;
 
    void CreateMember() { memberObj = std::make_shared<MyObj>(); }
 
    std::shared_ptr<MyObj> GetAsMyObj()
    {
        // 为成员使用使用别名 shared_ptr
        return std::shared_ptr<MyObj>(shared_from_this(), memberObj.get());
    }
};
 
#define COUT(str) std::cout << '\n' << str << '\n'
 
#define DEMO(...) std::cout << #__VA_ARGS__ << " = " << __VA_ARGS__ << '\n'
 
int main()
{
    COUT("创建共享容器");
    std::shared_ptr<Container> cont = std::make_shared<Container>();
    DEMO(cont.use_count());
    DEMO(cont->memberObj.use_count());
 
    COUT("创建成员");
    cont->CreateMember();
    DEMO(cont.use_count());
    DEMO(cont->memberObj.use_count());
 
    COUT("创建另一个共享容器");
    std::shared_ptr<Container> cont2 = cont;
    DEMO(cont.use_count());
    DEMO(cont->memberObj.use_count());
    DEMO(cont2.use_count());
    DEMO(cont2->memberObj.use_count());
 
    COUT("GetAsMyObj");
    std::shared_ptr<MyObj> myobj1 = cont->GetAsMyObj();
    DEMO(myobj1.use_count());
    DEMO(cont.use_count());
    DEMO(cont->memberObj.use_count());
    DEMO(cont2.use_count());
    DEMO(cont2->memberObj.use_count());
 
    COUT("复制别名对象");
    std::shared_ptr<MyObj> myobj2 = myobj1;
    DEMO(myobj1.use_count());
    DEMO(myobj2.use_count());
    DEMO(cont.use_count());
    DEMO(cont->memberObj.use_count());
    DEMO(cont2.use_count());
    DEMO(cont2->memberObj.use_count());
 
    COUT("重置 cont2");
    cont2.reset();
    DEMO(myobj1.use_count());
    DEMO(myobj2.use_count());
    DEMO(cont.use_count());
    DEMO(cont->memberObj.use_count());
 
    COUT("重置 myobj2");
    myobj2.reset();
    DEMO(myobj1.use_count());
    DEMO(cont.use_count());
    DEMO(cont->memberObj.use_count());
 
    COUT("重置 cont");
    cont.reset();
    DEMO(myobj1.use_count());
    DEMO(cont.use_count());
}