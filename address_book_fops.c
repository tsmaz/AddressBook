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
	FILE *f =fopen(DEFAULT_FILE,"r");
  	if (f != NULL) { 
		ret = 0;
	}
	else {
		ret = 1;
	}
	if (ret == 0)
	{
		//this section needs testing, but I can't save anything inside a csv
		int counter;
		address_book->fp = f;
		char temp[1024];
		int column = 0;
		int counting;
		address_book->list = (ContactInfo *)malloc(sizeof(ContactInfo)*100);
		while(fgets(temp,1024, f)){
			column = 0;
			char *value = strtok(temp, ",");
			while (value){
				if (column == 0){
					strcpy(address_book->list[counter].name[0],value);
				}

				if (column == 1){
					char *numerator = strtok(value, "\n");
					while (numerator){
						strcpy(address_book->list[counter].phone_numbers[counting],numerator);
						counting++;
						char *numerator = strtok(NULL, "\n");

					}
					counting = 0;

				}
				if (column == 2){
					char *numerator = strtok(value, "\n");
					while (numerator){
						strcpy(address_book->list[counter].email_addresses[counting],numerator);
						counting++;
						char *numerator = strtok(NULL, "\n");

					}
					counting = 0;
				}
				char *value = strtok(NULL, ",");
				column++;

			}
			address_book->list[counter].si_no = counter;
			counter++;


			
		}
		address_book->count = counter;
		

	}
	else
	{
		address_book->fp = NULL;
		address_book->fp = fopen(DEFAULT_FILE, "w");
		address_book->count = 0;
		address_book->list = (ContactInfo *)malloc(sizeof(ContactInfo)*100);
		if (address_book->fp == NULL){
			printf("Failed");
		}
	}
return e_success;
}
Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 

	fclose(address_book->fp);

	return e_success;
}
