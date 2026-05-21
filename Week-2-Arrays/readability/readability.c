#include <stdio.h>
#include <string.h>
#include <math.h>

float coleman_liau(char text[]);

int main(void)
{
  char text[1024];
  printf("Text: ");
//  scanf("%1023s", text);
  fgets(text, 1024, stdin);
  text[strcspn(text, "\n")] = '\0';

  int grade_level = coleman_liau(text);

  if (grade_level < 1) printf("Before Grade 1\n");
  else if (grade_level >= 1 && grade_level <= 16) printf("Grade %i\n", grade_level);
  else printf("Grade 16+\n");

  return 0;
}

float coleman_liau(char text[])
{
  int letter_counter = 0;
  int word_counter = 1;
  int sentence_counter = 0;

  for (int i = 0; text[i] != '\0'; i++)
  {
    if ((text[i] >= 'a' && text[i] <= 'z') ||
        (text[i] >= 'A' && text[i] <= 'Z')) letter_counter++;
    else if ( text[i] == ' ' ) word_counter++;
    else if ( text[i] == '.' ||
              text[i] == '!' ||
              text[i] == '?') sentence_counter++;
    else continue;
  }

//  printf("Letters: %i\nWords: %i\nSentences: %i\n", letter_counter, word_counter, sentence_counter);

  float letters_avg = ((float)letter_counter / word_counter) * 100.00;
  float sentences_avg = ((float)sentence_counter / word_counter) * 100.00;
  float index = ((0.0588 * letters_avg) - (0.296 * sentences_avg)) - 15.8;

//  printf("Letters Avg: %f\nSentences Avg: %f\nIndex: %f\n", letters_avg, sentences_avg, index);

  return round(index);
}