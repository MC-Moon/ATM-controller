// #include <iostream>
#include "controller.h"
#include "bank_api.h"


ATMController::ATMController(){
    printf("ATMController create! \n");
    state = Process::IDLE;
}

ATMController::Process ATMController::inputUserSelcet(){
    std::cout << "Select Option\n[1: Check Balance, 2: Deposit, 3: Withdrawal, 4: Exit]" << std::endl;
    int select;
    std::cin >> select;
    ATMController::Process state;
    switch (select)
    {
    case ATMController::Process::CHECK_BALANCE:
        state = ATMController::Process::CHECK_BALANCE;
        break;
    case ATMController::Process::DEPOSIT:
        state = ATMController::Process::DEPOSIT;
        break;
    case ATMController::Process::WITHDRAWAL:
        state = ATMController::Process::WITHDRAWAL;
        break;
    case ATMController::Process::EXIT:
        state = ATMController::Process::EXIT;
        break;
    default:
        printf("[%d] is invalid. please retry.\n",select);
        return inputUserSelcet();
    }
    return state;
}

void ATMController::start(){
    state = inputUserSelcet();
    printf("state : %d",state);
}

int main(int argc, char const *argv[])
{
    ATMController controller = ATMController();
    BankAPI bank_api = BankAPI();

    controller.start();

    return 0;
}
