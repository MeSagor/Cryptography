#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long modInverse(long long a, long long m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

void generateKeys(int& n, int& e, int& d, int p, int q) {
    n = p * q;
    int phi = (p - 1) * (q - 1);
    e = 2;
    while (e < phi) {
        if (gcd(e, phi) == 1) break;
        e++;
    }
    d = modInverse(e, phi);
}



long long bigMod(long long b, long long p, long long m) {
    if (p == 0) return 1;

    long long res = 1;
    while (p > 0) {
        if ((p & 1) == 1) res = (res * b) % m;
        p /= 2;
        b = (b * b) % m;
    }
    return res % m;
}


long long encrypt(long long plaintext, long long e, long long n) {
    return bigMod(plaintext, e, n);
}

long long decrypt(long long ciphertext, long long d, long long n) {
    return bigMod(ciphertext, d, n);
}



int main() {
    int n, e, d;
    int p = 47, q = 71;
    generateKeys(n, e, d, p, q);
    cout << "Public key: (" << e << ", " << n << ")" << endl;
    cout << "Private key: (" << d << ", " << n << ")" << endl << endl;;


    ifstream fin("message.txt");
    ofstream fout("cipher.txt");
    ofstream fout2("output.txt");

    string plaintext;
    char c;
    while (fin.get(c)) {
        plaintext += c;
    }
    cout << "plaintext: " << plaintext << endl;

    int chunkSize = to_string(n).size() - 1;

    vector<long long> chunksMessage, chunksCipher;
    vector<int> chunksLength;

    for (int i = 0; i < plaintext.size(); i += chunkSize) {
        string chunk = plaintext.substr(i, chunkSize);
        chunksMessage.push_back(stoll(chunk));
        chunksLength.push_back(chunk.size());
    }

    cout << "Cipher text: ";
    for (long long chunk : chunksMessage) {
        long long ciphertext = encrypt(chunk, e, n);
        chunksCipher.push_back(ciphertext);
        cout << ciphertext << " ";
        fout << ciphertext << " ";
    }
    cout << endl;

    cout << "Decrypted text: ";
    for (int i = 0; i < chunksCipher.size(); i++) {
        long long decrypted_long = decrypt(chunksCipher[i], d, n);
        string decrypted = to_string(decrypted_long);
        decrypted = string(chunksLength[i] - decrypted.size(), '0') + decrypted;
        cout << decrypted << ' ';
        fout2 << decrypted;
    }
    cout << endl;
}
