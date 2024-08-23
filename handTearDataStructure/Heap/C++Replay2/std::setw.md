#include <iomanip> 是一个C++头文件，提供了用于操纵数据流输入输出的功能。
std::setw 函数用于设置下一个输出字段的宽度。
这通常用于格式化输出，以对齐文本或数字，使其在指定的宽度内显示。

```C++
#include <iostream>
#include <iomanip>  // 引入 <iomanip> 头文件以使用 std::setw

int main() {
    int num1 = 42;
    int num2 = 1234;
    int num3 = 7;

    // 输出数字，设置最小宽度为5
    std::cout << std::setw(5) << num1 << std::endl;
    std::cout << std::setw(5) << num2 << std::endl;
    std::cout << std::setw(5) << num3 << std::endl;

    return 0;
}
输出：
   42
 1234
    7
在这个例子中，std::setw(5) 确保每个数字都在至少5个字符宽的字段中打印。
如果数字的位数少于5，则在左侧填充空格。
