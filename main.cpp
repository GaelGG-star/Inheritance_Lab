// Programmer: Gael Garcia Guzman
// Date: 1/31/2026
// Purpose: A Bank Account Management System demonstrating polymorphism and inheritance.

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <memory> // Required for std::unique_ptr
#include "BankAccount.h"

// Function to display the main menu to the user.
void displayMenu() {
    std::cout << "\n--- Bank Account Menu ---" << std::endl;
    std::cout << "1. Create a new account" << std::endl;
    std::cout << "2. Deposit money" << std::endl;
    std::cout << "3. Withdraw money" << std::endl;
    std::cout << "4. Display account details" << std::endl;
    std::cout << "5. Compare two accounts" << std::endl;
    std::cout << "6. Calculate interest for a savings account" << std::endl;
    std::cout << "7. Demonstrate Polymorphism" << std::endl;
    std::cout << "8. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

// Finds an account in the vector by its account number.
// Returns a raw pointer to the account if found, otherwise nullptr.
BankAccount* findAccount(const std::vector<std::unique_ptr<BankAccount>>& accounts, const std::string& accNum) {
    for (const auto& account : accounts) {
        if (account->getAccountNumber() == accNum) {
            return account.get(); // Return raw pointer for observation
        }
    }
    return nullptr; // Account not found
}

// Handles invalid user input by clearing the input stream.
void handleInvalidInput() {
    std::cout << "Invalid input. Please try again." << std::endl;
    std::cin.clear(); // Clear error flags
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard bad input
}

// Demonstrates polymorphic behavior of the withdrawal function.
void demonstratePolymorphism() {
    // Create a CheckingAccount and a SavingAccount
    CheckingAccount checking("CHK123", "John Doe", 1000.0, 1.50);
    SavingAccount saving("SAV456", "Jane Smith", 2000.0, 0.02);

    // Create a vector of base class pointers
    std::vector<BankAccount*> accounts;
    accounts.push_back(&checking);
    accounts.push_back(&saving);

    std::cout << "\n--- Demonstrating Polymorphism ---" << std::endl;

    // Call withdraw on each account through a base class pointer
    for (BankAccount* account : accounts) {
        std::cout << "\nInitial state of account " << account->getAccountNumber() << ":" << std::endl;
        BankAccount::printAccount(*account);

        std::cout << "Withdrawing $100..." << std::endl;
        account->withdraw(100.0);

        std::cout << "Final state of account " << account->getAccountNumber() << ":" << std::endl;
        BankAccount::printAccount(*account);
    }
    std::cout << "\n--- End of Demonstration ---" << std::endl;
}

int main() {
    // Use a vector of unique_ptr to manage BankAccount objects polymorphically.
    std::vector<std::unique_ptr<BankAccount>> accounts;
    int choice;

    // Main application loop
    do {
        displayMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            handleInvalidInput();
            choice = 0;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            std::cout << "Select account type (1 for Checking, 2 for Savings): ";
            int type;
            std::cin >> type;
            if (std::cin.fail()) {
                handleInvalidInput();
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::string num, name;
            double bal;

            std::cout << "Enter account number: ";
            std::getline(std::cin, num);

            if (findAccount(accounts, num)) {
                std::cout << "An account with this number already exists." << std::endl;
                continue;
            }

            std::cout << "Enter account holder name: ";
            std::getline(std::cin, name);

            std::cout << "Enter initial balance: ";
            std::cin >> bal;
            if (std::cin.fail()) {
                handleInvalidInput();
                continue;
            }

            if (type == 1) {
                double fee;
                std::cout << "Enter transaction fee: ";
                std::cin >> fee;
                if (std::cin.fail()) {
                    handleInvalidInput();
                    continue;
                }
                accounts.push_back(std::make_unique<CheckingAccount>(num, name, bal, fee));
                std::cout << "Checking account created successfully." << std::endl;
            } else if (type == 2) {
                double rate;
                std::cout << "Enter interest rate (e.g., 0.05 for 5%): ";
                std::cin >> rate;
                if (std::cin.fail()) {
                    handleInvalidInput();
                    continue;
                }
                accounts.push_back(std::make_unique<SavingAccount>(num, name, bal, rate));
                std::cout << "Savings account created successfully." << std::endl;
            } else {
                std::cout << "Invalid account type selected." << std::endl;
            }
        } else if (choice == 2) {
            std::string accNum;
            double amount;
            std::cout << "Enter account number: ";
            std::cin >> accNum;

            BankAccount* account = findAccount(accounts, accNum);
            if (account) {
                std::cout << "Enter amount to deposit: ";
                std::cin >> amount;
                if (std::cin.fail() || amount <= 0) {
                    handleInvalidInput();
                    continue;
                }
                *account += amount;
                std::cout << "Deposit successful. New balance: " << account->getBalance() << std::endl;
            } else {
                std::cout << "Account not found." << std::endl;
            }
        } else if (choice == 3) {
            std::string accNum;
            double amount;
            std::cout << "Enter account number: ";
            std::cin >> accNum;

            BankAccount* account = findAccount(accounts, accNum);
            if (account) {
                std::cout << "Enter amount to withdraw: ";
                std::cin >> amount;
                if (std::cin.fail() || amount <= 0) {
                    handleInvalidInput();
                    continue;
                }
                account->withdraw(amount);
                std::cout << "Withdrawal successful. New balance: " << account->getBalance() << std::endl;
            } else {
                std::cout << "Account not found." << std::endl;
            }
        } else if (choice == 4) {
            std::string accNum;
            std::cout << "Enter account number: ";
            std::cin >> accNum;

            BankAccount* account = findAccount(accounts, accNum);
            if (account) {
                BankAccount::printAccount(*account);
            } else {
                std::cout << "Account not found." << std::endl;
            }
        } else if (choice == 5) {
            std::string accNum1, accNum2;
            std::cout << "Enter first account number: ";
            std::cin >> accNum1;
            std::cout << "Enter second account number: ";
            std::cin >> accNum2;

            BankAccount* acc1 = findAccount(accounts, accNum1);
            BankAccount* acc2 = findAccount(accounts, accNum2);

            if (acc1 && acc2) {
                if (*acc1 == *acc2) std::cout << "The accounts have the same account number." << std::endl;
                if (*acc1 < *acc2) std::cout << "Account " << acc1->getAccountNumber() << " has a smaller balance." << std::endl;
                if (*acc1 > *acc2) std::cout << "Account " << acc1->getAccountNumber() << " has a larger balance." << std::endl;
            } else {
                std::cout << "One or both accounts not found." << std::endl;
            }
        } else if (choice == 6) {
            std::string accNum;
            std::cout << "Enter savings account number to calculate interest: ";
            std::cin >> accNum;

            BankAccount* account = findAccount(accounts, accNum);
            if (account) {
                if (SavingAccount* sa = dynamic_cast<SavingAccount*>(account)) {
                    sa->calculateInterest();
                    std::cout << "Interest calculated. New balance: " << sa->getBalance() << std::endl;
                } else {
                    std::cout << "This account is not a savings account." << std::endl;
                }
            } else {
                std::cout << "Account not found." << std::endl;
            }
        } else if (choice == 7) {
            demonstratePolymorphism();
        } else if (choice == 8) {
            std::cout << "Exiting program. Goodbye!" << std::endl;
        } else {
            std::cout << "Invalid choice. Please select a valid option." << std::endl;
        }
    } while (choice != 8);

    return 0;
}