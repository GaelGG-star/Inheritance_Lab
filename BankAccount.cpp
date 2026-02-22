// Programmer: Gael Garcia Guzman
// Date: 1/31/2026
// Purpose: Implements the methods for the BankAccount, CheckingAccount, and SavingAccount classes.

#include "BankAccount.h"
#include <iostream>
#include <limits>

// Default constructor initializes an empty account.
BankAccount::BankAccount() : accountNumber(""), accountHolderName(""), balance(0.0) {}

// Parameterized constructor initializes account with provided values.
BankAccount::BankAccount(std::string accountNumber, std::string accountHolderName, double balance)
    : accountNumber(accountNumber), accountHolderName(accountHolderName), balance(balance) {}

// Copy constructor.
BankAccount::BankAccount(const BankAccount& other)
    : accountNumber(other.accountNumber), accountHolderName(other.accountHolderName), balance(other.balance) {}

// Copy assignment operator with self-assignment check.
BankAccount& BankAccount::operator=(const BankAccount& other) {
    if (this != &other) {
        accountNumber = other.accountNumber;
        accountHolderName = other.accountHolderName;
        balance = other.balance;
    }
    return *this;
}

// Getter for account number.
std::string BankAccount::getAccountNumber() const {
    return accountNumber;
}

// Getter for account holder name.
std::string BankAccount::getAccountHolderName() const {
    return accountHolderName;
}

// Getter for balance.
double BankAccount::getBalance() const {
    return balance;
}

// Setter for account holder name.
void BankAccount::setAccountHolderName(std::string name) {
    accountHolderName = name;
}

// Adds a positive amount to the balance.
void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}

// Subtracts a positive amount from the balance if funds are sufficient.
void BankAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
    }
}

// Overloaded operators for convenience.
BankAccount& BankAccount::operator+=(double amount) {
    deposit(amount);
    return *this;
}

BankAccount& BankAccount::operator-=(double amount) {
    withdraw(amount);
    return *this;
}

// Compares accounts by account number for equality.
bool BankAccount::operator==(const BankAccount& other) const {
    return this->accountNumber == other.accountNumber;
}

// Compares accounts by balance.
bool BankAccount::operator<(const BankAccount& other) const {
    return this->balance < other.balance;
}

bool BankAccount::operator>(const BankAccount& other) const {
    return this->balance > other.balance;
}

// Static method to print account details in a formatted way.
void BankAccount::printAccount(const BankAccount& account) {
    std::cout << "------------------------\n"
              << "Account Holder: " << account.getAccountHolderName() << "\n"
              << "Account Number: " << account.getAccountNumber() << "\n"
              << "Balance: $" << account.getBalance() << "\n"
              << "------------------------" << std::endl;
}

// Static method to create a BankAccount from user input.
// Note: This is less used now that creation is handled in main for specific types.
BankAccount BankAccount::createAccountFromInput() {
    std::string num, name;
    double bal;

    std::cout << "Enter account number: ";
    std::getline(std::cin, num);

    std::cout << "Enter account holder name: ";
    std::getline(std::cin, name);

    std::cout << "Enter initial balance: ";
    std::cin >> bal;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return BankAccount(num, name, bal);
}

// --- CheckingAccount Implementation ---

// Constructor for CheckingAccount.
CheckingAccount::CheckingAccount(std::string accountNumber, std::string accountHolderName, double balance, double fee)
    : BankAccount(accountNumber, accountHolderName, balance), transactionFee(fee) {}

// Overridden withdraw method applies a transaction fee.
void CheckingAccount::withdraw(double amount) {
    double totalWithdrawal = amount + transactionFee;
    // Call the base class's withdraw method to perform the actual withdrawal.
    BankAccount::withdraw(totalWithdrawal);
}

// --- SavingAccount Implementation ---

// Constructor for SavingAccount.
SavingAccount::SavingAccount(std::string accountNumber, std::string accountHolderName, double balance, double rate)
    : BankAccount(accountNumber, accountHolderName, balance), interestRate(rate) {}

// Overridden withdraw method for savings account.
void SavingAccount::withdraw(double amount) {
    // Currently, it behaves just like a standard bank account.
    // Could be modified to include rules like minimum balance.
    BankAccount::withdraw(amount);
}

// Calculates interest based on the current balance and adds it to the account.
void SavingAccount::calculateInterest() {
    if (interestRate > 0) {
        double interest = getBalance() * interestRate;
        deposit(interest);
    }
}