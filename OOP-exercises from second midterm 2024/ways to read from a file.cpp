#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
using namespace std;

void WTF () {
    ofstream fout ("input.txt");
    if (!fout.is_open()) {
        cout << "Error opening the file " << endl;
        return;
    }
    fout << "Writing to a file using a global function" << endl;
    fout << "Second line for some of the test cases" << endl;
    fout << "Third line for testing" << endl;
    fout << "Fourth line to make sure the test case works" << endl;
}

void RFF (const string &fname) {
    string something ;

    ifstream fin (fname);

    if (!fin.is_open()) {
        cout << "Error opening the file " << endl;
        return;
    }

    while (getline (fin, something)) {

        cout << something << endl;

    }

    cout << "-----------------------" << endl;
}

int main() {
    WTF ();
    RFF ("input.txt");

    ifstream fin ("input.txt");

    int n;
    cin >> n;

    if (n == 1) {
        //reading from a file character by character
        char character;
        while (fin.get(character)) {
            cout << character << endl;
        }
    }

    if (n == 2) {
        //reading from a file word by word
        string word;
        while (fin >> word) {
            cout << word << endl;
        }
    }

    if (n == 3) {
        //reading from a file line by line
        string line;
        while (getline (fin, line)) {
            cout << line << endl;
        }
    }

    if (n == 4) {
        //reading from a file line by line, and then reading each line character by character
        string line;
        while (getline (fin, line)) {
            cout << line << endl;
            for (int i = 0; i < line.length(); i++) {
                cout << line[i] << endl;
            }
        }
    }

    if (n == 5) {
        //reading from a file line by line, and then reading each line word by word
        string line;
        while (getline (fin, line)) {
            cout << line << endl;
            stringstream ss(line);
            string word;
            while (ss >> word) {
                cout << word << endl;
            }
        }
    }

    //alternative solution for case 5, without using stringstream, using string
    // if (n == 5) {
    //     //reading from a file line by line, and then reading each line word by word
    //     string line;
    //     while (getline (fin, line)) {
    //         cout << line << endl;
    //         string word;
    //         for (int i = 0; i < line.length(); i++) {
    //             if (line[i] != ' ') {
    //                 word += line[i];
    //             }
    //             else {
    //                 cout << word << endl;
    //                 word = "";
    //             }
    //         }
    //         if (word != "") {
    //             cout << word << endl;
    //         }
    //     }
    // }

    //alternative solution for case 5, without using stringstream, using char
    // if (n == 5) {
    //     //reading from a file line by line, and then reading each line word by word
    //     string line;
    //     while (getline (fin, line)) {
    //         cout << line << endl;
    //         char word [100];
    //         int counter = 0;
    //         for (int i = 0; i < line.length(); i++) {
    //             if (line[i] != ' ') {
    //                 word[counter] = line[i];
    //                 counter++;
    //             }
    //             else {
    //                 word [counter] = '\0';
    //                 cout << word << endl;
    //                 counter = 0;
    //             }
    //         }
    //         if (word) {
    //             word [counter] = '\0';
    //             cout << word << endl;
    //         }
    //     }
    // }

    if (n == 6) {
        //reading from a file until we read a set character
        char character;
        while (fin.get(character) && character != 'e') {
            cout << character << endl;
        }
    }

    if (n == 7) {
        //reading from a file until we read a set word
        string word;
        while (fin >> word && word != "line") {
            cout << word << endl;
        }
    }

    if (n == 8) {
        //reading from a file until we read a set line
        string line;
        while (getline (fin,line) && line != "Third line for testing") {
            cout << line << endl;
        }
    }

    return 0;
}
