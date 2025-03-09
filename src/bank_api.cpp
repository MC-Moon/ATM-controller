#include "bank_api.h"

std::mutex BankAPI::mutex;

BankAPI::BankAPI(){
    // printf("BankAPI create! \n");
}

void BankAPI::addAccount(std::string card_number,int pin_number, unsigned int balance){
    printf("addAccount [%s], pin : %d, balance: %d\n",card_number.c_str(),pin_number,balance);
    account[card_number] = {card_number,pin_number,balance};
}

bool BankAPI::checkPIN(const std::string& card_number,const int& pin_number){
    // printf("checkPIN \n");
    return account.find(card_number) != account.end() &&
     account[card_number].pin == pin_number;
}

unsigned int BankAPI::getBalance(const std::string& card_number){
    // printf("getBalance : %d$\n",account[card_number].balance);
    std::lock_guard<std::mutex> lock(mutex);
    return account[card_number].balance;
}

bool BankAPI::deposit(const std::string& card_number,const unsigned int& dollars){
    // printf("deposit %d$\n",dollars);
    std::lock_guard<std::mutex> lock(mutex);
    if (dollars > MAX-getBalance(card_number))
    {
        return false;
    }
    account[card_number].balance+=dollars;
    return true;
}

bool BankAPI::withdrawal(const std::string& card_number,const unsigned int& dollars){
    // printf("withdrawal : %d$\n",dollars);
    std::lock_guard<std::mutex> lock(mutex);
    if (getBalance(card_number) >= dollars)
    {
        account[card_number].balance -= dollars;
    }else{
        // printf("Your balance is insufficient.");
        return false;
    }
    return true;
}
