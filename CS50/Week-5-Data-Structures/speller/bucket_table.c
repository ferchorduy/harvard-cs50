#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DICTIONARY "dictionaries/large"
#define MAX_WORD_LENGTH 50
#define ALPHABET_LENGTH 26
#define ABC_LEN_CUBED 17576

void populate_list(int freq[ALPHABET_LENGTH][ALPHABET_LENGTH][ALPHABET_LENGTH]);
void bubble_sort_list(void);
void selection_sort_list(void);
void insertion_sort_list(void);
int combo_to_index(char *combo);
void greedy(void);

// Combinaiton of hree A-Z chars and the count of frequency they occur in the dictionary provided.
typedef struct
{
    int i, j, k;
    int count;
} combo;

// List of all combinations in alphabetical order, not sorted by count when first populated.
combo list[ABC_LEN_CUBED];

// Records a combination of three letters in freq 3D array
int freq[ALPHABET_LENGTH][ALPHABET_LENGTH][ALPHABET_LENGTH];

// Each element stores the bucket number in an integer for each combination, list[] now sorted by count
int bucket_table[ABC_LEN_CUBED];

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./bucket_table [dictionary]\n");
        return 1;
    }

    FILE *dict = fopen(argv[1], "r");
    if (dict == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    char word_buffer[MAX_WORD_LENGTH];
    int skipped = 0;

    while (fgets(word_buffer, MAX_WORD_LENGTH, dict) != NULL)
    {
        if (isalpha(word_buffer[0]) && isalpha(word_buffer[1]) && isalpha(word_buffer[2]))
        {
            freq[word_buffer[0]-'a'][word_buffer[1]-'a'][word_buffer[2]-'a']++;
        }
        else skipped++; // In dictionaries/large, skips over about 235/143k words due to lenght being 2 or less. This counts them.
    }

    // Fun index to test populate_list() and combo_to_index()
    int combo_index = combo_to_index("cab");

    populate_list(freq);
    printf("%c%c%c: %d\n", list[combo_index].i + 'a', list[combo_index].j + 'a', list[combo_index].k + 'a', list[combo_index].count);

    insertion_sort_list();

    greedy();
    printf("con in bucket %d\n", bucket_table[combo_to_index("con")]);

    // Claude helped me export this data
    FILE *out = fopen("bucket_table.h", "w");
    fprintf(out, "int bucket_table[17576] = {");
    for (int i = 0; i < ABC_LEN_CUBED; i++)
    {
        fprintf(out, "%d", bucket_table[i]);
        if (i < ABC_LEN_CUBED - 1) fprintf(out, ", ");
    }
    fprintf(out, "};\n");
    fclose(out);

    fclose(dict);
    return 0;
}

// Takes the 3D array freq and makes a combo type for each combo in the list with frequency/count of combo
void populate_list(int freq[ALPHABET_LENGTH][ALPHABET_LENGTH][ALPHABET_LENGTH])
{
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        for (int j = 0; j < ALPHABET_LENGTH; j++)
        {
            for (int k = 0; k < ALPHABET_LENGTH; k++)
            {
                int h = i * ALPHABET_LENGTH * ALPHABET_LENGTH + j * ALPHABET_LENGTH + k;
                list[h].i = i;
                list[h].j = j;
                list[h].k = k;
                list[h].count = freq[i][j][k];
            }
        }
    }
}

void bubble_sort_list(void)
{
    int swap_counter = -1;
    for (int i = 0; i < ABC_LEN_CUBED - 1; i++)
    {
        swap_counter = 0;
        for (int j = 0; j < ABC_LEN_CUBED - 1 - i; j++)
        {
            if (list[j].count > list[j+1].count)
            {
                combo tmp = list[j];
                list[j] = list[j+1];
                list[j+1] = tmp;
                swap_counter++;
            }
        }
        if (swap_counter == 0) break;
    }
}

void selection_sort_list(void)
{
    for (int i = 0; i < ABC_LEN_CUBED; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < ABC_LEN_CUBED; j++)
        {
            if (list[j].count < list[min_index].count) min_index = j;
        }
        combo tmp = list[min_index];
        list[min_index] = list[i];
        list[i] = tmp;
    }
}

void insertion_sort_list(void)
{
    for (int i = 1; i < ABC_LEN_CUBED; i++)
    {
        combo tmp = list[i];
        int j = i - 1;
        while (j >= 0 && list[j].count > tmp.count)
        {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = tmp;
    }
}

// Fun index to return an int, the correct index within the 17,576 combo-sized list. 'aaa' == 0, 'aab' == 1, etc.
int combo_to_index(char *combo)
{
    return (combo[0] - 'a') * 676 + (combo[1] - 'a') * 26 + (combo[2] - 'a');
}

// In the now sorted from low to high list, this starts at bottom and stores all contiguous elements in one bucket
// until the value of the biggest count (1798 in dictionaries/large) is reached, then new bucket is made
void greedy(void)
{
    // Max for "max" in the max count / average count = 1.0 
    const int MAX = list[ABC_LEN_CUBED - 1].count; // 1798 counts: 'con' occurred 1798 times, the most of all combos
    int current_sum = 0;
    int current_bucket = 0;

    for (int i = 0; i < ABC_LEN_CUBED; i++)
    {
        int index = list[i].i * 676 + list[i].j * 26 + list[i].k;
        bucket_table[index] = current_bucket;
        current_sum += list[i].count;
        if (current_sum >= MAX)
        {
            current_bucket++;
            current_sum = 0;
        }
    }
}