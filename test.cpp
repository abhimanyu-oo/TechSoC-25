#include <iostream>
#include <string>
#include <cctype>
#include <array>
#include <algorithm>
#include <cmath>
using namespace std;
string Cipher(const string &text, int shift) {
    string result;
    for (char ch : text) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            result += char((ch - base + shift + 26) % 26 + base);
        } else {
            result += ch;
        }
    }
    return result;
}
static const array<double, 26> ENG = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094,
    6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929,
    0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};
static const array<double, 4> Markov = {5.56 , 32.48 , 32.20 , 29.78};
int vowel(char c) {
    string vowels = "aeiouAEIOU";
    if (isalpha(c)) {
        return (vowels.find(c) != string::npos) ? 0 : 1;
    }
    return 2;
}
array<double, 26> frequency(const string& sentence) {
    array<int, 26> freq = {0};
    int totalLetters = 0;
    for (char c : sentence) {
        if (isalpha(c)) {
            c = tolower(c);
            freq[c - 'a']++;
            totalLetters++;
        }
    }
    array<double, 26> percent = {0.0};
    if (totalLetters > 0) {
        for (int i = 0; i < 26; i++) {
            percent[i] = (freq[i] * 100.0) / totalLetters;
        }
    }
    return percent;
}

// Markov vowel-consonant transitions
array<double , 4> markov(const string& s) {
    array<double, 4> percent = {0.0};
    int freq[2][2] = {0};
    int totalPairs = 0;
    for (int i = 0; i < (int)s.size() - 1; i++) {
        int c1 = vowel(s[i]);
        int c2 = vowel(s[i+1]);
        if (c1 < 2 && c2 < 2) {
            freq[c1][c2]++;
            totalPairs++;
        }
    }
    if (totalPairs > 0) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                percent[i*2 + j] = (freq[i][j] * 100.0) / totalPairs;
            }
        }
    }
    return percent;
}

// Smart decoding using both ENG + Markov scores
void best(const string& message) {
    array<array<double, 26>, 26> freqs;
    array<array<double, 4>, 26> marcov = {}; // initialize to zeros

    // Step 1: frequency analysis
    for (int s = 0; s < 26; s++) {
        string attempt = Cipher(message, -s);
        freqs[s] = frequency(attempt);
    }

    double score[26] = {0.0};
    for (int s = 0; s < 26; s++) {
        for (int j = 0; j < 26; j++) {
            score[s] += abs(freqs[s][j] - ENG[j]);
        }
    }

    // Step 2: store shifts in array
    int bestShift[26];
    for (int i = 0; i < 26; i++) bestShift[i] = i;

    // sort by frequency score
    sort(bestShift, bestShift + 26,
         [&](int a, int b){ return score[a] < score[b]; });

    // compute markov for top 8 candidates
    for (int i = 0; i < 8; i++) {
        int s = bestShift[i];
        string attempt = Cipher(message, -s);
        marcov[s] = markov(attempt);
    }

    // Step 3: markov scoring
    double mscore[26] = {0.0};
    for (int s = 0; s < 26; s++) {
        for (int j = 0; j < 4; j++) {
            mscore[s] += abs(marcov[s][j] - Markov[j]);
        }
    }

    // Step 4: best by markov
    int bestByMarkov = min_element(mscore, mscore+26) - mscore;

    cout << "\nBest Guess (Shift " << bestByMarkov << "): "
         << Cipher(message, -bestByMarkov) << "\n";
    // compute L and vowel fraction
    int letterCount = 0, vowelCount = 0;
    for (char c : message) {
        if (isalpha(c)) {
            letterCount++;
            char cl = tolower(c);
            if (string("aeiou").find(cl) != string::npos) vowelCount++;
        }
    }
    double L = (double)letterCount;
    double vfrac = (L > 0.0) ? (double)vowelCount / L : 0.0;

    // adaptive Markov weight
    double w_m;
    if (L < 20) w_m = 0.35;
    else if (L < 60) w_m = 0.18;
    else w_m = 0.10;
    if (vfrac < 0.20) w_m *= 0.5;
    if (w_m < 0.02) w_m = 0.02;

    // frequency weight
    double w_f = 1.0 - w_m;

    // compute combined scores
    double combined[26] = {0.0};
    for (int s = 0; s < 26; s++) {
        combined[s] = w_f * score[s] + w_m * mscore[s];
    }

    // sort shifts by combined (lower is better)
    int finalOrder[26];
    for (int i = 0; i < 26; ++i) finalOrder[i] = i;
    sort(finalOrder, finalOrder + 26,
         [&](int a, int b){ return combined[a] < combined[b]; });

    // print top 3
    for (int i = 0; i < 3; ++i) {
        int s = finalOrder[i];
        cout << "\nResult (Shift " << s << "): " << Cipher(message, -s);
    }

}

int main() {
    char Opt;
    cout << "===Caesar Cipher Program===\n";
    cout << "Encode a message : E\n";
    cout << "Decode a message : D\n";
    cout << "Smart Decode     : S\n";
    cout << "Choose option: ";
    cin >> Opt;
    cin.ignore();

    if (Opt != 'e' && Opt != 'E' && Opt != 'd' && Opt != 'D' && Opt != 'S' && Opt != 's') {
        cout << "ERROR!!!\n";
        return 0;
    }

    int shift = 0;
    if (Opt == 'e' || Opt == 'E' || Opt == 'd' || Opt == 'D') {
        cout << "Enter shift amount (1-25): ";
        cin >> shift;
        shift %= 26;
        cin.ignore();
    }

    string message;
    cout << "Enter your message: ";
    getline(cin, message);

    if (Opt == 'e' || Opt == 'E') {
        cout << "\nResult: " << Cipher(message, shift) << "\n";
    } else if (Opt == 'd' || Opt == 'D') {
        cout << "\nResult: " << Cipher(message, -shift) << "\n";
    } else {
        best(message);
    }

    return 0;
}
