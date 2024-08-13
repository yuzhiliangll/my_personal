// main.cpp
#include "Context.h"
#include "ConcreteStrategyA.h"
#include "ConcreteStrategyB.h"


// 在主函数中创建不同的策略实例，并使用上下文类来演示策略模式的工作
int main() 
{
    ConcreteStrategyA strategyA;
    ConcreteStrategyB strategyB;

    Context context(&strategyA);
    std::cout << "Context using Strategy A:" << std::endl;
    context.performOperation();

    std::cout << "Changing strategy to Strategy B:" << std::endl;
    context.setStrategy(&strategyB);
    context.performOperation();

    return 0;
}
