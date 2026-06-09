#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define KEY_LENGTH 26

void get_ciphertext(const char plaintext[], const char key[]);
int is_valid_key(char key[]);

int main(int argc, char *argv[])
{
    // Check to see if number of arguments is only 2
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Copy key given in argument
    char key[KEY_LENGTH + 1];
    strncpy(key, argv[1], KEY_LENGTH);
    key[KEY_LENGTH] = '\0';

    // Validate key is 26 chars long, only alphabetical, and no repeating chars
    if (!is_valid_key(key))
    {
        return 1;
    }

    // Turn all chars in validated key to uppercase
    for (int i = 0; key[i] != '\0'; i++)
    {
        key[i] = toupper(key[i]);
    }

    char plaintext[50];
    printf("plaintext: ");
    fgets(plaintext, 50, stdin);
    // Turns \n in fgets to \0 
    plaintext[strcspn(plaintext, "\n")] = '\0';

    get_ciphertext(plaintext, key);

    return 0;
}

void get_ciphertext(const char plaintext[], const char key[])
{
  char ciphertext[50];
  int i;
  for (i = 0; plaintext[i] != '\0'; i++)
  {
    if (isupper(plaintext[i])) ciphertext[i] = toupper(key[plaintext[i] - 'A']);
    else if (islower(plaintext[i])) ciphertext[i] = tolower(key[plaintext[i] - 'a']);
    else ciphertext[i] = plaintext[i];
  }
  ciphertext[i] = '\0';
  printf("ciphertext: %s\n", ciphertext);
}

int is_valid_key(char key[])
{
    if (strlen(key) != KEY_LENGTH)
    {
        printf("Key must contain exactly 26 characters.\n");
        return 0;
    }

    int seen[26] = {0};
    for (int i = 0; key[i] != '\0'; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain letters.\n");
            return 0;
        }

        int index = toupper(key[i]) - 'A';
        if (seen[index])
        {
            printf("Key must not contain duplicate letters.\n");
            return 0;
        }
        seen[index] = 1;
    }

    return 1;
}