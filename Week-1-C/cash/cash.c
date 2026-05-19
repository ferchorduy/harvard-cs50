#include <stdio.h>

int get_change_owed(void);
void get_minimum_coins(int change);

int main(void) {

    int change_owed = get_change_owed();

    get_minimum_coins(change_owed);

    return 0;
}

// Function to verify input is an int greater than or equal to 0
int get_change_owed(void)
{
    int change_owed;
    int result;
    do
    {
        printf("Change owed: ");
        result = scanf("%d", &change_owed);
        if (result != 1)
        {
            printf("Invalid! Enter a number.\n");
            while(getchar() != '\n');
        }
    }
    while (change_owed < 0 || result != 1);
    return change_owed;
}

void get_minimum_coins(int change)
{
    // Will return this
    int coin_counter = 0;

    // While there is still change, subtract
    while (change >= 25)
    {
        coin_counter++;
        change -= 25;
    }
    while (change >= 10)
    {
        coin_counter++;
        change -= 10;
    }
    while (change >= 5)
    {
        coin_counter++;
        change -= 5;
    }
    while (change >= 1)
    {
        coin_counter++;
        change -= 1;
    }
    printf("%d\n", coin_counter);
}