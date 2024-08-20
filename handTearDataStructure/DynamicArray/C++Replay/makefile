OBJS=$(patsubst %.cpp, %.o, $(wildcard ./*.cpp))
# 变量定义赋值
TARGET=server

LDFLAGS=-L./src_so -L./src_a
LIBS=-lsqlite3 -lssl -lcrypto -ltinyxml2

SO_DIR=./src_so
A_DIR=./src_a

PATHS=/tmp/demoMain/
BIN=/usr/local/bin/

#变量取值用$()
$(TARGET):$(OBJS)
	$(CXX) $^ -o $@ $(LIBS) -g

# 模式匹配: %目标:%依赖
%.o:%.cpp
	@$(CXX) -c $^ -o $@

all:
	make -C $(SO_DIR)
	make -C $(A_DIR)


install:$(TARGET)
	@if [ -d $(PATHS) ];					\
		then echo $(PATHS) exist;		\
	else								\
		mkdir $(PATHS);					\
		cp $(TARGET) $(PATHS);			\
		sudo ln -sv $(PATHS)$(TARGET) $(BIN);	\
	fi

# 伪目标/伪文件
.PHONY:	clean

clean:
	$(RM) $(OBJS) $(TARGET)
	make -C $(SO_DIR) clean
	make -C $(A_DIR) clean
	
# wildcard : 匹配文件 			(获取指定目录下所有的.c文件)
# patsubst : 模式匹配与替换 	（指定目录下所有的.c文件替换成.o文件）
show:
	@echo $(wildcard ./*.cpp)
	@echo $(patsubst %.cpp, %.o, $(wildcard ./*.cpp))
# @ : 隐藏命令