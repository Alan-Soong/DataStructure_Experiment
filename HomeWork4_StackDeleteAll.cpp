#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include"Self_Stack.h"
using namespace std;

string openfile() {
    ifstream file("example.txt");
    string words;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            char word;
            while (iss >> word) {
                words.push_back(word);
            }
        }
        file.close();
        return words;
    }
    else {
        cout << "Unable to open file";
        string str0;
        return str0;
    }
}


void delete_all(LinkedStack<char>& s, const char& x) {
    while (!s.isEmpty()) {
        if (s.top() != x) {
            cout << s.top();
            if (!s.isEmpty()) {
                cout << " ";
            }
        }
        s.pop();
    }
    cout << endl;
}

int main() {
    string str = openfile();
    LinkedStack<char> con;
    char sel = str[0];
    for (int i = 1; i < str.size(); i++) {
        con.push(str[i]);
    }
    delete_all(con, sel);
    return 0;
}