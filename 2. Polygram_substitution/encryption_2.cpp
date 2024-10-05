#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, string> en_dictionary, de_dictionary;

void createDictionary() {
    ifstream dicin("dictionary.txt");
    unordered_map<string, string> dictionary;
    string key, value;
    while (dicin >> key >> value) {
        en_dictionary[key] = value;
        de_dictionary[value] = key;
    }
}

string Encrypter(string plaintext) {
    string cipher = "";
    string word = "";
    for (char ch : plaintext) {
        if (isalpha(ch)) {
            word += ch;
            if (en_dictionary.find(word) != en_dictionary.end()) {
                cipher += en_dictionary[word];
                word = "";
            }
        } else {
            cipher += ch;
        }
    }
    return cipher;
}

string Decrypter(string cyphertext) {
    string plaintext = "";
    string word = "";
    for (char ch : cyphertext) {
        if (isalpha(ch)) {
            word += ch;
            if (de_dictionary.find(word) != de_dictionary.end()) {
                plaintext += de_dictionary[word];
                word = "";
            }
        } else {
            plaintext += ch;
        }
    }
    return plaintext;
}


int main() {
    createDictionary();

    ifstream fin("message.txt");
    ofstream fout("cipher.txt");
    ofstream fout2("output.txt");

    string plaintext;
    char c;
    while (fin.get(c)) {
        plaintext += c;
    }

    string cyphertext = Encrypter(plaintext);
    fout << cyphertext;

    string decrypted = Decrypter(cyphertext);
    fout2 << decrypted;

}