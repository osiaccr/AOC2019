#include <iostream>
#include <fstream>

using namespace std;

ifstream fin ("in.in");

int sum = 0;

int main () {

    int x;
    while (fin >> x) {
        sum += x / 3 - 2;
    }

    cout << sum;

    return 0;
}
