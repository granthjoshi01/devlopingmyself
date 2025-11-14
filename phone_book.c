/*
 * ============================================================================
 * Phone Book Management System using Hash Table
 * ============================================================================
 * 
 * Description:
 *   A simple contact management system implemented using a hash table with
 *   linear probing for collision resolution. Supports adding, searching,
 *   deleting, and displaying contacts.
 * 
 * Features:
 *   - Hash table implementation with linear probing
 *   - Add new contacts (name and phone number)
 *   - Search for contacts by name
 *   - Delete existing contacts
 *   - Display all stored contacts
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================================
 * CONSTANTS AND MACROS
 * ============================================================================
 */

#define TABLE_SIZE 10        // Size of the hash table
#define MAX_NAME 30          // Maximum length of contact name

/* ============================================================================
 * DATA STRUCTURES
 * ============================================================================
 */

/**
 * Contact structure
 * 
 * Represents a single contact entry in the phone book.
 * 
 * @field name      - Contact's name (max 30 characters)
 * @field phone     - Contact's phone number (stored as long long)
 * @field isFilled  - Flag indicating if slot is occupied (1) or empty (0)
 */
typedef struct Contact {
    char name[MAX_NAME];
    long long phone;
    int isFilled;  // 1 = occupied, 0 = empty
} Contact;

/* ============================================================================
 * GLOBAL VARIABLES
 * ============================================================================
 */

// Hash table array to store contacts
Contact hashTable[TABLE_SIZE];

/* ============================================================================
 * FUNCTION PROTOTYPES
 * ============================================================================
 */

void initTable();
int hashFunction(char* name);
void insert(char* name, long long phone);
void search(char* name);
void deleteContact(char* name);
void display();

/* ============================================================================
 * FUNCTION IMPLEMENTATIONS
 * ============================================================================
 */

/**
 * Initialize hash table
 * 
 * Sets all slots in the hash table to empty state by marking isFilled as 0.
 * This function should be called before using the hash table.
 */
void initTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].isFilled = 0;
    }
}

/**
 * Hash function
 * 
 * Computes the hash value for a given name by summing ASCII values of all
 * characters and taking modulo with table size.
 * 
 * @param name - The contact name to hash
 * @return     - Hash index (0 to TABLE_SIZE-1)
 */
int hashFunction(char* name) {
    int sum = 0;
    
    // Sum ASCII values of all characters in the name
    for (int i = 0; name[i] != '\0'; i++) {
        sum += name[i];
    }
    
    // Return index within table bounds
    return sum % TABLE_SIZE;
}

/**
 * Insert a new contact
 * 
 * Adds a new contact to the hash table using linear probing to resolve
 * collisions. If a contact with the same name exists, it will not be added.
 * 
 * Linear Probing: If the calculated index is occupied, try the next index
 * (wrapping around to 0 after TABLE_SIZE-1) until an empty slot is found.
 * 
 * @param name  - Contact's name
 * @param phone - Contact's phone number
 */
void insert(char* name, long long phone) {
    int index = hashFunction(name);
    int originalIndex = index;

    // Linear probing: search for empty slot or duplicate
    while (hashTable[index].isFilled) {
        // Check if contact already exists
        if (strcmp(hashTable[index].name, name) == 0) {
            printf("Contact already exists!\n");
            return;
        }
        
        // Move to next index (circular)
        index = (index + 1) % TABLE_SIZE;
        
        // Table is full if we've circled back to start
        if (index == originalIndex) {
            printf("Hash table is full!\n");
            return;
        }
    }

    // Insert the contact at the found empty slot
    strcpy(hashTable[index].name, name);
    hashTable[index].phone = phone;
    hashTable[index].isFilled = 1;
    printf("Contact added: %s -> %lld\n", name, phone);
}

/**
 * Search for a contact
 * 
 * Looks up a contact by name in the hash table using linear probing.
 * If found, displays the contact's phone number.
 * 
 * @param name - Name of the contact to search for
 */
void search(char* name) {
    int index = hashFunction(name);
    int originalIndex = index;

    // Linear probing: search through occupied slots
    while (hashTable[index].isFilled) {
        // Check if current slot matches the search name
        if (strcmp(hashTable[index].name, name) == 0) {
            printf("Found: %s -> %lld\n", name, hashTable[index].phone);
            return;
        }
        
        // Move to next index
        index = (index + 1) % TABLE_SIZE;
        
        // Stop if we've checked all possible positions
        if (index == originalIndex) break;
    }
    
    printf("Contact not found!\n");
}

/**
 * Delete a contact
 * 
 * Removes a contact from the hash table by marking its slot as empty.
 * Uses linear probing to locate the contact.
 * 
 * Note: This simple deletion may cause issues with subsequent searches
 * due to breaking the probe sequence. A more robust implementation would
 * use tombstone marking or rehashing.
 * 
 * @param name - Name of the contact to delete
 */
void deleteContact(char* name) {
    int index = hashFunction(name);
    int originalIndex = index;

    // Linear probing: search for the contact
    while (hashTable[index].isFilled) {
        // Check if current slot matches the name to delete
        if (strcmp(hashTable[index].name, name) == 0) {
            hashTable[index].isFilled = 0;  // Mark slot as empty
            printf("Contact deleted: %s\n", name);
            return;
        }
        
        // Move to next index
        index = (index + 1) % TABLE_SIZE;
        
        // Stop if we've checked all possible positions
        if (index == originalIndex) break;
    }
    
    printf("Contact not found!\n");
}

/**
 * Display all contacts
 * 
 * Prints a formatted table showing all contacts currently stored in the
 * hash table, along with their index positions.
 */
void display() {
    printf("\n--- Phone Book ---\n");
    printf("Index | Name\t\t| Phone\n");
    printf("------|---------------|------------\n");
    
    int found = 0;
    
    // Iterate through entire hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i].isFilled) {
            printf("%d     | %-13s | %lld\n", i, hashTable[i].name, hashTable[i].phone);
            found = 1;
        }
    }
    
    // Display message if table is empty
    if (!found) {
        printf("      | (empty)       |\n");
    }
    
    printf("------|---------------|------------\n");
}

/* ============================================================================
 * MAIN FUNCTION
 * ============================================================================
 */

/**
 * Main program entry point
 * 
 * Provides an interactive menu-driven interface for managing the phone book.
 * Continuously displays menu options and processes user choices until exit.
 * 
 * @return 0 on successful program termination
 */
int main() {
    // Initialize the hash table
    initTable();
    
    int choice;
    char name[MAX_NAME];
    long long phone;

    // Main program loop
    while (1) {
        // Display menu
        printf("\n");
        printf("===============================\n");
        printf("     PHONE BOOK (HASHING)      \n");
        printf("===============================\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Delete Contact\n");
        printf("4. Display All\n");
        printf("5. Exit\n");
        printf("-------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        // Process user choice
        switch (choice) {
            case 1:
                // Add new contact
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter phone: ");
                scanf("%lld", &phone);
                insert(name, phone);
                break;

            case 2:
                // Search for contact
                printf("Enter name to search: ");
                scanf("%s", name);
                search(name);
                break;

            case 3:
                // Delete contact
                printf("Enter name to delete: ");
                scanf("%s", name);
                deleteContact(name);
                break;

            case 4:
                // Display all contacts
                display();
                break;

            case 5:
                // Exit program
                printf("Goodbye!\n");
                exit(0);

            default:
                // Invalid choice
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
