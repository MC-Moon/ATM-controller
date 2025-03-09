#include "bank_api.h"

BankAPI::BankAPI(){
    printf("BankAPI create! \n");
}

void BankAPI::addAccount(std::string card_number,int pin_number, int balance){
    printf("addAccount [%s], pin : %d, balance: %d\n",card_number.c_str(),pin_number,balance);
    account[card_number] = {card_number,pin_number,balance};
}

bool BankAPI::checkPIN(const std::string& card_number,const int& pin_number){
    printf("checkPIN \n");
    return account.find(card_number) != account.end() &&
     account[card_number].pin == pin_number;
}

int BankAPI::getBalance(const std::string& card_number){
    printf("getBalance : %d$\n",account[card_number].balance);
    return account[card_number].balance;
}

bool BankAPI::deposit(const std::string& card_number,const int& dollars){
    printf("deposit %d$\n",dollars);
    account[card_number].balance+=dollars;
    return true;
}

bool BankAPI::withdrawal(const std::string& card_number,const int& dollars){
    printf("withdrawal : %d$\n",dollars);
    if (getBalance(card_number) >= dollars)
    {
        account[card_number].balance -= dollars
    }else{
        printf("Your balance is insufficient.");
        return false
    }
    return true;
}
