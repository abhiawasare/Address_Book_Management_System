#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;
void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook,int *found, int *index_found);
void editContact(AddressBook *addressBook, int *found, int *index_found);
void deleteContact(AddressBook *addressBook,int *found, int *index_found);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

#endif
