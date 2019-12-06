#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#define DEF 60000

using namespace std;

ifstream fin ("in.in");
ofstream fout ("out.out");

int sol, root = 3108;

char line[10];

vector < int > L[DEF];

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
        L[orbited].push_back(orbitor);
    }

    deque < pair < int, int > > Q;

    Q.push_back({root, 0});

    while (!Q.empty()) {
        pair < int, int > curr = Q.front();
        Q.pop_front();
        int node = curr.first;
        int dist = curr.second;
        sol += dist;

        for (int i = 0; i < L[node].size(); ++ i) {
            Q.push_back({L[node][i], dist + 1});
        }
    }

    cout << sol;

    return 0;
}
