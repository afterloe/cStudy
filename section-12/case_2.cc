#include <iostream>

const float PI = 3.1415;

int main()
{
    float r;
    std::cout << "input r " << std::endl;
    std::cin >> r;

    std::cout << "area is " << PI * r * r;

    return 0;
}