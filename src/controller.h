#include <iostream>
#include "bank_api.h"

class ATMController{
    enum Process
    {
        IDLE,
        CHECK_BALANCE,
        DEPOSIT,
        WITHDRAWAL,
        EXIT
    };
    public:
        ATMController(BankAPI api);
        ~ATMController(){};
        
        void start(); // do main routine

    private:
        std::string card_number;
        int pin_number;
        BankAPI api;
        Process state;
        Process inputUserSelcet();
        bool insertCard();
};