#include <iostream>


class ATMController{
    enum Process
    {
        IDLE,
        INSERT,
        CHECK_BALANCE,
        DEPOSIT,
        WITHDRAWAL,
        EXIT
    };
    public:
        ATMController();
        ~ATMController(){};
        
        void start(); // do main routine

    private:
        Process state;
};