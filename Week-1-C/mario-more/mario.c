#include <stdio.h>

int get_height(void);
void print_row(int spaces, int bricks);

// Same function as mario-less
int main(void) {
    int height = get_height(); 
    
    for (int i = 1; i <= height; i++)
    {
        print_row(i, height);
    }
    return 0; 
}

// Same function as mario-less
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
            printf("Invalid! Enter a number.\n");
            while (getchar() != '\n');
        }
    }
    while (height < 1 || height > 8 || result != 1);
    return height;
}

void print_row(int spaces, int bricks)
{
    // Number of spaces before first #
    int difference = bricks - spaces;
    
    // Since spaces always increases by 1 because an int i that increments 1 is passed into the
    // parameter in the for loop in main(). Bricks stays the same. So, difference changes.
    for (int i = 0; i < difference; i++) 
    {
        printf(" ");
    }
    // Passing i to spaces, an incrementing int, so first iteration is 1 #, then 2 #, then 3 #...
    for (int i = 0; i < spaces; i++)
    {
        printf("#");
    }
    // Two spaces, little valley
    printf("  ");
    // Same for loop as the one right above
    for (int i = 0; i < spaces; i++)
    {
        printf("#");
    }
    printf("\n");
}



/*
    #  #
   ##  ##
  ###  ###
 ####  ####
#####  #####
*/