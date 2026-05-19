#include <stdio.h>

void print_row_left(int bricks);
void print_row_right(int spaces, int bricks);
int get_height(void);

int main(void)
{
    // Prompt user for height (int)
    int height = get_height();

    // Print pyramid of that height
    for (int i = 1; i <= height; i++)
    {
        // Print row based on which row
        print_row_right(i, height);
    }
  return 0;
}

// Given a number of bricks, print that number of bricks
void print_row_left(int bricks)
{
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    printf("\n");
}

// Given a number of spaces and bricks, print that number of spaces and bricks
void print_row_right(int spaces, int bricks)
{
    int difference = bricks - spaces;
    // Print spaces
    for (int i = 0; i < difference ; i++)
    {
        printf(" ");
    }
    // Print bricks
    for (int i = 0; i < spaces ; i++)
    {
        printf("#");
    }
    printf("\n");
}

// Function to get height from user
int get_height(void)
{
    int height;
    int result;
    do
    {
        printf("Height: ");
        result = scanf("%d", &height);
        if (result != 1)
        {
            printf("Invalid. Enter a number.\n");
            while (getchar() != '\n');
        }
    }
    while (height < 1 || height > 8 || result != 1);
    return height;
}



/*  EXAMPLES

    #
    ##
    ###
    ####
    #####



        #
       ##
      ###
     ####
    #####

*/


