// Write a function to replace vowels with numbers

#include <stdio.h>
#include <string.h>

char *replace(char *word);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./novowels word\n");
        return 1;
    }

    char *word = replace(argv[1]);
    printf("%s\n", word);

    return 0;

}

char *replace(char *word)
{
    char int_vowels[] = {'6', '3', '1', '0'};

    for (int i = 0; i < strlen(word); i++)
    {
        switch (word[i])
        {
            case 'a':
                word[i] = int_vowels[0];
                break;
            case 'e':
                word[i] = int_vowels[1];
                break;
            case 'i':
                word[i] = int_vowels[2];
                break;
            case 'o':
                word[i] = int_vowels[3];
                break;
        }
    }
    return word;
}