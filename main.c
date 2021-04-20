#include <stdio.h>
#include <string.h>

int main() {
    // (emulated) memory stuff
    int memp = 0; // memory pointer
    int memSize = 64;
    int mem[memSize];

    // stack
    int stack[memSize/4];
    int sp = memSize/4 - 1; // stack pointer

    // reset arrays
    for (int i = 0; i < memSize; i++) {
        mem[i] = 0;
        stack[i/4] = 0;  // must be a netter way of doing this...
    }
        

    char code[] = ">+++++++++[<++++++++>-]<.>+++++++[<++++>-]<+.+++++++..+++.[-]>++++++++[<++++>-] <.>+++++++++++[<++++++++>-]<-.--------.+++.------.--------.[-]>++++++++[<++++>- ]<+.[-]++++++++++.";

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
                stack[sp] = i;
                sp++;
                break;
            case ']':
                if (mem[memp] != 0) i = stack[sp-1];
                else sp--;
                break;
        }
    }

    return 0;
}