# include <iostream>
using namespace std;

int main() {
    char in;
    cout << "Hello user!\n"
    "This is a Program for Encoding and Decoding Caeser Cipher\n"
    "The Caesar Cipher is one of the oldest and simplest encryption techniques, named after Julius Caesar who used it to protect his military communications.\n"
    "It works by shifting each letter in the alphabet by a fixed number of positions.\n";   // Random Ignorable Gibbrish.
    cout << endl;
    cout << "This Program offers to both encode as well as decode caeser cipher by user determined shifting of code.\n";
    cout << "To Encode a message : E\n";
    cout << "To Decode a message : D\n";
    cout << "Which one do you wish to use : ";
    cin >> in;
    cin.ignore(); // This is there as without this the leftover \n from cin >> in interferes with cin.getline(ar , 1000) command.

    if (in == 'E' || in == 'e' || in == 'D' || in == 'd') {
        char ar[1000]; // Array to store the line to encoded to decoded.
        cout << "Please enter the line: ";
        cin.getline(ar , 1000);
        int x;
        cout << "How much Shift should be made in the statement (1-25): ";
        cin >> x;
        cin.ignore();
        x %= 26;

        if (in == 'E' || in == 'e') {
            for (int i = 0; ar[i] != '\0'; i++) {
                if (ar[i] >= ('z' - x + 1) && ar[i] <= 'z') { // if i had just put same command on all the letters it won't work so i made this range so that the value of char remains in range of alphabet.
                    ar[i] = ar[i] + x - 26;
                } else if (ar[i] >= ('Z' - x + 1) && ar[i] <= 'Z') {
                    ar[i] = ar[i] + x - 26;
                } else if (ar[i] >= 'a' && ar[i] < ('z' - x + 1)) { // these ranges were partially achieved through thinking and the edges were smoothed out later( adding the +1).
                    ar[i] += x;
                } else if (ar[i] >= 'A' && ar[i] < ('Z' - x + 1)) {
                    ar[i] += x;
                }
                cout << ar[i];
            }
        }
        else if (in == 'D' || in == 'd') {
            for (int i = 0; ar[i] != '\0'; i++) {
                if (ar[i] >= 'a' && ar[i] <= ('a' + x - 1)) {
                    ar[i] = ar[i] - x + 26;
                } else if (ar[i] >= 'A' && ar[i] <= ('A' + x - 1)) {
                    ar[i] = ar[i] - x + 26;
                } else if (ar[i] > ('a' + x - 1) && ar[i] <= 'z') {
                    ar[i] -= x;
                } else if (ar[i] > ('A' + x - 1) && ar[i] <= 'Z') {
                    ar[i] -= x;
                }
                cout << "Result : " << ar[i];
            }
        }
        else {
        }
    } else {
        cout << "Invalid Input!\n";
        cout << "ERROR!!!" << endl;
    }

    return 0;
}