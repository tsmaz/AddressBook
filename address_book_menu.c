#include <stdio.h>
// #include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "address_book.h"
#include "address_book_menu.h"
#include "address_book_fops.h"

// #include "abk_fileops.h"
// #include "abk_log.h"
// #include "abk_menus.h"
// #include "abk.h"

int get_option(int type, const char *msg)
{
	int n;
	char name;
	printf("%s\n", msg);
	switch (type)
	{
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
			save_file(address_book);
			break;
		}
	} while (option != 'N');

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	if (address_book->count == 0)
	{
		printf("No contacts found!\n");
		return e_no_match;
	}

	const int contacts_per_page = 2;
	int total_pages = (address_book->count + contacts_per_page - 1) / contacts_per_page;
	char option;


	// Ensure index is within bounds
	if (*index >= total_pages)
	{
		*index = total_pages - 1;
	}

	// Handle pagination commands
	if (mode == e_list && msg != NULL && *msg != '\0')
	{
		if (strcmp(msg, "n") == 0 && *index < total_pages - 1)
		{
			(*index)++;
		}
		else if (strcmp(msg, "p") == 0 && *index > 0)
		{
			(*index)--;
		}
	}

	menu_header(title);

	// Calculate start and end indices for current page
	int start = *index * contacts_per_page;
	int end = start + contacts_per_page;
	if (end > address_book->count)
	{
		end = address_book->count;
	}

	printf("=================================================================================================\n");
	printf(": S.No : Name                         : Phone No               : Email ID                       :\n");
	printf("=================================================================================================\n");

	// Ensure we don't go out of bounds
	if (start < address_book->count)
	{
		for (int i = start; i < end && i < address_book->count; i++)
		{
			if (address_book->list[i].name[0] != NULL)
			{
				printf(": %-4d: %-28s : %-22s : %-32s:\n",
					   address_book->list[i].si_no,
					   address_book->list[i].name[0],
					   address_book->list[i].phone_numbers[0][0] != '\0' ? address_book->list[i].phone_numbers[0] : " ",
					   address_book->list[i].email_addresses[0][0] != '\0' ? address_book->list[i].email_addresses[0] : " ");

				for (int j = 1; j < 5; j++)
				{
					printf(": %-4s: %-28s : %-22s : %-32s:\n",
						   " ",
						   " ",
						   address_book->list[i].phone_numbers[j][0] != '\0' ? address_book->list[i].phone_numbers[j] : " ",
						   address_book->list[i].email_addresses[j][0] != '\0' ? address_book->list[i].email_addresses[j] : " ");
				}
				printf("=================================================================================================\n");
			}
		}
	}

	// Display pagination information
	printf("\nPage %d of %d\n", *index + 1, total_pages);
	// Get option
	do
	{

		option = get_option(CHAR, "Press: [n] = Next Page, Press: [p] = Previous Page, Press: [q] | Cancle: ");
		
		if (option == 'n')
		{
			if (*index < total_pages - 1)
			{
				return list_contacts(address_book, title, index, "n", mode);
			}
			printf("Out of Bounds \n");
		}
		else if (option == 'p')
		{
			if (*index > 0)
			{
				return list_contacts(address_book, title, index, "p", mode);
			}
			printf("Out of Bounds \n");
		}
	} while (option != 'q');

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
	int page_index = 0;  // Initialize page index

	do
	{
		main_menu();
		option = get_option(NUM, "");

		if ((address_book->count == 0) && (option != e_add_contact))
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
			list_contacts(address_book, "Search Result", &page_index, "", e_list);
			break;
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
	int check = 1;
	int choice;
	char nameing[100];
	char number[100];
	char email[100];
	int names_list = 0;
	int numbers_list = 0;
	int emails_list = 0;
	int order = address_book->count;
	order++;
	
	// Initialize the new contact
	memset(&address_book->list[address_book->count], 0, sizeof(ContactInfo));
	address_book->list[address_book->count].si_no = order;

	do {
		printf("\nWhat would you like to do:\n");
		printf("0. Add contact and exit\n");
		printf("1. Add Name: %s\n", nameing);
		
		// Display phone numbers in numbered format
		printf("2. Phone No");
		if (numbers_list == 0) {
			printf(" (none added)\n");
		} else {
			printf(":\n");
			for (int i = 0; i < numbers_list; i++) {
				printf("   %d : %s\n", i + 1, address_book->list[address_book->count].phone_numbers[i]);
			}
		}
		
		// Display email addresses in numbered format
		printf("3. Email ID");
		if (emails_list == 0) {
			printf(" (none added)\n");
		} else {
			printf(":\n");
			for (int i = 0; i < emails_list; i++) {
				printf("   %d : %s\n", i + 1, address_book->list[address_book->count].email_addresses[i]);
			}
		}
		
		printf("4. Add current contact and start new contact\n");
		printf("5. Exit without adding contact\n");
		choice = get_option(NUM, "Please select an option: ");

		switch (choice) {
			case e_first_opt:
				if (names_list == 1) {
					address_book->count++;
					check = 0;
				} else {
					printf("Sorry, make sure the name is filled before sending\n");
				}
				break;

			case e_second_opt:
				printf("Write the name you want to add: ");
				scanf("%99s", nameing);
				strncpy(address_book->list[address_book->count].name[0], nameing, NAME_LEN - 1);
				address_book->list[address_book->count].name[0][NAME_LEN - 1] = '\0';
				names_list = 1;
				break;

			case e_third_opt:
				if (numbers_list < PHONE_NUMBER_COUNT) {
					printf("Enter Phone No %d: ", numbers_list + 1);
					scanf("%99s", number);
					strncpy(address_book->list[address_book->count].phone_numbers[numbers_list], 
						   number, NUMBER_LEN - 1);
					address_book->list[address_book->count].phone_numbers[numbers_list][NUMBER_LEN - 1] = '\0';
					numbers_list++;
				} else {
					printf("Maximum number of phone numbers reached!\n");
				}
				break;

			case e_fourth_opt:
				if (emails_list < EMAIL_ID_COUNT) {
					printf("Enter Email ID %d: ", emails_list + 1);
					scanf("%99s", email);
					strncpy(address_book->list[address_book->count].email_addresses[emails_list], 
						   email, EMAIL_ID_LEN - 1);
					address_book->list[address_book->count].email_addresses[emails_list][EMAIL_ID_LEN - 1] = '\0';
					emails_list++;
				} else {
					printf("Maximum number of email addresses reached!\n");
				}
				break;

			case e_fifth_opt:
				if (names_list == 1) {
					address_book->count++;
					// Initialize for new contact
					memset(&address_book->list[address_book->count], 0, sizeof(ContactInfo));
					names_list = 0;
					numbers_list = 0;
					emails_list = 0;
					order++;
					address_book->list[address_book->count].si_no = order;
					printf("Contact added! Please add your new contact now!\n");
				} else {
					printf("Sorry, make sure at least the name is filled out before moving on!\n");
				}
				break;

			case e_sixth_opt:
				printf("Are you sure you would like to exit without adding this current contact?\n0. Yes\n1. No\n");
				int confirm = get_option(NUM, "Please select an option: ");
				if (confirm == e_first_opt) {
					printf("Exiting add contact menu...\n");
					check = 0;
				} else {
					printf("Option selected was not 0, returning to add contact menu\n");
				}
				break;

			default:
				printf("Sorry, try again\n");
		}
		
		while (getchar() != '\n')
			;
	} while (check != 0);

	return e_success;
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
	char name[NAME_LEN];
	char phone[NUMBER_LEN];
	char email[EMAIL_ID_LEN];
	int index = -1;
	ContactInfo *contact = &address_book->list[index];
	menu_header("Edit contact:\n");
	printf("1. Find by name\n");
	printf("2. Find by phone number\n");
	printf("3. Find by email\n");
	printf("4. Find by ID\n");
	printf("\nPlease select an option: ");
	int option = get_option(NUM, "");

	if (option == 1) {
		printf("Please enter the name: ");
		scanf("%s", name);
		for (int i = 0; i < address_book->count; i++) {
			ContactInfo *contact = &address_book->list[i];
			if (strcasecmp(contact->name[0], name) == 0) {
				index = i;
				break;
			}
		}
	} else if (option == 2) {
		printf("Please enter the phone number: ");
		scanf("%s", phone);
		for (int i = 0; i < address_book->count; i++) {
			ContactInfo *contact = &address_book->list[i];
			for (int j = 0; j < PHONE_NUMBER_COUNT; j++) {
				if (strcasecmp(contact->phone_numbers[j], phone) == 0){
					index = i;
					break;
				}
			}
			if (index != -1) {
				break;
			}
		}
	} else if (option == 3) {
		printf("Please enter the email: ");
		scanf("%s", email);
		for (int i = 0; i < address_book->count; i++) {
			ContactInfo *contact = &address_book->list[i];
			for (int j = 0; j < EMAIL_ID_COUNT; j++) {
				if (strcasecmp(contact->email_addresses[j], email) == 0){
					index = i;
					break;
				}
			}
			if (index != -1) {
				break;
			}
		}
	}

	if (index == -1) {
		printf("No contact found.\n");
		return e_no_match;
	} 

	menu_header("Editing found contact:\n");
	printf("1. Edit name\n");
	printf("2. Edit phone number\n");
	printf("3. Edit email\n");
	printf("4. Main Menu\n");
	printf("\nPlease select an option: ");
	option = get_option(NUM, "");

	if (option == 1) {
		printf("Please enter the new name: ");
		scanf("%s", address_book->list[index].name[0]);
		printf("Name updated!");
		return e_success;
	} else if (option == 2) {
		printf("Phone numbers for %s:\n", contact->name[0]);
    	for (int j = 0; j < PHONE_NUMBER_COUNT; j++) {
        	if (contact->phone_numbers[j][0] != '\0') {  
            	printf("%d. %s\n", j + 1, contact->phone_numbers[j]);
        	}
    	}
		printf("\nPlease select an option: ");
		option = get_option(NUM, "");

		if (option < 1 || option > PHONE_NUMBER_COUNT || contact->phone_numbers[option - 1][0] == '\0') {
			printf("Invalid selection.\n");
			return e_fail;
		}
		
		printf("Please enter the new phone number: ");
		scanf("%s", address_book->list[index].phone_numbers[option - 1]);
		printf("\nPhone number changed!");
		return e_success;
	} else if (option == 3) {
		printf("Emails for %s:\n", contact->name[0]);
    	for (int j = 0; j < EMAIL_ID_COUNT; j++) {
        	if (contact->email_addresses[j][0] != '\0') {  
            	printf("%d. %s\n", j + 1, contact->email_addresses[j]);
        	}
    	}
		printf("\nPlease select an option: ");
		option = get_option(NUM, "");

		if (option < 1 || option > EMAIL_ID_COUNT || contact->email_addresses[option - 1][0] == '\0') {
			printf("Invalid selection.\n");
			return e_fail;
		}
		
		printf("Please enter the new email: ");
		scanf("%s", address_book->list[index].email_addresses[option - 1]);
		printf("\nEmail changed!");
		return e_success;
	}

	return e_fail;
}

