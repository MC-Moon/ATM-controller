// #include <iostream>
#include "controller.h"
#include "bank_api.h"


ATMController::ATMController(){
    printf("ATMController create! \n");
}

int main(int argc, char const *argv[])
{
    ATMController controller = ATMController();
    BankAPI bank_api = BankAPI();

    return 0;
}
