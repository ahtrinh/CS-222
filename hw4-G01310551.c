//Alex Trinh
//Homework 4 (hw4-G01310551.c)

/*
 * =============================================================================
 * MODULES
 * =============================================================================
 */
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * =============================================================================
 * DATA STRUCTURES
 * =============================================================================
 */
struct address_t {
    int octet[4];
    char alias[10];
};

/*
 * =============================================================================
 * FUNCTION PROTOTYPES
 * =============================================================================
 */
char* getDateAndTime();
int Read_Data_File(char fileName[], struct address_t *);
void Generate_Alias_List(char name[], struct address_t *, int n);
void bubbleSort(struct address_t *, int n, char sort_order);
void pretty(char funcname[], char message[]);
void prettyList(struct address_t *, int n);

/*
 * =============================================================================
 * CONSTANTS
 * =============================================================================
 */
#define DEBUG 0

/*
 * =============================================================================
 * FUNCTION: pretty
 * =============================================================================
 * Displays pretty debugging message
 */
void pretty(char funcname[], char message[]) {
    char padding[5] = ""; // Used for padding spaces

    if (DEBUG) {
        if (strcmp(funcname, "main")) {
            // Pad 3 spaces if not in main function
            strcpy(padding, "   ");
        }
        printf("[%20s] %s%s\n", funcname, padding, message);
    }
}

/*
 * =============================================================================
 * FUNCTION: prettyList
 * =============================================================================
 */
void prettyList(struct address_t list[100], int n) {
    pretty("prettyList", "=== START ===");
    int i; // Loop variable

    // Loop through all elements in the list
    for (i=0; i<n; i++) {
        // Print out the network alias address
        printf("[%d] %d.%d.%d.%d %s\n",i+1,list[i].octet[0],list[i].octet[1],list[i].octet[2],list[i].octet[3],list[i].alias);
    }
    pretty("prettyList", "=== END ===");
}

/*
 * =============================================================================
 * FUNCTION: getDateAndTime
 * =============================================================================
 * Returns a character string with the current date and time
 */
char *getDateAndTime() {
    time_t t; // Used to store the time using the time_t data structure
    struct tm* timeinfo; // Pointer to the time (tm) data structure
    char *cur_time[256]; // Used to store the current time string
    char mydate[256];

    // Call time to get the current date/time in seconds
    t = time(NULL);

    // Call localtime function to get the struct tm pointer
    timeinfo = ctime(&t);

    // Convert the time to a string format like the following: Oct. 22, 2022
    strftime(cur_time, 256, "%b. %#d, %Y", localtime(&t));
    pretty("getDateAndTime",cur_time);
    strcpy(mydate,cur_time);
    // Return the date stamp string
    return ctime(&t);
}

/*
 * =============================================================================
 * FUNCTION: Read_Data_File
 * =============================================================================
 */
int Read_Data_File(char fileName[], struct address_t *ptr) {
    pretty("Read_Data_File", "=== START ===");

    FILE *fptr;  // File pointer to write to
    int done = 0; // Flag used to check if looping through the file is done
    int i = 0; // Looping variable
    struct address_t data; // Temporary data structure to store the network alias address
    char line[80]; // Used to store a line of input from file
    char message[80] = ""; // Used for generating debugging messages
    char strToUpper[80] = ""; // Convert the network alias address to uppercase
    int counter = 0; // Count number of network aliases read from file

    // Open file for writing
    pretty("Read_Data_File","Opening a file to read...");
    if ((fptr = fopen(fileName, "r")) == NULL) {
        printf("[ERROR] Failed to open '%s' for reading!\n", fileName);
        exit(1);
    }

    // while ((!done) || (fgets(line, 30, fptr) != NULL)) {
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
            sprintf(message, "[Line] %s", line);
            pretty("Read_Data_File", message);

            sscanf(line, "%d.%d.%d.%d %s", &data.octet[0], &data.octet[1], &data.octet[2], &data.octet[3], data.alias);
            // printf("%d.%d.%d.%d %s\n", data.octet[0], data.octet[1], data.octet[2], data.octet[3], data.alias);

            // Convert all alias letters to uppercase
            for (i=0; data.alias[i] != '\0'; i++) {
                strToUpper[i] = toupper(data.alias[i]);
            }
            // Terminate string properly
            strToUpper[i] = '\0';

            // Replace the original alias string with all uppercase letters
            strcpy(data.alias, strToUpper);
            sprintf(message, "[Parsed] %d.%d.%d.%d %s", data.octet[0], data.octet[1], data.octet[2], data.octet[3], data.alias);
            pretty("Read_Data_File", message);

            // Terminate processing when sentinel IP address (0.0.0.0) is found
            if ((data.octet[0] == 0) && (data.octet[1] == 0) && (data.octet[2] == 0) && (data.octet[3] == 0)) {
                pretty("Read_Data_File", "Processing terminated: Found sentinel record!");
                done = 1;
            } else {
                // Add IP address and alias record to address
                for (i=0; i<4; i++) {
                    ptr[counter].octet[i] = data.octet[i];
                }
                strcpy(ptr[counter].alias, data.alias);
                counter++;
            }
        }
    } while (!done);

    // Close the file
    fclose(fptr);

    pretty("Read_Data_File", "=== END ===");

    // Return the total number of network aliases read from input data file
    return counter;
}

