# 变量定义
CC = gcc
CFLAGS = -g
LDFLAGS = -L./src_so -L./src_a
#LIBS = -lMyAdd -lMyDiv

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