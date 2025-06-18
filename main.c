/*************************************************************************************************
*Author		:MIHIR PANDYA
*Date		:Tue 29 Oct 2024
*File		:main.c
*Title		:Driver function
*Description	:This function acts like the driver function for the project inverted search
**************************************************************************************************/
#include "inverted_search.h"  

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("ERROR : Enter a valid number of arguments.\n");
        return 0;  // Exit the program as there are no valid file inputs
    }

    // Create the file list
    // Declare the file head pointer for the linked list of files
    Flist *f_head = NULL;

    // Validate and populate the file linked list with provided file names
    file_validation_n_file_list(&f_head, argv);
    
    // Check if the file list is empty after validation
    if (f_head == NULL)
    {
        printf("ERROR : No valid files are available in the file linked list.\n");
        return 1;  // Exit the program as no valid files are found
    }

    // Prompt the user for various operations
    int choice;              // Variable to store user choice
    char option;             // Variable to store the user's option to continue or not
    char word[WORD_SIZE];    // Buffer to store the word to be searched
    Wlist *head[27] = {NULL};  // Array of pointers to Wlist to hold the database for words (26 letters + special case)

    do
    {
        // Display menu options to the user
        printf("Select your choice among the following options:\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Update Database\n");
        printf("4. Search Database\n");
        printf("5. Save Database\n");
        printf("6.Exit\n");
        printf("Enter your Choice: ");
        scanf("%d", &choice);  // Read the user's choice
    
        switch (choice)
        {
            // Create the word database
            case 1:
                create_database(f_head, head);  // Call function to create database from file list
                break;
            
            // Display the word database
            case 2:
                display_database(head);  // Call function to display the database
                break;

            // Update the word database with new files
            case 3:
                update_database(head, &f_head);  // Call function to update the database with new files
                break;

            // Search for a specific word in the database
            case 4:
                printf("Enter the word you want to search: ");
                scanf("%s", word);  // Read the word to be searched
                search_database(head[tolower(word[0]) % 97], word);  // Call function to search for the word in the database
                break;

            // Save the current database to a file
            case 5:   
                save_database(head);  // Call function to save the database
                break;
            case 6 :
                exit(0);
            // Handle invalid input
            default:
                printf("Invalid choice! Please select a valid option.\n");
                break;
        }
        
    } while(choice != 6); 
    
    return 0;  // Exit the program successfully
}