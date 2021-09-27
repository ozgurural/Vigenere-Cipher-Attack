//
// Created by ozgur ural on 9/26/21.
//

#include <string>
#include <iostream>
#include <vector>

const int   MAX_LETTERS 	= 	26;
std::vector <std::string> CIPHER_MATRIX;
std::string CIPHER;
int KEY_LENGTH;
std::string KEY;

//FREQUENCY_OF_ENGLISH_LETTERS probability of frequency of english letters
const double FREQUENCY_OF_ENGLISH_LETTERS[MAX_LETTERS] = { 0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966,
                     0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
                     0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074 };

using namespace std;

void get_cypher_text() {
    cout << "Enter the Cipher text:\n";
    cin >> CIPHER;
    CIPHER_MATRIX.push_back(CIPHER);
}

void guess_key_length(){
    int maxKey = 1;
    int count;
    int i, j, k;
    int freq[50] = {0};
    std::vector <int> SUMS;
    std::vector<std::pair<int, int>> FINAL_VALUES;

    for (i = 1; i < CIPHER.length(); i++) {
        CIPHER_MATRIX.push_back(CIPHER.substr(0, CIPHER.length() - i));
    }

    for (i = 1; i < CIPHER_MATRIX.size(); i++) {
        count = 0;
        for (j = CIPHER_MATRIX[i].size() - 1, k = CIPHER_MATRIX[0].size() - 1; j >= 0; j--, k--) {
            if (CIPHER_MATRIX[i][j] == CIPHER_MATRIX[0][k])
                count++;
        }
        SUMS.push_back(count);
    }
    cout << "The number of repeating letters after each shift:\n";
    for (i = 0; i < 50; i++) {
        cout << SUMS[i] << " ";
    }
    cout << "\n";

    for (i = 0; i < SUMS.size(); i++) {
        if (SUMS[i] >= CIPHER.size() / 30) {
            FINAL_VALUES.emplace_back(SUMS[i], i);
        }
    }

    for (i = 1; i < FINAL_VALUES.size(); i++) {
        freq[FINAL_VALUES[i].second - FINAL_VALUES[i - 1].second]++;
    }

    for (i = 1; i < 50; i++) {
        if (freq[i] > maxKey) {
            maxKey = i;
        }
    }
    cout << maxKey << "\n";
    KEY_LENGTH = maxKey;
}

void guess_the_key() {
    double mul;
    double max_mul;
    int shift;
    int i, j, k;
    KEY[KEY_LENGTH];
    for (i = 0; i < KEY_LENGTH; i++) {
        double a[MAX_LETTERS] = {0};

        for (j = i; j < CIPHER.length(); j += KEY_LENGTH)
            a[CIPHER[j] - 'a']++;

        for (j = 0; j < MAX_LETTERS; j++) {
            a[j] *= KEY_LENGTH;
            a[j] = (double)a[j] / (double)CIPHER.size();
        }
        vector<pair<int, double>> allMuls;

        for (j = 0; j < MAX_LETTERS; j++) {
            mul = 0;
            for (k = 0; k < MAX_LETTERS; k++) {
                mul += FREQUENCY_OF_ENGLISH_LETTERS[k] * a[(j + k) % MAX_LETTERS];
            }
            allMuls.emplace_back(j, mul);
        }
        max_mul = allMuls[0].second;
        shift = 0;
        for (j = 0; j < MAX_LETTERS; j++) {
            if (max_mul < allMuls[j].second) {
                max_mul = allMuls[j].second;
                shift = j;
            }
        }
        KEY[i] = (char)(shift + 'a');
    }
    cout << "Key: ";
    for (j = 0; j < KEY_LENGTH; j++) {
        cout << KEY[j];
    }
    cout << "\n";
}

void decrypt_the_text() {
    cout << "Decrypted text: ";
    string PLAIN_TEXT = CIPHER;
    for (int i = 0; i < KEY_LENGTH; i++) {
        for (int j = i; j < CIPHER.length(); j += KEY_LENGTH) {
            PLAIN_TEXT[j] = (char)((PLAIN_TEXT[j] - KEY[i] + MAX_LETTERS) % MAX_LETTERS + 'a');
        }
    }
    cout << PLAIN_TEXT << "\n";
}

int main() {

    get_cypher_text();

    guess_key_length();

    guess_the_key();

    decrypt_the_text();

    return 0;
}