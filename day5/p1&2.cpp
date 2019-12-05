#include <iostream>
#include <fstream>
#define DEF 20000

using namespace std;

ifstream fin ("in.in");
ofstream fout ("out.out");

int Mem[DEF], mem_size;

char chr_dump;

int main () {

    int x;
    fin >> Mem[mem_size ++];
    while (fin >> chr_dump >> x) {
        Mem[mem_size ++] = x;
    }


    for (int pc = 0, is_halted = false; !is_halted;) {
        int instruction = Mem[pc];
        int opcode = instruction % 100;
        int par_1_mode = (instruction / 100) % 10;
        int par_2_mode = (instruction / 1000) % 10;
        int par_3_mode = (instruction / 10000) % 10;

        switch (opcode) {
        case 1: { // Addition
            int param1 = par_1_mode ? Mem[pc + 1] : Mem[Mem[pc + 1]];
            int param2 = par_2_mode ? Mem[pc + 2] : Mem[Mem[pc + 2]];
            Mem[Mem[pc + 3]] = param1 + param2;
            pc += 4;
            break;
        }

        case 2: { // Multiplication
            int param1 = par_1_mode ? Mem[pc + 1] : Mem[Mem[pc + 1]];
            int param2 = par_2_mode ? Mem[pc + 2] : Mem[Mem[pc + 2]];
            Mem[Mem[pc + 3]] = param1 * param2;
            pc += 4;
            break;
        }

        case 3: // Input
            cin >> x;
            Mem[Mem[pc + 1]] = x;
            pc += 2;
            break;

        case 4: {// Output
            int param1 = par_1_mode ? Mem[pc + 1] : Mem[Mem[pc + 1]];
            cout << param1 << "\n";
            pc += 2;
            break;
        }

        case 5 : { // Jump if true
            int param1 = par_1_mode ? Mem[pc + 1] : Mem[Mem[pc + 1]];
            int param2 = par_2_mode ? Mem[pc + 2] : Mem[Mem[pc + 2]];
            if (param1 != 0)
                pc = param2;
            else
                pc += 3;
            break;
        }

        case 6 : { // Jump if false
            int param1 = par_1_mode ? Mem[pc + 1] : Mem[Mem[pc + 1]];
            int param2 = par_2_mode ? Mem[pc + 2] : Mem[Mem[pc + 2]];
            if (param1 == 0)
                pc = param2;
            else
                pc += 3;
            break;
        }

        case 7 : { // Less than
            int param1 = par_1_mode ? Mem[pc + 1] : Mem[Mem[pc + 1]];
            int param2 = par_2_mode ? Mem[pc + 2] : Mem[Mem[pc + 2]];
            if (param1 < param2)
                Mem[Mem[pc + 3]] = 1;
            else
                Mem[Mem[pc + 3]] = 0;
            pc += 4;
            break;
        }

        case 8 : { // Equals
            int param1 = par_1_mode ? Mem[pc + 1] : Mem[Mem[pc + 1]];
            int param2 = par_2_mode ? Mem[pc + 2] : Mem[Mem[pc + 2]];
            if (param1 == param2)
                Mem[Mem[pc + 3]] = 1;
            else
                Mem[Mem[pc + 3]] = 0;
            pc += 4;
            break;
        }

        case 99: // Halt
            is_halted = true;
        }
    }


    return 0;
}
