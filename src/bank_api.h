#include <iostream>
#include <string>
#include <mutex>

class BankAPI{
    struct Account
    {
        std::string card_number;
        int pin;
        int balance;
    };
    
    public:
        BankAPI();
        ~BankAPI(){};
        bool checkPIN(const std::string& card_number,const int& pin_number);
        int getBalance(const std::string& card_number);
        bool deposit(const std::string& card_number,const int& dollars);
        bool widthdrawal(const std::string& card_number,const int& dollars);
    private:
        static std::mutex mutex;

};