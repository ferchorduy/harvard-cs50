#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int validate_key(char key[]);
void get_ciphertext(const char plaintext[], int key);

int main(int argc, char *argv[])
{

  if (argc != 2)
  {
    printf("Usage: ./caesar key\n");
    return 1;
  }

  char plaintext[50];
  printf("plaintext: ");
  fgets(plaintext, 50, stdin);
  // Turns \n in fgets to \0 
  plaintext[strcspn(plaintext, "\n")] = '\0';

  get_ciphertext(plaintext, validate_key(argv[1]));

  return 0;
}

int validate_key(char key[])
{

  int key_int = atoi(key);

  if (key_int <= 0)
  {
    printf("Usage: ./caesar key\n");
    return 0;
  }
  return key_int;
}

void get_ciphertext(const char plaintext[], int key)
{
  char ciphertext[50];
  int key_int = key % 26;
  int i;

  for (i = 0; plaintext[i] != '\0'; i++)
  {
    if (isupper(plaintext[i]))
    {
      ciphertext[i] = plaintext[i] + key_int;
      if (ciphertext[i] > 'Z') ciphertext[i] -= 26;
    }
    else if (islower(plaintext[i]))
    {
      ciphertext[i] = plaintext[i] - 'a';
      int new_position = (ciphertext[i] + key_int) % 26;
      ciphertext[i] = 'a' + new_position;
    }
    else ciphertext[i] = plaintext[i];
  }
  ciphertext[i] = '\0';
  printf("ciphertext: %s\n", ciphertext);
}