#include <stdio.h>

// Luhn's algorithm
int luhn(long n)
{
    int sum = 0;
    int toggle = 0;
    while (n > 0)
    {
        int d = n % 10; // d is assigned to last number
        if (toggle) // if false
        {
            d *= 2; // double d
            if (d > 9) d -= 9; // Nice trick d -= 9; and checks for 10, 12, 14, 16, 18 occurrences
        }
        sum += d; // sum adds d, the int assigned to the last digit
        toggle = !toggle; // change false to true, and vice versa
        n /= 10; // remove last number
    }
    return sum % 10 == 0; // return true means passed checksum check. return false means failed checksum check
}

// Return number of digits in the card number
int length(long n)
{
    int len = 0;
    while (n > 0) { n /= 10; len++; }
    return len;
}

// Return the first only or first two digits in the card number.
int first_digits(long n, int count)
{
    int len = length(n);
    for (int i = 0; i < len - count; i++) n /= 10;
    return n;
}

int main(void)
{
    long n;
    do
    {
        printf("Number: ");
    }
    while (scanf("%li", &n) != 1);

    int len = length(n);
    int start2 = first_digits(n, 2);
    int start1 = first_digits(n, 1);

    if (!luhn(n))                                          printf("INVALID\n");
    else if (len == 15 && (start2 == 34 || start2 == 37)) printf("AMEX\n");
    else if (len == 16 && start2 >= 51 && start2 <= 55)   printf("MASTERCARD\n");
    else if ((len == 13 || len == 16) && start1 == 4)     printf("VISA\n");
    else                                                   printf("INVALID\n");

    return 0;
}