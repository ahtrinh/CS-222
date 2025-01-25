//Alex Trinh
//Homework 3 (hw3-G01310551.c)

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

//Function Prototypes
char *getDateAndTime();
int	getInteger();
void decimalToBinary(int decValue,char binString[]);
void decimalToHex(int decValue, char hexString[]);
void decimalToOct(int decValue, char octString[]);
int saveFile(char name[], char dateTime[], int decValue, char octstring[],
             char hexString[], char binString[]);

/*
--------------------------------------------------------------------
Returns a character string with the current date and time
--------------------------------------------------------------------
*/
char *getDateAndTime()
{
    time_t t;
    time(&t);
    return ctime(&t); //returns current date and time
}
/*
--------------------------------------------------------------------
Read user input into a character stirng using fgets().
"x" returns -1 indicating program exit.
Otherwise, convert the string into an integer (which will be returned
to main()) using int atoi(const char *str);
or
int sscanf(const char *s, const char *format, ...);
--------------------------------------------------------------------
*/
int getInteger()
{
    char inputStr[32];
    char *pos; //pointer to character used for position
    
    //read input string
    printf("Enter an Integer [1 - 1,000,000] or type x to exit: ");
    fgets(inputStr, sizeof(inputStr), stdin);
    
    //replace hard return with end of string character
	if ((pos=strchr(inputStr,'\n')) != NULL)
	    *pos = '\0';
    
    //check for exit
	if ((pos=strchr(inputStr,'x')) != NULL)
	    return -1;
	else
	    return atoi(inputStr);
}
/*
----------------------------------------------------------------------------
Accepts a decimal value decValue and a character string buffer binString[].
Convert decvalue into its corresponding binary value and store the result as
a character string within binString[]. binString[] may then be displayed from
within main().
Paramters:
decValue: decimal value
binString: converted binary string
----------------------------------------------------------------------------
*/
void decimalToBinary(int decValue, char binString[])
{
    int quotient; // quotient 
    int binNumber[100]; //array of integers to store each digit
    int i=0, j, k=0;

    quotient = decValue;
    
    //keep converting until quotient > 0
    while (quotient > 0) 
    {
        binNumber[i] = quotient % 2; //Gets remainder
        quotient /= 2; //Divides number by 2
        i++; //increments index
    }
    
    //prints binary string in reverse order
    for(j=i-1; j>=0; j--)
    {
        binString[k] = 48+binNumber[j]; //converting integer to ascii character
        k++; //increment index
    }
    binString[k] = '\0'; //terminate string properly
}
/*
--------------------------------------------------------------------
Accepts a decimal value decValue and a character string buffer 
hexString[]. Convert decvalue into its corresponding hexadecimal value
and store the result as a character string within hexString[].
hexString[] may then be displayed from within main().
Paramters:
decValue: decimal value
hexString: converted hex string
--------------------------------------------------------------------
*/
void decimalToHex(int decValue, char hexString[])
{
    int quotient; //quotient
    int hexNumber[100]; //array of integers 
    int i=0, j, k=0; //index of arrays

    quotient = decValue;
    
    //keep converting until quotient > 0
    while (quotient > 0)
    {
        hexNumber[i] = quotient % 16; //gets remainder
        quotient /= 16; //divide number by 16 (hex)
        i++; //increment index
    }
    //prints hex string in reverse order
    for(j=i-1; j>=0; j--)
    {
        if(hexNumber[j]>9)
            hexString[k] = 65 + hexNumber[j] - 10; //Get letters for hex A-F
        else
            hexString[k] = 48 + hexNumber[j]; //Numbers 0-9
        k++; //increment index
    }
    hexString[k] = '\0'; //terminate string 
}

/*
--------------------------------------------------------------------
Accepts a decimal value decValue and a character string buffer octString[].
Convert decvalue into its corresponding octal value and store the result
as a character string within octString[]. octString may then be displayed
from within main().
Paramters:
decValue: decimal value
octString: converted octal string
--------------------------------------------------------------------
*/
void decimalToOct(int decValue, char octString[])
{
    int quotient; //quotient
    int octNumber[100]; //array of integers
    int i=0, j, k=0; //index of arrays

    quotient = decValue;
    
    //keep converting until quotient > 0
    while (quotient > 0)
    {
        octNumber[i] = quotient % 8; //get remainder
        quotient /= 8;  //divide number by 8 (octal)
        i++; //increment index
    }
    
    //print octal string in reverse order
    for(j=i-1; j>=0; j--)
    {
        octString[k] = 48+octNumber[j]; //converts integer to character string
        k++; //increment index
    }
    octString[k] = '\0'; //terminate string
}

