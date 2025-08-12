# include <iostream>

using namespace std;

double power(double base, double exp) {
    int result = 1;
    for (int i =0 ; i < exp; i ++) { // This function keep multiplying a number by itself as many times as the user want thereby answering a^b.
        result *= base;
    }
    return result;
}

double sqrt(double sq){
    double n=sq-1;
    double ans = 1+(n/2)-(n*n/8)+(n*n*n/16)-(5*n*n*n*n/128)+(7*n*n*n*n*n/256); // binomial expansion for square root
    return ans;
}

int main() {

    char func;
    cout << "Addition : +\n"
    "Subtraction : -\n"
    "Multiplication : *\n"
    "Division : /" << endl;
    cout << endl;
    cout << "Square Root : sq\n"
    "Integer Powers : p\n"
    "a^b (power) : ^\n"
    "e^x (Exponential) : e\n"
    "Natural Logarithm : ln\n"
    "Logarithm base 10 : 10" << endl;
    cout << endl;
    cout << "Which function do you want to perform: ";
    cin >> func;
    cin.ignore();


    double num1 , num2;
    cout << "Please enter a number: ";
    cin >> num1;

    if (func == '+' || func == '*' || func == '-' || func == '/' || func == '^' || func == 'p') {
        cout << "Please enter the second number: ";
        cin >> num2;
    } else {}

    if (func == '+' ) {
        cout << num1+num2;
    } else if (func == '-') {
        cout << num1-num2;
    } else if (func == '*' ) {
        cout << num1*num2;
    } else if (func == '/' ) {
        cout << num1/num2;
    } else if (func == 's' ) {
        double sq_root=sqrt(num1);
        cout << sq_root;
    } else if (func == 'p' ) {
        double ans = power(num1,num2);
        cout << ans;
    }else if (func == '^' ) {
        double ans = pow(num1, num2);
        cout << ans;
    }else if (func == 'e') {
        double ans = exp(num1);
        cout << ans;
    } else if (func == 'l') {
        double ans = log(num1);
        cout << ans;
    } else if (func == '1') {
        double ans = log(num1)/log(10);
        cout << ans;
    } else {
            cout << "Invalid function Entered" << endl;
        }
        return 0;
}
