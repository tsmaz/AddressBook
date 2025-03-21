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
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */
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

	system("clear");

	printf("#######  Address Book  #######\n");
	if (str != '\0')
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

		option = get_option(NUM, "");

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				/* Add your implementation to call add_contacts function here */
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
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
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
		scanf("%s", number);
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
