gdb 是由 GNU 软件系统社区提供的调试器，同 gcc 配套组成了一套完整的开发环境，可移植性很好，支持非常多的体系结构并被移植到各种系统中（包括各种类 Unix 系统与 Windows 系统里的 MinGW 和 Cygwin ）。此外，除了 C 语言之外，gcc/gdb 还支持包括 C++、Objective-C、Ada 和 Pascal 等各种语言后端的编译和调试。 gcc/gdb 是 Linux 和许多类 Unix 系统中的标准开发环境，Linux 内核也是专门针对 gcc 进行编码的。

GDB 是一套字符界面的程序集，可以使用命令 gdb 加载要调试的程序。 
下面为大家介绍一些常用的GDB调试命令。

1. 调试准备
项目程序如果是为了进行调试而编译时， 必须要打开调试选项(-g)。另外还有一些可选项，比如: 在尽量不影响程序行为的情况下关掉编译器的优化选项(-O0)，-Wall选项打开所有 warning，也可以发现许多问题，避免一些不必要的 bug。

-g选项的作用是在可执行文件中加入源代码的信息，比如可执行文件中第几条机器指令对应源代码的第几行，但并不是把整个源文件嵌入到可执行文件中，所以在调试时必须保证gdb能找到源文件。

习惯上如果是c程序就使用gcc编译, 如果是 c++程序就使用g++编译, 编译命令中添加上边提到的参数即可。

假设有一个文件 args.c, 要对其进行gdb调试，
编译的时候必须要添加参数 -g，加入了源代码信息的可执行文件比不加之前要大一些。

# -g 将调试信息写入到可执行程序中
$ gcc -g args.c -o app

# 编译不添加 -g 参数
$ gcc args.c -o app1  

# 查看生成的两个可执行程序的大小
$ ll

-rwxrwxr-x  1 robin robin 9816 Apr 19 09:25 app*	# 可以用于gdb调试
-rwxrwxr-x  1 robin robin 8608 Apr 19 09:25 app1*	# 不能用于gdb调试

2. 启动和退出gdb
2.1 启动gdb
gdb是一个用于应用程序调试的进程, 需要先将其打开, 一定要注意 gdb进程启动之后, 需要的被调试的应用程序是没有执行的。打开Linux终端，切换到要调试的可执行程序所在路径，执行如下命令就可以启动 gdb了。

SHELL
# 在终端中执行如下命令
# gdb程序启动了, 但是可执行程序并没有执行
$ gdb 可执行程序的名字

# 使用举例：
$ gdb app
(gdb) 		# gdb等待输入调试的相关命令
2.2 命令行传参
有些程序在启动的时候需要传递命令行参数，如果要调试这类程序，这些命令行参数必须要在应用程序启动之前通过调试程序的gdb进程传递进去。下面是一段带命令行参数的程序：

// args.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NUM 10

// argc, argv 是命令行参数
// 启动应用程序的时候
int main(int argc, char* argv[])
{
    printf("参数个数: %d\n", argc);
    for(int i=0; i<argc; ++i)
    {
        printf("%d\n", NUM);
        printf("参数 %d: %s\n", i, argv[i]);
    }
    return 0;
}

第一步: 编译出带条信息的可执行程序

SHELL
1
$ gcc args.c -o app -g
第二步: 启动gdb进程, 指定需要gdb调试的应用程序名称

SHELL
1
2
$ gdb app
(gdb) 
第三步: 在启动应用程序 app之前设置命令行参数。gdb中设置参数的命令叫做set args ...，查看设置的命令行参数命令是 show args。 语法格式如下：

SHELL
1
2
3
4
# 设置的时机: 启动gdb之后, 在应用程序启动之前
(gdb) set args 参数1 参数2 .... ...
# 查看设置的命令行参数
(gdb) show args
使用举例：

SHELL
# 非gdb调试命令行传参
# argc 参数总个数，argv[0] == ./app， argv[1] == "11"  argv[2] == "22"  ...  argv[5] == "55"
$ ./app 11 22 33 44 55		# 这是数据传递给main函数
 
# 使用 gdb 调试
$ gdb app
GNU gdb (Ubuntu 7.11.1-0ubuntu1~16.5) 7.11.1
Copyright (C) 2016 Free Software Foundation, Inc.
# 通过gdb给应用程序设置命令行参数
(gdb) set args 11 22 33 44 55
# 查看设置的命令行参数
(gdb) show args
Argument list to give program being debugged when it is started is "11 22 33 44 55".
2.3 gdb中启动程序
在gdb中启动要调试的应用程序有两种方式, 一种是使用run命令, 另一种是使用start命令启动。在整个 gdb 调试过程中, 启动应用程序的命令只能使用一次。

