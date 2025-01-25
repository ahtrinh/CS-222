//Alex Trinh
//Homework 2 (hw2-G01310551.c)

#include <stdio.h>

//define get_input function
int get_input()
{
    //declare integer num
    int num;
    
    //constructed do while loop
    do
    {
        //Prompt user with enter integer
        printf("Enter an Integer[1,999999]: ");
        scanf("%d",&num);
        
        //check if num is less than 1 or greater than 999999
        if(num < 1 || num > 999999)
            
            //Print error message that the number is out of range
            printf("Number out of range.\n");
    }
    //check while num is less than 1 or greater than 999999
    while(num < 1 || num > 999999);
        
        //return num value
        return num;
}

//define display function
int display(int val)
{
    //declare current value 
    int cur_val;
    
    //declare right most digit value
    int rightmost_digit;
    
    //declare total int to calculate right most digits
    int total = 0;
    
    //check while current value is greater than 0
    while(cur_val > 0)
    {
        //find right most digit of current value by modding by 10
        rightmost_digit = cur_val%10;
       
        //cut off right most digit from the current value by dividing by 10
        cur_val /= 10;
        
        //add right most digit to total
        total += rightmost_digit;
        
        //print column of right most digits
        printf("%d\n",rightmost_digit);
    }
    //Check if total can be divided by 9
    if(total % 9 == 0)
    {
        //Print value is divisible by 9
        printf("%d is divisible by 9\n",val);
        return 0;
    }
        // Else total cannot be divided by 9
        else
        {
            //Print value is not divisible by 9
            printf("%d is not divisible by 9\n",val);
            return 1;
        }
    }
int main()
{
    //declare integer number
    int number;
    
    //declare integer result 
    int result;
    
    //Call function to get user input
    number = get_input();
    //Call function to display the result
    result = display(number);
    
    return result;
    
}
