#include <stdio.h>
#include "operations.h"

int main()
{
    // Dumb Comment
    int a = 10;
    int b = 5;

    printf("Addition de %d et %d est %d\n", a, b, add(a, b));
    printf("Soustraction de %d par %d est %d\n", a, b, subtract(a, b));

    return 0;
}
