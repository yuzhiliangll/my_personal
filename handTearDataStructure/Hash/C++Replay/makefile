# 变量定义
CXX = g++              # 使用 g++ 编译 C++ 代码
CXXFLAGS = -g         # C++ 编译选项
LDFLAGS = -L./src_so -L./src_a
#LIBS = -lMyAdd -lMyDiv # 链接库

# 目标名称
TARGET = main

# 自动生成的对象文件列表
OBJS = $(patsubst %.cpp, %.o, $(wildcard ./*.cpp))

# 规则：生成目标文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LIBS) $(LDFLAGS) -o $(TARGET)

# 规则：生成对象文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 伪目标：clean
.PHONY: clean

clean:
	$(RM) $(OBJS) $(TARGET)

# 伪目标：显示文件
.PHONY: show
show:
	@echo $(wildcard ./*.cpp)
	@echo $(patsubst %.cpp, %.o, $(wildcard ./*.cpp))