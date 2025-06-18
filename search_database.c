#include "inverted_search.h"

// Function to search for a specific word in the database
void search_database(Wlist *head, char *word)
{
    // Check if the word list is empty
    if (head == NULL)
    {
        printf("Search word is not available in the list as list is empty\n");
        return;  // Exit the function if the list is empty
    }
    
    // Traverse the word list to find the specified word
    while (head)
    {
        // Compare the search word with the current word in the list
        if (!(strcmp(head->word, word)))
        {
            // If the word is found, print the word and the number of files it appears in
            printf("Word %s is present in %d file\n", head->word, head->file_count);

            // Access the link table to retrieve file-specific details
            Ltable *Thead = head->Tlink;

            // Traverse the link table to print details for each file containing the word
            while (Thead)
            {
                // Print the name of the file and the number of times the word appears in that file
                printf("In File : %s\t%d time/s \n", Thead->file_name, Thead->word_count);
                
                // Move to the next entry in the link table
                Thead = Thead->table_link;
            }
            return;  // Exit the function after finding the word
        }
        
        // Move to the next word in the word list
        head = head->link;
    }
    
    // If the word was not found in the list, print an error message
    printf("Error: Search word is not found in list \n");
}
