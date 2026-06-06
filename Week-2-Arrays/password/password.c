// Check that a password has at least one lowercase letter, uppercase letter, number and symbol

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

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
    bool upper = false;
    bool lower = false;
    bool number = false;
    bool symbol = false;

    for (int i = 0; i < strlen(password); i++)
    {
        if (isupper(password[i])) upper = true;
        else if (islower(password[i])) lower = true;
        else if (isdigit(password[i])) number = true;
        else if (!isalnum(password[i])) symbol = true;
    }

    return upper && lower && number && symbol;
}