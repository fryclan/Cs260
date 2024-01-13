#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_validation.h"

int main(int argc, char const *argv[])
{
    int marble = 0;

    printf("How many marbles do you have.\n");
    readline_int("%d", &marble);
    printf("Marble Count: %d", marble);
}

