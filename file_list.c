#include "inverted_search.h" 

// Function to validate files and add them to the linked list of files (`Flist`)
void file_validation_n_file_list(Flist **f_head, char *argv[])
{
    // Variable to iterate through the command-line arguments
    int i = 1, ret_val, empty;

    // Loop through the command-line arguments starting from index 1 (index 0 is the program name)
    while (argv[i] != NULL)
    {
        // Check if the file is empty or not available
        empty = isFileEmpty(argv[i]);

        // If the file is not available, display an error message and skip adding it to the linked list
        if (empty == FILE_NOTAVAILABLE)
        {
            printf("File: %s is not available\n", argv[i]);
            printf("Hence we are not adding this into File Linked List\n");
            i++; // Move to the next file
            continue; // Skip to the next iteration
        }
        // If the file is empty, display a message and skip adding it to the linked list
        else if (empty == FILE_EMPTY)
        {
            printf("File: %s is Empty\n", argv[i]);
            printf("Hence we are not adding %s into File Linked List\n", argv[i]);
            i++; // Move to the next file
            continue; // Skip to the next iteration
        }
        else
        {
            // If the file is valid (not empty), add it to the file linked list
            ret_val = to_create_list_of_files(f_head, argv[i]);

            // If the file was successfully added to the list, display a success message
            if (ret_val == SUCCESS)
            {
                printf("Successfully : Inserting file %s into the File Linked List\n", argv[i]);
            }
            // If the file is already present in the list, display a message indicating repetition
            else if (ret_val == REPEATATION)
            {
                printf("This file name : %s is repeated. So do not add more than once:\n", argv[i]);
            }
            else
            {
                // If adding the file failed due to some other reason, display an error message
                printf("Failed: to add the file into the File Linked List\n");
            }
            i++; // Move to the next file
        }
    }
}

/* Function to check if a file is empty or not available */
int isFileEmpty(char *filename)
{
    // Open the file in read-only mode
    FILE *fptr = fopen(filename, "r");

    // If the file pointer is NULL, it means the file is not available
    if (fptr == NULL)
    {
        return FILE_NOTAVAILABLE;
    }

    // Move the file pointer to the end of the file to check its size
    fseek(fptr, 0L, SEEK_END);

    // If the file pointer position is 0, it means the file is empty
    if (ftell(fptr) == 0)
    {
        fclose(fptr); // Close the file before returning
        return FILE_EMPTY;
    }

    // If the file pointer position is not 0, the file has some content
    fclose(fptr); // Close the file before returning
    return SUCCESS;
}

/* Function to insert a file into the linked list of files (Flist) */
int to_create_list_of_files(Flist **head, char *filename)
{
    Flist *temp = *head; // Temporary pointer to traverse the linked list

    // Traverse the list to check if the file name already exists
    while (temp != NULL)
    {
        // If the file name is found, return `REPEATATION` to indicate that the file is already in the list
        if (strcmp(temp->file_name, filename) == 0)
        {
            return REPEATATION;
        }
        temp = temp->link; // Move to the next node in the list
    }

    // Create a new node for the file
    Flist *new_file = malloc(sizeof(Flist));

    // Check if memory allocation was successful
    if (new_file == NULL)
    {
        return FAILURE; // Return failure if memory allocation failed
    }

    // Copy the filename into the new node and initialize its link to NULL
    strcpy(new_file->file_name, filename);
    new_file->link = NULL;

    // If the linked list is empty, set the new node as the head
    if (*head == NULL)
    {
        *head = new_file;
        return SUCCESS; // Return success after adding the new node
    }

    // Traverse to the last node of the linked list
    temp = *head;
    while (temp->link != NULL)
    {
        temp = temp->link; // Move to the next node
    }

    // Add the new node at the end of the linked list
    temp->link = new_file;
    return SUCCESS; // Return success after inserting the new node
}

