#include "inverted_search.h" // Include the necessary header file for structures and declarations

// Function to display the word database with file names and their word counts
void display_database(Wlist *head[])
{
    // Print the header for the database display
    printf("[index]        [word]        file_count file/s :         File: File_name     word_count\n");

    // Iterate through the `head` array of word lists for all 27 indices (0-25 for 'a-z' and 26 for non-alphabet characters)
    for (int i = 0; i < 27; i++)
    {
        Wlist *temp = head[i]; // Temporary pointer to traverse the word list at index `i`

        // Traverse through the linked list of words at the current index until the last node
        while (temp != NULL)
        {
            // Print the index, word, and number of files the word appears in
            printf("[%d]            [%s]            %d file/s:\t  ", i, temp->word, temp->file_count);

            // Pointer to traverse the link table that contains files for the current word
            Ltable *Thead = temp->Tlink;

            // Traverse through the linked list of files in the link table
            while (Thead != NULL)
            {
                // Print the file name and word count in that file
                printf("       File : %s       %d\t", Thead->file_name, Thead->word_count);
                
                // Move to the next file node in the link table
                Thead = Thead->table_link;
            }

            // Print a new line after displaying all files for the current word
            printf("\n");

            // Move to the next word in the word list
            temp = temp->link;
        }
    }
}