#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char *s1[50];
    char *s2[50];
    printf("Enter string 1: \n");
    scanf("%s", s1);
    printf("Enter string 2: \n");
    scanf("%s", s2);
    char *s3 = concat(s1, s2);
    printf("%s", s3);
}

char *concat(char *string1, char *string2)
{
    char *new_string = malloc(strlen(string1) + strlen(string2) + 1);

    for (int i = 0, n = strlen(string1); i < n; i++)
    {
        new_string[i] = string1[i];
    }

    for (int i = strlen(string1), n = strlen(string2) + strlen(string1); i < n; i++)
    {
        new_string[i] = string2[i - n];
    }



    return new_string;
}