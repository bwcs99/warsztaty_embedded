/* Poprawne nawiasowanie */

#include <stdio.h>
#include <stdlib.h>

/*

[[ kkkk ggggg ((( kk

*/

int maximum(int a, int b){

    return a > b ? a:b;
}

// aaaaaaaa [[[]]] { b

int main(void){

    int a = 10;
    int b = 1000;

    char test1[] = "aaaaa [[[[[[ aaabb {{{{{ (((((";
    char test2[] = "aaaasdsdd[[[ {{}} (( ) vcvnkc""asasdsddsdf{";

    printf("Wynik: %d", maximum(a, b));

    return 0;
}