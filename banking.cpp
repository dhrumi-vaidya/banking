// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <map>
// using namespace std;
// class Account
// {
// private:
//     int ac_no;
//     float balance;
//     string fname, lname;
//     static int nextacNo;

// public:
//     Account() {};
//     Account(string fname, string lname, float balance);
//     int getAccountNo() { return ac_no; };
//     float getBalance() { return balance; };
//     string getFname() { return fname; };
//     string getLname() { return lname; };

//     void Deposit(float amount);
//     void Withdraw(float amount);
//     static void setLastAcNO(int ac_no);
//     static int getAcNo();
//     friend ofstream &operator<<(ofstream &ofs, Account acc);
//     friend ifstream &operator>>(ifstream &ifs, Account acc);
// };
// int Account::nextacNo = 0;
// class Bank
// {
// private:
//     map<int, Account> accounts;

// public:
//     Bank();
//     Account openAccount(string fname, string lname, int balance);
//     Account balanceEnquiry(int ac_no);
//     Account Deposit(int ac_no, float amount);
//     Account Withdraw(int ac_no, float amount);
//     void showAllDetails();
//     void closeAccount(int ac_no);
//     ~Bank();
// };

// void Account :: Deposit(int ac_no , float amount )

// int main()
// {
//     Account ac;
//     bank b;
//     int balance;
//     string fname, lname;
//     int amount;
//     int ac_no;
//     int choices;

//     do
//     {

//         cout << "Select an operation: " << endl;
//         cout << "1.) Open an Account" << endl;
//         cout << "2.) Balance Enquiry" << endl;
//         cout << "3.) Deposit Money " << endl;
//         cout << "4.) Withdraw Money " << endl;
//         cout << "5.) View  Account Details" << endl;
//         cout << "6.) Close an Account " << endl;
//         cout << "7.) Quit" << endl;
//         cin >> choices;

//         switch (choices)
//         {
//         case 1:
//             cout << "Operation : Open Account" << endl;
//             cout<<"Enter your First Name: ";
//             cin>> fname;
//             cout<<endl;
//             cout<< "Enter your Last Name : ";
//             cin >> lname;
//             cout<<endl;
//             cout<<" Enter Balance : ";
//             cin>>balance;
//             cout<<endl;
//             ac = b.
//             cout << "CONGRATULATIONS !!! Account Created Successfully " << endl;
//             break;
//         case 2:
//             cout << "Operation : Balance Enquiry" << endl;

//             break;
//         case 3:
//             cout << "Operation : Deposit Money" << endl;

//             break;
//         case 4:
//             cout << "Operation : Withdraw Money" << endl;

//             break;
//         case 5:
//             cout << "Operation : View Ac Details" << endl;

//             break;
//         case 6:
//             cout << "Operation : Close Account" << endl;

//             break;
//         case 7:
//             cout << "Operation : Quit" << endl;

//             break;
//         default:
//             cout << "Choose a valid operation" << endl;
//             break;
//         }
//     } while (choices != 7);
//     return 0;
// }

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