run: 可以缩写为 r, 如果程序中设置了断点会停在第一个断点的位置, 如果没有设置断点, 程序就执行完了
start: 启动程序, 最终会阻塞在main函数的第一行，等待输入后续其它 gdb 指令
SHELL

# 两种方式
# 方式1: run == r 
(gdb) run  

# 方式2: start
(gdb) start
如果想让程序start之后继续运行, 或者在断点处继续运行，可以使用 continue命令, 可以简写为 c

SHELL
1
2
# continue == c
(gdb) continue
2.4 退出gdb
退出gdb调试, 就是终止 gdb 进程, 需要使用 quit命令, 可以缩写为 q

SHELL
1
2
# quit == q
(gdb) quit
3. 查看代码
因为gdb调试没有IDE那样的完善的可视化窗口界面，给调试的程序打断点又是调试之前必须做的一项工作。因此gdb提供了查看代码的命令，这样就可以轻松定位要调试的代码行的位置了。

查看代码的命令叫做list可以缩写为 l, 通过这个命令我们可以查看项目中任意一个文件中的内容，并且还可以通过文件行号，函数名等方式查看。

3.1 当前文件
一个项目中一般是有很多源文件的, 默认情况下通过list查看到代码信息位于程序入口函数main对应的的那个文件中。因此如果不进行文件切换main函数所在的文件就是当前文件, 如果进行了文件切换, 切换到哪个文件哪个文件就是当前文件。查看文件内容的方式如下：

SHELL
# 使用 list 和使用 l 都可以
# 从第一行开始显示
(gdb) list 

# 列值这行号对应的上下文代码, 默认情况下只显示10行内容
(gdb) list 行号

# 显示这个函数的上下文内容, 默认显示10行
(gdb) list 函数名
通过list去查看文件代码, 默认只显示10行, 如果还想继续查看后边的内容, 可以继续执行list命令, 也可以直接回车（再次执行上一次执行的那个gdb命令）。

3.2 切换文件
在查看文件内容的时候，很多情况下需要进行文件切换，我们只需要在list命令后边将要查看的文件名指定出来就可以了，切换命令执行完毕之后，这个文件就变成了当前文件。文件切换方式如下：

SHELL
1
2
3
4
5
# 切换到指定的文件，并列出这行号对应的上下文代码, 默认情况下只显示10行内容
(gdb) l 文件名:行号

# 切换到指定的文件，并显示这个函数的上下文内容, 默认显示10行
(gdb) l 文件名:函数名
3.3 设置显示的行数
默认通过list只能一次查看10行代码, 如果想显示更多, 可以通过set listsize设置, 同样如果想查看当前显示的行数可以通过 show listsize查看, 这里的listsize可以简写为 list。具体语法格式如下:

SHELL
1
2
3
4
5
# 以下两个命令中的 listsize 都可以写成 list
(gdb) set listsize 行数

# 查看当前list一次显示的行数
(gdb) show listsize
4. 断点操作
想要通过gdb调试某一行或者得到某个变量在运行状态下的实际值，就需要在在这一行设置断点，程序指定到断点的位置就会阻塞，我们就可以通过gdb的调试命令得到我们想要的信息了。

设置断点的命令叫做break可以缩写为b。

4.1 设置断点
断点的设置有两种方式一种是常规断点，程序只要运行到这个位置就会被阻塞，还有一种叫条件断点，只有指定的条件被满足了程序才会在断点处阻塞。

调试程序的断点可以设置到某个具体的行, 也可以设置到某个函数上，具体的设置方式如下：

设置普通断点到当前文件

SHELL
1
2
3
4
# 在当前文件的某一行上设置断点
# break == b
(gdb) b 行号
(gdb) b 函数名		# 停止在函数的第一行
设置普通断点到某个非当前文件上

SHELL
1
2
3
# 在非当前文件的某一行上设置断点
(gdb) b 文件名:行号
(gdb) b 文件名:函数名		# 停止在函数的第一行
设置条件断点

SHELL
1
2
3
# 必须要满足某个条件, 程序才会停在这个断点的位置上
# 通常情况下, 在循环中条件断点用的比较多
(gdb) b 行数 if 变量名==某个值
4.2 查看断点
断点设置完毕之后, 可以通过 info break命令查看设置的断点信息，其中info可以缩写为i

SHELL
# info == i
# 查看设置的断点信息
(gdb) i b   #info break

