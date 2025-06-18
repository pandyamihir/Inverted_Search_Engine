#ifndef INVERTED_SEARCH_H          // Include guard: prevents multiple inclusions of this header file
#define INVERTED_SEARCH_H

#include <stdio.h>                 // Standard I/O operations (e.g., file handling)
#include <stdlib.h>                // Memory allocation functions (e.g., malloc, free)
#include <string.h>                // String manipulation functions (e.g., strcpy, strcmp)
#include <ctype.h>                 // Character manipulation functions (e.g., tolower)

// Defining macros for various constants and status codes
#define FAILURE -1                 // Macro for failure status
#define SUCCESS 0                  // Macro for success status
#define FNAME_SIZE 20              // Maximum size for a file name
#define WORD_SIZE 15               // Maximum size for a word
#define FILE_EMPTY -2              // Status code for an empty file
#define FILE_NOTAVAILABLE -3       // Status code for a file that is not available
#define REPEATATION -4             // Status code for a repeated file name

// Structure to store file information in a linked list
typedef char data_t;               // `data_t` is defined as a type alias for `char`
typedef struct file_node
{
    data_t file_name[FNAME_SIZE];  // Array to store the file name (up to 20 characters)
    struct file_node *link;        // Pointer to the next file node in the linked list
} Flist;                           // Typedef for `file_node` structure as `Flist`

// Structure for link table, which stores word occurrence details for each file
typedef struct linkTable_node
{
    int word_count;                // Count of how many times the word appears in the file
    data_t file_name[FNAME_SIZE];  // File name in which the word is found
    struct linkTable_node *table_link;  // Pointer to the next link table node
} Ltable;                          // Typedef for `linkTable_node` structure as `Ltable`

// Structure to store each word and its occurrence in a linked list of words
typedef struct word_node
{
    int file_count;                // Number of files in which the word appears
    data_t word[WORD_SIZE];        // Word stored as a character array (up to 15 characters)
    Ltable *Tlink;                 // Pointer to the head of the link table for this word
    struct word_node *link;        // Pointer to the next word node in the word linked list
} Wlist;                           // Typedef for `word_node` structure as `Wlist`

// Function Prototypes:

// Function to create and add files to the file linked list
int to_create_list_of_files(Flist **head, char *filename);

// Function to create a word database from the file linked list
void create_database(Flist *f_head, Wlist *head[]);

// Function to read contents from a file and populate the word linked list
Wlist *read_datafile(Flist *file, Wlist *head[], char *filename);

// Function to insert a word at the end of the word linked list
int insert_at_last(Wlist **head, data_t *data);

// Function to update the link table for a specific word
int update_link_table(Wlist **head);

// Function to update the word count and link table for a word
int update_word_count(Wlist **f_head, char *file_name);

// Function to print the word count for each word in the word linked list
int print_word_count(Wlist *head);

// Function to search for a specific word in the word linked list and display its details
void search_database(Wlist *head, char *word);

// Function to display the entire word database with file and word count details
void display_database(Wlist *head[]);

// Function to save the current word database to a file
void save_database(Wlist *head[]);

// Function to write the word database details to a specified file
void write_databasefile(Wlist *head, FILE* databasefile);

// Function to insert a file into the file linked list
int file_insert(Flist **head, char *filename);

// Function to update the word database with new files
void update_database(Wlist *head[], Flist **f_head);

// Function to check if a file is empty or not available
int isFileEmpty(char *filename);

// Function to validate files and add them to the file linked list
void file_validation_n_file_list(Flist **f_head, char *argv[]);

#endif  // End of include guard `INVERTED_SEARCH_H`
