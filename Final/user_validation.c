#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define InputBufferSize (80)


void readline_int(char *input_char, int *ptr_var)
{
    char *input_buffer = malloc(InputBufferSize);
    int input_returned = 0;
    input_returned = scanf(input_char, ptr_var);
    while(input_returned <= 0)
    {
        gets_s(input_buffer, InputBufferSize);
        printf("input not valid try again (input must be int):\n");
        input_returned = scanf(input_char, ptr_var);
    }
    free(input_buffer);
}

void readline_string(char *input_char, char *ptr_var)
{
    char *input_buffer = malloc(InputBufferSize);
    int input_returned = 0;
    input_returned = scanf(input_char, ptr_var);
    while(input_returned <= 0)
    {
        gets_s(input_buffer, InputBufferSize);
        printf("input not valid try again:\n");
        input_returned = scanf(input_char, ptr_var);
    }
    free(input_buffer); 
}

void readline_double(char *input_char, double *ptr_var)
{
    char *input_buffer = malloc(InputBufferSize);
    int input_returned = 0;
    input_returned = scanf(input_char, ptr_var);
    while(input_returned <= 0)
    {
        gets_s(input_buffer, InputBufferSize);
        printf("input not valid try again:\n");
        input_returned = scanf(input_char, ptr_var);
    }
    free(input_buffer);
}
