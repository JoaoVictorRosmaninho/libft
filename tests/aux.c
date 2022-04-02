#include <stdio.h>
#include <ctype.h>



int main(void) {
    printf("%d %d\n", isascii(127), isalnum('B'));
}
