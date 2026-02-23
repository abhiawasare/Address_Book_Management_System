/* 
Description:
This file has the functions and logic for the Address Book project.

The Address Book program lets the user:
  - Add new contacts
  - Edit, delete, and search contacts
  - Show the list of all saved contacts

All contacts (name, phone, email) are saved in a file
so that the data is not lost. 
The contacts can also be sorted by name, phone, or email.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include<ctype.h>

void listContacts(AddressBook *addressBook, int sortCriteria) //function prototype
{
    Contact temp;
    if(addressBook->contactCount == 0) //file is empty
    {
        printf("File Empty!\n");
        return;
    }
    printf("Short By :-\n"); //short the list
    printf("1. Name :- \n 2. Phone :- \n 3. Email :- \n");
    printf("Enter your Choice: ");
    scanf("%d",&sortCriteria);
    int cmpshort = 0;
    for(int i = 0; i < addressBook ->contactCount -1 ; i++)
    {
        for(int j = 0; j < addressBook ->contactCount -i-1; j++)
        {
            if(sortCriteria == 1) //compare choice is equal to number
            {
                cmpshort = strcasecmp(addressBook ->contacts[j].name, addressBook ->contacts[j+1].name);
            }else if(sortCriteria == 2)
            {
                cmpshort = strcasecmp(addressBook ->contacts[j].phone, addressBook ->contacts[j+1].phone);
            }else if(sortCriteria == 3)
            {
                cmpshort = strcasecmp(addressBook ->contacts[j].email, addressBook ->contacts[j+1].email);
            }else
            {
                printf("Invalid Choice\n");
            }
            if(cmpshort > 0)
            {
                temp = addressBook->contacts[j]; //using swap condition
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }


printf("\n\n           =-=-=-=-=-=-=-=-=-=-= [ CONTACTS LIST ] =-=-=-=-=-=-=-=-=-=-= \n");
    printf("\n=======================================================================================\n");
    printf("| %-5s | %-20s | %-20s | %-30s |\n", "No", "Name", "Phone", "Email");
    printf("========================================================================================\n");
    for (int i = 0; i < addressBook->contactCount;i++) //print the contacts list
    {
        printf("| %-5d | %-20s | %-20s | %-30s |\n",
            i+1,
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
    printf("========================================================================================\n");
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook); //load contact to file
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook) //function prototype
{
    printf("\n =-=-=-=-=-=-=-= [ CREATE CONTACT ] =-=-=-=-=-=-=-=\n");
    Contact new_contact; //using structure
    
    reEnter_name:
    getchar();
    printf("Enter Name: ");
    scanf("%[^\n]",new_contact.name);

    for(int i = 0; new_contact.name[i] != '\0'; i++) 
        if(!isalpha(new_contact.name[i]) && new_contact.name[i] != ' ')// Check if it is a character or a space
    {
        {
             printf("Invalid name! Only alphabets are allowed.\n");
             goto reEnter_name;
        }
    }
    
    reEnter_phone:
    getchar();
    printf("Enter Phone (Digits must be [10]) : ");
    scanf("%s",new_contact.phone); 
    for(int i = 0; i < addressBook -> contactCount; i++)
    {
        if(strcmp(new_contact.phone, addressBook -> contacts[i].phone) == 0) // Check if the phone number matches the number in the list.
        {
            printf("Phone already exists! Please try again with a different phone.\n");
            goto reEnter_phone;
        }
    }
    for(int i = 0; i < strlen(new_contact.phone); i++)
{
    if(!isdigit(new_contact.phone[i])) //to check phone are digit or not.
    {
        printf("Invalid Phone! Phone Number must be Digits\n");
        goto reEnter_phone;
    }
}
    if(strlen(new_contact.phone) != 10) //The condition checks whether the phone number has exactly 10 digits or not.
    {
        printf("Invalid Phone! Phone Number must be Exactly 10 digits.\n");
        goto reEnter_phone;
    }

    reEnter_email:
    getchar();
    printf("Enter Email (must end with @gmail.com): ");
    scanf("%s",new_contact.email); 

    int len = strlen(new_contact.email);
    // if(len <= 10) //the condition check -whether the email has at least greater than @gmail.com.
    // {
    //     printf("Invalid Email! There must be at least 1 character before '@gmail.com'\n");
    //     goto reEnter_email;
    // }
    

    for(int i = 0; i < addressBook -> contactCount; i++)
    {
        if(strcmp(new_contact.email, addressBook -> contacts[i].email) == 0) // Check if the email matches the email in the list.
        {
            printf("Email already exists! Please try again with a different Email.\n");
            goto reEnter_email;
        }
    }
char *found;
        found = strstr(new_contact.email, "@gmail.com");
        if(found != NULL)
        {   
        // at least 1 character must exists before '@gmail.com'
        if(len<=10)
        {
            printf("Error: There must be at least 1 character before @gmail.com!\n");
            goto reEnter_email;
        }
            // char *end = found + strlen("@gmail.com");  
            if(*(found + strlen("@gmail.com"))!='\0')
            {
                printf("Error: After @gmail.com there must be nothing!\n");
                goto reEnter_email;
            }
        }    
        else
        {
            printf("Error: Email must end with @gmail.com!\n");
            goto reEnter_email;
        }
    
    for(int i = 0; new_contact.email[i] != '\0'; i++)
    {
        char a = new_contact.email[i];
        if(a == '@')
        {
            break;
        }
        if(!islower(a) && !isdigit(a) && a != '.' && a != '_') //the condition to check whether the email allowed the give conditions.
        {
            printf("Invalid email! only lowercase letters, digits, '.', '_' allowed before @gmail.com.\n");
            goto reEnter_email;
        }
    
}
    getchar();
    addressBook -> contacts[addressBook ->contactCount] = new_contact; //save contact to the contacts list.
    addressBook ->contactCount++;

    printf("Contact Create Successfully!!!\n");
}
int searchContact(AddressBook *addressBook, int* found, int index_found[]) 
{
    printf("\n =-=-=-=-=-=-=-= [ SEARCH CONTACT ] =-=-=-=-=-=-=-=\n");
    int choice, flag = 0;
    *found = 0;
    char new_name[50];
    char new_phone[20];
    char new_email[50];
   
    printf("Search Contact Menu\n");
    printf("1. Name \n");
    printf("2. Phone \n");
    printf("3. Email \n");
    printf("Enter your choice : ");
    scanf("%d",&choice); // Choose what you want to search: name, phone, or email
    switch (choice)
    {
    case 1:
    getchar();
       printf("Enter Name:");
       scanf("%[^\n]",new_name);
      for(int i = 0; i < addressBook -> contactCount; i++)
      {
       if (strcasestr(addressBook->contacts[i].name,new_name) != NULL) //search the name in contacts list
       {
        flag = 1;
        printf("%d. %s \t \t %s \t \t %s\n",
            *found+1,
            addressBook -> contacts[i].name, 
            addressBook ->contacts[i].phone, 
            addressBook ->contacts[i].email);
            index_found[*found] = i;
            (*found)++;
        }
      }
      if(flag == 0) //the name not found contacts list.
      {
        printf("Name not found");
      }
        break;

    case 2:
       getchar();
       printf("Enter Phone:");
       scanf("%[^\n]",new_phone);
      for(int i = 0; i < addressBook -> contactCount; i++)
      {
       if (strstr(addressBook->contacts[i].phone,new_phone) != NULL) // search phone to contacts list.
       {
        flag = 1;
        printf("%d. %s \t \t %s \t \t %s\n",
            *found+1,
            addressBook -> contacts[i].name, 
            addressBook ->contacts[i].phone, 
            addressBook ->contacts[i].email);
           index_found[*found] = i;
           (*found)++;
        }
      }
      if(flag == 0)
      {
        printf("Phone not found");
      }
      break;

    case 3:
       getchar();
       printf("Enter Email:");
       scanf("%[^\n]",new_email);
      for(int i = 0; i < addressBook -> contactCount; i++)
      {
       if (strstr(addressBook->contacts[i].email,new_email) != NULL) //search email to contacts list.
       {
        flag = 1;
        printf("%d. %s \t \t %s \t \t %s\n",
            *found+1,
            addressBook -> contacts[i].name, 
            addressBook ->contacts[i].phone, 
            addressBook ->contacts[i].email);
            index_found[*found] = i;
            (*found)++;
        }
      }
      if(flag == 0)
      {
        printf("Email not found");
      }
      break;
    
    default:
    printf("Invalid Detail");
        break;
    }
    return *found; //return count
}

void editContact(AddressBook *addressBook, int* found, int index_found[])
{
    int pos = searchContact(addressBook, found, index_found); 
    if(!pos)
    {
        printf("Invalid Contact");
        return;
    }
   
    int num ;

    printf("\nEnter the index number of contact to edit: "); // When multiple numbers are found, choose which contact to edit.
    scanf("%d", &num);

    if (num < 0 || num >= addressBook->contactCount)
    {
        printf("Invalid index!\n");
        return;
    }
    printf("\n =-=-=-=-=-=-=-= [ EDIT CONTACT ] =-=-=-=-=-=-=-=\n");
    int index = index_found[num - 1];
    int choice;
    char edit_name[50];
    char edit_phone[20];
    char edit_email[50];
    printf("Edit Contact Menu :\n");
    printf("1. Edit Name \n");
    printf("2. Edit Phone \n");
    printf("3. Edit Email \n");

    printf("Enter Your Choice : "); // Choose what you want to search: name, phone, or email
    scanf("%d",&choice);

    switch (choice)
    {
    case 1:
    re_enter_name:
        getchar();
        printf("Enter New Name : ");
        scanf("%[^\n]",edit_name);
         int i = 0, upper = -1;
    
    
    for(int i = 0; edit_name[i] != '\0'; i++)
    {
        if(!isalpha(edit_name[i]) && edit_name[i] != ' ') //Check if it is a character or a space
        {
             printf("Invalid name! Only alphabets are allowed.\n");
             goto re_enter_name;
        }
     }
  
         strcpy(addressBook -> contacts[index].name, edit_name); // Update the contact name with the edited name.
        break;

    case 2:
    re_enter_phone:
        getchar();
        printf("Enter New Phone : ");
        scanf("%[^\n]",edit_phone); //user edit phone
         for(int i = 0; i < strlen(edit_phone); i++)
{
    if(!isdigit(edit_phone[i])) //to check phone digit or not
    {
        printf("Invalid Phone! Phone Number must be Digits\n");
        goto re_enter_phone;
    }
}
    if(strlen(edit_phone) != 10) //The condition checks whether the phone number has exactly 10 digits or not.
    {
        printf("Invalid Phone! Phone Number must be Exactly 10 digits.\n");
        goto re_enter_phone;
    }
        strcpy(addressBook -> contacts[index].phone, edit_phone); // Update the contact phone with the edited phone
        break;

    case 3:
        re_enter_email:
        getchar();
        printf("Enter New Email : ");
        scanf("%[^\n]",edit_email);
        int len = strlen(edit_email); //find email length
        if(len <= 10) //the condition check whether the email has at least greater than @gmail.com.
        {
        printf("Invalid Email! There must be at least 1 character before '@gmail.com'\n");
        goto re_enter_email;
        }else{

    for(int i = 0; i < addressBook -> contactCount; i++)
    {
        if(strcmp(edit_email, addressBook -> contacts[i].email) == 0)// Check if the email matches the email in the list.
        {
            printf("Email already exists! Please try again with a different Email.\n");
            goto re_enter_email;
        }
    }
    }
    char *found;
        found = strstr(edit_email, "@gmail.com");
        if(found != NULL)
        {   
        // at least 1 character must exists before '@gmail.com'
        if(len<=10)
        {
            printf("Error: There must be at least 1 character before @gmail.com!\n");
            goto re_enter_email;
        }
            // char *end = found + strlen("@gmail.com");  
            if(*(found + strlen("@gmail.com"))!='\0')
            {
                printf("Error: After @gmail.com there must be nothing!\n");
                goto re_enter_email;
            }
        }    
        else
        {
            printf("Error: Email must end with @gmail.com!\n");
            goto re_enter_email;
        }
    for(int i = 0; edit_email[i] != '\0'; i++)
    {
        char c = edit_email[i];
        if(c == '@') //the mail to check before the @.
        {
            break;
        }
        if(!islower(c) && !isdigit(c) && c != '.' && c != '_') //the condition to check whether the email allowed the give conditions.
        {
            printf("Invalid email! only lowercase letters, digits, '.', '_' allowed before @gmail.com.\n");
            goto re_enter_email;
        }
    }
        strcpy(addressBook -> contacts[index].email, edit_email); // Update the contact gmail with the edited gmail.
        break;
    
    default:
    printf("Invalid Detail");
        break;
    }
    printf("Record Updated Successfully!\n"); 

}

void deleteContact(AddressBook *addressBook, int* found, int index_found[])
{
   searchContact(addressBook, found, index_found);
   int index;
re_enter_index:
   if(*found > 1)
   {
   int num;
    printf("\nEnter the index number of contact to Delete: "); // When multiple numbers are found, choose which contact to delete.
    scanf("%d", &num);
    if (num <= 0 || num > *found)
    {
        printf("Invalid index!\n");
        goto re_enter_index;
    }
    index = index_found[num -1];
}else if(*found == 1)
    {
    index = index_found[0];
    }else
    {
        printf("No contact found.\n");
        return;
    }
    printf("\n =-=-=-=-=-=-=-= [ DELETE CONTACT ] =-=-=-=-=-=-=-=\n");
    getchar();

    char choice;
    printf("Do You Want To delete this Contact (y/n): "); // When a contact is found, confirm whether to delete it or not.

    scanf("%c",&choice);

    getchar();

    if(choice == 'y' || choice == 'Y') // If they choose 'y', the contact will be deleted
    {
        int i , j;
        for (i = index; i < addressBook -> contactCount; i++) 
        {
             addressBook -> contacts[i] = addressBook -> contacts[i+1]; //swap the contacts for the contacts list.
        }
        addressBook -> contactCount--; //contacts list len are decreases
        printf("Deleted Contact Successfully!\n");
    }else if(choice == 'n' || choice == 'N') // If they choose 'n', the contact not be deleted
    {
        printf("Contact Not Deleted.\n");
        return;
    }else
    {
    printf("Cancelled.\n");
    }
    return; 
}