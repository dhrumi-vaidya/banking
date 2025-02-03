

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Account
{
private:
    int ac_no;
    string c_name;
    int balance;

    static int next_ac_no;

public:
    Account() : ac_no(0), c_name(""), balance(0) {}

    void openAccount()
    {
        ac_no = next_ac_no++;
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, c_name);
        cout << "Enter initial balance: ";
        cin >> balance;

        ofstream ofs("Account.txt", ios::app);
        ofs << ac_no << " " << c_name << " " << balance << endl;
        ofs.close();

        cout << "Account created successfully! Your account number is: " << ac_no << endl;
    }

    void balanceEnquiry(int account_no)
    {
        ifstream ifs("Account.txt");
        bool found = false;
        while (ifs >> ac_no >> c_name >> balance)
        {
            if (ac_no == account_no)
            {
                cout << "Account found! Current balance: " << balance << endl;
                found = true;
                break;
            }
        }
        ifs.close();

        if (!found)
        {
            cout << "Account not found!" << endl;
        }
    }

    void deposit(int account_no, int amount)
    {
        ifstream ifs("Account.txt");
        ofstream ofs("Temp.txt");

        // bool found = false;
        while (ifs >> ac_no >> c_name >> balance)
        {
            if (ac_no == account_no)
            {
                balance += amount;
                // found = true;
                cout << "Deposit successful! New balance: " << balance << endl;
            }
            ofs << ac_no << " " << c_name << " " << balance << endl;
        }
        ifs.close();
        ofs.close();

        remove("Account.txt");
        rename("Temp.txt", "Account.txt");

        // if (!found)
        // {
        //     cout << "Account not found!" << endl;
        // }
    }

    void withdraw(int account_no, int amount)
    {
        ifstream ifs("Account.txt");
        ofstream ofs("Temp.txt");

        bool found = false;
        while (ifs >> ac_no >> c_name >> balance)
        {
            if (ac_no == account_no)
            {
                if (balance >= amount)
                {
                    balance -= amount;
                    cout << "Withdrawal successful! New balance: " << balance << endl;
                }
                else
                {
                    cout << "Insufficient balance!" << endl;
                }
                found = true;
            }
            ofs << ac_no << " " << c_name << " " << balance << endl;
        }
        ifs.close();
        ofs.close();

        remove("Account.txt");
        rename("Temp.txt", "Account.txt");

        if (!found)
        {
            cout << "Account not found!" << endl;
        }
    }

    void displayAllAccounts()
    {
        ifstream ifs("Account.txt");
        cout << "All Accounts:\n";
        cout << "--------------------------------------\n";
        while (ifs >> ac_no >> c_name >> balance)
        {
            cout << "Account No: " << ac_no << ", Name: " << c_name << ", Balance: " << balance << endl;
        }
        ifs.close();
    }
};

// Initialize static variable
int Account::next_ac_no = 1;

int main()
{
    Account account;
    int choice, account_no, amount;

    do
    {
        cout << "\nSelect an operation:\n";
        cout << "1. Open Account\n2. Balance Enquiry\n3. Deposit\n4. Withdraw\n5. View All Accounts\n6. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            account.openAccount();
            break;

        case 2:
            cout << "Enter account number: ";
            cin >> account_no;
            account.balanceEnquiry(account_no);
            break;

        case 3:
            cout << "Enter account number: ";
            cin >> account_no;
            cout << "Enter deposit amount: ";
            cin >> amount;
            account.deposit(account_no, amount);
            break;

        case 4:
            cout << "Enter account number: ";
            cin >> account_no;
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            account.withdraw(account_no, amount);
            break;

        case 5:
            account.displayAllAccounts();
            break;

        case 6:
            cout << "Exiting... Thank you!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
