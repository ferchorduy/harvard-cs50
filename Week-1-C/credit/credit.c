#include <stdio.h>

long get_card_number(void);
int get_length_of_card_number(long card_number);
int calculate_checksum(long card_number);
int get_starting_numbers(long card_number);
void validate_card_number(long card_number, int length);

int main(void) {
    
    long int card_number = get_card_number();
    int length = get_length_of_card_number(card_number);

    validate_card_number(card_number, length);

    return 0;
}

// Returns valid card number input from user
long get_card_number(void)
{
    long int card_number;
    int result;
    do
    {
      printf("Number: ");
      result = scanf("%li", &card_number);
      if (result != 1)
      {
          while (getchar() != '\n');
      }
    }
    while (result != 1);
    return card_number;
}

// Returns the length of the card number
int get_length_of_card_number(long card_number)
{
    int length = 0;
    if (card_number == 0) length = 1;
    else
    {
        while (card_number != 0)
        {
            card_number /= 10;
            length++;
        }
    }
    return length;
}

// Returns a sum from checksum algorithm to determine is last digit of sum is 0
int calculate_checksum(long card_number)
{
    int normal_sum = 0;
    int doubled_sum = 0;
    int should_double = 0;

    while (card_number != 0)
    {
        int num = card_number % 10;

        if (should_double)
        {
            int num_doubled = num * 2;
            if (num_doubled > 9)
            {
                doubled_sum += num_doubled % 10;
                doubled_sum += num_doubled / 10;
            }
            else
            {
                doubled_sum += num_doubled;
            }
        }
        else
        {
            normal_sum += num;
        }

        card_number /= 10;
        should_double = !should_double;
    }
    return normal_sum + doubled_sum;
}

// Return the starting numbers to compare to valid card starting numbers
int get_starting_numbers(long card_number)
{
    int length = get_length_of_card_number(card_number);

    if (length == 16 || length == 15)
    {
        for (int i = 0; i < length-2; i++) card_number /= 10;
        return card_number;
    }
    else if (length == 13)
    {
        for (int i = 0; i < length-1; i++) card_number /= 10;
        return card_number;
    }
    else return 0;
}

// Validate and print into console the correct output
void validate_card_number(long card_number, int length)
{
    if (calculate_checksum(card_number) % 10 == 0)
    {
        if (length == 16)
        {
            if (get_starting_numbers(card_number) == 51 ||
                get_starting_numbers(card_number) == 52 ||
                get_starting_numbers(card_number) == 53 ||
                get_starting_numbers(card_number) == 54 ||
                get_starting_numbers(card_number) == 55 ) printf("MASTERCARD\n");
            if (get_starting_numbers(card_number) >= 40 &&
                get_starting_numbers(card_number) <= 49) printf("VISA\n");
        }
        if (length == 15 && (get_starting_numbers(card_number) == 34 || get_starting_numbers(card_number) == 37 )) printf("AMEX\n");
        if (length == 13 && get_starting_numbers(card_number) == 4 ) printf("VISA\n");
    }
    else printf("INVALID\n");
}
