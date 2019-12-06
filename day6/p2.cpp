#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#define DEF 60000

using namespace std;

ifstream fin ("in.in");
ofstream fout ("out.out");

int sol, root = 3108, you = 31628, san = 23341, T[DEF], Dist[DEF];

char line[10];

int get_encoding(char c) {
    if (c >= 'A' and c <= 'Z') {
        return c - 'A';
    }
    return c - '0' + 26;
}

int main () {

    while (fin >> line) {
        int orbitor =  0, orbited = 0;
        orbitor = get_encoding(line[6]) + 36 * get_encoding(line[5]) + 36 * 36 * get_encoding(line[4]);
        orbited = get_encoding(line[2]) + 36 * get_encoding(line[1]) + 36 * 36 * get_encoding(line[0]);
        // fout << orbited << ")" << orbitor << "\n";
        T[orbitor] = orbited;
    }

    int curr_node = you, curr_dist = 0;
    while (curr_node != 0) {
        Dist[curr_node] = curr_dist;
        curr_node = T[curr_node];
        ++ curr_dist;
    }

    curr_node = san, curr_dist = 0;
    while (curr_node != 0) {
        if (Dist[curr_node] != 0) {
            sol = Dist[curr_node] + curr_dist;
            break;
        }
        Dist[curr_node] = curr_dist;
        curr_node = T[curr_node];
        ++ curr_dist;
    }

    cout << sol - 2;

    return 0;
}
