// 类型转换
#include "stdafx.h"
#include <iostream>

int main () {
    const unsigned int feet_per_yard { 3 };
    const unsigned inches_per_foot { 12 };

    double length{};
    unsigned int yards{};
    unsigned int feet{};
    unsigned int inches{};

    std::cout << "enter a length in yards as decimal: ";
    std::cin >> length;

    yards = static_cast<unsigned int>(length);
    feet = static_cast<unsigned int>((length - yards) * feet_per_yard);   // 把表达式的值转换为给定类型
    
    // 另外一种写法
    inches = static_cast<unsigned int>                                    
        (length * feet_per_yard * inches_per_foot) % inches_per_foot;

    inches = static_cast<unsigned int>
        (((length - yards) * feet_per_yard - feet) * inches_per_foot);  // 一定注意最外面的括号，如果不括号，结果就不对，被类型
                                                                        // 强制转换 
    std::cout << length << " yards converts to"
        << yards << " yards  "
        << feet << " feet "
        << inches << " inches." << std::endl;

    return 0;
}
