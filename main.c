#include <stdio.h>
#include <string.h>

#define COLOR_RED     "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: `bf FILE`");
        return 1;
    }

    FILE * fpointer;
    fpointer = fopen(argv[1], "r"); 

    if (fpointer == NULL) {
        printf(COLOR_RED "file can't be opened\n" COLOR_RESET);
        return 1;
    }

    char line[1024];
    char code[1024];
    while (!feof(fpointer)) {
        fgets(line, 1024, fpointer);
        strcat(code, line);
    }
    fclose(fpointer); 

    int memp = 0; // memory pointer
    int memSize = 64;
    int mem[memSize];

    int stack[memSize/4];
    int sp = memSize/4 - 1; // stack pointer

    char iscomment = 0;

    // reset arrays
    for (int i = 0; i < memSize; i++) {
        mem[i] = 0;
        stack[i/4] = 0;  // must be a netter way of doing this...
    }

    // loop chars in code
    for (int i = 0; i < strlen(code); i++) {

        if (code[i] == '\n') {
            iscomment = 0;
            continue;
        }

        if (iscomment)
            continue;

        //printf("\nmem[memp]: %d\ni: %d", mem[memp], i);
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
                if (mem[memp] != 0) {
                    if (i - 1 == stack[sp-1])
                        return 0;

                    i = stack[sp-1];
                } else sp--;
                break;
        }
    }

    return 0;
}