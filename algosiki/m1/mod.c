#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void) {
    long long int a, b, m;
    scanf("%lld %lld %lld", &a, &b, &m);
    int r = b;
    int n = 0;
    while (r > 0) {
        n++;
        r /= 2;
    }
    int* bin = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        bin[i] = b % 2;
        b /= 2;
    }
    long long int s = 0;
    long long int p = 1;
    for (int i = 0; i < n; i++)
    {
        s = (s+(a * bin[i])%m * p)%m;
        p =(p * 2)%m;
    }
    printf("%lld\n", s % m);
}
