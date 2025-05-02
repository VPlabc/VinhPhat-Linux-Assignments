#include <stdio.h>
#include "../inc/myMath.h"



void main()
{
    printf("Hello World\n");
    printf("2 + 3 = %d\n", add(2, 3));
    printf("2 - 3 = %d\n", subtract(2, 3));
    printf("2 * 3 = %d\n", multiply(2, 3));
    printf("2 / 3 = %d\n", divide(2, 3));
    printf("2 ^ 3 = %d\n", power(2, 3));
    printf("f = %d\n", factorial(5));
    printf("sqrt(4) = %f\n", square_root(4));
}