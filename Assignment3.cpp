/*
CMPS 385-Data Structures
Aditya Singh
September 17,2025
Assignment 3:Bank Account system
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

//Base Class with virtual methods and shared fields 
class Account {
protected:
    string name;
    int number;
    double balance;
public:
    Account(string n, int num, double b)
    {
        name = n; number = num; balance = b;
    }

    int getNumber()
        const {
        return number;
    }
    string getName()
        const {
        return name;
    }

    // polymorphism
    //Same function name can perform different actions of object
    virtual void deposit(double amount)
    {
        balance = balance + amount;
    }
    virtual bool withdraw(double amount) {
        if (amount <= balance) { balance = balance - amount; return true; }
        return false;
    }
    virtual void showBalance() const {
        cout << "Your current balance is $" << balance << ".\n";
    }
};

//Derived class will inherit account
class CheckingAccount : public Account {
public:
    CheckingAccount(string n, int num, double bal) :
        Account(n, num, bal) {
    }
};

const int max_acc = 100;
Account* bank[max_acc];
int countAccounts = 0;


//returns array index for account number
// otherwise -1 if not found
int findIndexByNumber(int num) {
    int index = 0;
    while (index < countAccounts) {
        if (bank[index]->getNumber() == num) { return index; }
        index = index + 1;
    }
    return -1;
}

//This make Accout Number makes it so 
//theres always a unique number 1-999999
//Reruns the code if same numbers match
int makeAccountNumber() {
    int number = 0;
    do { number = 100000 + (rand() % 900000); }
    while (findIndexByNumber(number) != -1);
    return number;
}


//Simple function to return to the main menu
void MenuPause() {
    cout << "Press any key to return to Main Menu !\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
//Main program which loops and uses users inputs
int main() {
    srand((unsigned)time(0));

    while (true) {
        cout << "********Welcome To Chase********\n\n";
        cout << "1.Create a new bank account with an initial balance\n";
        cout << "2.Deposit money to an account\n";
        cout << "3.withdraw money from an account\n";
        cout << "4.Display Current Balance from an account\n";


        int choice; 
        if (!(cin >> choice))
        { return 0; }

        if (choice == 1) {
            if (countAccounts >= max_acc) 
            { cout << "The max amount of accounts have been reached you cannot make more!\n\n"; MenuPause(); continue; }
            string n;
            double initBal;
            cout << "Enter your name:  ";
            //Clears the leftover newLine(used many times)
            cin.ignore();
            getline(cin, n);
            cout << "Enter your initial balance:  ";
            cin >> initBal;

            int num = makeAccountNumber();
            bank[countAccounts] = new CheckingAccount(n, num, initBal);
            countAccounts++;

            cout << "Congratulations " << n << "! You have successfully opened a new bank account. "
                << "with an initial balance of (" << initBal << ") Dollars. Your account number will be " << num << ".\n\n";
            MenuPause();
        }
        else if (choice == 2) {
            int num; cout << "Enter your account number: "; cin >> num;
            int index = findIndexByNumber(num);
            if (index == -1) { cout << "This account number does not exist sorry.\n\n"; 
            MenuPause();
            continue; }

            double amount;
            cout << "Enter the amount that you would like to deposit: ";
            cin >> amount;
            bank[index]->deposit(amount);

            cout << "Congratulations !!!" << bank[index]->getName()
            << " You have successfully deposited the amount of $" << amount
            << " in your account #" << num << ". \n";
            bank[index]->showBalance();
            MenuPause();
        }
        else if (choice == 3) {
            int num; cout << "Enter the account number: "; cin >> num;
            int index = findIndexByNumber(num);
            if (index == -1) { cout << "No account number exists!\n\n"; MenuPause(); continue; }

            double amount; cout << "Enter the amount that you would like to withdraw: ";
            cin >> amount;
            bool amt = bank[index]->withdraw(amount);
            if (amt) {
                cout << "Congratulations " << bank[index]->getName()
                    << "! You have successfully withdrawn the amount of $" << amount
                    << " in your account #" << num << ". ";
                bank[index]->showBalance();
            }
            else {
                cout << "Withdrawal failed. You cannot withdraw this amount.\n";
            }
            MenuPause();
        }
        else if (choice == 4) {
            int num; cout << "Enter the account number: ";
            cin >> num;
            int index = findIndexByNumber(num);
            if (index == -1) { cout << "No account number exists!\n\n";
            MenuPause();
            continue; }

            bank[index]->showBalance();
            cout << "\n";
            MenuPause();
        }
        else {
            cout << "Invalid option.\n\n";
            MenuPause();
        }
    }
    return 0;
}
