#include <iostream>
#include <fstream>
#include <cstring>
#define DEF 20000

#define H 6
#define W 25

using namespace std;

ifstream fin ("in.in");
ofstream fout ("out.out");

int width = W, height = H, sol, min_digit_0 = 1 << 29, img[H][W];

char input[DEF];

int main () {

    fin >> input;

    int layer = 0;

    for (int i = 0; i < height; ++ i) {
        for (int j = 0; j < width; ++ j) {
            img[i][j] = 2;
        }
    }

    while (layer < strlen(input)) {
        for (int i = 0; i < height; ++ i) {
            for (int j = 0; j < width; ++ j) {
                if (img[i][j] == 2) {
                    img[i][j] = input[layer + i * width + j] - '0';
                }
            }
        }

        layer += width * height;

    }

    for (int i = 0; i < height; ++ i) {
        for (int j = 0; j < width; ++ j) {
            if (img[i][j])
                cout << "#";
            else
                cout << ".";
        }
        cout << "\n";
    }


    return 0;
}
