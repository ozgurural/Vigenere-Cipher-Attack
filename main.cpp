//
// Created by ozgur ural on 9/26/21.
//

#include <string>
#include <iostream>
#include <vector>

std::vector <std::string> matrix;
std::vector<std::pair<int, int>> finals;
std::vector <int> sums;

//FREQUENCY_OF_ENGLISH_LETTERS probability of frequency of english letters
double FREQUENCY_OF_ENGLISH_LETTERS[26] = { 0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966,
                     0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
                     0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074 };

using namespace std;

int main() {
    int i = 0;
    int j = 0;
    int k;
    int key_len;
    string text;
    cout << "Enter the Cipher text:\n";
    cin >> text;

    matrix.push_back(text);

    /* Guessing Key Length */

    for (i = 1; i < text.length(); i++)
        matrix.push_back(text.substr(0, text.length() - i));

    for (i = 1; i < matrix.size(); i++) {
        int count = 0;
        for (j = matrix[i].size() - 1, k = matrix[0].size() - 1; j >= 0; j--, k--)
            if (matrix[i][j] == matrix[0][k])
                count++;
        sums.push_back(count);
    }
    cout << "For the given cipher text, the number of repeating letters after each shift:\n";
    for (i = 0; i < 50; i++)
        cout << sums[i] << " ";
    cout << "\n";

    int freq[50] = {0};
    for (i = 0; i < sums.size(); i++)
        if (sums[i] >= text.size() / 30)
            finals.emplace_back(sums[i], i);

    for (i = 1; i < finals.size(); i++)
        freq[finals[i].second - finals[i - 1].second]++;

    int max = 1;
    for (i = 1; i < 50; i++)
        if (freq[i] > max)
            max = i;
    cout << max << "\n";

    key_len = max;

    /* Guessing The Key */

    char Key[key_len];
    for (i = 0; i < key_len; i++) {
        double a[26] = {0};

        for (j = i; j < text.length(); j += key_len)
            a[text[j] - 'a']++;

        for (j = 0; j < 26; j++) {
            a[j] *= key_len;
            a[j] = (double)a[j] / (double)text.size();
        }
        vector<pair<int, double>> allMuls;

        for (j = 0; j < 26; j++) {
            double mul = 0;
            for (k = 0; k < 26; k++)
                mul += FREQUENCY_OF_ENGLISH_LETTERS[k] * a[(j + k) % 26];
            allMuls.emplace_back(j, mul);
        }
        double max_mul = allMuls[0].second;
        int shift = 0;
        for (j = 0; j < 26; j++) {
            if (max_mul < allMuls[j].second) {
                max_mul = allMuls[j].second;
                shift = j;
            }
        }
        Key[i] = (char)(shift + 'a');
    }
    cout << "Key: ";
    for (j = 0; j < key_len; j++)
        cout << Key[j];
    cout << "\n";

    //Decrypting the text
    cout << "Decrypted text: ";
    string plain_text = text;
    for (i = 0; i < key_len; i++) {
        for (j = i; j < text.length(); j += key_len)
            plain_text[j] = (char)((plain_text[j] - Key[i] + 26) % 26 + 'a');
    }
    cout << plain_text << "\n";
    return 0;
}