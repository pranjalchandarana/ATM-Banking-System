# ATM-Banking-System
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Account {
    int accNo;
    int pin;
    double balance;
};

vector<Account> accounts;

void loadAccounts() {
    ifstream file("accounts.txt");
    Account a;
    while (file >> a.accNo >> a.pin >> a.balance) {
        accounts.push_back(a);
    }
    file.close();
}

void saveAccounts() {
    ofstream file("accounts.txt");
    for (auto &a : accounts) {
        file << a.accNo << " " << a.pin << " " << a.balance << endl;
    }
    file.close();
}

int findAccount(int accNo) {
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].accNo == accNo)
            return i;
    }
    return -1;
}

void deposit(int index) {
    double amt;
    cout << "Enter amount to deposit: ";
    cin >> amt;
    accounts[index].balance += amt;
    cout << "Deposit successful\n";
}

void withdraw(int index) {
    double amt;
    cout << "Enter amount to withdraw: ";
    cin >> amt;

    if (amt > accounts[index].balance) {
        cout << "Insufficient balance\n";
    } else {
        accounts[index].balance -= amt;
        cout << "Withdrawal successful\n";
    }
}

void checkBalance(int index) {
    cout << "Current Balance: " << accounts[index].balance << endl;
}

void adminCreateAccount() {
    Account a;
    cout << "Enter new Account Number: ";
    cin >> a.accNo;
    cout << "Set PIN: ";
    cin >> a.pin;
    cout << "Initial Balance: ";
    cin >> a.balance;

    accounts.push_back(a);
    saveAccounts();
    cout << "Account created successfully\n";
}

void userMenu(int index) {
    int choice;
    do {
        cout << "\n1. Deposit\n2. Withdraw\n3. Check Balance\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: deposit(index); break;
            case 2: withdraw(index); break;
            case 3: checkBalance(index); break;
        }

        saveAccounts();

    } while(choice != 4);
}

int main(){
    loadAccounts();
    int choice;
    do{
        cout<<"\n==== ATM SYSTEM ====\n";
        cout<<"1. Login\n2. Admin Create Account\n3. Exit\n";
        cout<<"Enter choice: ";
        cin>>choice;
        if(choice==1){
            int accNo,pin;
            cout<<"Enter Account Number: ";
            cin>>accNo;
            cout<<"Enter PIN: ";
            cin>>pin;
            int index=findAccount(accNo);
            if(index!=-1 && accounts[index].pin==pin){
                cout<<"Login successful\n";
                userMenu(index);
            }else{
                cout<<"Invalid account or PIN\n";
            }
        }
        else if (choice==2) {
            adminCreateAccount();
        }
    } while(choice!= 3);
    return 0;
}
Console-based ATM Banking System built using C++ with PIN authentication, multi-account support, transaction history, and file storage.
