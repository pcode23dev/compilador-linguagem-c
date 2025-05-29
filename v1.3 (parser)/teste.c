#include <stdio.h>
#include <stdlib.h>

typedef int inteiro;

inteiro func() {
    inteiro x = 10;
    return x;
}

void test_break_continue() {
    int i = 0;
    while (i < 10) {
        i++;
        if (i == 5) {
            continue;
        }
        if (i == 8) {
            break;
        }
    }
}


int max(int x, int y) {
    float a = 1.5, b = 2.5, c;
    if (x > y) {
        return x;
    } else {
        return y;
    }
}
void loop_example() {
    int i = 0;
    for ( i = 0; i < 10; i++) {
        printf("i = %d\n", i);
    }

    int j = 0;
    while (j < 5) {
        j++;
    }
}


int main() {
    int result = max(10, 20) + 5 * 2;
    printf("Resultado: %d\n", result);
    return 0;
}