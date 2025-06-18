#include "inverted_search.h"

// Function to save the database to a file specified by the user
void save_database(Wlist *head[])
{
    // Prompt the user to enter the name of the file to save the database
    char file_name[FNAME_SIZE];
    printf("Enter the file name\n");
    scanf("%s", file_name);  // Read the file name from the user

    // Open the specified file in write mode ("w")
    FILE *fptr = fopen(file_name, "w");
    
    // Check if the file was successfully opened
    if (fptr == NULL)
    {
        printf("Error opening file %s. Database not saved.\n", file_name);
        return;
    }

    // Iterate through the `head` array to find non-empty word lists
    for (int i = 0; i < 27; i++)
    {
        // If the list at index `i` is not empty, write its contents to the file
        if (head[i] != NULL)
        {
            write_databasefile(head[i], fptr);  // Call function to write the list to the file
        }
    }

    printf("Database saved\n");  // Confirm that the database has been saved successfully
}

// Function to write a single word list and its associated file details to the database file
void write_databasefile(Wlist *head, FILE* databasefile)
{
    // Write the index header (e.g., # [0]) for the word list in the file
    fprintf(databasefile, "#[%d]", tolower(head->word[0]) % 97);  
    fprintf(databasefile, "\n");  // Move to the next line

    // Traverse through the word list and write each word's details
    while (head)
    {
        // Print the word, its file count, and other related details to the file
        fprintf(databasefile, "word is ");
        fprintf(databasefile, "[%s]: ", head->word);  // Write the word to the file
        fprintf(databasefile, "file count is ");
        fprintf(databasefile, "%d:file/s: ", head->file_count);  // Write the file count
        
        // Traverse through the link table (Ltable) to get file-specific details
        Ltable *temp = head->Tlink;
        while (temp)
        {
            // Write the file name and word count to the file
            fprintf(databasefile, "file is ");
            fprintf(databasefile, "%s: ", temp->file_name);  // Write the file name
            fprintf(databasefile, "word count is ");
            fprintf(databasefile, "%d \n", temp->word_count);  // Write the word count in that file
            
            // Move to the next file in the link table
            temp = temp->table_link;
        }
        
        // Move to the next word in the word list
        head = head->link;
        
        fprintf(databasefile, "\n");  // Add a newline to separate word entries
    }
}