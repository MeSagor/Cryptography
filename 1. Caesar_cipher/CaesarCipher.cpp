#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string Encrypter(string plaintext, int shift) {
    string ans = "";
    for (char ch : plaintext) {
        if (isalpha(ch)) {
            char start = islower(ch) ? 'a' : 'A';

            char cy_ch = start + ((ch - start + shift) % 26);
            ans += cy_ch;
        } else {
            ans += ch;
        }
    }
    return ans;
}

string Decrypter(string cyphertext, int shift) {
    return Encrypter(cyphertext, 26 - shift);
}

int main() {
    ifstream fin("message.txt");
    ofstream fout("cypher.txt");
    ofstream fout2("output.txt");

    string plaintext;
    char c;
    while (fin.get(c)) {
        plaintext += c;
    }

    int shift = 3;
    string cyphertext = Encrypter(plaintext, shift);
    fout << cyphertext;

    string decrypted = Decrypter(cyphertext, shift);
    fout2 << decrypted;
}