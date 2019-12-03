#include <iostream>
#include <fstream>
#define DEF 20000

using namespace std;

ifstream fin ("in.in");
ofstream fout ("out.out");

char char_dump;

int x, Vis[DEF][DEF], curr_x = DEF / 2, curr_y = DEF / 2, minimum_dist = 1 << 29;

int di[] = {1, -1, 0, 0},
    dj[] = {0, 0, -1, 1};

int abs (int x) {
    return x >= 0 ? x : -x;
}

int main () {

    do {
        fin >> char_dump >> x;
        int dir = 0;

        switch(char_dump) {
        case 'R':
            dir = 3;
            break;
        case 'L':
            dir = 2;
            break;
        case 'U':
            dir = 1;
            break;
        case 'D':
            dir = 0;
            break;
        }

        for (int i = 1; i <= x; ++ i) {
            curr_x += di[dir];
            curr_y += dj[dir];

            Vis[curr_x][curr_y] = 1;

        }

        fin >> char_dump;
     } while (char_dump == ',');

     curr_x = DEF / 2;
     curr_y = DEF / 2;

     fin >> x;

     do {
        if (char_dump == ',')
            fin >> char_dump >> x;

        int dir = 0;
        switch(char_dump) {
        case 'R':
            dir = 3;
            break;
        case 'L':
            dir = 2;
            break;
        case 'U':
            dir = 1;
            break;
        case 'D':
            dir = 0;
            break;
        }

        for (int i = 1; i <= x; ++ i) {
            curr_x += di[dir];
            curr_y += dj[dir];

            if (Vis[curr_x][curr_y] == 1) {
                minimum_dist = min(minimum_dist, abs(DEF / 2 - curr_x) + abs(DEF / 2 - curr_y));
            }
            else {
                Vis[curr_x][curr_y] = 2;
            }
        }

        fin >> char_dump;
     } while (char_dump == ',');

   /*for (int i = 1; i < DEF; ++ i) {
        for (int j = 1; j < DEF; ++ j) {
            if (Vis[i][j] == 0)
                fout << ' ';
            else if (Vis[i][j] == 1)
                fout << '#';
            else
                fout << '%';
        }
        fout << "\n";
    }*/

     cout << minimum_dist;

    return 0;
}
