#include <stdio.h>
#include <stdlib.h>
#include "myMath.h"

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero\n");
        return 0;
    }
    return a / b;
}

int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int factorial(int n) {
    if (n < 0) {
        printf("Error: Factorial of a negative number is undefined\n");
        return 0;
    }
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

double square_root(double num) {
    if (num < 0) {
        printf("Error: Square root of a negative number is undefined\n");
        return -1;
    }
    double guess = num / 2.0;
    double epsilon = 0.00001;
    while ((guess * guess - num) > epsilon || (num - guess * guess) > epsilon) {
        guess = (guess + num / guess) / 2.0;
    }
    return guess;
}