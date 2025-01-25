//Alex Trinh
//Homework 5 (hw5-G01310551.c)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
/*
 * =============================================================================
 * DATA STRUCTURES
 * =============================================================================
 */
struct address_t
{
    int octet[4];
    char alias[10];
};

struct checkAddress_t
{
    int octet[4];
    char alias[80];
};

/*
 * =============================================================================
 * FUNCTION PROTOTYPES
 * =============================================================================
 */
char *getDateAndTime();
struct address_t *readDataFile(char [], unsigned long *);
int checkAlias(struct checkAddress_t);
int checkAddress(struct checkAddress_t);
void generateLocalityRpt(char [], struct address_t *, unsigned long);

char *getDateAndTime()
{
    time_t t;
    time(&t);
    return ctime(&t); //returns current date and time
}

struct address_t *readDataFile(char fileName[], unsigned long *num_valid)
{

    FILE *fptr;  // File pointer to read data file
    FILE *errorfptr; // File pointer for error report
    int done = 0; // Flag used to check if looping through the file is done
    int i = 0; // Looping variable
    struct address_t data; // Temporary data structure to store the network alias address
    struct checkAddress_t checkData; // Validate data read in
    char line[80]; // Used to store a line of input from file
    char message[80] = ""; // Used for generating debugging messages
    char strToUpper[80] = ""; // Convert the network alias address to uppercase
    char errorFileName[] = "CS222_Error_Report";
    int indexptr = 0; // Store good ip addresses


    // Open file for reading
    if ((fptr = fopen(fileName, "r")) == NULL) {
        printf("[ERROR] Failed to open '%s' for reading!\n", fileName);
        exit(1);
    }

    // Open file for writing to error report
    if ((errorfptr = fopen(errorFileName, "w")) == NULL) {
        printf("[ERROR] Failed to open '%s' for writing!\n", errorFileName);
        exit(1);
    }

    // ROUND 1
    // STEP 1: READ THE FILE
    // STEP 2: CHECK FOR INVALID ENTRIES
    // STEP 3: REPORT INVALID ENTRIES TO ERROR FILE
    // STEP 4: COUNT VALID NUMBER OF ENTRIES
    do {
        // Read a line from the file
        fgets(line, 80, fptr);

        // Remove the hard return from line read in
        line[strlen(line)-1] = '\0';

        // Check for end of file
        if (feof(fptr)) {
            // Update flag to terminate loop
            done = 1;
        }
        else {
            // sprintf(message, "[Line] %s", line);

            sscanf(line, "%d.%d.%d.%d %s", &checkData.octet[0], &checkData.octet[1], &checkData.octet[2], &checkData.octet[3], checkData.alias);
            // printf("%d.%d.%d.%d %s\n", data.octet[0], data.octet[1], data.octet[2], data.octet[3], data.alias);

            // Terminate processing when sentinel IP address (0.0.0.0) is found
            if ((checkData.octet[0] == 0) && (checkData.octet[1] == 0) && (checkData.octet[2] == 0) && (checkData.octet[3] == 0)) {
                done = 1;
            }
            else
            {
                //check if entry has a valid ip address and alias
                if(checkAddress(checkData) && checkAlias(checkData))
                {
                    (*num_valid)++; // increment valid address counter
                }
                //report invalid address to error file
                else
                {
                    fprintf(errorfptr, "%s\n", line);
                }
            }
        }
    } while (!done);

    // ROUND 2
    // STEP 1: REWIND FILE
    // STEP 2: DYNAMICALLY ALLOCATE ARRAY
    // STEP 3: READ THE FILE
    // STEP 4: PARSE VALID ENTRIES ONLY
    // STEP 5: POPULATE DYNAMICALLY ALLOCATED ARRAYS WITH ADDRESSES AND ALIASES

    // Rewind data file
    rewind(fptr);

    // Dynamically allocate array with addresses and aliases
    struct address_t *ip_addressptr = (struct address_t*) malloc((*num_valid) * sizeof(struct address_t));

