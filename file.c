#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) //save to new contacts to the file.
{ 
    FILE *fp;
    fp = fopen("contacts.txt","w");
    if(fp == NULL)
    {
        printf("Error! Saving Contact.\n");
        return;
    }
    fprintf(fp, "%d\n", addressBook -> contactCount);

    for(int i = 0; i < addressBook -> contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
        addressBook->contacts[i].name,
        addressBook->contacts[i].phone,
        addressBook->contacts[i].email);
    }
    fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook)  //load to the save contacts to the file
{
    FILE *fp;
    fp = fopen("contacts.txt","r");
    if(fp == NULL)
    {
        printf("No saved Contact found.\n");
        return;
    }
    fscanf(fp, "%d\n", &addressBook -> contactCount);

 for(int i = 0; i < addressBook -> contactCount; i++)
    {
       fscanf(fp, "%[^,],%[^,],%[^\n]\n",
       addressBook->contacts[i].name,
       addressBook->contacts[i].phone,
       addressBook->contacts[i].email);
    }
    fclose(fp);
}
