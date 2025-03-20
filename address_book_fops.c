#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book)
{
	int ret;
	FILE *f = fopen(DEFAULT_FILE, "r");
	if (f != NULL)
	{
		ret = 0;
	}
	else
	{
		ret = 1;
	}
	if (ret == 0)
	{
		int counter = 0;
		address_book->fp = f;
		char temp[1024];
		int counting = 0;
		address_book->list = (ContactInfo *)malloc(sizeof(ContactInfo) * 100);

		while (fgets(temp, 1024, f))
		{
			temp[strcspn(temp, "\n")] = 0;

			int column = 0;
			char *saveptr1;
			char *value = strtok_r(temp, ",", &saveptr1);

			while (value != NULL)
			{
				if (column == 0)
				{
					strcpy(address_book->list[counter].name[0], value);
				}
				else if (column == 1)
				{
					counting = 0;
					char *phone_copy = strdup(value);
					char *saveptr2;
					char *phone = strtok_r(phone_copy, " ", &saveptr2);

					while (phone && counting < PHONE_NUMBER_COUNT)
					{
						strcpy(address_book->list[counter].phone_numbers[counting], phone);
						counting++;
						phone = strtok_r(NULL, " ", &saveptr2);
					}
					free(phone_copy);
				}
				else if (column == 2)
				{
					counting = 0;
					char *email_copy = strdup(value);
					char *saveptr3;
					char *email = strtok_r(email_copy, " ", &saveptr3);

					while (email && counting < EMAIL_ID_COUNT)
					{
						strcpy(address_book->list[counter].email_addresses[counting], email);
						counting++;
						email = strtok_r(NULL, " ", &saveptr3);
					}
					free(email_copy);
				}
				else if (column == 3)
				{
					address_book->list[counter].si_no = atoi(value);
				}
				value = strtok_r(NULL, ",", &saveptr1);
				column++;
			}
			counter++;
		}
		address_book->count = counter;

		// Debug
		printf("Address book loaded successfully\n");
		for (int contact = 0; contact < address_book->count; contact++)
		{
			printf("Contact Name: %s\n", address_book->list[contact].name);

			for (int i = 0; address_book->list[contact].phone_numbers[i][0] != '\0'; i++)
			{
				printf("Phone Number: %s\n", address_book->list[contact].phone_numbers[i]);
			}
			for (int i = 0; address_book->list[contact].email_addresses[i][0] != '\0'; i++)
			{
				printf("Email: %s\n", address_book->list[contact].email_addresses[i]);
			}
			printf("ID: %d\n", address_book->list[contact].si_no);
		}
	}
	else
	{
		if (address_book->fp == NULL)
		{
			printf("Failed to create file\n");
			return e_fail;
		}
	}
	return e_success;
}

Status save_file(AddressBook *address_book)
{
	if (address_book->fp != NULL)
	{
		fclose(address_book->fp);
	}

	address_book->fp = fopen(DEFAULT_FILE, "w");
	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	// Write to file
	for (int i = 0; i < address_book->count; i++)
	{
		printf("Exiting. Data saved in address_book.csv\n");
		fprintf(address_book->fp, "%s,", address_book->list[i].name[0]);

		// Write phone numbers
		if (address_book->list[i].phone_numbers[0][0] == '\0'){
			fprintf(address_book->fp, " ");
		}
		for (int j = 0; j < PHONE_NUMBER_COUNT && address_book->list[i].phone_numbers[j][0] != '\0'; j++)
		{
			if (j > 0)
				fprintf(address_book->fp, " ");
			fprintf(address_book->fp, "%s", address_book->list[i].phone_numbers[j]);
		}
		fprintf(address_book->fp, ",");

		// Write email addresses
		if (address_book->list[i].email_addresses[0][0] == '\0'){
			fprintf(address_book->fp, " ");
		}
		for (int j = 0; j < EMAIL_ID_COUNT && address_book->list[i].email_addresses[j][0] != '\0'; j++)
		{
			if (j > 0)
				fprintf(address_book->fp, " ");
			fprintf(address_book->fp, "%s", address_book->list[i].email_addresses[j]);
		}
		fprintf(address_book->fp, ",");

		address_book->list[i].si_no = i + 1;
		fprintf(address_book->fp, "%d\n", address_book->list[i].si_no);
	}

	fclose(address_book->fp);
	return e_success;
}