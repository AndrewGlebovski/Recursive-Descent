#include <stdio.h>
#include "parser.hpp"


int main() {
    char exp[256] = "";

    scanf("%s", exp);

    printf("%i\n", getG(exp));

    printf("Syntax parser!\n");

    return 0;
}