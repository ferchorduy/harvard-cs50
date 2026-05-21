#include <stdio.h>

int get_word_points(char word[]);

int main(void)
{
  char first_word[50];
  char second_word[50];

  printf("Player 1: ");
  scanf("%49s", first_word);

  printf("Player 2: ");
  scanf("%49s", second_word);

  int first_word_points = get_word_points(first_word);
  int second_word_points = get_word_points(second_word);

  if (first_word_points > second_word_points) printf("Player 1 wins!\n");
  else if (first_word_points == second_word_points) printf("Tie!\n");
  else printf("Player 2 wins!\n");

  return 0;

}

int get_word_points(char word[])
{
  int points[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
  int word_points = 0;

  for (int i = 0; word[i] != '\0'; i++)
  {
    if (word[i] >= 'a' && word[i] <= 'z')
    {
      word_points += points[word[i] - 'a'];
    }
    else if (word[i] >= 'A' && word[i] <= 'Z')
    {
      char lower = word[i] + ('a' - 'A');
      word_points += points[lower - 'a'];
    }
    else
    {
      continue;
    }
  }

  return word_points;
}
