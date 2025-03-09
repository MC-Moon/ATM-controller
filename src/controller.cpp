// #include <iostream>
#include "controller.h"


ATMController::ATMController(BankAPI _api):api(_api) {
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

bool ATMController::insertCard(){
    std::string _card_number;
    int pin;
    std::cout << "Insert Card (Enter Card Number): ";
    std::cin >> _card_number;

    std::cout << "Enter PIN: ";
    std::cin >> pin;

    if (!api.checkPIN(_card_number, pin)) {
        std::cout << "Invalid PIN. Transaction Cancelled.\n";
        return false;
    }
    card_number = _card_number;
    pin_number = pin;
    return true;
}

void ATMController::start(){
    if(!insertCard()){
        printf("This card is invalid. please insert valid card.\n");
        return;
    }

    while (true)
    {
        state = inputUserSelcet();
        switch (state)
        {
            case ATMController::Process::CHECK_BALANCE:
                {
                    printf("Your balance is %d$.",api.getBalance(card_number));
                    break;
                }
            case ATMController::Process::DEPOSIT:
                
                break;
            case ATMController::Process::WITHDRAWAL:
                
                break;
            case ATMController::Process::EXIT:
                
                break;
        }
    }
}

int main(int argc, char const *argv[])
{
    BankAPI bank_api = BankAPI();

    bank_api.addAccount("111",123,500); //add simply account

    ATMController controller = ATMController(bank_api);

    controller.start();

    return 0;
}
