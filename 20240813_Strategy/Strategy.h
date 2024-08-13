// Strategy.h
#ifndef STRATEGY_H
#define STRATEGY_H

class Strategy {
public:
    virtual ~Strategy() {}
    virtual void execute() const = 0;
};

#endif // STRATEGY_H
