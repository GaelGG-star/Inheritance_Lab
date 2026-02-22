//
// Created by Gaelg on 1/31/2026.
//

#ifndef OBJECTS_CLASSES_LAB_BANKACCOUNT_H
#define OBJECTS_CLASSES_LAB_BANKACCOUNT_H

#include <string>

// Class declaration
class BankAccount {
private:
    std::string accountNumber;
    std::string accountHolderName;
    double balance;

public:
    ~BankAccount(); // Destructor
    BankAccount(const BankAccount& other); // Copy constructor
    BankAccount& operator=(const BankAccount& other); // Copy Assignment Operator

    // Member operators that add and subtract money from the balance
    BankAccount& operator+=(double amount);
    BankAccount& operator-=(double amount);

    // Comparison operators for comparing accounts
    bool operator==(const BankAccount& other) const;
    bool operator<(const BankAccount& other) const;
    bool operator>(const BankAccount& other) const;

    // Static methods for printing and creating accounts
    static void printAccount(const BankAccount& account);
    static BankAccount createAccountFromInput();

    // Constructors
    BankAccount();
    BankAccount(std::string accountNumber, std::string accountHolderName, double balance);

    // Getter methods
    std::string getAccountNumber() const;
    std::string getAccountHolderName() const;
    double getBalance() const;

    // Setter method for account holder name
    void setAccountHolderName(std::string name);

    // Methods for depositing and withdrawing money
    void deposit(double amount);
    void withdraw(double amount);
};

// Non-member operators for expressions like `newAccount = oldAccount + 50;`
BankAccount operator+(BankAccount lhs, double amount);
BankAccount operator-(BankAccount lhs, double amount);


#endif //OBJECTS_CLASSES_LAB_BANKACCOUNT_H