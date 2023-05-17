#include <stdio.h>

int func(int a, int b) {
    return a + b;
}

int (*save)(int, int) = func;

int main() {
    printf("%d\n", save(1, 2));
    return 0;
}
