
execl 和 execlp 是在 Linux/Unix 系统中用于执行新的程序的系统调用。它们属于 exec 家族的函数，exec 系列函数用于替换当前进程的镜像为一个新程序的镜像。具体来说，execl 和 execlp 函数分别有以下作用：
```C
1. execl 函数
原型：int execl(const char *path, const char *arg, ... /* (char *) NULL */);

作用：execl 用于执行指定路径下的程序。该函数的第一个参数是可执行文件的路径，后续的参数是传递给该程序的命令行参数列表，参数列表最后必须以 NULL 结束。

使用示例：


#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Before exec\n");

    // 使用 execl 执行 /bin/ls 程序，显示当前目录的文件列表
    execl("/bin/ls", "ls", "-l", (char *)NULL);

    // execl 如果成功，将不会返回，下面的代码将不会执行
    printf("After exec\n");

    return 0;
}
解释：

/bin/ls：表示程序的绝对路径。
"ls"：这是命令行中的第一个参数，通常是程序名。
"-l"：这是命令行参数，传递给 ls 程序。
(char *)NULL：表示参数列表的结束，必须有。
在这个示例中，execl 函数成功执行后，当前进程的镜像被 ls 程序替换，因此 "After exec" 将不会被打印。

2. execlp 函数
原型：int execlp(const char *file, const char *arg, ... /* (char *) NULL */);

作用：execlp 与 execl 类似，但它会根据 PATH 环境变量搜索可执行文件，而不需要提供完整路径。

使用示例：


#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Before exec\n");

    // 使用 execlp 执行 ls 程序，显示当前目录的文件列表
    execlp("ls", "ls", "-l", (char *)NULL);

    // execlp 如果成功，将不会返回，下面的代码将不会执行
    printf("After exec\n");

    return 0;
}
解释：

"ls"：作为可执行文件名传递给 execlp，不需要提供绝对路径。
execlp：会根据 PATH 环境变量搜索 ls 程序，因此你只需提供程序名即可。
在这个示例中，execlp 也是替换当前进程镜像为 ls 程序，如果成功，"After exec" 将不会被打印。

注意事项：
执行成功与否：如果 execl 或 execlp 成功执行，它们不会返回，程序的控制权将交给新的程序。如果执行失败，函数将返回 -1，并设置 errno 以指示错误类型。
PATH 环境变量：使用 execlp 时，程序必须在 PATH 环境变量指示的路径之一中，否则执行会失败。
这些函数通常用于在进程间执行新的程序，比如在 Shell 脚本或系统级编程中切换进程执行的程序。



