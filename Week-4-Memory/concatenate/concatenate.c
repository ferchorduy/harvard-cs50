#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *concat(char *string1, char *string2);

int main(void)
{
    char string1[50];
    char string2[50];
    printf("Enter string 1: ");
    fgets(string1, 50, stdin);
    string1[strcspn(string1, "\n")] = '\0';
    printf("Enter string 2: ");
    fgets(string2, 50, stdin);
    string2[strcspn(string2, "\n")] = '\0';
    char *string3 = concat(string1, string2);
    printf("%s\n", string3);
    free(string3);
}

char *concat(char *string1, char *string2)
{
    int len1 = strlen(string1);
    int len2 = strlen(string2);
    char *string3 = malloc(len1 + len2 + 1);

    for (int i = 0; i < len1; i++)
    {
        string3[i] = string1[i];
    }
    for (int i = 0; i < len2; i++)
    {
        string3[len1 + i] = string2[i];
    }
    string3[len1 + len2] = '\0';

    return string3;
}