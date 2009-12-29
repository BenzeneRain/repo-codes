/*
ID: wchzw1
PROG: hello
*/

#include <stdio.h>
#include <stdlib.h>

main ()
{
    FILE *out = fopen ("hello.out", "w");
    fprintf(out, "Hello world.\n");
    exit (0);
}
