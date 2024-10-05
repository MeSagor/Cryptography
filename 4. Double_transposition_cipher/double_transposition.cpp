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

string transpositionEncrypt(const string& plaintext, int width, char fill) {
    string ciphertext = "";
    int length = plaintext.length();
    int height = ceil((double)length / width);

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            int index = j * width + i;
            if (index < length) {
                ciphertext += plaintext[index];
            } else {
                ciphertext += fill;
            }
        }
    }
    return ciphertext;
}

string transpositionDecrypt(const string& ciphertext, int width, char fill) {
    string plaintext = "";
    int length = ciphertext.length();
    int height = ceil((double)length / width);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int index = j * height + i;
            if (index < length && ciphertext[index] != fill)
                plaintext += ciphertext[index];
        }
    }
    return plaintext;
}

int main() {

    ifstream fin("message.txt");
    ofstream fout("cypher.txt");
    ofstream fout2("decrypted.txt");

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

    string ciphertext1 = transpositionEncrypt(plaintext, width, '-');
    cout << "Ciphertext #1: " << ciphertext1 << endl;

    string ciphertext2 = transpositionEncrypt(ciphertext1, width, '*');
    fout << ciphertext2;
    cout << "Ciphertext #2: " << ciphertext2 << endl;

    string decryptedText2 = transpositionDecrypt(ciphertext2, width, '*');
    cout << "Decrypted text #1: " << decryptedText2 << endl;

    string decryptedText1 = transpositionDecrypt(decryptedText2, width, '-');
    fout2 << decryptedText1;
    cout << "Decrypted text #2: " << decryptedText1 << endl;

    return 0;
}
