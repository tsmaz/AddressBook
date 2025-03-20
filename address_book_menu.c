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
	while (getchar() != '\n')
		;
	int check = 1;
	int choice;
	char nameing[100] = "\0";
	char number[100];
	char email[100];
	int names_list = 0;
	int numbers_list = 0;
	int emails_list = 0;
	int order = address_book->count;
	order++;
	address_book->list[address_book->count].si_no = order;
	do
	{

		printf("what would you like to do:\n");
		printf("0. Exit\n");
		printf("1. Add Name: %s\n", nameing);
		if (numbers_list == 0)
		{
			printf("2. Add phone number: \n");
		}
		else
		{
			printf("2. Add phone number: %s\n", number);
		}
		printf("3. Add email: %s\n", email);
		choice = get_option(NUM, "Please select an option: ");

		switch (choice)
		{
		case e_first_opt:
			if (names_list == 1)
			{
				address_book->count++;
				check = 0;
			}
			else
			{
				printf("Sorry, make sure the name is filled before sending\n");
			}
			break;

		case e_second_opt:
			printf("Write the name you want to add:");
			scanf("%s", &nameing);
			strcpy(address_book->list[address_book->count].name[0], nameing);
			names_list = 1;
			break;
		case e_third_opt:
			printf("Write the phone number you want to add:");
			scanf("%s", &number);
			strcpy(address_book->list[address_book->count].phone_numbers[numbers_list], number);
			numbers_list++;
			break;
		case e_fourth_opt:
			printf("Write what email you want to add:");
			scanf("%s", &email);
			strcpy(address_book->list[address_book->count].email_addresses[emails_list], email);
			emails_list++;
			break;
		default:
			printf("Sorry, try again\n");
		}
		while (getchar() != '\n')
			;
	} while (check != 0);

	return e_back;
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
