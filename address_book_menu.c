#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "address_book.h"
#include "address_book_menu.h"

//#include "abk_fileops.h"
//#include "abk_log.h"
//#include "abk_menus.h"
//#include "abk.h"

int get_option(int type, const char *msg)
{
	int n;
	char name;
	printf("%s\n",msg);
	switch(type){
		case NUM:
			scanf("%d", &n);
			return n;
		case CHAR:
			scanf("%s", &name);
			return name;
		default:
			return 0;
	}
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	printf("#######  Address Book  #######\n");
	if (*str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;

	do
	{
		main_menu();
		option = get_option(NUM,"");

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				add_contacts(address_book);
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				break;
				/* Add your implementation to call list_contacts function here */
			case e_save:
				save_prompt(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	while (getchar() != '\n');
	int check = 1;
	int choice;
	char nameing[100] = "\0";
	char number[100];
	char email[100];
	int names_list = 0;
	int	numbers_list = 0;
	int emails_list = 0;
	int order = address_book->count;
	order++;
	address_book->list[address_book->count].si_no = order;
	do{
		
		printf("what would you like to do:\n");
		printf("0. Exit\n");
		printf("1. Add Name: %s\n", nameing);
		if (numbers_list == 0){
			printf("2. Add phone number: \n");
		}
		else{
			printf("2. Add phone number: %s\n", number);
		}
		printf("3. Add email: %s\n", email);
		choice = get_option(NUM,"Please select an option: ");

		switch (choice){
			case e_first_opt:
				if (names_list == 1){
					address_book->count++;
					check = 0;
				}
				else {
					printf("Sorry, make sure the name is filled before sending\n");
				}
				break;
		
			case e_second_opt:
				printf("Write the name you want to add:");
				scanf("%s", &nameing);
				strcpy(address_book->list[address_book->count].name[0],nameing);
				names_list = 1;
				break;
			case  e_third_opt:
				printf("Write the phone number you want to add:");
				scanf("%s", &number);
				strcpy(address_book->list[address_book->count].phone_numbers[numbers_list],number);
				numbers_list++;
				break;
			case  e_fourth_opt:
				printf("Write what email you want to add:");
				scanf("%s",&email);
				strcpy(address_book->list[address_book->count].email_addresses[emails_list],email);
				emails_list++;
				break;
			default:
				printf("Sorry, try again\n");
				

		}
		while (getchar() != '\n');
	}while (check != 0);
	return e_back;
				
}

Status search_contact(AddressBook *address_book)
{
    int userSelection;
    char search_term[32];
    int i, j;
    int contactFound;
    char input;
    
    if (address_book->count == 0)
    {
        printf("\nNo entries found! Please add contacts first.\n");
        return e_no_match;
    }
    
    do
    {
        printf("\n###### Search Contact ######\n");
        printf("0. Back\n");
        printf("1. By Name\n");
        printf("2. By Phone Number\n");
        printf("3. By Email ID\n");
        printf("\n");
        
        userSelection = get_option(NUM, "Please select an option: ");
        
        if (userSelection == 0)
        {
            break;
        }
        
        while (getchar() != '\n');
        
        switch (userSelection)
        {
            case 1:
                printf("Enter name: ");
                break;
            case 2:
                printf("Enter phone number: ");
                break;
            case 3:
                printf("Enter email: ");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                continue;
        }
        
        fgets(search_term, sizeof(search_term), stdin);
        search_term[strcspn(search_term, "\n")] = '\0';
        
        printf("\n#######  Address Book  #######\n");
        printf("#######  Search Result:\n\n");
        printf("===============================================================================================\n");
        printf(": S.No : Name                            : Phone No                       : Email ID                        :\n");
        printf("===============================================================================================\n");
        
        contactFound = 0;
        for (i = 0; i < address_book->count; i++)
        {
            int isMatchFound = 0;
            
            if (userSelection == 1)
            {
                if (strstr(*address_book->list[i].name, search_term) != NULL)
                {
                    isMatchFound = 1;
                }
            }

            else if (userSelection == 2) 
            {
                for (j = 0; j < PHONE_NUMBER_COUNT; j++)
                {
                    if (address_book->list[i].phone_numbers[j][0] != '\0' &&
                        strstr(address_book->list[i].phone_numbers[j], search_term) != NULL)
                    {
                        isMatchFound = 1;
                        break;
                    }
                }
            }

            else if (userSelection == 3)
            {
                for (j = 0; j < EMAIL_ID_COUNT; j++)
                {
                    if (address_book->list[i].email_addresses[j][0] != '\0' &&
                        strstr(address_book->list[i].email_addresses[j], search_term) != NULL)
                    {
                        isMatchFound = 1;
                        break;
                    }
                }
            }
            
            if (isMatchFound)
            {
                contactFound = 1;
                printf(": %-4d : %-32s :", i + 1, *address_book->list[i].name);
                
                for (j = 0; j < PHONE_NUMBER_COUNT; j++)
                {
                    if (address_book->list[i].phone_numbers[j][0] != '\0')
                    {
                        if (j == 0)
                        {
                            printf(" %-32s :", address_book->list[i].phone_numbers[j]);
                        }
                        else
                        {
                            printf("\n:      :                                : %-32s :", address_book->list[i].phone_numbers[j]);
                        }
                    }
                }
                
                for (j = 0; j < EMAIL_ID_COUNT; j++)
                {
                    if (address_book->list[i].email_addresses[j][0] != '\0')
                    {
                        if (j == 0 && address_book->list[i].phone_numbers[0][0] != '\0')
                        {
                            printf(" %-32s :", address_book->list[i].email_addresses[j]);
                        }
                        else if (j == 0)
                        {
                            printf("                                : %-32s :", address_book->list[i].email_addresses[j]);
                        }
                        else
                        {
                            printf("\n:      :                                :                                : %-32s :", address_book->list[i].email_addresses[j]);
                        }
                    }
                }
                
                printf("\n");
            }
        }
        
        if (contactFound == 0)
        {
            printf(": No matching contacts found\n");
        }
        
        printf("===============================================================================================\n");
        printf("Press any key to continue or 'q' to Cancel: ");
        {
            char buffer[10];
            if (fgets(buffer, sizeof(buffer), stdin) != NULL)
            {
                input = buffer[0];
            }
            else
            {
                input = '\n';
            }
        }
        
    } while (userSelection != 0 && input != 'q');
    
    return e_success;
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
