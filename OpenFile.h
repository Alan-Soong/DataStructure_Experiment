#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
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