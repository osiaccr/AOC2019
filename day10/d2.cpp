#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
#define DEF 20000
#define EPS 0.001

#define H 6
#define W 25

using namespace std;

ifstream fin ("in.in");
ofstream fout ("out.out");

int maximum, Viz[DEF], del_ast;

char line[DEF];

pair < int, int > laser;

vector < pair < int, int > > Ast, Quad[4];

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
    return abs(dist_bc - (dist_ab + dist_ac)) < EPS;
}

bool ast_sort(pair < int, int > a, pair < int, int > b) {
    float angle1 = - atan2(a.second, a.first);
    float angle2 = - atan2(b.second, b.first);

    if (abs(angle1 - angle2) < EPS) {
        float dist1 = dist({0, 0}, a);
        float dist2 = dist({0, 0}, b);

        return dist1 < dist2;
    }

    return angle1 < angle2;
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

        if (maximum < Selected.size()) {
            maximum = Selected.size();
            laser = asteroid;
        }
    }

    for (int i = 0; i < Ast.size(); ++ i) {
        Ast[i].first -= laser.first;
        Ast[i].second -= laser.second;
    }

    sort(Ast.begin(), Ast.end(), ast_sort);

    /*for (int i = 0; i < Ast.size(); ++ i) {
        fout << Ast[i].first + laser.first << " " << Ast[i].second + laser.second << "\n";
    }*/

    i = 0;
    float last_del = 0;
    while (del_ast <= 200) {
        auto curr = make_pair(Ast[i].first + laser.first, Ast[i].second + laser.second);

        if (i == Ast.size())
            i = 0;

        if (Viz[i] or Ast[i] == make_pair(0, 0)) {
            ++ i;
            continue;
        }

        float angle = - atan2(Ast[i].second, Ast[i].first);
        if (abs(angle - last_del) < EPS) {
            ++ i;
            continue;
        }

        Viz[i] = 1;
        last_del = angle;
        del_ast += 1;
        if (del_ast == 200 or true) {
            fout << Ast[i].first + laser.first << " " << Ast[i].second + laser.second << '\n';
            // break;
        }
        ++ i;

    }


    return 0;
}
