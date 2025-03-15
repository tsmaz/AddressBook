#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book)
{
	int ret;

	FILE *file = fopen(address_book->fp, "r");
  	if (file != NULL) {
    	fclose(file);
    	ret = 0;
	}
	else {
		ret = 1;
	}

	if (ret == 0)
	{
		int counter = address_book->count;
		FILE *reader = fopen(address_book->fp, "r");
		char temp[1024];
		int column = 0;
		while(fgets(temp,1024, reader)){
			column = 0;
			char value = strtok(temp, FIELD_DELIMITER);
			while (value){
				if (column == 0){
					*address_book->list->name = value;
				}

				if (column == 1){
					*address_book->list->phone_numbers = value;
				}
				if (column == 2){
					*address_book->list->email_addresses = value;
				}
				value = strtok(NULL, FIELD_DELIMITER);
				column++;
			}
			
		}
		fclose(reader);
		

	}
	else
	{
		FILE *ftpr;
		ftpr = fopen(DEFAULT_FILE, "r");
		if (ftpr == "NULL"){
			printf("Failed");
		}
		else {
			address_book->fp = ftpr;
			fclose(ftpr);

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
