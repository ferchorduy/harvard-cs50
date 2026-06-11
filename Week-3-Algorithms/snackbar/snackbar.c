// Practice using structs
// Practice writing a linear search function

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

// Number of menu items
// Adjust this value (10) to number of items input below
#define NUM_ITEMS 10

// Menu itmes have item name and price
typedef struct
{
    char item[50];
    float price;
} menu_item;

// Array of menu items
menu_item menu[NUM_ITEMS];

// Add items to menu
void add_items(void);

// Calculate total cost
float get_cost(char *item);

int main(void)
{
    add_items();

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i].price);
    }
    printf("\n");

    float total = 0;
    while (true)
    {
        char item[50];
        printf("Enter a food item: ");
        fgets(item, 50, stdin);
        item[strcspn(item, "\n")] = '\0';
        
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        total += get_cost(item);
    }

    printf("Your total cost is: $%.2f\n", total);
    return 0;
}

// Add at least the first four items to the menu array
void add_items(void)
{
    strcpy(menu[0].item, "Burger");
    menu[0].price = 9.50;

    strcpy(menu[1].item, "Vegan Burger");
    menu[1].price = 11.00;

    strcpy(menu[2].item, "Hot Dog");
    menu[2].price = 5.00;

    strcpy(menu[3].item, "Cheese Dog");
    menu[3].price = 7.00;

    strcpy(menu[4].item, "Fries");
    menu[4].price = 5.00;

    strcpy(menu[5].item, "Cheese Fries");
    menu[5].price = 6.00;

    strcpy(menu[6].item, "Cold Pressed Juice");
    menu[6].price = 7.00;

    strcpy(menu[7].item, "Cold Brew");
    menu[7].price = 3.00;

    strcpy(menu[8].item, "Water");
    menu[8].price = 2.00;

    strcpy(menu[9].item, "Soda");
    menu[9].price = 2.00;
}

// Search through the menu array to find an item's cost
float get_cost(char *item)
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        if (strcasecmp(item, menu[i].item) == 0)
        {
            return menu[i].price;
        }
    }
    return 0;
}
