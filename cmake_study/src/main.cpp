/*
 * @Author: chamip
 * @Date: 2023-01-06 15:14:50
 * @LastEditTime: 2023-01-12 23:32:36
 * @LastEditors: chamip
 * @FilePath: /cmake_practice/cmake_study/src/main.cpp
 */
#include <iostream>
#include "../ext/mySqrt.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    double ori;
    std::cout << "Please input a digit: ";
    std::cin >> ori;
    std::cout << ori << "'s sqrt is: " << mySqrt123(ori) << std::endl;
    std::cout << "Goodbye!" << std::endl;
    return 0;
}