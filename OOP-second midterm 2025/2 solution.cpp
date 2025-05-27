#include <iostream>
using namespace std;

class User {
protected:
    string name;
    string email;
    string password;
    public:
    virtual void print () = 0;
    virtual int calculatePasswordStrength () = 0;
};

class regularUser : public User {
private:
    bool FA;
    public:
    regularUser (const string &name = "", const string &email = "", const string &password = "", bool FA = false) {
        this->name = name;
        this->email = email;
        this->password = password;
        this->FA = FA;
    }
    void print () {
        cout << name << " " << email << " " << password << " ";
        if (FA) {
            cout << "Yes";
        }
        else {
            cout << "No";
        }
        cout << " " << calculatePasswordStrength() << endl;
    }
    int calculatePasswordStrength () {
        int strength = 0;
        if (password.length() >= 8) {
            strength = strength + 1;
        }
        if (isalpha(password[0])) {
            strength = strength + 1;
        }
        if (FA) {
            strength = strength + 1;
        }
        bool found = false;
        for (int i = 1; i < password.length(); i++) {
            if (isdigit(password[i])) {
                found = true;
                break;
            }
        }
        if (found) {
            strength = strength + 2;
        }
        return strength;
    }
};

class adminUser : public User {
private:
    string level;
    bool multiFactorAuth;
    public:
    adminUser (const string &name = "", const string &email = "", const string &password = "", const string &level = "",bool multiFactorAuth = false) {
        this->name = name;
        this->email = email;
        this->password = password;
        this->level = level;
        this->multiFactorAuth = multiFactorAuth;
    }
    void print () {
        cout << name << " " << email << " " << password << " ";
        if (multiFactorAuth) {
            cout << "Yes";
        }
        else {
            cout << "No";
        }
        cout << " " << calculatePasswordStrength() << endl;
    }
    int calculatePasswordStrength () {
        int strength = 0;
        if (password.length() > 10) {
            strength = strength + 1;
        }
        int length = password.length();
        if (isalpha(password [length-1])) {
            strength = strength + 1;
        }
        if (multiFactorAuth) {
            strength = strength + 1;
        }
        if (level == "superuser" || level == "admin") {
            strength = strength + 2;
        }
        return strength;
    }
};

void printAverage (User **array, int n) {
    int sum = 0;
    int counter = 0;
    cout << "Printing regular users: " << endl;
    for (int i = 0; i < n; i++) {
        regularUser *r = dynamic_cast<regularUser *>(array[i]);
        if (r) {
            sum = sum + r->calculatePasswordStrength();
            counter ++;
            r->print();
        }
    }
    cout << endl;
    cout << "Average strength of passwords for regular users: " << sum * 1.0 / counter * 1.0;
}
int main () {
    regularUser *ru1 = new regularUser("Alice", "alice@example.com", "Apass123", true);
    regularUser *ru2 = new regularUser("Bob", "bob@example.com", "b123", false);
    regularUser *ru3 = new regularUser("Charlie", "charlie@example.com", "Charlie789", true);

    adminUser *au1 = new adminUser("Diana", "diana@admin.com", "adminpass123", "admin", true);
    adminUser *au2 = new adminUser("Edward", "edward@admin.com", "Epass", "user", false);
    adminUser *au3 = new adminUser("Frank", "frank@admin.com", "f123super", "superuser", true);

    User *users[6];
    users[0] = ru1;
    users[1] = ru2;
    users[2] = ru3;
    users[3] = au1;
    users[4] = au2;
    users[5] = au3;

    cout << "Printing all users:"<<endl;
    for (int i = 0; i < 6; i++) {
        users[i]->print();
    }

    cout << endl;
    printAverage(users, 6);

    for (int i = 0; i < 6; i++) {
        delete users[i];
    }
    return 0;
}