# 举例
(gdb) i b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x0000000000400cb5 in main() at test.cpp:12
2       breakpoint     keep y   0x0000000000400cbd in main() at test.cpp:13
3       breakpoint     keep y   0x0000000000400cec in main() at test.cpp:18
4       breakpoint     keep y   0x00000000004009a5 in insertionSort(int*, int) 
                                                   at insert.cpp:8
5       breakpoint     keep y   0x0000000000400cdd in main() at test.cpp:16
6       breakpoint     keep y   0x00000000004009e5 in insertionSort(int*, int) 
                                                   at insert.cpp:16
在显示的断点信息中有一些属性需要在其他操作中被使用, 下面介绍一下:

Num: 断点的编号, 删除断点或者设置断点状态的时候都需要使用
Enb: 当前断点的状态, y表示断点可用, n表示断点不可用
What: 描述断点被设置在了哪个文件的哪一行或者哪个函数上
4.3 删除断点
如果确定设置的某个断点不再被使用了, 可用将其删除, 删除命令是 delete 断点编号, 这个delete可以简写为del也可以再简写为d。

删除断点的方式有两种: 删除(一个或者多个)指定断点或者删除一个连续的断点区间，具体操作如下：

SHELL

# delete == del == d
# 需要 info b 查看断点的信息, 第一列就是编号
(gdb) d 断点的编号1 [断点编号2 ...]
# 举例: 
(gdb) d 1          # 删除第1个断点
(gdb) d 2 4 6      # 删除第2,4,6个断点

# 删除一个范围, 断点编号 num1 - numN 是一个连续区间
(gdb) d num1-numN
# 举例, 删除第1到第5个断点
(gdb) d 1-5
4.4 设置断点状态
如果某个断点只是临时不需要了，我们可以将其设置为不可用状态, 设置命令为disable 断点编号，当需要的时候再将其设置回可用状态，设置命令为 enable 断点编号。

设置断点无效

SHELL

# 让断点失效之后, gdb调试过程中程序是不会停在这个位置的
# disable == dis
# 设置某一个或者某几个断点无效
(gdb) dis 断点1的编号 [断点2的编号 ...]

# 设置某个区间断点无效
(gdb) dis 断点1编号-断点n编号
演示设置断点为无效状态:

SHELL
# 查看断点信息
(gdb) i b
Num     Type           Disp Enb Address            What
2       breakpoint     keep y   0x0000000000400cce in main() at test.cpp:14
4       breakpoint     keep y   0x0000000000400cdd in main() at test.cpp:16
5       breakpoint     keep y   0x0000000000400d46 in main() at test.cpp:23
6       breakpoint     keep y   0x0000000000400d4e in main() at test.cpp:25
7       breakpoint     keep y   0x0000000000400d6e in main() at test.cpp:28
8       breakpoint     keep y   0x0000000000400d7d in main() at test.cpp:30

# 设置第2, 第4 个断点无效
(gdb) dis 2 4

# 查看断点信息
(gdb) i b
Num     Type           Disp Enb Address            What
2       breakpoint     keep n   0x0000000000400cce in main() at test.cpp:14
4       breakpoint     keep n   0x0000000000400cdd in main() at test.cpp:16
5       breakpoint     keep y   0x0000000000400d46 in main() at test.cpp:23
6       breakpoint     keep y   0x0000000000400d4e in main() at test.cpp:25
7       breakpoint     keep y   0x0000000000400d6e in main() at test.cpp:28
8       breakpoint     keep y   0x0000000000400d7d in main() at test.cpp:30

# 设置 第5,6,7,8个 断点无效
(gdb) dis 5-8

# 查看断点信息
(gdb) i b
Num     Type           Disp Enb Address            What
2       breakpoint     keep n   0x0000000000400cce in main() at test.cpp:14
4       breakpoint     keep n   0x0000000000400cdd in main() at test.cpp:16
5       breakpoint     keep n   0x0000000000400d46 in main() at test.cpp:23
6       breakpoint     keep n   0x0000000000400d4e in main() at test.cpp:25
7       breakpoint     keep n   0x0000000000400d6e in main() at test.cpp:28
8       breakpoint     keep n   0x0000000000400d7d in main() at test.cpp:30
让无效的断点生效

SHELL

# enable == ena
# 设置某一个或者某几个断点有效
(gdb) ena 断点1的编号 [断点2的编号 ...]

# 设置某个区间断点有效
(gdb) ena 断点1编号-断点n编号
演示设置断点为有效状态:

