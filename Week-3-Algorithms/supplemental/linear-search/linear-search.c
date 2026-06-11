#include <stdio.h>

int main(void)
{
    int nums[] = {3, 7, 9, 2, 1, 4, 8, 0, 6, 5};
    int num_input;
    printf("Search for the position of a number 0 through 9 in a ten digit array: ");
    scanf("%d", &num_input);

    int nums_length = sizeof(nums) / sizeof(nums[0]); // sizeof(nums) is 10 elements by 4 bytes per int element, 40 bytes
                                                      // sizeof(nums[0]) is one int, which is 4 bytes. so, 40 / 4 = 10 elements (length)
    int number_of_hops_in_search = 0;

    for (int i = 0; i < nums_length; i++)
    {
        number_of_hops_in_search++;
        printf("%d hop(s) so far. ", number_of_hops_in_search);
        if (num_input != nums[i])
            {
                printf("Not here!\n");
            }
        else
        {
            printf("Found it!\n");
            printf("Your selected number %d was in position number %d in our array of nums.\n", num_input, i + 1);
            printf("Total number of search hops was %d.\n", number_of_hops_in_search);
            break;
        }
    }

    return 0;

}