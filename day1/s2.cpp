#include <iostream>
#include <fstream>

using namespace std;

ifstream fin ("in.in");

int sum = 0;

int fuel(int mass) {
    int f = mass / 3 - 2;
    if (f <= 0) {
        return 0;
    }
    else {
        return f + fuel(f);
    }
}

int main () {

    int x;
    while (fin >> x) {
        sum += fuel(x);
    }

    cout << sum;

    return 0;
}
