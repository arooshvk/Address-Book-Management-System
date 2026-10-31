#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <ctype.h>
int exit1;
int matchedIndexes[MAX_CONTACTS];
int matchCount = 0;
int validatename(char temp[])
{
    if(temp[0]>='a'&&temp[0]<='z'||temp[0]>='A'&&temp[0]<='Z' )
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}
int validatenum(char num[])
{
    if(strlen(num)!=10)
    {
        printf("Phone number must contain exactly 10 digits\n");
        return 0;
    }
    else if(!(num[0]>='6' &&num[0]<='9'))
    {
        printf("First digit must be between 6 and 9 \n");
        return 0;
    }
    for(int i=0;num[i]!='\0';i++)
    {
        if(!(num[i]>='0'&&num[i]<='9'))
        {
           printf("symbols are not allowed in phone number \n");
           return 0;
        }
       
    }
    return  1;


}
int uniquenum(AddressBook *addressBook , char num[])
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(num,addressBook->contacts[i].phone)==0)
        {
            printf("Number is not unique\n");
            return 0;

        }
    }
    return 1;

}
int validatemail(char mail[])
{
    int atcount =0,at=-1;
    for(int i=0;mail[i]!='\0';i++)
    {
        if(mail[i]=='@')
        {
            atcount++;
            at=i;

        }
    }
    if(atcount !=1)
    {
        printf("Email ID must contain exactly one @ symbol\n");
        return 0;
    }
    else if(at==0)
    {
        printf("Starting of the email should not be a @ symbol\n");
        return 0;

    }
    int dotcount=0,dot=-1;
    for(int i=0;mail[i]!='\0';i++)
    {
        if(mail[i]=='.')
        {
            dotcount++;
            dot=i;
        }
    }
    if(dotcount <1)
    {
        printf("Email ID must contain atleast one . symbol\n");
        return 0;
    }
    else if(dot==0)
    {
        printf("Starting of the email should not be a .symbol\n");
        return 0;

    }
    else if(dot<at)
    {
        printf("The . (dot) must appear after @, not before. \n");
        return 0;

    }
    else if(dot==(at+1))
    {
        printf("There must be at least one character between @ and .\n");
        return 0;
    } 
    int ret = strlen(mail);

    if (strcmp(mail + ret - 4, ".com") != 0)
    {
        printf("After the final domain no extra characters should be present.\n");
        return 0;
    } 
    for(int i=0;mail[i]!='\0';i++)
    {
        if(!(isalnum(mail[i])||mail[i]=='@'||mail[i]=='.'))
        {
            printf("Only @ and . are allowed as symbols in the email ID.\n");
            return 0;
        }
    }
    return 1;
}
int uniquemail(AddressBook *addressBook , char mail[])
{
   for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(mail,addressBook->contacts[i].email)==0)
        {
            printf("Mail is not unique\n");
            return 0;

        }
    }
    return 1; 
}
void searchbyname(AddressBook *addressBook)
{
    char tempname[50];
    printf("ENTER THE NAME : ");
    scanf(" %49[^\n]", tempname);
    int found=0;
    matchCount = 0;
    int ret=validatename(tempname);

    if(ret==0)
    {
        int i=2;
        while(i!=0)
        {
            printf("%d attempts left :\nEnter the name : ",i);
            scanf(" %49[^\n]", tempname);
            ret=validatename(tempname);
            if(ret==1)
            {
                break;
            }
            i--;
        }
        if(i==0)
        return;
    }
    if(ret==1)
    {
        int arr[100]={0};
        for( int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].name,tempname)==0)
            {
                arr[i]=1;
                matchedIndexes[matchCount] = i;
                matchCount++;
                found =1;    
            }
        }
        if(found==1)
        {
            printf("+------------+---------------------------+-----------------+--------------------------------+\n");
            printf("| %-10s | %-25s | %-15s | %-30s |\n","Index","Name","Phone number","Email");
            printf("+------------+---------------------------+-----------------+--------------------------------+\n");
        }
        int serial = 0;
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(arr[i]==1)
            {    
                serial++;       
                printf("| %-10d | %-25s | %-15s | %-30s |\n",serial,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
        }
        if(found==1)
        {
            printf("+------------+---------------------------+-----------------+--------------------------------+\n");
        }
    }
    if(found==0)
    {
        printf("+------------------------------+\n");
        printf("| No matching record is found! |\n");
        printf("+------------------------------+\n");
        exit1=1;
    }
   
}
void searchbynumber(AddressBook *addressBook)
{
    char tempnumber[20];
    printf("Enter the number : ");
    scanf(" %19[^\n]", tempnumber);
    int found=0;
    matchCount =0;
    int ret=validatenum(tempnumber);

    if(ret==0)
    {
        int i=2;
        while(i!=0)
        {
            printf("%d attempts left :\nEnter the number : ",i);
            scanf(" %19[^\n]", tempnumber);
            ret=validatenum(tempnumber);
            if(ret==1)
            {
                break;
            }
            i--;
        }
        if(i==0)
        return;
    }
    if(ret==1)
    {
        int arr[100]={0};
        for( int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].phone,tempnumber)==0)
            {
                arr[i]=1;
                matchedIndexes[matchCount] = i;
                matchCount++;
                found =1;    
            }
        }
        if(found==1)
        {
            printf("+------------+---------------------------+-----------------+--------------------------------+\n");
            printf("| %-10s | %-25s | %-15s | %-30s |\n","Index","Name","Phone number","Email");
            printf("+------------+---------------------------+-----------------+--------------------------------+\n");
        }
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(arr[i]==1)
            {           
                printf("| %-10d | %-25s | %-15s | %-30s |\n",1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
        }
        if(found==1)
        {
            printf("+------------+---------------------------+-----------------+--------------------------------+\n");
        }
    }
    if(found==0)
    {
        printf("+------------------------------+\n");
        printf("| No matching record is found! |\n");
        printf("+------------------------------+\n");
        exit1=1;
    }
   
}
void searchbyemail(AddressBook *addressBook)
{
    char tempmail[50];
    printf("Enter the mail ID : ");
    scanf(" %49[^\n]", tempmail);
    int found=0;
    matchCount = 0;
    int ret=validatemail(tempmail);

    if(ret==0)
    {
        int i=2;
        while(i!=0)
        {
            printf("%d attempts left :\nEnter the mail ID : ",i);
            scanf(" %49[^\n]", tempmail);
            ret=validatemail(tempmail);
            if(ret==1)
            {
                break;
            }
            i--;
        }
        if(i==0)
        return;
    }
    if(ret==1)
    {
        int arr[100]={0};
        for( int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].email,tempmail)==0)
            {
                arr[i]=1;
                matchedIndexes[matchCount] = i;
                matchCount++;
                found =1;    
            }
        }
        if(found==1)
        {
            printf("+------------+---------------------------+-----------------+--------------------------------+\n");
            printf("| %-10s | %-25s | %-15s | %-30s |\n","Index","Name","Phone number","Email");
            printf("+------------+---------------------------+-----------------+--------------------------------+\n");
        }
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(arr[i]==1)
            {           
                printf("| %-10d | %-25s | %-15s | %-30s |\n",1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
        }
        if(found==1)
        {
            printf("+------------+---------------------------+-----------------+--------------------------------+\n");
        }
    }
    if(found==0)
    {
        printf("+------------------------------+\n");
        printf("| No matching record is found! |\n");
        printf("+------------------------------+\n");
        exit1=1;
    }
   
}
void listContacts(AddressBook *addressBook) 
{
    
    printf("+------------+---------------------------+-----------------+--------------------------------+\n");
    printf("| %-10s | %-25s | %-15s | %-30s |\n","Index","Names","Phone number","Email");
    printf("+------------+---------------------------+-----------------+--------------------------------+\n");
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("| %-10d | %-25s | %-15s | %-30s |\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf("+------------+---------------------------+-----------------+--------------------------------+\n");
    
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0; 
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{  
    //NAME

	char temp[50];
    if(addressBook->contactCount==100)
    {
        printf("CONTACT FULL !\n");
    }
    else 
    {
        printf("ENTER THE NAME : ");
        scanf(" %49[^\n]", temp);
        int ret=validatename(temp);
        if(ret==0)
        {
            int i=2;
            while(i!=0)
            {
                printf("INVALID ! Name should start with  alphabet. \n%d attempts left :\nEnter the name : ",i);
                scanf(" %49[^\n]", temp);
                int ret=validatename(temp);
                if(ret==1)
                {
                    break;
                }
                i--;
            }
            if(i==0)
            return ;

        }
    }
    
    //NUMBER

    char num[20];
    if(addressBook->contactCount==100)
    {
        printf("CONTACT FULL !\n");
    }
    else
    {
        printf("ENTER THE NUMBER : ");
        scanf(" %19[^\n]", num);
        int ret2=(validatenum(num)&&uniquenum(addressBook,num));;
        if(ret2==0)
        {
            int j=2;
            while(j!=0)
            {
                printf("%d attempts left! \nENTER THE NUMBER : ",j);
                scanf(" %19[^\n]", num);
                int ret2=(validatenum(num)&&uniquenum(addressBook,num));
                if(ret2==1)
                {
                    break;
                }
                j--;
                
            }
            if(j==0)
            return ;
        }
    } 

    //MAIL

    char mail[50];
    if(addressBook->contactCount==100)
    {
        printf("CONTACT FULL !\n");
    }
    else
    {
        printf("ENTER THE EMAIL ID  : ");
        scanf("%49s", mail);
        int ret3=validatemail(mail)&&uniquemail(addressBook ,mail);
        if(ret3==0)
        {
            int j=2;
            while(j!=0)
            {
                printf("%d attempts left! \nENTER THE EMAIL ID  : ",j);
                scanf("%49s", mail);
                int ret3=validatemail(mail)&&uniquemail(addressBook ,mail);
                if(ret3==1)
                {  
                    break;
                }
                j--;
                
            }
            if(j==0)
            return ;
        }
    
    }
    strcpy(addressBook->contacts[addressBook->contactCount].name,temp);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,num);
    strcpy(addressBook->contacts[addressBook->contactCount].email,mail);
    addressBook->contactCount++;
   //saveContactsToFile(addressBook);


}

void searchContact(AddressBook *addressBook) 
{
    int choice;
    printf("SEARCH CONTACT\n");
    printf("1. Search by NAME\n");
    printf("2. Search by NUMBER\n");
    printf("3. Search by EMAIL\n");
    printf("4. Exit\n");
    printf("Enter your choice : ");
 

    if (scanf("%d", &choice) != 1)
    {
        printf("Invalid input! Please enter a number.\n");
        exit1=1;

        while (getchar() != '\n');

        return;
    }

    switch (choice)
    {
        case 1:
            searchbyname(addressBook);
            break;
        case 2:
            searchbynumber(addressBook);
            break;
        case 3:
            searchbyemail(addressBook);
            break;
        case 4:
            exit1=1;
            return;
        default :
            printf("Invalid choice !\n");
            exit1=1;
            return;
    }

}

void editContact(AddressBook *addressBook)
{
    exit1=0;
    searchContact(addressBook);
    if(exit1==1)
    return;
    int index;
    char temp[50];
    printf("enter the index of contact to be edited : ");
    if (scanf("%d", &index) != 1)
    {
        printf("Invalid input! Please enter a number.\n");
        exit1=1;

        while (getchar() != '\n');

        return;
    }
    if(index < 1 || index > matchCount)
    return;
    index = matchedIndexes[index-1];

    int choice;
    printf("1.Edit name\n");
    printf("2.Edit number\n");
    printf("3.Edit mail ID\n");
    printf("4.Exit\n");
    printf("enter the choice : ");
    if (scanf("%d", &choice) != 1)
    {
        printf("Invalid input! Please enter a number.\n");
        exit1=1;

        while (getchar() != '\n');

        return;
    }


    switch (choice)
    {
        case 1: //edit by name

            printf("ENTER THE NAME : ");
            scanf("%49s", temp);
            int ret=validatename(temp);
            if(ret==0)
            {
                int i=2;
                while(i!=0)
                {
                    printf("INVALID ! Name should start with  alphabet. \n%d attempts left :\nEnter the name : ",i);
                    scanf(" %49[^\n]", temp);
                    int ret=validatename(temp);
                    if(ret==1)
                    {
                        break;
                    }
                    i--;
                }
                if(i==0)
                return ;
            }
            strcpy(addressBook->contacts[index].name,temp);
            break;

        case 2://edit by number

            printf("ENTER THE NUMBER : ");
            scanf("%19s", temp);
            int ret2=(validatenum(temp)&&uniquenum(addressBook,temp));;
            if(ret2==0)
            {
                int j=2;
                while(j!=0)
                {
                    printf("%d attempts left! \nENTER THE NUMBER : ",j);
                    scanf("%19s",temp);
                    int ret2=(validatenum(temp)&&uniquenum(addressBook,temp));
                    if(ret2==1)
                    {
                        break;
                    }
                    j--;
                    
                }
                if(j==0)
                return ;
            }
            strcpy(addressBook->contacts[index].phone,temp);
            break;
        case 3://edit by mail

            printf("ENTER THE EMAIL ID  : ");
            scanf("%49s",temp);
            int ret3=validatemail(temp)&&uniquemail(addressBook ,temp);
            if(ret3==0)
            {
                int j=2;
                while(j!=0)
                {
                    printf("%d attempts left! \nENTER THE EMAIL ID  : ",j);
                    scanf("%49s", temp);
                    int ret3=validatemail(temp)&&uniquemail(addressBook ,temp);
                    if(ret3==1)
                    {  
                        break;
                    }
                    j--;
                    
                }
                if(j==0)
                return ;
            }
            strcpy(addressBook->contacts[index].email,temp);
            break;
        case 4: 
            return;
        default :
        printf("INVALID CHOICE!\n");
            
    }
    //saveContactsToFile(addressBook);
    
}

void deleteContact(AddressBook *addressBook)
{
    exit1=0;
	searchContact(addressBook);
    if(exit1==1)
    return;
    int index,confirm;
    printf("Enter the index to be deleted : ");
    scanf("%d",&index);

    if (index < 1 || index > matchCount)
    {
        printf("Invalid index!\n");
        return;
    }

    index = matchedIndexes[index - 1];

    printf("confirm to delete by pressing 1\n OR\nTo exit press 0 :\n");
    scanf("%d",&confirm);
    if(confirm==1)
    {
        for(int i=index;i<addressBook->contactCount-1;i++)
        {
            addressBook->contacts[i]=addressBook->contacts[i+1];
            
        }
        addressBook->contactCount--;
    }
    else
    {
        return ;
    }
    //saveContactsToFile(addressBook);
 
}