//
// Created by Gaelg on 1/31/2026.
//

#include "BankAccount.h"
#include <iostream>
#include <limits>

// Constructor
BankAccount::BankAccount() {
    accountNumber = "";
    accountHolderName = "";
    balance = 0.0;
}

// Parameterized Constructor
BankAccount::BankAccount(std::string accountNumber, std::string accountHolderName, double balance) {
    this->accountNumber = accountNumber;
    this->accountHolderName = accountHolderName;
    this->balance = balance;
}

// Getter methods for account number
std::string BankAccount::getAccountNumber() const {
    return accountNumber;
}

// Getter methods for account holder name
std::string BankAccount::getAccountHolderName() const {
    return accountHolderName;
}

// Getter methods for balance
double BankAccount::getBalance() const {
    return balance;
}

// Setter method for account holder name
void BankAccount::setAccountHolderName(std::string name) {
    accountHolderName = name;
}

// Methods for depositing money
void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}

// Methods for withdrawing money
void BankAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
    }
}

// Destructor for BankAccount
BankAccount::~BankAccount() {
    // No dynamic memory was allocated, so the destructor can be empty.
    // std::string and other standard library containers manage their own memory.
}

// Copy constructor for BankAccount
BankAccount::BankAccount(const BankAccount& other) {
    accountNumber = other.accountNumber;
    accountHolderName = other.accountHolderName;
    balance = other.balance;
}

// Copy Assignment Operator for BankAccount
BankAccount& BankAccount::operator=(const BankAccount& other) {
    // Check for self-assignment to prevent issues like `myAccount = myAccount;`
    if (this != &other) {
        accountNumber = other.accountNumber;
        accountHolderName = other.accountHolderName;
        balance = other.balance;
    }
    return *this; // Return a reference to the current object
}

// Member operator+=
BankAccount& BankAccount::operator+=(double amount) {
    this->deposit(amount);
    return *this;
}

// Member operator-=
BankAccount& BankAccount::operator-=(double amount) {
    this->withdraw(amount);
    return *this;
}

// Comparison operator== (compares account numbers for equality)
bool BankAccount::operator==(const BankAccount& other) const {
    return this->accountNumber == other.accountNumber;
}

// Comparison operator< (compares balances)
bool BankAccount::operator<(const BankAccount& other) const {
    return this->balance < other.balance;
}

// Comparison operator> (compares balances)
bool BankAccount::operator>(const BankAccount& other) const {
    return this->balance > other.balance;
}

// Static method to print account details
void BankAccount::printAccount(const BankAccount& account) {
    std::cout << "------------------------\n"
              << "Account Holder: " << account.getAccountHolderName() << "\n"
              << "Account Number: " << account.getAccountNumber() << "\n"
              << "Balance: $" << account.getBalance() << "\n"
              << "------------------------" << std::endl;
}

// Static method to create an account from user input
BankAccount BankAccount::createAccountFromInput() {
    std::string num, name;
    double bal;

    std::cout << "Enter account number: ";
    // Use std::getline to allow spaces in input
    std::getline(std::cin, num);

    std::cout << "Enter account holder name: ";
    std::getline(std::cin, name);

    std::cout << "Enter initial balance: ";
    std::cin >> bal;
    // Clear the input buffer to handle the newline character left by std::cin
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return BankAccount(num, name, bal);
}