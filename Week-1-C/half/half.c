// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount;
    float tax_percent;
    int tip_percent;
    printf("Bill before tax and tip: ");
    scanf("%f", &bill_amount);
    printf("Sales Tax Percent: ");
    scanf("%f", &tax_percent);
    printf("Tip percent: ");
    scanf("%i", &tip_percent);

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// TODO: Complete the function
float half(float bill, float tax, int tip)
{
    float tax_percentage = tax / 100.0;
    float tip_percentage = (float)tip / 100.0;
    float total_before_tip = bill * (1 + tax_percentage);
    float tip_amount = total_before_tip * tip_percentage;
    return ((total_before_tip + tip_amount) / 2.0);
}

