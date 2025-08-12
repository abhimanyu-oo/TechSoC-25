# include <iostream>

double power(double base, double exp) {
    int result = 1;
    for (int i =0 ; i < exp; i ++) {
        result *= base;
    }
    return result;
}

double sqrt(double num1){
    double n=num1-1;
    double ans = 1+(n/2)-(n*n/8)+(n*n*n/16)-(5*n*n*n*n/128)+(7*n*n*n*n*n/256);
    return ans;
}