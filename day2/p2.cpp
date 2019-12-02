#include <iostream>
#include <fstream>
#define DEF 1000

using namespace std;

ifstream fin ("in.in");

char char_dump;

int code, V[DEF], size_v;

int main () {

    while (fin >> code) {
        V[size_v ++] = code;
        fin >> char_dump;
    }

    V[1] = 67;
    V[2] = 18;

    for (int i = 0; i < size_v;) {
        if(V[i] == 99)
            break;

        switch (V[i]) {
        case 1:
            V[V[i + 3]] = V[V[i + 1]] + V[V[i + 2]];
            i += 4;
            break;
        case 2:
            V[V[i + 3]] = V[V[i + 1]] * V[V[i + 2]];
            i += 4;
            break;
        default:
            cout << "Bad instruction";
            return 1;
        }
    }

    cout << V[0];

    return 0;
}
