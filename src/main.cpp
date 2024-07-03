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

//////////////////////////DATA///////////////////////////
int i = 0;
class MyData{
public:
      ~MyData() { std::cout << " MyData xi gou" <<std::endl;}
    int i;
};


class TaskRunner {
public:

     ~TaskRunner() { std::cout << "in taskrunner xi gou" <<std::endl;}
    void my_task(MyData &mydata) {
    mydata.i++;
        i++;
        // std::cout << "Task is running in thread " << boost::this_thread::get_id() << '\n';
    }

    void my_task_ptr(std::shared_ptr<MyData> mydata) {
        mydata->i++;
        i++;
        // boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
        std::cout << "Task is running in thread |" << boost::this_thread::get_id() << mydata.use_count() << "|" << i << '\n';
        // std::cout << "Task is running in thread " << boost::this_thread::get_id() << '\n';
    }
};

////////////////////////////////////thread-pool//////////////////////////////////////////
boost::asio::thread_pool  *mypool;
void processmd(){
    TaskRunner runner;
   auto mydata_ptr = std::make_shared<MyData>();
    // strand_.post(boost::bind(&TaskRunner::my_task_ptr, &runner,  mydata_ptr));
   boost::asio::post(*mypool,boost::bind(&TaskRunner::my_task_ptr, &runner,  mydata_ptr));
    boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
   boost::asio::post(*mypool,boost::bind(&TaskRunner::my_task_ptr, &runner,  mydata_ptr));
    boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
   boost::asio::post(*mypool,boost::bind(&TaskRunner::my_task_ptr, &runner,  mydata_ptr));
    boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
   boost::asio::post(*mypool,boost::bind(&TaskRunner::my_task_ptr, &runner,  mydata_ptr));
    boost::this_thread::sleep_for(boost::chrono::milliseconds(100));

}
////////////////////////////////////thread-pool//////////////////////////////////////////

int main() {
    mypool = new boost::asio::thread_pool(4);
    // test_boost_strand();
    processmd();


    while(1){};
    return 0;
}