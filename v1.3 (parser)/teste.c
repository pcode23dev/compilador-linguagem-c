#include <stdio.h>

int soma(int a, int b) {
    int resultado = a + b;
    return resultado;
}

int main() {
    int x = 10, y = 20, z;
    float media;
    char letra = 'A';

    z = soma(x, y);

    if (z > 20) {
        printf("z é maior que 20\n");
    } else {
        printf("z não é maior que 20\n");
    }

    media = (x + y + z) / 3.0;

    while (media > 10.0) {
        media = media - 1.0;
    }

    return 0;
}