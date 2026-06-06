#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks;

    printf("Number of weeks taking CS50: ");
    scanf("%i", &weeks);

    int hours[weeks];
    for (int i = 0; i < weeks; i++)
    {
        printf("Week %i HW Hours: ", i);
        scanf("%i", &hours[i]);
    }

    char output;
    do
    {
        printf("Enter T for total hours, A for average hours per week: ");
        scanf("%c", &output);
    }
    while (toupper(output) != 'T' && toupper(output) != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output)
{
    int sum = 0;
    for (int i = 0; i < weeks; i++)
    {
        sum += hours[i];
    }

    if (output == 'T') return (float)sum;
    return (float)sum / weeks;
}