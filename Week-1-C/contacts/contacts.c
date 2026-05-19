#include <stdio.h>

int main(void) {
  char name[50];
  int age;
  char phoneNumber[50];
  char location[50];
  printf("Name: ");
  scanf("%49s", name);
  printf("Age: ");
  scanf("%d", &age);
  printf("Phone Number: ");
  scanf("%49s", phoneNumber);
  printf("Location: ");
  scanf("%49s", location);
  printf("New contact: %s, %i, lives in %s and can be reached at %s\n", name, age, location, phoneNumber);
  return 0;
}