#include <stdio.h>

int main(void)
{
    int nums[] = {3, 7, 9, 2, 1, 4, 8, 0, 6, 5};

    int swap_counter = -1;

    int nums_length = sizeof(nums) / sizeof(nums[0]); // sizeof(nums) is 10 elements by 4 bytes per int element, 40 bytes
    // sizeof(nums[0]) is one int, which is 4 bytes. so, 40 / 4 = 10 elements (length)
    
    int number_of_hops_in_sort = 0;

    
}