// #include <iostream>
#include "controller.h"


ATMController::ATMController(BankAPI _api):api(_api) {
    printf("ATMController create! \n");
    state = Process::IDLE;
}
unsigned int ATMController::inputOnlyInteger(){
    unsigned int data;
    while (true)
    {
        std::cin >> data;
        if (!std::cin)
        {
            std::cout << "Please input integer type only. : ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }else{
            break;
        }
    }
    return data;
}
ATMController::Process ATMController::inputUserSelcet(){
    std::cout << "Select Option [1: Check Balance, 2: Deposit, 3: Withdrawal, 4: Exit] : ";
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
                printf("Your balance is %u $\n",api.getBalance(card_number));
                break;
            }
            case ATMController::Process::DEPOSIT:
            {
                unsigned int amount;
                std::cout << "How much would you like to deposit? : ";
                amount = inputOnlyInteger();
                if (api.deposit(card_number,amount))
                {
                    printf("Success to deposit.\nThe balance of acocunt is %u $\n",api.getBalance(card_number));
                }else{
                    printf("The deposit amount exceeds the maximum.\n");
                    printf("The balance in your account cannot exceed %u $.\nPlease try again.\n",MAX);
                }
                break;
            }
            case ATMController::Process::WITHDRAWAL:
            {
                unsigned int amount;
                std::cout << "How much would you like to withdrawal? : ";
                amount = inputOnlyInteger();
                if (api.withdrawal(card_number,amount))
                {
                    printf("Success to deposit.\nThe balance of acocunt is %u $\n",api.getBalance(card_number));
                }else{
                    printf("Your balance is insufficient.\nPlease check your the balance of account.\n");
                }
                break;
            }
            case ATMController::Process::EXIT:
                printf("Thank you.\n");
                return;
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
