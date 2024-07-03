#include <boost/lockfree/queue.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <vector>

// 定义 Boost 无锁队列的最大容量
const size_t QueueCapacity = 10;

// 创建一个无锁队列，用于在生产者和消费者之间传递整数
boost::lockfree::queue<int, boost::lockfree::capacity<QueueCapacity>> lfqueue;

// 生产者函数
void producer(int id, boost::lockfree::queue<int, boost::lockfree::capacity<QueueCapacity>> &q) {
    for (int i = 0; i < 20; ++i) {
        // 尝试将元素推入队列
        if (q.push(id * 100 + i)) {
            std::cout << "Producer " << id << " produced " << (id * 100 + i) << std::endl;
        } else {
            std::cout << "Producer " << id << " failed to produce " << (id * 100 + i) << std::endl;
        }
    }
}

// 消费者函数
void consumer(int id, boost::lockfree::queue<int, boost::lockfree::capacity<QueueCapacity>> &q) {
    while (true) {
        int value = 0;
        // 尝试从队列中弹出元素
        if (q.pop(value)) {
            std::cout << "Consumer " << id << " consumed " << value << std::endl;
        } else {
            // 这里我们简单地休眠，以避免繁忙等待
            boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
        }
    }
}

int main() {
    // 创建两个生产者线程和两个消费者线程
    boost::thread producer1(producer, 1, std::ref(lfqueue));
    boost::thread producer2(producer, 2, std::ref(lfqueue));
    boost::thread consumer1(consumer, 1, std::ref(lfqueue));
    boost::thread consumer2(consumer, 2, std::ref(lfqueue));

    // 等待生产者线程结束
    producer1.join();
    producer2.join();

    // 这里我们使用一个简单的方法来终止消费者线程
    // 实际上，你需要实现更优雅的关闭机制
    consumer1.interrupt();
    consumer2.interrupt();

    // 等待消费者线程结束
    consumer1.join();
    consumer2.join();

    return 0;
}