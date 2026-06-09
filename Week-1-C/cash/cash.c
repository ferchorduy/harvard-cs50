#include <stdio.h>

#define QUARTER 25
#define DIME 10
#define NICKEL 5
#define PENNY 1

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
    while (change >= QUARTER)
    {
        coin_counter++;
        change -= QUARTER;
    }
    while (change >= DIME)
    {
        coin_counter++;
        change -= DIME;
    }
    while (change >= NICKEL)
    {
        coin_counter++;
        change -= NICKEL;
    }
    while (change >= PENNY)
    {
        coin_counter++;
        change -= PENNY;
    }
    printf("%d\n", coin_counter);
}