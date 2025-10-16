/**
 * Bank Management System
 * ======================
 * 
 * A simple console-based banking application that demonstrates:
 * - Object-Oriented Programming concepts
 * - Encapsulation and data hiding
 * - Menu-driven interface
 * - Basic banking operations (deposit, withdraw, balance inquiry)
 * 
 * Features:
 * ---------
 * 1. Deposit money into account
 * 2. Withdraw money from account
 * 3. Check account balance
 * 4. Input validation and error handling
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

/**
 * Account class
 * Manages individual bank account operations
 */
class Account
{
private:
    int accountNumber;
    string accountHolder;
    double balance;

public:
    /**
     * Constructor to initialize account
     * @param accNum Account number
     * @param holder Account holder name
     * @param initialBalance Starting balance
     */
    Account(int accNum, string holder, double initialBalance)
    {
        accountNumber = accNum;
        accountHolder = holder;
        balance = initialBalance;
    }

    /**
     * Deposit money into the account
     * @param amount Amount to deposit
     */
    void deposit(double amount)
    {
        if (amount <= 0)
        {
            cout << "\n❌ Error: Deposit amount must be positive!" << endl;
            return;
        }

        balance += amount;
        cout << "\n✅ Successfully deposited: ₹" << fixed << setprecision(2) << amount << endl;
        cout << "💰 New balance: ₹" << balance << endl;
        cout << "Thank you for banking with us!" << endl;
    }

    /**
     * Withdraw money from the account
     * @param amount Amount to withdraw
     */
    void withdraw(double amount)
    {
        if (amount <= 0)
        {
            cout << "\n❌ Error: Withdrawal amount must be positive!" << endl;
            return;
        }

        if (amount > balance)
        {
            cout << "\n❌ Error: Insufficient funds!" << endl;
            cout << "💰 Available balance: ₹" << fixed << setprecision(2) << balance << endl;
            return;
        }

        balance -= amount;
        cout << "\n✅ Successfully withdrawn: ₹" << fixed << setprecision(2) << amount << endl;
        cout << "💰 Remaining balance: ₹" << balance << endl;
        cout << "Thank you for banking with us!" << endl;
    }

    /**
     * Display current account balance
     */
    void checkBalance() const
    {
        cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
        cout << "     ACCOUNT INFORMATION" << endl;
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Current Balance: ₹" << fixed << setprecision(2) << balance << endl;
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    }

    /**
     * Get account holder name
     * @return Account holder name
     */
    string getAccountHolder() const
    {
        return accountHolder;
    }
};

/**
 * Display the main menu
 */
void displayMenu()
{
    cout << "\n╔════════════════════════════════════╗" << endl;
    cout << "║   BANK MANAGEMENT SYSTEM          ║" << endl;
    cout << "╠════════════════════════════════════╣" << endl;
    cout << "║  1. 💵 Deposit Money              ║" << endl;
    cout << "║  2. 💸 Withdraw Money             ║" << endl;
    cout << "║  3. 💰 Check Balance              ║" << endl;
    cout << "║  4. 🚪 Exit                       ║" << endl;
    cout << "╚════════════════════════════════════╝" << endl;
    cout << "Enter your choice (1-4): ";
}

/**
 * Clear input buffer in case of invalid input
 */
void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * Main function
 */
int main()
{
    // Create account with initial details
    Account myAccount(101, "Granth", 1000.0);

    int choice;
    double amount;

    cout << "\n🏦 Welcome to the Bank Management System!" << endl;
    cout << "Account holder: " << myAccount.getAccountHolder() << endl;

    do
    {
        displayMenu();
        cin >> choice;

        // Handle invalid input
        if (cin.fail())
        {
            clearInputBuffer();
            cout << "\n❌ Invalid input! Please enter a number between 1 and 4." << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            cout << "\n💵 Enter the amount to deposit: ₹";
            cin >> amount;

            if (cin.fail())
            {
                clearInputBuffer();
                cout << "\n❌ Invalid amount! Please enter a valid number." << endl;
            }
            else
            {
                myAccount.deposit(amount);
            }
            break;

        case 2:
            cout << "\n💸 Enter the amount to withdraw: ₹";
            cin >> amount;

            if (cin.fail())
            {
                clearInputBuffer();
                cout << "\n❌ Invalid amount! Please enter a valid number." << endl;
            }
            else
            {
                myAccount.withdraw(amount);
            }
            break;

        case 3:
            myAccount.checkBalance();
            break;

        case 4:
            cout << "\n🚪 Thank you for using Bank Management System!" << endl;
            cout << "Exiting program... Goodbye! 👋" << endl;
            break;

        default:
            cout << "\n❌ Error: Invalid choice! Please select 1-4." << endl;
        }

    } while (choice != 4);

    return 0;
}
