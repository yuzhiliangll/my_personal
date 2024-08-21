perror 函数
用途: perror 用于输出错误信息，通常与系统调用或库函数发生错误时一起使用。
它会打印用户指定的错误消息（例如 "Failed to create a new node"），
然后在后面附加一个与当前全局变量 errno 对应的系统错误消息。

头文件: 要使用 perror，需要包含 <stdio.h> 和 <errno.h> 头文件。

```C++
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *file = fopen("nonexistentfile.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // 其他代码...

    fclose(file);
    return 0;
}
fopen: 尝试以读取模式打开名为 nonexistentfile.txt 的文件。由于文件不存在，fopen 返回 NULL。

if (file == NULL): 检查 fopen 是否成功。如果文件未成功打开，则 file 为 NULL。

perror("Error opening file"): 当文件打开失败时，perror 输出用户指定的错误消息 "Error opening file"，并附带一个描述当前 errno 值的系统错误消息。这个错误消息可能是：

Error opening file: No such file or directory




exit 函数
用途: exit 用于终止程序执行，并返回一个状态码给操作系统。EXIT_FAILURE 是一个标准的宏，表示程序以失败状态终止（通常值为 1），而 EXIT_SUCCESS 表示成功终止（通常值为 0）。

行为: exit 会终止程序，执行一些清理工作（如调用已注册的 atexit 函数和刷新缓冲区），然后返回指定的状态码。

头文件: exit 函数定义在 <stdlib.h> 头文件中。


valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./文件

