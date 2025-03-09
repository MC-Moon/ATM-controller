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
        void addAccount(const std::string& card_number,int pin, unsigned int balance);
        bool checkPIN(const std::string& card_number,const int& pin_number);
        unsigned int getBalance(const std::string& card_number);
        bool deposit(const std::string& card_number,const unsigned int& dollars);
        bool deposit(const std::string& card_number,const std::string& target_card,const unsigned int& dollars);
        bool withdrawal(const std::string& card_number,const unsigned int& dollars);

        void showAllAccountInfo(); //for test
    private:
        static std::mutex mutex;
        std::map<std::string,Account> account;

    private:
        bool hasAccount(const std::string& card_number);


};