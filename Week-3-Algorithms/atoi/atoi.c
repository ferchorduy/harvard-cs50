#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(char *input);
int recursive_convert(char *input);

int main(void)
{
    char input[50];
    printf("Enter a positive integer: ");
    scanf("%49s", input);

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", recursive_convert(input));
}

int convert(char *input)
{
    int base_counter = strlen(input) - 1;
    int sum = 0;
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        sum += (input[i] - '0') * pow(10, base_counter);
        base_counter--;
    }
    return sum;
}

int recursive_convert(char *input)
{
    int len = strlen(input);
    if (input[1] == '\0')
    {
        return input[len - 1] - '0';
    }
    int num = input[len - 1] - '0';
    input[len - 1] = '\0';
    return num + (recursive_convert(input) * 10);
}