#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

int main()
{
    printf("\033[2J\033[0;0H");

    exit(0);
}

