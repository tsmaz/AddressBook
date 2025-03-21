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
		
		printf("What would you like to do:\n");
		printf("0. Add contact and exit\n");
		printf("1. Add Name: %s\n", nameing);
		if (numbers_list == 0){
			printf("2. Add phone number: \n");
		}
		else{
			printf("2. Add phone number: %s\n", number);
		}
		printf("3. Add email: %s\n", email);
		printf("4. Add current contact and start new contact\n");
		printf("5. Exit without adding contact\n");
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
				printf("Write the name you want to add: ");
				scanf("%s", &nameing);
				strcpy(address_book->list[address_book->count].name[0],nameing);
				names_list = 1;
				break;
			case  e_third_opt:
				printf("Write the phone number you want to add: ");
				scanf("%s", &number);
				strcpy(address_book->list[address_book->count].phone_numbers[numbers_list],number);
				numbers_list++;
				break;
			case  e_fourth_opt:
				printf("Write what email you want to add: ");
				scanf("%s",&email);
				strcpy(address_book->list[address_book->count].email_addresses[emails_list],email);
				emails_list++;
				break;
			case e_fifth_opt:
				if (names_list == 1){
					address_book->count++;
					strcpy(nameing, "\0");
					strcpy(number, "\0");
					strcpy(email, "\0");
					names_list = 0;
					numbers_list = 0;
					emails_list = 0;
					order++;
					address_book->list[address_book->count].si_no = order;
					printf("Contact added! Please add your new contact now!\n");
				}
				else {
					printf("Sorry, make sure at least the name is filled out before moving on!\n");
				}
				break;
			case e_sixth_opt:
				printf("Are you sure you would like to exit without adding this current contact?\n0. Yes\n1. No\n");
				int confirm = get_option(NUM,"Please select an option: ");
				switch(confirm) {
					case e_first_opt:
						printf("Exiting add contact menu...\n");
						check = 0;
						break;
					default:
						printf("Option selected was not 0, returning to add contact menu\n");
						break;
				}
				break;
			default:
				printf("Sorry, try again\n");
				

		}
		while (getchar() != '\n');
	}while (check != 0);
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
