#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <queue>
#include <memory>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/chrono.hpp>
#include <iostream>


// int xigoucishu = 0;
std::atomic<int > xigoucishu{0};


//////////////////////////ASIO/////////////////////////
boost::asio::thread_pool  *mypool;
boost::asio::thread_pool  *signal_thread;
boost::asio::thread_pool  *strand_thread;

//////////////////////////DATA///////////////////////////
int i = 0;
void strand_task() ;
class MyData{
public:
      ~MyData() { std::cout << " MyData xi gou" <<std::endl;  xigoucishu++;}
    int i;
};
//////////////////////////DATA///////////////////////////


class TaskRunner {
public:

     ~TaskRunner() { 
        //std::cout << "TaskRunner xi gou" <<std::endl;
     }
    void my_task(MyData &mydata) {
    mydata.i++;
        i++;
        // std::cout << "Task is running in thread " << boost::this_thread::get_id() << '\n';
    }


    void my_task_ptr(const std::shared_ptr<MyData> mydata) {
        mydata->i++;
        // boost::this_thread::sleep_for(boost::chrono::seconds(1)); 
        // std::cout <<  __LINE__ << "|" << boost::this_thread::get_id() << "|" << mydata.use_count() << "|" << i << '\n';
        std::cout << __FUNCTION__ << "yinyong_use use: " << mydata.use_count() << std::endl;

        // boost::asio::post(*mypool,boost::bind(&TaskRunner::my_task_ptr2, this,  mydata));
        // boost::asio::post(*mypool,boost::bind(&TaskRunner::my_task_ptr3, this,  mydata));
    }

    // 异步任务
    void my_task_ptr2(const std::shared_ptr<MyData> mydata) {
        mydata->i++;
        std::cout << __FUNCTION__ << "yinyong_use use: " << mydata.use_count() << std::endl;
        // std::cout <<  __LINE__<< "|"  << boost::this_thread::get_id() << "|" << mydata.use_count() << "|" << i << '\n';
    }

        // 异步任务
    void my_task_ptr3(const std::shared_ptr<MyData> mydata) {
        mydata->i++;
        std::cout << __FUNCTION__ << "yinyong_use use: " << mydata.use_count() << std::endl;

        // boost::this_thread::sleep_for(boost::chrono::seconds(1));
        // std::cout <<  __LINE__<< "|"  << boost::this_thread::get_id() << "|" << mydata.use_count() << "|" << i << '\n';
    }

    
    void strand_task(const std::shared_ptr<MyData> mydata){
        // boost::asio::post(*mypool,boost::bind(&TaskRunner::my_task_ptr, this,  mydata));
        boost::asio::post(*mypool,boost::bind(&TaskRunner::my_task_ptr, this,  mydata));
        std::cout << __FUNCTION__ << "yinyong_use use: " << mydata.use_count() << std::endl;

        // std::cout <<  __LINE__ << "|" << boost::this_thread::get_id() << "|" << mydata_ptr.use_count() << "|" << i << '\n';
        // boost::asio::post(*mypool,boost::bind(&TaskRunner::my_task_ptr2, this,  mydata_ptr));
       // std::cout <<  __LINE__<< "|"  << boost::this_thread::get_id() << "|" << mydata_ptr.use_count() << "|" << i << '\n';
    }

};

////////////////////////////////////asio-strand///////////////////////////////////////////
TaskRunner runner;
// MyData mydata;
boost::asio::io_service io_s;
boost::thread_group threads;
boost::asio::io_service::work work_(io_s);
boost::asio::io_service::strand strand_(io_s);
void init_ios() {
    for (int i = 0; i < 4; ++i) {
        threads.create_thread( boost::bind(&boost::asio::io_service::run, &io_s));
    }
    // boost::this_thread::sleep_for(boost::chrono::seconds(1));
    std::cout << "Task is running in thread " << i <<std::endl;
    // 等待所有任务完成
    threads.join_all();
}


// // 提交智能指针任务到线程池
// void processmd(std::shared_ptr<MyData > mydata_ptr){
//     boost::asio::post(*mypool,boost::bind(&TaskRunner::my_task_ptr, &runner,  mydata_ptr));
//        // std::cout <<  __LINE__<< "|"  << boost::this_thread::get_id() << "|" << mydata_ptr.use_count() << "|" << i << '\n';
// }


// void thread_pool_task() {
//     auto mydata_ptr = std::make_shared<MyData>();
//     // 线性执行
//     boost::asio::post(*signal_thread,boost::bind(&TaskRunner::my_task_ptr, &runner,  mydata_ptr));
//    // std::cout <<  __LINE__<< "|"  << boost::this_thread::get_id() << "|" << mydata_ptr.use_count() << "|" << i << '\n';

// }


// mock
void strand_task(){
    auto mydata_ptr = std::make_shared<MyData>();
   // std::cout <<  __LINE__<< "|"  << boost::this_thread::get_id() << "|" << mydata_ptr.use_count() << "|" << i << '\n';
    boost::asio::post(*signal_thread,boost::bind(&TaskRunner::my_task_ptr, &runner,  mydata_ptr));
}

////////////////////////////////////asio-strand///////////////////////////////////////////




int main() {
    mypool = new boost::asio::thread_pool(4);
    signal_thread = new boost::asio::thread_pool(4);
    strand_thread = new boost::asio::thread_pool(1);

    for(int i=0 ; i< 1 ;i++){
        strand_task();
    }
    // boost::asio::post(*mypool, boost::bind(&TaskRunner::strand_task, &runner,  mydata_ptr));
    boost::this_thread::sleep_for(boost::chrono::seconds(10));
    std::cout << "=======>" << std::endl;
    
    std::cout << "xigou cnt :" << xigoucishu << std::endl;
    while(1){};
    return 0;
}