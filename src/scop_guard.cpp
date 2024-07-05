// #include <boost/scop_exit.hpp>
#include <iostream>
#include <fstream>
#include <boost/config.hpp>

#include <functional>
#include <iostream>
 
using namespace std;
 
class ScopeGuard {
public:
	ScopeGuard(function<void()> op) : m_op(op) {}
	~ScopeGuard() {
		if (m_op) m_op();
	}
 
private:
	function<void()> m_op;
};
 
// int main()
// {
// 	ScopeGuard sg([]() {
// 		cout << "scope guard destroy" << endl;
// 	});
// 	cout << "exit main" << endl;
// }
void processFile(const std::string& filename) {
    std::ifstream file(filename);

    // 确保文件在作用域结束时关闭
    ScopeGuard defer_close( [&file](){

        file.close();
        std::cout << "close file" << std::endl;
        
        } );


    // boost::BOOST_SCOPE_EXIT(&file) {
    //     file.close();
    //     std::cout << "Closing file: " << filename << std::endl;
    // } BOOST_SCOPE_EXIT_END

    // 处理文件内容
    // ...
    std::cout << "get file " << std::endl;

    if (!file) {
        std::cerr << "Unable to open file!" << std::endl;
        // 错误处理
}
    std::string line;
    while (getline(file, line)) {
        std::cout << line << std::endl;
    }
    
    // 当离开这个作用域时，scopguard 会自动调用上面的代码
    // 这将关闭文件并打印消息
}

int main() {
    processFile("/root/klab/build/bins/1.txt");
    return 0;
}