/*
 * =============================================================================
 * FUNCTION: Generate_Alias_List
 * =============================================================================
 */
void Generate_Alias_List(char name[], struct address_t *ptr, int n) {
    pretty("Generate_Alias_List", "=== START ===");

    FILE *fptr;        // File pointer to write to
    char fileName[80] = "222_Alias_List"; // File name
    int i; // Looping variable

    pretty("Generate_Alias_List","Opening a file to write to...");

    // Open file for writing
    fptr = fopen(fileName, "w");

    if (fptr == NULL) {
        // Print error message when system cannot open file for writing
        printf("*** ERROR ***: Can not open a file (%s) for writing!\n", fileName);
        exit(1);
    } else {
        pretty("Generate_Alias_List","Writing to file now...");
        // Write the name and datestamp to file

        //pretty("Generate_Alias_List",date);
        printf("%s",getDateAndTime());
        fprintf(fptr, "%s %s\n", name, getDateAndTime());

        // Write the report header to file
        fprintf(fptr, "CS222 Network Alias Listing\n\n");

        for (i=0; i<n; i++) {
            // Write the network alias address to file
            fprintf(fptr, "%-10s %d.%d.%d.%d", ptr[i].alias, ptr[i].octet[0], ptr[i].octet[1], ptr[i].octet[2], ptr[i].octet[3]);

            // Send a hard return except for the last line of the report to the output file
            if (i<n-1) {
                fprintf(fptr, "\n");
            }
        }
    }

    pretty("Generate_Alias_List","Closing file...");
    // Close the file appropriately
    fclose(fptr);
    printf("File saved.\n\n");

    pretty("Generate_Alias_List", "=== END ===");
}

/*
 * =============================================================================
 * FUNCTION:  bubbleSort
 * =============================================================================
 *
 */
void bubbleSort(struct address_t list[100], int n, char sort_order) {
    pretty("bubbleSort", "=== START ===");

    int i, j; // Looping variables
    struct address_t temp; // Temporary network alias data structure
    int is_swapped; // Flag used to check if swapping was performed
    int sort_it; // Flag used to check if swapping is required

    pretty("bubbleSort", "Starting Bubble Sort...");
    // Loop through each element in the list
    for (i=0; i<n-1; i++) {
        // Flag to check if swapping was performed
        is_swapped = 0;

        // Loop to compare each element in the list
        for (j=0; j<n-i-1; j++) {
            // Flag to check if swapping elements is required
            sort_it = 0;

            if (sort_order == 'A') {
                // Compare adjacent elements for swapping in ASCENDING order
                if (strcmp(list[j].alias, list[j+1].alias) > 0) {
                    // Swapping is required
                    sort_it = 1;
                }
            } else if (sort_order == 'D') {
                // Compare adjacent elements for swapping in DESCENDING order
                if (strcmp(list[j].alias, list[j+1].alias) < 0) {
                    // Swapping is required
                    sort_it = 1;
                }
            }
            if (sort_it) {
                // Swap the elements when they are not in the intended order
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;

                // Flag that swapping was performed
                is_swapped = 1;
            }
        }

        // If nothing got swapped, then exit sort
        if (is_swapped == 0) {
            pretty("bubbleSort", "Done sorting...");
            break;
        }
    }

    pretty("bubbleSort", "=== END ===");
}

/*
 * =============================================================================
 * MAIN
 * =============================================================================
 */
int main() {
    int n; // Number of network alias addresses
    struct address_t aliases[100]; // Used to store aliases read and parsed from data file
    char username[32]; // Username
    char sorting_order; // Sorting order
    int done = 0; // Flag used for looping for a valid sorting order response

    pretty("main", "=== START ===");

    // Prompt for filename
    printf("Enter your name: ");
    // Get the username and store it
    fgets(username, 32, stdin);
    // Remove the hard return from username
    username[strlen(username) - 1] = '\0';

    do {
        // Prompt for sorting order
        printf("Sorting order: enter [A]scending or [D]escending? (A/D): ");

        // Read one character input for sorting order A or D
        scanf("%c", &sorting_order);

        // Clear out the input buffer
        while (getchar() != '\n');

        // Check input for [A]scending sorting order
        if ((sorting_order == 'A') || (sorting_order == 'a')) {
            sorting_order = 'A';
            done = 1;
            // Check input for [D]escending sorting order
        } else if ((sorting_order == 'D') || (sorting_order == 'd')) {
            sorting_order = 'D';
            done = 1;
        } else {
            // Print error message for invalid inputs
            printf("*** ERROR ***: Invalid sorting order input!\nNOTE: Valid input ONLY includes a letter 'A' for ascending or a letter 'D' for descending (A/D).\n");
        }
    } while (!done);

    // Call function to read and parse data from input text file
    n = Read_Data_File("CS222_Inet.txt", aliases);
    prettyList(aliases, n);

    // Call function to sort list using the Bubble Sort algorithm
    bubbleSort(aliases, n, sorting_order);
    prettyList(aliases, n);

    pretty("main", "Calling Generate_Alias_List");
    // Call function to generate an alias list and write to file
    Generate_Alias_List("Alex Trinh", aliases, n);

    pretty("main", "=== END ===");

    // Return 0 if all goes well
    return 0;
}