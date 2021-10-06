#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define COLOR_RED       "\x1b[31m"
#define COLOR_RESET     "\x1b[0m"
#define MEM_SIZE        4096

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: `bf FILE`\n");
        return 1;
    }

    FILE * fpointer;
    fpointer = fopen(argv[1], "r"); 

    if (fpointer == NULL) {
        printf("file can't be opened\n");
        return 1;
    }

    char line[MEM_SIZE];  // memsize was chosen at random
    char code[MEM_SIZE*4]; 

    while (!feof(fpointer)) {
        fgets(line, MEM_SIZE, fpointer);
        strcat(code, line);
    }
    fclose(fpointer); 

    int memp = 0; // memory pointer
    unsigned char mem[MEM_SIZE];
    int stack[MEM_SIZE/4];
    int sp = MEM_SIZE/4 - 1; // stack pointer
    
    int bCount = 0; // bracket count 

    char iscomment = 0;

    // reset arrays
    for (int i = 0; i < MEM_SIZE; i++) {
        mem[i] = 0;
        stack[i/4] = 0;  // must be a netter way of doing this...
    }

    // loop chars in code
    for (int i = 0; i < strlen(code); i++) {

        if (code[i] == '\n') {
            iscomment = 0;
            continue;
        }

        if (iscomment) continue;

        switch (code[i]) {
            case '#':
                iscomment = 1;
                break;
            case '+':
                mem[memp]++;
                break;
            case '-':
                mem[memp]--;
                break;
            case '>':
                if (memp < MEM_SIZE - 1) memp++;
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
                // if not 0, enter
                if (mem[memp] != 0) {
                    stack[sp] = i;
                    sp--;
                } else {
                    bCount = 0;
                    for (int j = i+1; j < MEM_SIZE; j++) {
                        if (code[j] == ']')
                            if (bCount == 0) {
                                i = j;
                                break;
                            } else bCount--;

                        else if (code[j] == '[')
                            bCount++; 
                    }
                }
                break;
            case ']':
                if (mem[memp] != 0) {
                    if (i - 1 == stack[sp+1]) return 0;
                    i = stack[sp+1];
                } else sp++;
                break;
        }
    }

    return 0;
}