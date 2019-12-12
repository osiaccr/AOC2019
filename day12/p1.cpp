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

unsigned long long sol = 0;

point Moons[4], Vels[4];

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
    }

    for (int step = 0; step < steps; ++ step) {
        for (int i = 0; i < n; ++ i) {
            Vels[i] += get_velocity(Moons[i], Moons, n);
        }

        for (int i = 0; i < n; ++ i) {
            Moons[i] += Vels[i];
        }
    }

    for (int i = 0; i < n; ++ i) {
        sol += get_energy(Moons[i], Vels[i]);
    }

    cout << sol;

    for (int i = 0; i < n; ++ i) {
        fout << Moons[i].x << " " << Moons[i].y << " " << Moons[i].z << "\n";
    }

    fout << "--------------------------\n";

    for (int i = 0; i < n; ++ i) {
        fout << Vels[i].x << " " << Vels[i].y << " " << Vels[i].z << "\n";
    }

    return 0;
}
