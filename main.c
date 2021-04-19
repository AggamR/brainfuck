#include <stdio.h>
#include <string.h>

int main() {
    // (emulated) memory stuff
    int memp = 0; // memory pointer
    int memSize = 64;
    int mem[memSize];

    // reset array
    for (int i = 0; i < memSize; i++)
        mem[i] = 0;

    int bracks[memSize]; // locations of brackets
    int cbracks[memSize]; // location of closing brackets
    int bracksp = 0; // bracks pointer, last one
    int cbracksp = 0; // closing bracks pointer, last one
    int brackCount = 1;

    char code[] = "++++++++++[>+++++++>++++++++++>+++>++++<<<<-]>++.>+.+++++++..+++.>>++++.<++.<++++++++.--------.+++.------.--------.>+.";

    /* Find location of brackets
    Can't think of any way to make both for loops one loop */
    for (int i = 0; i < strlen(code); i++) {
        switch (code[i]) {
            case '[':
                bracks[bracksp] = i;
                bracksp++;
                break;
            case ']':
                cbracks[cbracksp] = i;
                cbracksp++;
                break;
        }
    }

    // loop chars in code
    for (int i = 0; i < strlen(code); i++) {
        //printf("\nmem[memp]: %d\ni: %d", mem[memp], i);
        switch (code[i]) {
            case '+':
                mem[memp]++;
                break;
            case '-':
                mem[memp]--;
                break;
            case '>':
                if (memp < memSize - 1) memp++;
                break;
            case '<':
                if (memp > 0) memp--;
                break;
            case '.':
                putchar(mem[memp]);
                break;
            case ',':
                mem[memp] = getchar();
                break;
            case '[':
                if (mem[memp] == 0) i = cbracks[cbracksp-brackCount];
                break;
            case ']':
                if (cbracks[brackCount - 1] != i) brackCount++;
                if (mem[memp] != 0) i = bracks[bracksp-brackCount];
                break;
        }
    }

    return 0;
}