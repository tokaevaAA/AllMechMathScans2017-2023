#include<stdio.h>

int main() {
    double x = 2;
    double y = x;
    double h = 1. / 3200;
    printf("h = %e\n", h);
    for (int i = 0; i < 10; ++i, x += h) {
        printf("%e\n", x);
        printf("%e\n\n", y + h * i);
    }
    return 0;
}
