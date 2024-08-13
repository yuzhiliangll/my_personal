// ConcreteStrategyB.h
#ifndef CONCRETE_STRATEGY_B_H
#define CONCRETE_STRATEGY_B_H

#include "Strategy.h"
#include <iostream>

class ConcreteStrategyB : public Strategy {
public:
    void execute() const override {
        std::cout << "Executing Strategy B" << std::endl;
    }
};

#endif // CONCRETE_STRATEGY_B_H
