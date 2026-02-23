/*
Student Name: Abhijit Awasare
Project Name: Address Book
Description:  This AddressBook Project allows users to add, search, edit, delete, 
               display, and save contact information in a file.
*/
#include <stdio.h>
#include "contact.h"

int main() {
    int choice, sortChoice;
    AddressBook addressBook;
    int found = 0;
    int index_found[20];
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\n=-=-=-=-=-=-=-= [ Address Book Menu: ] =-=-=-=-=-=-=-=\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook, &found, index_found);
                break;
            case 3:
                editContact(&addressBook, &found, index_found);
                break;
            case 4:
                deleteContact(&addressBook, &found, index_found);
                break;
            case 5:          
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            case 7:
                printf("Exit Successfuly!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
       return 0;
}
