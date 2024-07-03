// #include <gperftools/profiler.h>
// #include <stdlib.h>
// #include<iostream>
// #include<iomanip>


// #include<vector>
// using namespace std;

// class Complex {
// private:
// 	vector<double> pis;
// 	void recordPI(double x);
// public:
// 	Complex();
// 	double calculatePI(int n);
// 	~Complex();
// };


// using namespace std;

// vector<long long> vll;



// Complex::Complex() {
// }

// void Complex::recordPI(double x) {
// 	pis.push_back(x);
// 	if (pis.size() > 10000) pis.clear();
// }

// double Complex::calculatePI(int n) {
// 	double x = 2, z = 2;
// 	int a = 1, b = 3;
// 	while (n--) {
// 		z = z*a / b;
// 		x += z;
// 		a++;
// 		b += 2;
// 		recordPI(x);
// 	}
// 	return x;
// }

// Complex::~Complex() {
// }

// void recordSum(long long s) {
// 	vll.push_back(s);
// 	if (vll.size() > 10000) vll.clear();
// }

// long long calculateSum(long long n) {
//   	ProfilerStart("1.out");

// 	long long s = 0;
// 	for (int i = 1; i <= n; ++i) {
// 		s += i;
// 		recordSum(s);
// 	}
//   	ProfilerStop();

// 	return s;
// }

// int main() {
//   	ProfilerStart("");
// 	long long n = 10000000;
// 	Complex c;
// 	double p = c.calculatePI(n);
// 	long long s = calculateSum(n);
// 	cout << "pi=" << fixed << setprecision(13) << p << endl;
// 	cout << "1+2+...+" << n << "=" << s << endl;
//   	ProfilerStop();
// 	return 0;
// }

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

#define PUTSIZE  10000
class LockFreeCircularQueue {
private:
    std::atomic<int> head;
    std::atomic<int> tail;
    std::vector<int> buffer;
    const int capacity;

public:
    LockFreeCircularQueue(int size) : capacity(size), head(0), tail(0) {
        buffer.resize(size);
    }

    bool enqueue(int value) {
        int currentTail = tail.load(std::memory_order_relaxed);
        int nextTail = (currentTail + 1) % capacity;

        if (nextTail == head.load(std::memory_order_acquire)) {
            return false; // 队列已满
        }

        buffer[currentTail] = value;
        tail.store(nextTail, std::memory_order_release);
        return true;
    }

    bool dequeue(int &value, bool (*predicate)(int)) {
        // 首先检查队列中的元素数量是否小于10
        int size = (tail.load(std::memory_order_acquire) - head.load(std::memory_order_acquire) + capacity) % capacity;
        if (size < 10) {
            return false; // 队列中的元素数量小于10，不执行出队操作
        }

        int currentHead = head.load(std::memory_order_relaxed);
        if (currentHead == tail.load(std::memory_order_acquire)) {
            return false; // 队列为空
        }

        value = buffer[currentHead];
        head.store((currentHead + 1) % capacity, std::memory_order_release);
        return true;
    }
};

// 条件判断函数，用于决定是否执行出队操作
bool shouldDequeue(int size) {
    return size >= 10;
}

void threadSafeDequeue(LockFreeCircularQueue &queue) {
    int value;


    for(int i =PUTSIZE  ; i < PUTSIZE/5 ; i++ ) {
        if (queue.dequeue(value, shouldDequeue)) {
            std::cout << "Dequeued: " << value << std::endl;
        } else {
            std::cout << "Dequeue condition not met or queue is empty!" << std::endl;
        }
    }

}




int test_free_queue() {
    const int queueSize = 15; // 队列大小设置为15，以允许队列中的元素数量小于10
    LockFreeCircularQueue queue(queueSize);

    // 启动多个线程进行入队和出队操作
    std::thread producers[1];
    std::thread consumers[5];


    for (int i = 0; i < 5; ++i) {
        producers[i] = std::thread([&queue, i]() {

            for(int i =PUTSIZE  ; i < PUTSIZE ; i++ ) {
                bool success = queue.enqueue(i * 2);
                if (!success) {
                    std::cout << "Failed to enqueue value " << i * 2 << std::endl;
                }
            }
        });
    }

    for (int i = 0; i < 5; ++i) {
        consumers[i] = std::thread([&queue]() {
            {
                threadSafeDequeue(queue);
            }
        });
    }

    // 等待所有线程完成
    for (int i = 0; i < 5; ++i) {
        producers[i].join();
        consumers[i].join();
    }

    return 0;
}







#include <iostream>
#include <memory>

class Resource {
public:
    Resource() { std::cout << "Resource created.\n"; }
    ~Resource() { std::cout << "Resource destroyed.\n"; }
};


void copy_use(std::shared_ptr<Resource> ptr1){
      std::cout << "copy_use use: " << ptr1.use_count() << std::endl;
}


void yinyong_use(std::shared_ptr<Resource> &ptr1){
      std::cout << "yinyong_use use: " << ptr1.use_count() << std::endl;
}


int test_ptr() {
    {
        std::shared_ptr<Resource> ptr1(new Resource); // 引用计数设置为 1
        std::cout << "Use count: " << ptr1.use_count() << std::endl;

        {
            std::shared_ptr<Resource> ptr2 = ptr1; // 复制构造，引用计数递增为 2
            std::cout << "Use count after copy: " << ptr1.use_count() << std::endl;
        } // ptr2 作用域结束，引用计数减 1


        copy_use(ptr1);
         std::cout << "after copy_use destroyed: " << ptr1.use_count() << std::endl;
        yinyong_use(ptr1);
        std::cout << " after yinyong_use destroyed: " << ptr1.use_count() << std::endl;
    } // ptr1 作用域结束，引用计数减至 0，资源被删除

    return 0;
}









//  gprof ./demo1 gmon.out > profile.txt > gprof ./demo1 -l gmon.out > profile_line.txt