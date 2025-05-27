#include <iostream>
#include <fstream>
using namespace std;

class User {
private:
    int id;
    string email;
    string name;
    string surname;
    int connections;
    public:
    User(int id = 0,const string &email = "",const string &name = "",const string &surname = "", int connections = 0) {
        this->id = id;
        this->email = email;
        this->name = name;
        this->surname = surname;
        this->connections = connections;
    }
    User &operator -- () {
        if (connections > 0) {
            connections--;
        }
        return *this;
    }
    bool operator >= (const User &other) const{
        return connections >= other.connections;
    }
    friend ostream &operator << (ostream &os, const User &user) {
        os << user.id << " " << user.email << " " << user.name << " " << user.surname << " " << user.connections << endl;
        return os;
    }
    int getId() const {
        return id;
    }
    int getConnections() const {
        return connections;
    }
};

class UserWithIndexNotFound : public exception {
private:
    int id;
    public:
    UserWithIndexNotFound(int id = 0) {
        this->id = id;
    }
    void print () {
        cout << "The user with this id: " << id << " doesnt exist!"<<endl;
    }
};

class UserData {
private:
    User *array;
    int n;
    public:
    UserData (const User *array = nullptr, int n = 0) {
        this-> n = n;
        this -> array = new User[n];
        for (int i = 0; i < n; i++) {
            if (array) {
                this -> array[i] = array[i];
            }
            else {
                this -> array[i] = User();
            }
        }
    }
    UserData (const UserData &u) {
        this-> n = u.n;
        this-> array = new User[n];
        for (int i = 0; i < n; i++) {
            this -> array[i] = u.array[i];
        }
    }
    UserData &operator = (const UserData &u) {
        if (this != &u) {
            delete [] array;
            this-> n = u.n;
            this-> array = new User[n];
            for (int i = 0; i < n; i++) {
                this -> array[i] = u.array[i];
            }
        }
        return *this;
    }
    ~UserData() {
        delete [] array;
    }
    User &operator [] (int id) {
        for (int i=0; i<n; i++) {
            if (array[i].getId() == id) {
                return array[i];
            }
        }
        throw UserWithIndexNotFound(id);
    }
    UserData &operator += (const User &u) {
        User *temp = new User[n+1];
        for (int i=0; i<n; i++) {
            temp[i] = array[i];
        }
        temp[n]=u;
        delete [] array;
        array = temp;
        n++;
        return *this;
    }
    UserData filterByConnections (int connections) {
        UserData temp;
        for (int i = 0; i < n; i++) {
            if (connections == array[i].getConnections()) {
                temp+=array[i];
            }
        }
        return temp;
    }
    friend ostream &operator << (ostream &os, const UserData &u) {
        if (u.n == 0) {
            cout << "UserData is empty!" << endl;
        }
        for (int i=0; i<u.n; i++) {
            cout << u.array[i] ;
        }
        return os;
    }
};

User ReadUser (ifstream &in) {
    int id;
    string email;
    string name;
    string surname;
    int connections;
    in >> id;
    in.ignore();
    getline (in, email);
    getline (in, name);
    getline (in, surname);
    in >> connections;
    in.ignore();
    User user(id, email, name, surname, connections);
    return user;
}

void wtf() {
    ofstream fout("input.txt");
    string line;
    line = "1";
    fout << line << endl;
    line = "Frist email ";
    fout << line << endl;
    line = "First name";
    fout << line << endl;
    line = "First surname";
    fout << line << endl;
    line = "20";
    fout << line << endl;
    //----------------
    line = "2";
    fout << line << endl;
    line = "Second email ";
    fout << line << endl;
    line = "Second name";
    fout << line << endl;
    line = "Second surname";
    fout << line << endl;
    line = "30";
    fout << line << endl;
    //--------------------------
    line = "3";
    fout << line << endl;
    line = "Third email ";
    fout << line << endl;
    line = "Third name";
    fout << line << endl;
    line = "Third surname";
    fout << line << endl;
    line = "40";
    fout << line << endl;
}

void rff(const string &path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}

int main () {
    User u1 = User (1,"email","john","jhony",10);
    cout<<u1;
    --u1;
    cout<<u1;
    User u2 = User (2, "john","jhony","john",20);
    cout<<u2;
    cout<<(u1>=u2)<<endl;
    User u3 = User (3, "john","jhony","john",30);
    User u4 = User (4, "john","jhony","john",40);
    User u5 = User (5, "john","jhony","john",50);
    UserData users;
    users+=u1;
    users+=u2;
    users+=u3;
    users+=u4;
    users+=u5;
    cout<<"-----------------------------"<<endl;
    cout<<users;
    cout<<"-----------------------------"<<endl;
    try {
        cout<<users[1];
    }catch (UserWithIndexNotFound &u) {
        u.print();
    }
    try {
        cout<<users[10];
    }catch (UserWithIndexNotFound &u) {
        u.print();
    }
    User u6 = User (6, "john","jhony","john",60);
    User u7 = User (7, "john","jhony","john",60);
    User u8 = User (8, "john","jhony","john",60);
    users+=u6;
    users+=u7;
    users+=u8;
    UserData filtered = users.filterByConnections(60);
    cout<<"------------------------------------"<<endl;
    cout<<filtered;
    cout<<"------------------------------------"<<endl;
    wtf ();
    ofstream fout ("output.txt");
    ifstream fin ("input.txt");
    UserData temp2;
    while (true) {
        if (fin.peek() == EOF) break;
        User u = ReadUser(fin);
        temp2 += u;
    }
    fin.close();
    --temp2[1];
    fout << temp2;
    fout.close();
    rff("output.txt");
    return 0;
}