SHELL
# 查看断点信息
(gdb) i b
Num     Type           Disp Enb Address            What
2       breakpoint     keep n   0x0000000000400cce in main() at test.cpp:14
4       breakpoint     keep n   0x0000000000400cdd in main() at test.cpp:16
5       breakpoint     keep n   0x0000000000400d46 in main() at test.cpp:23
6       breakpoint     keep n   0x0000000000400d4e in main() at test.cpp:25
7       breakpoint     keep n   0x0000000000400d6e in main() at test.cpp:28
8       breakpoint     keep n   0x0000000000400d7d in main() at test.cpp:30

# 设置第2, 第4个断点有效
(gdb) ena 2 4

# 查看断点信息
(gdb) i b
Num     Type           Disp Enb Address            What
2       breakpoint     keep y   0x0000000000400cce in main() at test.cpp:14
4       breakpoint     keep y   0x0000000000400cdd in main() at test.cpp:16
5       breakpoint     keep n   0x0000000000400d46 in main() at test.cpp:23
6       breakpoint     keep n   0x0000000000400d4e in main() at test.cpp:25
7       breakpoint     keep n   0x0000000000400d6e in main() at test.cpp:28
8       breakpoint     keep n   0x0000000000400d7d in main() at test.cpp:30

# 设置第5,6,7个断点有效
(gdb) ena 5-7

# 查看断点信息
(gdb) i b
Num     Type           Disp Enb Address            What
2       breakpoint     keep y   0x0000000000400cce in main() at test.cpp:14
4       breakpoint     keep y   0x0000000000400cdd in main() at test.cpp:16
5       breakpoint     keep y   0x0000000000400d46 in main() at test.cpp:23
6       breakpoint     keep y   0x0000000000400d4e in main() at test.cpp:25
7       breakpoint     keep y   0x0000000000400d6e in main() at test.cpp:28
8       breakpoint     keep n   0x0000000000400d7d in main() at test.cpp:30
5. 调试命令
5.1 继续运行gdb
如果调试的程序被断点阻塞了又想让程序继续执行，这时候就可以使用continue命令。程序会继续运行, 直到遇到下一个有效的断点。continue可以缩写为 c。

SHELL
1
2
# continue == c
(gdb) continue
5.2 手动打印信息
当程序被某个断点阻塞之后, 可以通过一些命令打印变量的名字或者变量的类型，并且还可以跟踪打印某个变量的值。

5.2.1 打印变量值
在gdb调试的时候如果需要打印变量的值， 使用的命令是 print, 可缩写为 p。如果打印的变量是整数还可以指定输出的整数的格式, 格式化输出的整数对应的字符表如下：

格式化字符(/fmt)	说明
/x	以十六进制的形式打印出整数。
/d	以有符号、十进制的形式打印出整数。
/u	以无符号、十进制的形式打印出整数。
/o	以八进制的形式打印出整数。
/t	以二进制的形式打印出整数。
/f	以浮点数的形式打印变量或表达式的值。
/c	以字符形式打印变量或表达式的值。
print命令的语法格式如下:

SHELL
1
2
3
4
5
# print == p
(gdb) p 变量名

# 如果变量是一个整形, 默认对应的值是以10进制格式输出, 其他格式请参考上表
(gdb) p/fmt 变量名
举例:

SHELL

# 举例
(gdb) p i       # 10进制
$5 = 3
(gdb) p/x i     # 16进制
$6 = 0x3
(gdb) p/o i     # 8进制
$7 = 03
5.2.2 打印变量类型
如果在调试过程中需要查看某个变量的类型, 可以使用命令ptype, 语法格式如下:

SHELL
1
2
# 语法格式
(gdb) ptype 变量名
举例:

SHELL

# 打印变量类型
(gdb) ptype i
type = int
(gdb) ptype array[i]
type = int
(gdb) ptype array
type = int [12]
5.3 自动打印信息
5.3.1 设置变量名自动显示
和 print 命令一样，display 命令也用于调试阶段查看某个变量或表达式的值，它们的区别是，使用 display 命令查看变量或表达式的值，每当程序暂停执行（例如单步执行）时，GDB 调试器都会自动帮我们打印出来，而 print 命令则不会。因此，当我们想频繁查看某个变量或表达式的值从而观察它的变化情况时，使用 display 命令可以一劳永逸。display 命令没有缩写形式，常用的语法格式如下 2 种：

SHELL
1
2
3
4
5
# 在变量的有效取值范围内, 自动打印变量的值(设置一次, 以后就会自动显示)
(gdb) display 变量名

