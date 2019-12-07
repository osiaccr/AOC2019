#include <iostream>
#include <fstream>
#define DEF 20000

using namespace std;

ifstream fin ("in.in");
ofstream fout ("out.out");

int Mem[5][DEF], Prog[DEF], mem_size, prog_size, pc[5];

char chr_dump;

pair < int, int > process(int args[], int Mem[], int pc) {
    int args_parse = 0;
    int output = 0;

    for (int is_halted = false; !is_halted;) {
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

        case 3: { // Input
            int x = args[args_parse ++];
            Mem[Mem[pc + 1]] = x;
            pc += 2;
            break;
        }

        case 4: {// Output
            int param1 = par_1_mode ? Mem[pc + 1] : Mem[Mem[pc + 1]];
            output = param1;
            pc += 2;
            return {output, pc};
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

    return {-1, -1};

}

void set_Mem(int Mem[], int Prog[], int prog_size) {
    for (int i = 0; i < prog_size; ++ i) {
        Mem[i] = Prog[i];
    }
}

int test_sequence(int seq[], int Prog[], int prog_size) {
    pair < int, int > result = {0, 0}, last_result = {0, 0}, output = {0, 0};
    int args[1] = {0};

    for (int i = 0; i <= 4; ++ i) {
        set_Mem(Mem[i], Prog, prog_size);
        pc[i] = 0;
    }

    output = result;
    for (int i = 0; i <= 4; ++ i) {
        args[0] = seq[i];
        output = process(args, Mem[i], pc[i]);
        pc[i] = output.second;
    }
    last_result = result;
    result = output;

    while (result != make_pair(-1, -1)) {
        output = result;
        for (int i = 0; i <= 4; ++ i) {
            args[0] = output.first;
            output = process(args, Mem[i], pc[i]);
            pc[i] = output.second;
        }
        last_result = result;
        result = output;
    }

    return last_result.first;
}

int main () {

    int x;
    fin >> Prog[prog_size ++];
    while (fin >> chr_dump >> x) {
        Prog[prog_size ++] = x;
    }

    int maximum = 0;
    for (int curr_seq = 0; curr_seq <= 3124; ++ curr_seq) {
        int sequence[] = {(curr_seq / 625) % 5 + 5, (curr_seq / 125) % 5  + 5, (curr_seq / 25) % 5  + 5, (curr_seq / 5) % 5  + 5, curr_seq % 5 + 5};
        bool used[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        bool correct_seq = true;

        for (int i = 0; i <= 4; ++ i) {
            if (used[sequence[i]]) {
                correct_seq = false;
                break;
            }
            used[sequence[i]] = true;
        }

        if (!correct_seq)
            continue;

        int result = test_sequence(sequence, Prog, prog_size);
        if (maximum < result) {
            maximum = result;
        }
    }

    cout << maximum;

    return 0;
}