Status delete_contact(AddressBook *address_book)
{
	char name[NAME_LEN];
	char email[EMAIL_ID_LEN];
	char phone[NUMBER_LEN];
	int index = -1;
	menu_header("Delete contact:\n");
	printf("1. Delete by name\n");
	printf("2. Delete by phone number\n");
	printf("3. Delete by email\n");
	printf("4. Delete by ID\n");
	printf("\nPlease select an option: ");
	int option = get_option(NUM, "");

	if (option == 1) {
		printf("Please enter the name: ");
		scanf("%s", name);
		for (int i = 0; i < address_book->count; i++) {
			ContactInfo *contact = &address_book->list[i];
			if (strcasecmp(contact->name[0], name) == 0) {
				index = i;
				break;
			}
		}
	} else if (option == 2) {
		printf("Please enter the phone number: ");
		scanf("%s", phone);
		for (int i = 0; i < address_book->count; i++) {
			ContactInfo *contact = &address_book->list[i];
			for (int j = 0; j < PHONE_NUMBER_COUNT; j++) {
				if (strcasecmp(contact->phone_numbers[j], phone) == 0){
					index = i;
					break;
				}
			}
			if (index != -1) {
				break;
			}
		}
	} else if (option == 3) {
		printf("Please enter the email: ");
		scanf("%s", email);
		for (int i = 0; i < address_book->count; i++) {
			ContactInfo *contact = &address_book->list[i];
			for (int j = 0; j < EMAIL_ID_COUNT; j++) {
				if (strcasecmp(contact->email_addresses[j], email) == 0){
					index = i;
					break;
				}
			}
			if (index != -1) {
				break;
			}
		}
	}

	if (index == -1) {
		printf("No contact found.\n");
		return e_no_match;
	} else {
		printf("Contact found. Deleting...\n");
	}

	for (int i = index; i < address_book->count - 1; i++) {
		address_book->list[i] = address_book->list[i + 1];
	}
	ContactInfo *last_contact = &address_book->list[address_book->count - 1];
    memset(last_contact, 0, sizeof(ContactInfo));
	address_book->count--;
	printf("Contact successfully deleted.\n");
	return e_success;
}
