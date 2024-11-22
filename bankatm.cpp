#include <iostream>
#include <string>

using namespace std;
class account
{
private:
    int accountnumber;
    string accountholder;
    double balance;

public:
    account(int a, string b, double c)
    {
        accountnumber = a;
        accountholder = b;
        balance = c;
    }
    void deposite(double amount)
    {
        balance += amount;

        cout << "Deposited: ₹" << amount << endl;
        cout << "thank you" << endl;
    }
    void withdraw(double amount)
    {
        balance -= amount;
        cout << "withdrawn :₹" << amount << endl;
        cout << "thank you" << endl;
    }
    void mybalance() const
    {
        cout << "your balance is: ₹ " << balance << endl;
    }
};
int main()
{
    account myaccount(101, "granth", 1000);
    int choice;
    double amount;
    do
    {
        cout << "\nbank managment system:\n";
        cout << "1....deposite\n";
        cout << "2....withdraw\n";
        cout << "3....mybalance\n";
        cout << "4....exit\n";
        cout << "enter your choice:";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "enter the amount to be deposited :₹" << endl;
            cin >> amount;
            myaccount.deposite(amount);
            break;
        case 2:
            cout << "enter the amount to be withdrawn :₹" << endl;
            cin >> amount;
            myaccount.withdraw(amount);
            break;
        case 3:
            myaccount.mybalance();
            break;

        case 4:
            cout << "exiting program" << endl;
            break;

        default:
            cout << "error:not an option" << endl;
        }
    } while (choice != 4);

    return 0;
}