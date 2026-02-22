// Programmer: [Gael Garcia Guzman]
// Date:       [1/31/2026]
// Purpose:    Bank Account Management System

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "BankAccount.h"

// Beginning of Program

// Function to display the main menu
void displayMenu() {
    std::cout << "\n--- Bank Account Menu ---" << std::endl;
    std::cout << "1. Create a new account" << std::endl;
    std::cout << "2. Deposit money" << std::endl;
    std::cout << "3. Withdraw money" << std::endl;
    std::cout << "4. Display account details" << std::endl;
    std::cout << "5. Compare two accounts" << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

// Function to find an account by its number
// Returns a pointer to the account if found, otherwise nullptr
BankAccount* findAccount(std::vector<BankAccount>& accounts, const std::string& accNum) {
    for (auto& account : accounts) {
        if (account.getAccountNumber() == accNum) {
            return &account;
        }
    }
    return nullptr;
}

// Function to handle invalid input and clear the input buffer
void handleInvalidInput() {
    std::cout << "Invalid input. Please try again." << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    // Vector to store bank accounts
    std::vector<BankAccount> accounts;
    int choice;
// Main loop for the program
    do {
        displayMenu();
        std::cin >> choice;

        // Input validation for menu choice
        if (std::cin.fail()) {
            handleInvalidInput();
            choice = 0; // Reset choice to avoid exiting
            continue;
        }
// Handle menu options
// create a new account
        if (choice == 1) {
            // Consume the newline character left by `std::cin >> choice;`
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Use the static method to encapsulate account creation logic
            BankAccount newAccount = BankAccount::createAccountFromInput();

            // Check for duplicates before adding
            if (findAccount(accounts, newAccount.getAccountNumber())) {
                std::cout << "An account with this number already exists." << std::endl;
            } else {
                accounts.push_back(newAccount); // Add the new account to the vector
                std::cout << "Account created successfully." << std::endl;
            }
// Deposit Money
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
                *account += amount; // Use the overloaded += operator
                std::cout << "Deposit successful. New balance: " << account->getBalance() << std::endl;
            } else {
                std::cout << "Account not found." << std::endl;
            }
// Withdraw Money
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
                *account -= amount; // Use the overloaded -= operator
                std::cout << "Withdrawal successful. New balance: " << account->getBalance() << std::endl;
            } else {
                std::cout << "Account not found." << std::endl;
            }
// Display Account Details
        } else if (choice == 4) {
            std::string accNum;
            std::cout << "Enter account number: ";
            std::cin >> accNum;

            BankAccount* account = findAccount(accounts, accNum);
            if (account) {
                // Use the static print method for clean, consistent output
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
                // Demonstrate the overloaded comparison operators
                if (*acc1 == *acc2) {
                    std::cout << "The accounts have the same account number." << std::endl;
                }
                if (*acc1 < *acc2) {
                    std::cout << "Account " << acc1->getAccountNumber() << " has a smaller balance than account " << acc2->getAccountNumber() << "." << std::endl;
                }
                if (*acc1 > *acc2) {
                    std::cout << "Account " << acc1->getAccountNumber() << " has a larger balance than account " << acc2->getAccountNumber() << "." << std::endl;
                }
            } else {
                std::cout << "One or both accounts not found." << std::endl;
            }
            // Exit the program
        } else if (choice == 6) {
            std::cout << "Exiting program. Goodbye!" << std::endl;
        } else {
            std::cout << "Invalid choice. Please select a valid option." << std::endl;
        }
    } while (choice != 6);
    return 0;
}

// End of Program