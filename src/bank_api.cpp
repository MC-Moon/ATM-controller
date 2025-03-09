#include "bank_api.h"

std::mutex BankAPI::mutex;

BankAPI::BankAPI(){
    // printf("BankAPI create! \n");
}

bool BankAPI::hasAccount(const std::string& card_number){
    // printf("[%s] has Account is %d",card_number.c_str(),account.find(card_number) != account.end());
    return account.find(card_number) != account.end();
}

/**
 * @brief
 * addAccount.
 * This can be omitted if a list of accounts can be received from the server.
 * @param card_number
 * @param pin_number
 * @param balance
 */
void BankAPI::addAccount(const std::string& card_number,int pin_number, unsigned int balance){
    printf("addAccount [%s], pin : %d, balance: %d\n",card_number.c_str(),pin_number,balance);
    account[card_number] = {card_number,pin_number,balance};
}

/**
 * @brief
 * validation check by pin
 * @param card_number
 * @param pin_number
 * @return true
 * @return false
 */
bool BankAPI::checkPIN(const std::string& card_number,const int& pin_number){
    // printf("checkPIN \n");
    return account.find(card_number) != account.end() &&
     account[card_number].pin == pin_number;
}

/**
 * @brief
 * see the balance of my account
 * @param card_number
 * @return unsigned int
 */
unsigned int BankAPI::getBalance(const std::string& card_number){
    // printf("getBalance : %d$\n",account[card_number].balance);
    std::lock_guard<std::mutex> lock(mutex);
    return account[card_number].balance;
}

/**
 * @brief
 * Deposit to my card
 * @param card_number
 * @param dollars
 * @return true
 * @return false
 */
bool BankAPI::deposit(const std::string& card_number,const unsigned int& dollars){
    // printf("[%s] deposit %u$\n",card_number.c_str(),dollars);
    std::lock_guard<std::mutex> lock(mutex);
    if (dollars > MAX-getBalance(card_number))
    {
        return false;
    }
    account[card_number].balance+=dollars;
    // printf("[%s] deposit %u$\n",card_number.c_str(),getBalance(card_number));
    return true;
}

/**
 * @brief
 * Deposit to another account
 * @param card_number
 * @param target_card
 * @param dollars
 * @return true
 * @return false
 */
bool BankAPI::deposit(const std::string& card_number,const std::string& target_card,const unsigned int& dollars){
    // printf("deposit %d$\n",dollars);
    std::lock_guard<std::mutex> lock(mutex);
    if(!hasAccount(target_card))
    {
        printf("%s card number cannot be found\n",target_card.c_str());
        return false;
    }
    if (getBalance(card_number) < dollars || dollars > MAX-getBalance(target_card))
    {
        printf("Please Check your balance: %u $.\nPlease try again.\n",getBalance(card_number));
        return false;
    }
    if(!deposit(target_card,dollars)){
        return false;
    }
    account[card_number].balance-=dollars;
    return true;
}

/**
 * @brief
 *
 * @param card_number
 * @param dollars
 * @return true
 * @return false
 */
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

void BankAPI::showAllAccountInfo(){
    printf("===============================\n");
    for (auto it : account)
    {
        printf("card number : %s\n",it.first.c_str());
        printf("pin number  : %d\n",it.second.pin);
        printf("balance     : %u\n",it.second.balance);
        printf("===============================\n");
    }
    
}