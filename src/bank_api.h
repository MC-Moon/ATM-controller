#include <iostream>
#include <string>
#include <mutex>
#include <map>

constexpr unsigned int MAX = std::numeric_limits<unsigned int>::max();

class BankAPI{
    struct Account
    {
        std::string card_number;
        int pin;
        unsigned int balance;
    };
    public:
        BankAPI();
        ~BankAPI(){};
        void addAccount(std::string card_number,int pin, unsigned int balance);
        bool checkPIN(const std::string& card_number,const int& pin_number);
        unsigned int getBalance(const std::string& card_number);
        bool deposit(const std::string& card_number,const unsigned int& dollars);
        bool withdrawal(const std::string& card_number,const unsigned int& dollars);
    private:
        static std::mutex mutex;
        std::map<std::string,Account> account;


};