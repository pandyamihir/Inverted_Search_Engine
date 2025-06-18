#include "inverted_search.h" // Include the header file with necessary declarations and structures

char *fname; // Global pointer to store filename

// Function to create a database from files in the file linked list
void create_database(Flist *f_head, Wlist *head[])
{
    // Traverse through the file linked list
    while (f_head)
    {
        // Call read_datafile to read and insert words into the database for each file
        read_datafile(f_head, head, f_head->file_name);
        
        // Move to the next file in the linked list
        f_head = f_head->link;
    }
}

/* Function to read data from a file and populate the word linked list */
Wlist *read_datafile(Flist *file, Wlist *head[], char *filename)
{
    fname = filename; // Store the current file name in the global pointer

    // Open the file in read mode
    FILE *fptr = fopen(filename, "r");
    
    char word[WORD_SIZE]; // Array to store each word read from the file
    int flag = 1; // Flag to indicate if a word is already in the database

    // Check if the file is successfully opened
    if (fptr == NULL)
    {
        printf("Error in opening %s file\n", filename);
        return NULL;
    }

    // Read each word from the file using fscanf
    while (fscanf(fptr, "%s", word) != EOF)
    {
        // Calculate the index based on the first character of the word (a-z)
        int index = tolower(word[0]) % 97;

        // If the character is not an alphabet, assign index 26 for non-alphabet words
        if (!(index >= 0 && index <= 25))
            index = 26;

        // Check if there are words already stored at this index
        if (head[index] != NULL)
        {
            Wlist *temp = head[index]; // Temporary pointer to traverse the word linked list

            // Traverse through the word list to check for duplicate words
            while (temp)
            {
                // If the word is already present, update its count in the corresponding file
                if (!strcmp(temp->word, word))
                {
                    update_word_count(&temp, filename); // Update word count for the file
                    flag = 0; // Set flag to indicate that the word already exists
                    break; // Exit the loop as we found the word
                }
                temp = temp->link; // Move to the next word in the list
            }
        }

        // If the word is not found in the list, insert it as a new word at the end
        if (flag == 1)
        {
            insert_at_last(&head[index], word); // Insert the new word at the last position
        }
    }

    // Close the file after reading all the words
    fclose(fptr);

    printf("Successfully created database for %s file\n", filename);
    return NULL;
}

/* Function to update the word count in the linked list table for a given word */
int update_word_count(Wlist **head, char *file_name)
{
//ltable == sub_node
//Wlist == main_node
    Ltable* l_temp = (*head)->Tlink; // Pointer to traverse the link table for the word
    Ltable* prev = NULL; // Pointer to track the previous node

    // Traverse the link table to find the file name
    while (l_temp)
    {
        // Check if the current file name matches the file name in the link table
        if (!strcmp(l_temp->file_name, file_name))
        {
            l_temp->word_count++; // Increment the word count for the file
            return SUCCESS; // Return success after updating the count
        }
        prev = l_temp; // Update previous node pointer
        l_temp = l_temp->table_link; // Move to the next node in the link table
    }

    // If the file name is not found, increment and update the file count
    (*head)->file_count++;

    // Allocate memory for a new node in the link table
    Ltable* new_link_table_node = malloc(sizeof(Ltable));

    // Check for memory allocation failure
    if (new_link_table_node == NULL)
    {
        return FAILURE; // Return failure if memory allocation fails
    }

    // Update the new link table node with file name and word count
    strcpy(new_link_table_node->file_name, file_name);
    new_link_table_node->word_count = 1; // Set initial word count to 1
    new_link_table_node->table_link = NULL; // Set next pointer of the node to NULL

    // Establish the link between the previous node and the new node
    if (prev) // If there's a previous node, link it to the new node
    {
        prev->table_link = new_link_table_node;
    }
    else // If there's no previous node, update the head's link table
    {
        (*head)->Tlink = new_link_table_node;
    }

    return SUCCESS; // Return success after inserting the new node
}