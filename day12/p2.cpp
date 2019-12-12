#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
#define DEF 20000
#define DEF_GRID 1000

using namespace std;

struct point {
    long long x;
    long long y;
    long long z;

    point(long long _x, long long _y, long long _z) {
        x = _x;
        y = _y;
        z = _z;
    }

    point() {}

    point operator+= (const point & b) {
        x += b.x;
        y += b.y;
        z += b.z;
    }
};

ifstream fin ("in.in");
ofstream fout ("out.out");

int n = 4, steps = 0;

unsigned long long sol = 0, x_repeat, y_repeat, z_repeat;

point Moons[4], Vels[4], Moons0[4], Vels0[4];

long long gcd (long long a, long long b) {
    if (a == 0)
        return b;
    return gcd (b % a, a);
}

long long lcm (long long a, long long b) {
    return (a * b) / gcd(a, b);
}

long long get_sign (long long x) {
    if (x == 0)
        return 0;
    if (x > 0)
        return 1;
    return -1;
}

point get_velocity(point moon, point Moons[], int nr_moons) {
    point vel(0, 0, 0);

    for (int i = 0; i < nr_moons; ++ i) {
        vel.x += get_sign(Moons[i].x - moon.x);
        vel.y += get_sign(Moons[i].y - moon.y);
        vel.z += get_sign(Moons[i].z - moon.z);
    }

    return vel;
}

long long get_energy(const point & moon, const point & vel) {
    long long p_en = abs(moon.x) + abs(moon.y) + abs(moon.z);
    long long k_en = abs(vel.x) + abs(vel.y) + abs(vel.z);
    return p_en * k_en;
}

int main () {

    cin >> steps;

    for (int i = 0; i < n; ++ i) {
        fin >> Moons[i].x >> Moons[i].y >> Moons[i].z;
        Moons0[i] = Moons[i];
    }

    for (int step = 1; true; ++ step) {
        if (x_repeat and y_repeat and z_repeat)
            break;

        for (int i = 0; i < n; ++ i) {
            Vels[i] += get_velocity(Moons[i], Moons, n);
        }

        for (int i = 0; i < n; ++ i) {
            Moons[i] += Vels[i];
        }

        if (not x_repeat and Moons[0].x == Moons0[0].x and Moons[1].x == Moons0[1].x and Moons[2].x == Moons0[2].x and Moons[3].x == Moons0[3].x) {
            x_repeat = step + 1;
            cout << "found x";
        }

        if (not y_repeat and Moons[0].y == Moons0[0].y and Moons[1].y == Moons0[1].y and Moons[2].y == Moons0[2].y and Moons[3].y == Moons0[3].y) {
            y_repeat = step + 1;
            cout << "found y";
        }

        if (not z_repeat and Moons[0].z == Moons0[0].z and Moons[1].z == Moons0[1].z and Moons[2].z == Moons0[2].z and Moons[3].z == Moons0[3].z) {
            z_repeat = step + 1;
            cout << "found z";
        }
    }

    fout << lcm(x_repeat, lcm(y_repeat, z_repeat)) << "\n";

    /*for (int i = 0; i < n; ++ i) {
        sol += get_energy(Moons[i], Vels[i]);
    }

    cout << sol;*/

    for (int i = 0; i < n; ++ i) {
        fout << Moons[i].x << " " << Moons[i].y << " " << Moons[i].z << "\n";
    }

    fout << "--------------------------\n";

    for (int i = 0; i < n; ++ i) {
        fout << Vels[i].x << " " << Vels[i].y << " " << Vels[i].z << "\n";
    }

    return 0;
}
