// 定义一个上下文类，它使用策略接口，并可以在运行时选择具体的策略：
// Context.h
#ifndef CONTEXT_H
#define CONTEXT_H

#include "Strategy.h"

class Context {
private:
    Strategy* strategy;

public:
    Context(Strategy* initialStrategy) : strategy(initialStrategy) {}

    void setStrategy(Strategy* newStrategy) {
        strategy = newStrategy;
    }

    void performOperation() const {
        strategy->execute();
    }
};

#endif // CONTEXT_H

