#include <iostream>
#include <fstream>
#include <cstring>
#define DEF 20000

#define H 6
#define W 25

using namespace std;

ifstream fin ("in.in");
ofstream fout ("out.out");

int pc, prog_size;

long long Mem[DEF], Prog[DEF];

char chr_dump;

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
            cin >> x;
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
            cout << output << '\n';
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

    process(Mem, 0);


    return 0;
}
