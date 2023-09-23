#include<iostream>
#include<string>
using namespace std;

class Person {
private:
    string name, ID, address;
    int contact;
    float cash;
    static int stat;

public:
    // Constructor
    Person() : name(""), ID(""), address(""), contact(0), cash(0.0) {
        stat++;
    }

    // Friend functions
    friend ostream& operator<<(ostream& out, const Person& p);
    friend void inputData(Person& p);
    // friend void showData(const Person& p);

    // Inline function
    void deposit(int amount) {
        cash += amount;
    }
    
    //Function overload
    void deposit(float amt) {
        cash += amt;
    }

    //this pointer
    void dep(float cash, int amount){
        this->cash = cash + amount;
    }

    bool withdraw(int amount) {
        if (cash >= amount) {
            cash -= amount;
            return true;
        }
        return false;
    }

    string getID() const {
        return ID;
    }

    // Static function to display count
    static void displayCount() {
        cout << "Total accounts: " << stat << endl;
    }

};

int Person::stat = 0;

//Derived class NOT TO BE INCLUDED JUST SHOWING DESTRUCTOR
class People: public Person{
  public:
//Destructor
    ~People(){
        cout<<"derived class destroyed";
    }

};

//operator overload
ostream& operator<<(ostream& out, const Person& p) {
    out << "Name: " << p.name << endl;
    out << "ID: " << p.ID << endl;
    out << "Address: " << p.address << endl;
    out << "Contact: " << p.contact << endl;
    out << "Cash: " << p.cash << endl;
    return out;
}
void showData(const Person& p) {
    cout << p;
}

void inputData(Person& p) {
     cin.ignore();
     cout << "Enter name: ";
     getline(cin, p.name);
     cout << "ID: ";
     cin >> p.ID;
     cin.ignore();
     cout << "Address: ";
     getline(cin, p.address);
     cout << "Contact: ";
     cin >> p.contact;
     cin.ignore();
     cout << "Total Cash: ";
     cin >> p.cash;
 }

// void showData(const Person& p) {
//     cout << "Name: " << p.name << endl;
//     cout << "ID: " << p.ID << endl;
//     cout << "Address: " << p.address << endl;
//     cout << "Contact: " << p.contact << endl;
//     cout << "Cash: " << p.cash << endl;
// }

class Bank {
private:
    Person persons[100];
    int total;

public:
    Bank() : total(0) {}

    void choice();
    void createAccount();
    void showAccounts();
    void updateAccount();
    void viewAccount();
    void transactions();
    void deleteAccount();
};

void Bank::choice() {
    char option;
    do {
        cout << "\nMenu:\n";
        cout << "1. Create new account\n";
        cout << "2. View customers list\n";
        cout << "3. Update account\n";
        cout << "4. View account details\n";
        cout << "5. Transactions\n";
        cout << "6. Delete account\n";
        cout << "7. Display total accounts\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case '1': createAccount(); break;
            case '2': showAccounts(); break;
            case '3': updateAccount(); break;
            case '4': viewAccount(); break;
            case '5': transactions(); break;
            case '6': deleteAccount(); break;
            case '7': Person::displayCount(); break;
            case '8': break;
            default: cout << "Invalid choice.\n";
        }
    } while (option != '8');
}

void Bank::createAccount() {
    if (total < 100) {
        inputData(persons[total]);
        total++;
    } else {
        cout << "Bank capacity full. Can't create more accounts." << endl;
    }
}

void Bank::showAccounts() {
    for (int i = 0; i < total; ++i) {
        showData(persons[i]);
    }
}

void Bank::updateAccount() {
    string id;
    cout << "Enter ID of the account you wish to update: ";
    cin >> id;
    for (int i = 0; i < total; ++i) {
        if (persons[i].getID() == id) {
            cout << "Enter new data:\n";
            inputData(persons[i]);
            return;
        }
    }
    cout << "Account not found.\n";
}

void Bank::viewAccount() {
    string id;
    cout << "Enter ID of the account you wish to view: ";
    cin >> id;
    for (int i = 0; i < total; ++i) {
        if (persons[i].getID() == id) {
            showData(persons[i]);
            return;
        }
    }
    cout << "Account not found.\n";
}

void Bank::transactions() {
    string id;
    int amount;
    char transOption;
    cout << "Enter ID of the account for transaction: ";
    cin >> id;
    for (int i = 0; i < total; ++i) {
        if (persons[i].getID() == id) {
            cout << "Enter (d)eposit or (w)ithdraw: ";
            cin >> transOption;
            if (transOption == 'd') {
                cout << "Enter amount to deposit: ";
                cin >> amount;
                persons[i].deposit(amount);
            } else if (transOption == 'w') {
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                if (!persons[i].withdraw(amount)) {
                    cout << "Insufficient funds.\n";
                    return;
                }
            } else {
                cout << "Invalid option.\n";
                return;
            }
            cout << "Transaction successful.\n";
            return;
        }
    }
    cout << "Account not found.\n";
}

void Bank::deleteAccount() {
    string id;
    cout << "Enter ID of the account you wish to delete: ";
    cin >> id;
    for (int i = 0; i < total; ++i) {
        if (persons[i].getID() == id) {
            for (int j = i; j < total - 1; ++j) {
                persons[j] = persons[j + 1];
            }
            total--;
            cout << "Account deleted successfully.\n";
            return;
        }
    }
    cout << "Account not found.\n";
}

int main() {
    People *p3= new People;
    delete p3;
    People p4;
    cout <<endl<<endl<< "Banking Management System" << endl;
    cout<<p4<<endl<<endl;
    Bank bank;
    bank.choice();
    return 0;
   
}
