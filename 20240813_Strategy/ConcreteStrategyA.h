
// 接下来，创建一些具体策略类，继承自策略接口，并实现不同的算法：
// ConcreteStrategyA.h
#ifndef CONCRETE_STRATEGY_A_H
#define CONCRETE_STRATEGY_A_H

#include "Strategy.h"
#include <iostream>

class ConcreteStrategyA : public Strategy {
public:
    void execute() const override {
        std::cout << "Executing Strategy A" << std::endl;
    }
};

#endif // CONCRETE_STRATEGY_A_H
