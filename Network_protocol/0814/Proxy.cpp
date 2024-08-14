#include <iostream>
#include <string>


// 抽象主题类，定义了账户的接口
class Account
{
public:
    virtual void withdraw(double amount) = 0;// 抽象方法,定义取款操作
    // virtual void deposit(double amount) = 0;// 抽象方法,定义存款操作
    virtual ~Account() {}

};

// 实现类，具体的账户类
// 真实主题类，表示一个实际的银行账户
class RealAccount : public Account
{
private:
    double balance;// 账户余额

public:
    RealAccount(double initialBalance) : balance(initialBalance) {}

    // 实现取款操作
    void withdraw(double amount) override
    {
        if (amount <= balance)
        {
            balance -= amount;
            std::cout << "Withdrawal of $" << amount << " successful. Remaining balance: $" << balance << std::endl;
        } 
        else 
        {
            std::cout << "Insufficient funds. Withdrawal of $" << amount << " failed. Current balance: $" << balance << std::endl;
        }  
    }

    double getBalance() const
    {
        return balance;// 返回账户余额
    }

};

// 代理类，表示一个代理账户
// 控制对真实账户的访问
class AccountProxy : public Account
{
private:
    RealAccount* realAccount;// 真实主题对象--对真实账户对象的引用
    std::string password;// 用于访问账户的密码

public:
    // 初始化真实账户和密码
    AccountProxy(double initialBalance, const std::string& pwd)
        : realAccount(new RealAccount(initialBalance)), password(pwd) {}

    ~AccountProxy()
    {
        delete realAccount;// 释放真实账户对象的内存
    }

    // 代理的取款操作, 需要进行密码验证
    void withdraw(double amount) override
    {
        std::string inputPwd;
        std::cout << "Enter password: ";
        std::cin >> inputPwd;

        if (inputPwd == password)
        {
            realAccount->withdraw(amount);// 调用真实账户的取款操作
        }
        else
        {
            std::cout << "Invalid password. Withdrawal failed." << std::endl;
        }
    }

    // 代理类也可以提供其他功能,如检查余额
    void checkBalance() const
    {
        std::cout << "Checking balance..." << std::endl;
        std::cout << "Current balance:  $" << realAccount->getBalance() << std::endl;
    }

};

int main(int argc, char* argv[])
{
    // 创建代理对象并初始化账户
    AccountProxy* account = new AccountProxy(1000.0, "secret");

    // 尝试取款操作
    account->withdraw(200.0);// 输入密码后成功取款
    // 检查余额
    account->checkBalance();


    account->withdraw(900.0);  // 尝试超过余额的取款
    account->checkBalance();   // 再次检查余额

    account->withdraw(100.0);  // 验证失败的尝试

    // 清理资源
    delete account;
    return 0;
}




