#include <iostream>
#include <fstream>
#include <cstring>
#define DEF 20000

using namespace std;

ifstream fin ("in.in");
ofstream fout ("out.out");

int width = 25, height = 6, sol, min_digit_0 = 1 << 29, img[6][25];

char input[DEF];

int main () {

    fin >> input;

    int i = 0;

    while (i < strlen(input)) {
        int digits[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (int j = 0; j < width * height; ++ j) {
            ++ digits[input[i + j] - '0'];
        }

        if (digits[0] < min_digit_0) {
            min_digit_0 = digits[0];
            sol = digits[1] * digits[2];
        }

        i += width * height;
    }

    cout << sol;


    return 0;
}
