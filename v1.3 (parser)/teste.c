int max(int x, int y) {
    float a = 1.5, b = 2.5, c;
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

int main() {
    int result = max(10, 20) + 5 * 2;
    printf("Resultado: %d\n", result);
    return 0;
}