/*
--------------------------------------------------------------------
Prompt the user whether the output should be saved to a text file. If
user replies in the affirmative, a name for the text file is requested.
The newly created text file will contain the user's name, current date,
and output results. If the output file cannot be opened, print an
appropriate error message and return 0. Otherwise return 1;
Paramters:
char name: username
dateTime: date and time
decValue: decimal value
octString: converted octal string
hexString: converted hex string
binString: converted binary string
--------------------------------------------------------------------
*/
int saveFile(char name[], char dateTime[], int decValue, char octString[], char hexString[], char binString[])
{
    char saveToFile;
    char fileName[32];
    char *pos;
    FILE *fptr;
    do
    {
        //read input string
        printf("Save to a file? (y/n): ");
        scanf("%c",&saveToFile);
        //gets rid of hard return
        while (getchar() != '\n');
    
        //check if char is y, operation to save file
	    if (saveToFile == 'y')
	    {   
	        
	        printf("\nEnter file name: "); //prompt user for file name
	        fgets(fileName, sizeof(fileName), stdin); //get file name from stdin
	   
	        //replaces hard return with end of string character
	        if ((pos=strchr(fileName,'\n')) != NULL)
	            *pos = '\0'; //terminate string 
	            
	        fptr = fopen(fileName, "w"); //open file
	        
	        if (fptr == NULL) //check if file open successfully
	            return 0; //exit when file fail to open
	        else
	        {
	            //writing output to file
	            fprintf(fptr,"%s\n",name);
	            fprintf(fptr,"Today's date: %s\n",dateTime);
	            fprintf(fptr,"Decimal: %d\n", decValue);
	            fprintf(fptr,"Hexadecimal: %s\n", hexString);
	            fprintf(fptr,"Octal: %s\n", octString);
	            fprintf(fptr,"Binary: %s\n", binString);
            
                fclose(fptr); //close file 
                printf("File saved.\n\n");
                return 1;
	        }
	    }
	    //check if char is n
	    else if (saveToFile == 'n')
	        return 1; //exit since not saving file
	    else
	        printf("Error: illegal value\n"); //print error message
    }
    //keep looping until y or n
    while (saveToFile != 'y' || saveToFile != 'n');
    
    return 0;
}

int main()
{
    char dateTime[32]; //date and time string
	char name[32];	// username
	char binString[32]; //converted binary string
	char octString[32]; //converted octal string
	char hexString[32]; //converted hex string
	char *pos; //pointer variable used to replace hard return with \0
	
	int	decValue = 0; //value entered by user
	int	saveSuccess = 0; //exit status of save file
	int done = 0; //used for looping
	
	//get the current date and time		
	strcpy(dateTime,getDateAndTime());
	
	//read in name 
	printf("Enter your name: ");
	fgets(name,sizeof(name),stdin);
	//replace hard return with end of string character
	if ((pos=strchr(name,'\n')) != NULL)
	    *pos = '\0'; //terminates string
	
	while (!done) //loop forever until user exits
	{
    	do //keep looping until valid input
	    {
    	    //read integer input
	        decValue = getInteger();
	
	        //	exit clause
	        if (decValue == -1)
	        {
	            printf("\nGoodbye!\n");
	            return	0;
	        }
	        //check if input is within range
	        else if (decValue < 1 || decValue > 1000000)
	            printf("Error: %d is out of range\n", decValue);
	
	    } while (decValue < 1 || decValue > 1000000);
	
	    //run conversions	
	    decimalToBinary(decValue, binString);
	    decimalToHex(decValue, hexString);
	    decimalToOct(decValue, octString);
	
	    //print	conversions	to	the	console	
	    printf("\nDecimal: %d\n",	decValue);
	    printf("Hexidecimal: %s\n",	hexString);
	    printf("Octal: %s\n", octString);
	    printf("Binary: %s\n\n", binString);

	    //save the file
	    saveSuccess	= saveFile(name, dateTime, decValue, octString, hexString, binString);
	    if (!saveSuccess) // equivalent	to:	if (saveSuccess == 0)
	        printf("Error: cannot open file\n");
    }
}
