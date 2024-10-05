#include <iostream>
#include <fstream>

using namespace std;

string encrypt(string plaintext, string key) {
    string ciphertext = "";
    for (int i = 0; i < plaintext.size(); i++) {
        if (isalpha(plaintext[i])) {
            char start = isupper(plaintext[i]) ? 'A' : 'a';
            char keyStart = isupper(key[i]) ? 'A' : 'a';
            char cipherChar = start + ((plaintext[i] - start + key[i] - keyStart) % 26);
            ciphertext += cipherChar;
        } else {
            ciphertext += plaintext[i];
        }
    }
    return ciphertext;
}

string decrypt(string ciphertext, string key) {
    string plaintext = "";
    for (int i = 0; i < ciphertext.size(); i++) {
        if (isalpha(ciphertext[i])) {
            char start = isupper(ciphertext[i]) ? 'A' : 'a';
            char keyStart = isupper(key[i]) ? 'A' : 'a';
            char plainChar = start + (((ciphertext[i] - start) - (key[i] - keyStart) + 26) % 26);
            plaintext += plainChar;
        } else {
            plaintext += ciphertext[i];
        }
    }
    return plaintext;
}

int main() {
    ifstream key_file("OTP_key.txt");
    ifstream fin("message.txt");
    ofstream fout("cipher.txt");

    string key, plaintext;
    char c;
    while (key_file.get(c)) {
        key += c;
    }
    while (fin.get(c)) {
        plaintext += c;
    }

    cout<< "plaintext: " << plaintext << endl;

    string ciphertext = encrypt(plaintext, key);
    fout << ciphertext;
    cout << "Ciphertext: " << ciphertext << endl;

    string decrypted = decrypt(ciphertext, key);
    cout << "Decrypted: " << decrypted << endl;
}