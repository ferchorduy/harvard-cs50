// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <stdio.h>
#include <stdbool.h>

bool valid(char *password);

int main(void)
{
    char password[50];
    printf("Enter your password: ");
    scanf("%49s", password);

    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(char *password)
{
    
    return false;
}