#include <iostream>
#include <fstream>

using namespace std;

class Song {
private:
    string title;
    string author;
    string performer;
    int time;

public:
    Song(const string &title = "", const string &author = "", const string &performer = "",const int time = 0) {
        this->title = title;
        this->author = author;
        this->performer = performer;
        this->time = time;
    }
    
    friend istream &operator>>(istream &is, Song &s) {
        getline(is, s.title);
        getline(is, s.author);
        getline(is, s.performer);
        is >> s.time;
        return is;
    }
    
    friend ostream &operator<<(ostream &os, const Song &s) {
        os << "Song title: " << s.title << ", Author: " << s.author << ", Interpreted by: " << s.performer << ", " << s.
                time << " sek." << endl;
        return os;
    }

    bool isEqual(Song &s) {
        if (title == s.title && author == s.author && performer == s.performer && time == s.time) {
            return true;
        }
        return false;
    }

    string getAuthor() {
        return author;
    }
};

class Festival {
private:
    string name;
    string city;
    string date;
    Song *array;
    int n;

public:
    Festival(const string &name = "", const string &city = "", const string &date = "",const Song *array = nullptr,const int n = 0) {
        this->name = name;
        this->city = city;
        this->date = date;
        this->n = n;
        this->array = new Song [n];
        for (int i = 0; i < n; i++) {
            if (array) {
                this->array[i] = array[i];
            } else {
                this->array[i] = Song();
            }
        }
    }

    Festival(const Festival &f) {
        this->name = f.name;
        this->city = f.city;
        this->date = f.date;
        this->n = f.n;
        this->array = new Song [n];
        for (int i = 0; i < n; i++) {
            this->array[i] = f.array[i];
        }
    }

    Festival &operator=(const Festival &f) {
        if (this != &f) {
            delete [] array;
            this->name = f.name;
            this->city = f.city;
            this->date = f.date;
            this->n = f.n;
            this->array = new Song [n];
            for (int i = 0; i < n; i++) {
                this->array[i] = f.array[i];
            }
        }
        return *this;
    }

    ~Festival() {
        delete [] array;
    }

    Festival &operator -=(Song &s) {
        if (n == 0) {
            cout << "Trying to delete from an empty list!" << endl;
        } else {
            for (int i = 0; i < n; i++) {
                if (array[i].isEqual(s)) {
                    for (int j = i; j < n - 1; j++) {
                        array[j] = array[j + 1];
                    }
                }
            }
        }
        return *this;
    }

    void print(ofstream &out) {
        out << "Festival: " << name << " - " << city << ", " << date << endl;
        for (int i = 0; i < n; i++) {
            out << array[i];
        }
    }
    
    friend istream &operator>>(istream &is, Festival &f) {
        getline(is, f.name);
        getline(is, f.city);
        getline(is, f.date);
        is >> f.n;
        is.ignore();
        f.array = new Song [f.n];
        for (int i = 0; i < f.n; i++) {
            is >> f.array[i];
            is.ignore();
        }
        return is;
    }

    Festival &operator +=(Song &s) {
        Song *temp = new Song [n + 1];
        for (int i = 0; i < n; i++) {
            temp[i] = array[i];
        }
        temp[n] = s;
        delete [] array;
        array = temp;
        n++;
        return *this;
    }

    Festival notFromAuthor(const string &author) {
        Festival f;
        for (int i = 0; i < n; i++) {
            if (author != array[i].getAuthor()) {
                f += array[i];
            }
        }
        f.name = this->name;
        f.city = this->city;
        f.date = this->date;
        return f;
    }
};

void wtf() {
    ofstream fout("vlezna.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

void rff(const string &path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}

int main() {
    wtf();

    Festival festival;
    //TODO your code here
    //TODO Read the data from the file and store them in `festival`

    ifstream fin("vlezna.txt");
    Festival f;
    fin >> f;
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT
    string author;
    getline(cin, author);
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files izlezna1.txt and izlezna2.txt after this line
    Song s = Song();
    f -= s;
    ofstream fout("izlezna1.txt");
    f.print(fout);
    f = f.notFromAuthor(author);
    ofstream fout2("izlezna2.txt");
    f.print(fout2);
    //DO NOT MODIFY THE CODE BELLOW

    cout << "All the data for the festival:" << endl;
    rff("izlezna1.txt");
    cout << "Songs NOT from the author " << author << ": " << endl;
    rff("izlezna2.txt");


    return 0;
}