    // Reset done flag for do loop
    done = 0;
    do {
        // Read a line from the file
        fgets(line, 80, fptr);

        // Remove the hard return from line read in
        line[strlen(line)-1] = '\0';

        // Check for end of file
        if (feof(fptr)) {
            // Update flag to terminate loop
            done = 1;
        }
        else {
            // printf("[Line] %s\n", line);

            sscanf(line, "%d.%d.%d.%d %s", &checkData.octet[0], &checkData.octet[1], &checkData.octet[2], &checkData.octet[3], checkData.alias);
            //printf("[READ] %d.%d.%d.%d %s\n", checkData.octet[0], checkData.octet[1], checkData.octet[2], checkData.octet[3], checkData.alias);

            // Terminate processing when sentinel IP address (0.0.0.0) is found
            if ((checkData.octet[0] == 0) && (checkData.octet[1] == 0) && (checkData.octet[2] == 0) && (checkData.octet[3] == 0)) {
                done = 1;
            }
            else
            {
                //check to see if there is valid address and alias
                if(checkAddress(checkData) && checkAlias(checkData))
                {
                    // Convert all alias letters to uppercase
                    for (i=0; checkData.alias[i] != '\0'; i++) {
                        strToUpper[i] = toupper(checkData.alias[i]);
                    }
                    // Terminate string properly
                    strToUpper[i] = '\0';

                    // Replace the original alias string with all uppercase letters
                    strcpy(checkData.alias, strToUpper);

                    // Add IP address and alias record to address
                    for (i=0; i<4; i++) {
                        ip_addressptr[indexptr].octet[i] = checkData.octet[i];
                    }
                    strcpy(ip_addressptr[indexptr].alias, strToUpper);
                    indexptr++;
                }
            }
        }
    } while (!done);

    // Close the file
    fclose(fptr);

    // Close the file
    fclose(errorfptr);

    // Return the total number of network aliases read from input data file
    return ip_addressptr;
}

//checks for valid address
int checkAddress(struct checkAddress_t address)
{
    for(int i=0; i<4; i++) //iterate through individual octets
    {
        if((address.octet[i] < 0) || (address.octet[i] > 255)) //check each octet to see if value is out of range
        {
            return 0; //return false
        }
    }
    return 1; //return true when valid ip address
}

//checksAlias
int checkAlias(struct checkAddress_t address)
{
    if((strlen(address.alias) > 0) && (strlen(address.alias) <= 10)) //check if alias string range is valid
    {
        return 1; //return true
    }
    else
    {
        return 0; //return false
    }
}

//generates locality report
//username
//ip_address - pointer to array
//num address - number of ip addresses
void generateLocalityRpt(char username[50], struct address_t *ip_addressptr, unsigned long num_address)
{
    char dateTime[80]; //datetime string
    int locality[256][256] = {0}; //locality array
    FILE *fptr;        // File pointer to write to
    char fileName[] = "CS222_Locality_Report"; // File name
    int i,j,k; // Looping variable
    int num_locality = 0; // number of localities
    int rpt_loc_counter = 0;

    //get the current date and time
    strcpy(dateTime,getDateAndTime());

    // Count number of localities and IP addresses in each locality
    for(i=0;i<num_address;i++)
    {
        if(locality[ip_addressptr[i].octet[0]][ip_addressptr[i].octet[1]] == 0)
        {
            // Count number of localities
            num_locality++;
        }
        // Count IP address in locality
        locality[ip_addressptr[i].octet[0]][ip_addressptr[i].octet[1]]++;
    }

    // Open file for writing
    fptr = fopen(fileName, "w");

    if (fptr == NULL)
    {
        // Print error message when system cannot open file for writing
        printf("*** ERROR ***: Can not open a file (%s) for writing!\n", fileName);
        exit(1);
    }
    else
    {
        // Write the name and datestamp to file
        fprintf(fptr, "%s %s\n", username, dateTime);

        // Write the report header to file
        fprintf(fptr, "CS222 Network Locality Report\n");
        fprintf(fptr, "Address total:%d\n",num_address);
        fprintf(fptr, "Localities:%d\n",num_locality);

        // Iterate through all possible locality combinations
        for (i=0; i<256; i++) {
            for (j=0; j<256; j++) {
                // If there is locality data, include in the report
                if (locality[i][j]) {
                    // Used to print the unique locality address only once in the report
                    rpt_loc_counter = 0;

                    // Iterate through all valid IP addresses
                    for(k=0; k<num_address; k++) {
                        // Only print when the valid IP address and locality address matches for the report
                        if ((ip_addressptr[k].octet[0] == i) && (ip_addressptr[k].octet[1] == j)) {
                            // Only print the locality address header when first encountered
                            if (rpt_loc_counter == 0) {
                                // Print the locality address header
                                fprintf(fptr, "\n%d.%d\n", i, j);

                                // Increment the counter so the header only prints once
                                rpt_loc_counter++;
                            }

                            // Print the alias within the locality address
                            fprintf(fptr, "%-10s\n", ip_addressptr[k].alias);
                        }
                    }
                }
            }
        }
    }
}


int main()
{
    struct address_t *ip_addressptr; //pointer to array of ip address and alias
    char username[50]; //username
    unsigned long num_address = 0; //number of ip addresses

    printf("Enter Your Name: ");
    fgets(username,50,stdin);
    username[strlen(username)-1] = '\0';

    // Read the data file
    ip_addressptr = readDataFile("CS222_Inet.txt", &num_address);

    // Generate the locality report
    generateLocalityRpt(username,ip_addressptr,num_address);

}
