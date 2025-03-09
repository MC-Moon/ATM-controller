#include <iostream>
#include <limits>
#include "bank_api.h"
#include <vector>
class ATMController{
    enum Process
    {
        IDLE,
        CHECK_BALANCE,
        DEPOSIT,
        DEPOSIT_ANOTHER,
        WITHDRAWAL,
        EXIT
    };
    public:
        ATMController(BankAPI& api);
        ~ATMController(){};
        
        void start(); // do main routine

    private:
        std::string card_number;
        int pin_number;
        BankAPI& api;
        Process state;
    private:
        Process inputUserSelcet();
        unsigned int inputOnlyInteger();
        bool insertCard();
};