# 以指定的整形格式打印变量的值, 关于 fmt 的取值, 请参考 print 命令
(gdb) display/fmt 变量名
5.3.2 查看自动显示列表
对于使用 display 命令查看的目标变量或表达式，都会被记录在一张列表（称为自动显示列表）中。通过执行info dispaly命令，可以打印出这张表：

SHELL

# info == i
(gdb) info display
Auto-display expressions now in effect:
Num Enb Expression
1:   y  i
2:   y  array[i]
3:   y  /x array[i]
在展示出的信息中, 每个列的含义如下:

Num : 变量或表达式的编号，GDB 调试器为每个变量或表达式都分配有唯一的编号
Enb : 表示当前变量（表达式）是处于激活状态还是禁用状态，如果处于激活状态（用 y 表示），则每次程序停止执行，该变量的值都会被打印出来；反之，如果处于禁用状态（用 n 表示），则该变量（表达式）的值不会被打印。
Expression ：被自动打印值的变量或表达式的名字。
5.3.3 取消自动显示
对于不需要再打印值的变量或表达式，可以将其删除或者禁用。

删除自动显示列表中的变量或表达式

SHELL
1
2
3
4
5
6
7
# 命令中的 num 是通过 info display 得到的编号, 编号可以是一个或者多个
(gdb) undisplay num [num1 ...]
# num1 - numN 表示一个范围
(gdb) undisplay num1-numN

(gdb) delete display num [num1 ...]
(gdb) delete display num1-numN
举例说明:

SHELL
# 查看显示列表
(gdb) info display
Auto-display expressions now in effect:
Num Enb Expression
1:   y  i
2:   y  array[i]
3:   y  /x array[i]

# 删除变量显示, 需要使用 info display 得到的变量/表达式编号
(gdb) undisplay 1 2

# 查看显示列表, 只剩下一个了
(gdb) i display
Auto-display expressions now in effect:
Num Enb Expression
3:   y  /x array[i]
如果不想删除自动显示的变量, 也可以禁用自动显示列表中处于激活状态下的变量或表达式

SHELL
1
2
3
4
# 命令中的 num 是通过 info display 得到的编号, 编号可以是一个或者多个
(gdb) disable display num [num1 ...]
# num1 - numN 表示一个范围
(gdb) disable display num1-numN
当需要启用自动显示列表中被禁用的变量或表达式时, 可以使用下边的命令

SHELL
1
2
3
4
# 命令中的 num 是通过 info display 得到的编号, 编号可以是一个或者多个
(gdb) enable  display num [num1 ...]
# num1 - numN 表示一个范围
(gdb) disable display num1-numN
5.3 单步调试
当程序阻塞到某个断点上之后, 可以通过以下命令对程序进行单步调试:

5.3.1 step
step命令可以缩写为s, 命令被执行一次代码被向下执行一行，如果这一行是一个函数调用，那么程序会进入到函数体内部。

SHELL
1
2
3
4
# 从当前代码行位置, 一次调试当前行下的每一行代码
# step == s
# 如果这一行是函数调用, 执行这个命令, 就可以进入到函数体的内部
(gdb) step
5.3.2 finish
如果通过 s 单步调试进入到函数内部, 想要跳出这个函数体， 可以执行finish命令。如果想要跳出函数体必须要保证函数体内不能有有效断点，否则无法跳出。

SHELL
1
2
# 如果通过 s 单步调试进入到函数内部, 想要跳出这个函数体
(gdb) finish
5.3.3 next
next命令和step命令功能是相似的，只是在使用next调试程序的时候不会进入到函数体内部，next可以缩写为 n

SHELL
1
2
3
# next == n
# 如果这一行是函数调用, 执行这个命令, 不会进入到函数体的内部
(gdb) next
5.3.4 until
通过 until 命令可以直接跳出某个循环体，这样就能提高调试效率了。如果想直接从循环体中跳出, 必须要满足以下的条件，否则命令不会生效：

要跳出的循环体内部不能有有效的断点
必须要在循环体的开始/结束行执行该命令
SHELL
1
(gdb) until
5.4 设置变量值
在调试程序的时候, 我们需要在某个变量等于某个特殊值的时候查看程序的运行状态, 但是通过程序运行让变量等于这个值又非常困难, 这种情况下就可以在 gdb 中直接对这个变量进行值的设置, 或者是在单步调试的时候通过设置循环因子的值直接跳出某个循环, 值设置的命令格式为: set var 变量名=值

SHELL
1
2
3
# 可以在循环中使用, 直接设置循环因子的值
# 假设某个变量的值在程序中==90的概率是5%, 这时候可以直接通过命令将这个变量值设置为90
(gdb) set var 变量名=值




