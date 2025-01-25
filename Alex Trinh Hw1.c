// Alex Trinh
// Homework 1
// hw1-G01310551.c

#include <stdio.h>
int main()
{
   int number;
   
   printf("Enter an integer: ");
   scanf("%d", &number);
   
   //Check if number is even
   if(number % 2 == 0)
   {
   printf("%d is even.\n", number);
   }
   else
   {
   printf("%d is odd\n", number);
   }
   return 0;
}