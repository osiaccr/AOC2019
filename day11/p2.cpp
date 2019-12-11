#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
#define DEF 20000
#define DEF_GRID 1000

using namespace std;

ifstream fin ("in.in");
ofstream fout ("out.out");

int pc, prog_size, robot_pos_x = DEF_GRID / 2, robot_pos_y = DEF_GRID / 2, robot_dir = 0, nr_viz, Grid[DEF_GRID][DEF_GRID], Viz[DEF_GRID][DEF_GRID];

long long Mem[DEF], Prog[DEF];

char chr_dump;

pair < long long, long long > output_pair = {-1, -1};

int di[] = {-1, 0, 1, 0},
    dj[] = {0, 1, 0, -1};

void manage_output(long long output) {
    if (output_pair.first == -1) {
        output_pair.first = output;
        return;
    }
    output_pair.second = output;

    Grid[robot_pos_x][robot_pos_y] = output_pair.first;

    if (output_pair.second == 0) {
        // Left turn
        robot_dir -= 1;
        if (robot_dir < 0)
            robot_dir = 3;
    }
    else {
        // Right turn
        robot_dir += 1;
        if (robot_dir > 3)
            robot_dir = 0;
    }

    robot_pos_x += di[robot_dir];
    robot_pos_y += dj[robot_dir];

    if (not Viz[robot_pos_x][robot_pos_y]) {
        Viz[robot_pos_x][robot_pos_y] = 1;
        ++ nr_viz;
    }

    output_pair = {-1, -1};
}

int get_input() {
    return Grid[robot_pos_x][robot_pos_y];
}

void process(long long Mem[], int pc) {
    long long output = 0;
    long long base = 0;

    for (int is_halted = false; !is_halted;) {
        int instruction = Mem[pc];
        int opcode = instruction % 100;
        int par_1_mode = (instruction / 100) % 10;
        int par_2_mode = (instruction / 1000) % 10;
        int par_3_mode = (instruction / 10000) % 10;

        long long param1 = 0;
        if (par_1_mode == 0) {
            param1 = Mem[Mem[pc + 1]];
        }
        else if (par_1_mode == 1) {
            param1 = Mem[pc + 1];
        }
        else {
            param1 = Mem[Mem[pc + 1] + base];
        }

        long long param2 = 0;
        if (par_2_mode == 0) {
            param2 = Mem[Mem[pc + 2]];
        }
        else if (par_2_mode == 1) {
            param2 = Mem[pc + 2];
        }
        else {
            param2 = Mem[Mem[pc + 2] + base];
        }

        long long param3 = 0;
        if (par_3_mode == 0) {
            param3 = Mem[pc + 3];
        }
        else {
            param3 = Mem[pc + 3] + base;
        }

        switch (opcode) {
        case 1: { // Addition
            Mem[param3] = param1 + param2;
            pc += 4;
            break;
        }

        case 2: { // Multiplication
            Mem[param3] = param1 * param2;
            pc += 4;
            break;
        }

        case 3: { // Input
            long long x;
            x = get_input();
            if (par_1_mode == 2) {
                Mem[Mem[pc + 1] + base] = x;
            }
            else {
                Mem[Mem[pc + 1]] = x;
            }
            pc += 2;
            break;
        }

        case 4: {// Output
            output = param1;
            pc += 2;
            manage_output(output);
            break;
        }

        case 5 : { // Jump if true
            if (param1 != 0)
                pc = param2;
            else
                pc += 3;
            break;
        }

        case 6 : { // Jump if false
            if (param1 == 0)
                pc = param2;
            else
                pc += 3;
            break;
        }

        case 7 : { // Less than
            if (param1 < param2)
                Mem[param3] = 1;
            else
                Mem[param3] = 0;
            pc += 4;
            break;
        }

        case 8 : { // Equals
            if (param1 == param2)
                Mem[param3] = 1;
            else
                Mem[param3] = 0;
            pc += 4;
            break;
        }

        case 9 : { // Base ajust
            base += param1;
            pc += 2;
            break;
        }

        case 99: // Halt
            is_halted = true;
        }

    }

}

void set_Mem(long long Mem[], long long Prog[], int prog_size) {
    for (int i = 0; i < prog_size; ++ i) {
        Mem[i] = Prog[i];
    }
}


int main () {

    long long x;
    fin >> Prog[prog_size ++];
    while (fin >> chr_dump >> x) {
        Prog[prog_size ++] = x;
    }

    set_Mem(Mem, Prog, prog_size);

    Grid[robot_pos_x][robot_pos_y] = 1;
    Viz[robot_pos_x][robot_pos_y] = 1;
    ++ nr_viz;

    process(Mem, 0);

    for (int i = 0; i < DEF_GRID; ++ i) {
        for (int j = 0; j < DEF_GRID; ++ j) {
            fout << (Grid[i][j] ? '@' : ' ');
        }
        fout << '\n';
    }

    return 0;
}
