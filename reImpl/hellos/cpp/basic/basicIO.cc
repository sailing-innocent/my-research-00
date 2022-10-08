#include <iostream>

int main() {
    std::cout << "Please Input Two Numbers: ";
    int v1, v2;
    std::cin >> v1 >> v2;
    std::clog << "get numbers: " << v1 << "," << v2 << std::endl;
    std::cout << v1 << " + " << v2 << " = " << v1+v2 << std::endl;
    std::cerr << "NO ERROR(s) is the biggest ERROR" << std::endl;
    return 0;
}