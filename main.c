#include <stdio.h>

#define PROGSIZE  15000
#define REGISTERS 10000
#define CELLSIZE  256

typedef enum { false, true } bool;

bool get_content(char* filename, char* content) {
    int i = 0;
    FILE* fptr = fopen(filename, "r");
    if (fptr == NULL) return false;
    while (!feof(fptr) && i < PROGSIZE) {
        content[i] = fgetc(fptr); ++i;
    } return true;
}

void loop(const char* code, int* code_ptr, char matched, char wanted, int increment, bool b) {
    int count = 1;
    (*code_ptr)+=increment;
    while (count != 0) {
        if (code[*code_ptr] == wanted) count--;
        if (code[*code_ptr] == matched) count++;
        if (count == 0 && b) break;
        (*code_ptr)+=increment;
    }
}

void handle(const char* code, char registers[], int* ptr, int* code_ptr) {
    switch(code[*code_ptr]) {
        case '>': (*ptr) = (*ptr + 1) % REGISTERS; break;
        case '<': (*ptr) = (*ptr - 1) % REGISTERS; break;
        case '+': registers[*ptr] = (registers[*ptr] + 1) % CELLSIZE; break;
        case '-': registers[*ptr] = (registers[*ptr] - 1) % CELLSIZE; break;
        case '.': putchar(registers[*ptr]); break;
        case '[': if (registers[*ptr] == 0) loop(code, code_ptr, '[', ']',  1, true ); break;
        case ']': if (registers[*ptr] != 0) loop(code, code_ptr, ']', '[', -1, false); break;
        case ',': registers[*ptr] = getchar(); break;
        default: break;
    }
}

void run(const char* code) {
    char registers[REGISTERS] = {0};
    int ptr = 0, code_ptr = 0;
    while (true) {
        handle(code, registers, &ptr, &code_ptr);
        code_ptr++;
        if (code[code_ptr] == '\0') break;
    }
}

int main(int argc, char** argv) {
    if (argc < 2) return 1;
    char content[PROGSIZE];
    if (!get_content(argv[1], content))
        return 1;
    run(content);
    puts("\n");
    return 0;
}
