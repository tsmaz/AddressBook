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
	char name[100];
	printf("%s\n",msg);
	switch(type){
		case NUM:
			scanf("%d", &n);
			return n;
		case CHAR:
			scanf("%s", &name);
			return (int)(uintptr_t)name;
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
		printf("hello");
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
	int check;
	int choice;
	char nameing[100];
	int number;
	char email[100];
	int names_list = 0;
	int	numbers_list = 0;
	int emails_list = 0;
	int order = address_book->count;
	order++;
	printf("Adding contact %d at index %d\n", order, address_book->count);
	address_book->list[address_book->count].si_no = order;
	printf("Assigned si_no: %d to contact at index %d\n", order + 1, address_book->count);
	printf("WHATS THE PROBLEM??");
	do{
		printf("what would you like to do:\n");
		printf("0. Exit\n");
		printf("1. Add Name: %s\n", nameing);
		printf("2. Add phone number: %d\n", number);
		printf("3. Add email: %s\n", email);
		
		int check = 1;
		choice = get_option(NUM,"");

		switch (choice){
			case e_first_opt:
				if (names_list == 1){
					address_book->count++;
					check = 0;
				}
				else {
					printf("Sorry, make sure the name is filled before sending");
				}
		
			case  e_second_opt:
				strcpy(nameing,(char *)(uintptr_t) get_option(CHAR,"Write what name you want to add:"));
				printf("%s",nameing);
				names_list = 1;
				strcpy(address_book->list[address_book->count].name[0],nameing);
				break;
			case  e_third_opt:
				number = get_option(NUM,"Write the phone number you want to add:");
				*address_book->list[address_book->count].phone_numbers[numbers_list] = number;
				numbers_list++;
				break;
			case  e_fourth_opt:
				strcpy(email,(char *)(uintptr_t)get_option(CHAR,"Write what email you want to add:"));
				strcpy(address_book->list[address_book->count].email_addresses[emails_list],email);
				emails_list++;
				break;
		}
	}while (check == 1);
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
