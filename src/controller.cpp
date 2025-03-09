// #include <iostream>
#include "controller.h"
#include "version.h"

ATMController::ATMController(BankAPI& _api):api(_api) {
    // printf("ATMController create! \n");
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
    std::cout << "Select Option [1: Check Balance, 2: Deposit, 3: Deposit Another, 4: Withdrawal, 5: Exit] : ";
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
    case ATMController::Process::DEPOSIT_ANOTHER:
        state = ATMController::Process::DEPOSIT_ANOTHER;
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

/**
 * @brief 
 * insertCard action
 * Replace the card input action with the card number input.
 * @return true 
 * @return false 
 */
bool ATMController::insertCard(){
    std::string _card_number;
    int pin;
    std::cout << "Insert Card (Enter Card Number): ";
    std::getline(std::cin >> std::ws, _card_number);

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

/**
 * @brief 
 * main process.
 */
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
            case ATMController::Process::DEPOSIT_ANOTHER:
            {
                unsigned int amount;
                std::cout << "How much would you like to deposit? : ";
                amount = inputOnlyInteger();
                std::cout << "Please enter the card number to deposit : ";
                std::string target_card_name;
                std::getline(std::cin >> std::ws, target_card_name);
                if (api.deposit(card_number,target_card_name,amount))
                {
                    printf("Success to deposit.\nThe balance of acocunt is %u $\n",api.getBalance(card_number));
                }else{
                    printf("Fail to deposit.\n");
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

void makeAccountListForTest(BankAPI& api){
    api.addAccount("111 111 111",123,100);
    api.addAccount("222 222 222",456,200);
    api.addAccount("333 333 333",789,300);
    api.addAccount("444 444 444",654,400);
    api.addAccount("555 555 555",321,500);
}

int main(int argc, char const *argv[])
{
    printf("ATM_Controller Version: %s\n",ATM_CONTROLLER_VERSION_STRING);
    BankAPI bank_api = BankAPI();

    makeAccountListForTest(bank_api); //add simply account

    ATMController controller = ATMController(bank_api);

    controller.start();

    bank_api.showAllAccountInfo();

    return 0;
}
