# 变量定义
CC = gcc
CFLAGS = -g
LDFLAGS = -L./src_so -L./src_a
LIBS = -lMyAdd -lMyDiv

# 目标名称
TARGET = main

# 自动生成的对象文件列表
OBJS = $(patsubst %.c, %.o, $(wildcard ./*.c))

# 规则：生成目标文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LDFLAGS) -o $(TARGET)

# 规则：生成对象文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 伪目标：clean
.PHONY: clean

clean:
	$(RM) $(OBJS) $(TARGET)

# 伪目标：显示文件
.PHONY: show
show:
	@echo $(wildcard ./*.c)
	@echo $(patsubst %.c, %.o, $(wildcard ./*.c))
===============================================================================
修改说明：
变量定义：

CC = gcc：指定编译器。
CFLAGS = -g：编译选项，包含调试信息。
LDFLAGS = -L./src_so -L./src_a：链接选项，用于指定库目录。
LIBS = -lMyAdd -lMyDiv：链接库，假设你需要链接 MyAdd 和 MyDiv 库。
目标文件：

OBJS = $(patsubst %.c, %.o, $(wildcard ./*.c))：自动生成的对象文件列表。
生成目标文件：

$(TARGET): $(OBJS)：指定如何生成最终目标 main，使用 $(CC) 链接所有对象文件，并指定库和链接选项。
生成对象文件：

%.o: %.c：指定如何从源文件生成对象文件，使用 $(CC) 进行编译。
伪目标：

.PHONY: clean：标记 clean 为伪目标，以便 make 不会将其视为文件。
.PHONY: show：标记 show 为伪目标。
清理目标：

clean：删除所有对象文件和目标文件。
显示文件：

show：用于显示当前目录下的所有 .c 文件和对应的 .o 文件。

=================================================================
测试编译
编译项目：

make
这将根据 Makefile 自动编译和链接源文件，生成 main 可执行文件。

清理生成的文件：

make clean
这将删除所有对象文件和目标文件。

显示文件：

make show
这将显示当前目录下的 .c 文件和对应的 .o 文件列表


