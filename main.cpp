#include <iostream>
#include <boost/filesystem.hpp>

int main() {
    boost::filesystem::path p = "/path/to/some/file/or/directory";
    std::cout << "Path: " << p << std::endl;
    return 0;
}