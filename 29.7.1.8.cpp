#include <iostream>

int main() {
    int c = 0;
    for (int t = 1; t < 10; t++) {
        for (int r = 0; r < 10; r++) {
            if (t != r) {
                for (int i = 0; i < 10; i++) {
                    if (i != t && i != r) {
                        for (int d = 1; d < 10; d++) {
                            if (d != t && d != r && d != i) {
                                for (int v = 0; v < 10; v++) {
                                    if (v != d && v != t && v != r && v != i) {
                                        for (int a = 0; a < 10; a++) {
                                            if (a != v && a != d && a != t && a != r && a != i) {
                                                for (int p = 1; p < 10; p++) {
                                                    if (p != a && p != v && p != d && p != t && p != r && p != i) {
                                                        for (int ia = 0; ia < 10; ia++) {
                                                            if (ia != p && ia != a && ia != v && ia != d && ia != t && ia != r && ia != i) {
                                                                for (int b = 0; b < 10; b++) {
                                                                    if (b != ia && b != p && b != a && b != v && b != d && b != t && b != r && b != i) {
                                                                        if ((t * 100 + r * 10 + i) + (d * 100 + v * 10 + a) == (p * 1000 + ia * 100 + t * 10 + b)) {
                                                                            c++;
                                                                            std::cout << c << ")\t" << t << r << i << '+' << d << v << a << '=' << p << ia << t << b << std::endl;
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
