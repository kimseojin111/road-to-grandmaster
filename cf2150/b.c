#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void free_ptr(int* x) {
    *x = 19; 
    printf("Free ptr %d\n",*x);
}


void print_hello_world() {
    int buf_size = 1024;
    __attribute__((__cleanup__(free_ptr))) int x = 10; 
    printf("%d\n", x);
}

int main() {
    for (int i = 0; i < 10; i++) {
        print_hello_world();
    }

    return 0;
}