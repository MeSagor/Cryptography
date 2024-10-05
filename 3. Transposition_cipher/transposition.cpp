#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

void printTable(const string& text, int width) {
    int length = text.length();
    int height = ceil((double)length / width);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int index = i * width + j;
            if (index < length)
                cout << text[index] << "  ";
            else
                cout << "-  ";
        }
        cout << endl << endl;
    }
}

string transpositionEncrypt(const string& plaintext, int width) {
    string ciphertext = "";
    int length = plaintext.length();
    int height = ceil((double)length / width);

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            int index = j * width + i;
            if (index < length) {
                ciphertext += plaintext[index];
            } else {
                ciphertext += '-';
            }
        }
    }
    return ciphertext;
}

string transpositionDecrypt(const string& ciphertext, int width) {
    string plaintext = "";
    int length = ciphertext.length();
    int height = ceil((double)length / width);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int index = j * height + i;
            if (index < length && ciphertext[index] != '-')
                plaintext += ciphertext[index];
        }
    }
    return plaintext;
}

int main() {

    ifstream fin("message.txt");
    ofstream fout("cypher.txt");
    ofstream fout2("output.txt");

    string plaintext = "";
    char c;
    while (fin.get(c)) {
        plaintext += c;
    }

    int width;
    cout << "Enter width: ";
    cin >> width;

    cout << "Table: " << endl;
    printTable(plaintext, width);

    string ciphertext = transpositionEncrypt(plaintext, width);
    fout << ciphertext;
    cout << "Ciphertext: " << ciphertext << endl;

    string decryptedText = transpositionDecrypt(ciphertext, width);
    fout2 << decryptedText;
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}
