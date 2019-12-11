#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#define DEF 20000

#define H 6
#define W 25

using namespace std;

ifstream fin ("in.in");
ofstream fout ("out.out");

int maximum, M[100][100];

char line[DEF];

vector < pair < int, int > > Ast;

vector < int > Selected;

bool check_inline(pair < int, int > a, pair < int, int > b, pair < int, int > c) {
    int area = (a.first - c.first) * (b.second - c.second) - (b.first - c.first) * (a.second - c.second);
    return area == 0;
}

float dist(pair < int, int > a, pair < int, int > b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

bool check_a_in_middle(pair < int, int > a, pair < int, int > b, pair < int, int > c) {
    float dist_ab = dist(a, b);
    float dist_ac = dist(a, c);
    float dist_bc = dist(b, c);
    return abs(dist_bc - (dist_ab + dist_ac)) < 0.0001;
}

int main () {

    int i = 0;
    while (fin >> line) {
        for (int j = 0; line[j] != 0; ++ j) {
            if (line[j] == '#')
                Ast.push_back({i, j});
        }
        ++ i;
    }

    for (auto asteroid : Ast) {
        Selected.clear();
        for (int j = 0; j < Ast.size(); ++ j) {
            if (asteroid == Ast[j])
                continue;

            bool is_blocked = false;

            for (int k = 0; k < Selected.size(); ++ k) {
                if (asteroid == Ast[Selected[k]] or Ast[j] == Ast[Selected[k]])
                    continue;

                pair < int, int > to_add_asteroid = Ast[j], check_asteroid = Ast[Selected[k]];
                if (check_inline(asteroid, to_add_asteroid, check_asteroid) and not check_a_in_middle(asteroid, to_add_asteroid, check_asteroid)) {
                    is_blocked = true;
                }
            }

            if (not is_blocked) {
                Selected.push_back(j);
            }
        }

        M[asteroid.first][asteroid.second] = int(Selected.size());
        maximum = max(maximum, int(Selected.size()));
    }

    for (int i = 0; i < 20; ++ i) {
        for (int j = 0; j < 20; ++ j) {
            if (M[i][j] != 0) {
                cout << M[i][j];
            }
            else {
                cout << '.';
            }
        }
        cout << "\n";
    }

    cout << maximum;


    return 0;
}
