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
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
int validatename(char temp[]);
int validatenum(char num[]);
int uniquenum(AddressBook *addressBook , char num[]);
int uniquemail(AddressBook *addressBook , char mail[]);
void searchbyname(AddressBook *addressBook);
void searchbynumber(AddressBook *addressBook);
void searchbyemail(AddressBook *addressBook);

#endif
