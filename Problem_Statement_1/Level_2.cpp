#include <iostream>
#include <string>
#include <cctype>
#include <array>
using namespace std;
string Cipher(const string &text, int shift) { // coding function. improved or simpler than prev submitted in PS0.
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
    static const array<double, 26> ENG = { // Array with percentage frequency of english letters.
        8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
        0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
        2.758, 0.978, 2.360, 0.150, 1.974, 0.074
    };
array<double, 26> frequency(const string& sentence) { //array function that finds the frequency of each letter in a single message.
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
int best(const string& message) { // function that finds the most optimum shift.
    array<array<double, 26>, 26> freqs;
    for (int s = 0; s < 26; s++) {
        string attempt = Cipher(message, -s);
        freqs[s] = frequency(attempt);
    } // find frequency of letters for each shift and stores them in a 2-D Array.
    int bestShift1;
    double bestScore = 100000000;// given a high value so that this can change in further loops.
    double score[26];
    for (int s = 0; s < 26; s++) {
        for (int j = 0; j < 26; j++) {
            score[s] += abs(freqs[s][j] - ENG[j]);
        } // finds the difference of frequency in a random decoding and compares that to english lang.
        if (score[s] < bestScore) {// reason why it was given high value otherwise this won't work.
            bestScore = score[s];
            bestShift1 = s;
        }
    }
    cout << "Detected shift: " << bestShift1 << endl;
    cout << "\nResult: " << Cipher(message, -bestShift1);
    return bestShift1;
}
int main() {
    char Opt;
    cout << "===Caesar Cipher Program===\n";
    cout << "This Program offers to both encode as well as decode caesar cipher by user determined shifting of code.\n";
    cout << "To Encode a message : E\n";
    cout << "To Decode a message : D\n";
    cout << "For Smart Decoding a the message : S\n";
    cout << "Which one do you wish to use : ";
    cin >> Opt;
    cin.ignore();
    if (Opt != 'e' && Opt != 'E' && Opt != 'd' && Opt != 'D' && Opt != 'S' && Opt != 's') {
        cout << "ERROR!!!\n";
        return 0;
    }
    int shift;
    if (Opt == 'e' || Opt == 'E' || Opt == 'd' || Opt == 'D') {
        cout << "Enter shift amount (1-25): ";
        cin >> shift;
        shift %= 26;
        cin.ignore();
    }
    string message , output;
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