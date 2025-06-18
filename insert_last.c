#include "inverted_search.h"  // Include the header file with necessary declarations and structures

// `fname` is declared as an external variable, indicating that it is defined in another file
extern char* fname;

// Function to insert a new word at the end of the word linked list (Wlist)
int insert_at_last(Wlist **head, data_t *data)
{
    // Allocate memory for a new node of type Wlist
    Wlist *new = malloc(sizeof(Wlist));

    // If memory allocation fails, return FAILURE
    if (new == NULL)
    {
        return FAILURE;
    }

    // Initialize the new node with the word data and set initial values
    new->file_count = 1;              // Set file count to 1 as it's the first occurrence of the word
    strcpy(new->word, data);          // Copy the word data into the new node's word field
    new->Tlink = NULL;                // Initialize the link to the link table (Ltable) to NULL
    new->link = NULL;                 // Initialize the link to the next word node to NULL

    // Call the function `update_link_table` to create and add a link table node (Ltable) to the new word node
    update_link_table(&new);

    // Check if the word linked list (`Wlist`) is empty
    if (*head == NULL)
    {
        // If the list is empty, set the new node as the head of the list
        *head = new;
        return SUCCESS;               // Return SUCCESS after adding the new node
    }

    // If the word linked list is not empty, traverse to the last node
    Wlist *temp = *head;
    while (temp->link)
    {
        temp = temp->link;            // Move to the next node in the word list
    }

    // Set the new node as the last node's next link
    temp->link = new;
    return SUCCESS;                   // Return SUCCESS after inserting the new node at the end
}

// Function to update the link table for a given word node in the word linked list (Wlist)
int update_link_table(Wlist **head)
{
    // Allocate memory for a new node of type Ltable (link table node)
    Ltable *new = malloc(sizeof(Ltable));

    // If memory allocation fails, return FAILURE
    if (new == NULL)
    {
        return FAILURE;
    }

    // Initialize the new link table node with file name and word count
    new->word_count = 1;              // Set word count to 1 as it's the first occurrence of the word in this file
    strcpy(new->file_name, fname);    // Copy the current file name (`fname`) into the file name field of the link table
    new->table_link = NULL;           // Initialize the link to the next link table node to NULL

    // Set the `Tlink` of the current word node to the new link table node
    (*head)->Tlink = new;
    return SUCCESS;                   // Return SUCCESS after creating and linking the new link table node
}
