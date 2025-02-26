#include <stdio.h>

void print(char *str)
{
    printf(" execute print prog\n");
    printf("%s\n", str);
    return;
}

int main(int argc, char **argv)
{
    print(argv[1]);
    return(0);
}