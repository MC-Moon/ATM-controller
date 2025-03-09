#include <iostream>
#include <string>
#include <mutex>
#include <map>

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
        void addAccount(std::string card_number,int pin, int balance);
        bool checkPIN(const std::string& card_number,const int& pin_number);
        int getBalance(const std::string& card_number);
        bool deposit(const std::string& card_number,const int& dollars);
        bool withdrawal(const std::string& card_number,const int& dollars);
    private:
        static std::mutex mutex;
        std::map<std::string,Account> account;


};