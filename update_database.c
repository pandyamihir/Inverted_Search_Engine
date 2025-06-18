#include "inverted_search.h"

// Function to update the database by adding a new file
void update_database(Wlist* head[], Flist** f_head)
{
    int empty;  // Variable to check if the file is empty or not
    char file_name[FNAME_SIZE];  // Buffer to hold the input filename

    // Prompt the user to enter the filename to be added to the database
    printf("Enter the filename do you want to add in Database: ");
    scanf("%s", file_name);
        
    // Validate if the specified file is empty or not
    empty = isFileEmpty(file_name);
    if (empty == FILE_NOTAVAILABLE)
    {
        // If the file is not available, notify the user and exit
        printf("The file %s is not available\n", file_name);
        printf("Hence we are not adding this into File Linked List\n");
        return;
    }
    else if (empty == FILE_EMPTY)
    {
        // If the file is empty, notify the user and exit
        printf("The file %s is Empty\n", file_name);
        printf("Hence we are not adding %s into File Linked List\n", file_name);
        return;
    }
    else
    {
        // If the file is valid, add it to the linked list
        int result = to_create_list_of_files(f_head, file_name);	        
        if (result == SUCCESS)
        {
            // If the file was successfully inserted, notify the user
            printf("Successful in Inserting file %s into the File Linked List\n", file_name);
        }
        else if (result == REPEATATION)
        {
            // If the file is a duplicate, notify the user
            printf("This file %s is Repeated\n", file_name);
            printf("Hence we are not adding %s into file Linked List\n", file_name);
            return;
        }
        else
        {
            // If there was an error adding the file, notify the user
            printf("Failed to add the file into the File Linked List");
            return;
        }   
    }

    // After successful insertion of the file into the file linked list
    Flist* f_temp = *f_head;  // Temporary pointer to traverse the file linked list
    while (f_temp)
    {	
        // Compare the current file in the linked list with the new filename
        if (!strcmp(f_temp->file_name, file_name))
        {
            // If a match is found, create the database for the file
            create_database(f_temp, head);
            return;
        }
        f_temp = f_temp->link;  // Move to the next file in the list
    }
    
    // Notify the user that the database has been updated successfully
    printf("Database updated successfully!!\n");
}
