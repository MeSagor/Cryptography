#include <iostream>
#include <vector>
#include <fstream>
#include <time.h> 

using namespace std;

int main() {
    string vocabulary = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    vector<string> combinations, replacements;
    for (int length = 1; length <= 4; length++) {
        if (length == 1) {
            for (char c1 : vocabulary) {
                string word = "";
                word += c1;
                combinations.push_back(word);
            }
        } else if (length == 2) {
            for (char c1 : vocabulary) {
                for (char c2 : vocabulary) {
                    string word = "";
                    word += c1;
                    word += c2;
                    combinations.push_back(word);
                }
            }
        } else if (length == 3) {
            for (char c1 : vocabulary) {
                for (char c2 : vocabulary) {
                    for (char c3 : vocabulary) {
                        string word = "";
                        word += c1;
                        word += c2;
                        word += c3;
                        combinations.push_back(word);
                    }
                }
            }
        } else if (length == 4) {
            for (char c1 : vocabulary) {
                for (char c2 : vocabulary) {
                    for (char c3 : vocabulary) {
                        for (char c4 : vocabulary) {
                            string word = "";
                            word += c1;
                            word += c2;
                            word += c3;
                            word += c4;
                            replacements.push_back(word);
                        }
                    }
                }
            }
        }
    }


ofstream fout("dictionary.txt");

srand(time(0));
int randIdx = rand() % replacements.size();
cout << "Size of dictionary: " << combinations.size() << endl;
cout << "Size of replacements: " << replacements.size() << "\nRandom Idx: " << randIdx << endl;


for (string word : combinations) {
    randIdx = randIdx % replacements.size();
    fout << word << " " << replacements[randIdx] << endl;
    randIdx++;
}

return 0;
}
