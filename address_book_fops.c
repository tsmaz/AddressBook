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
  	if (address_book->fp == NULL) {
    	ret = 0;
	}
	else {
		ret = 1;
	}
	printf("%d",ret);
	if (ret == 0)
	{
		int counter = address_book->count;
		FILE *read = address_book->fp;
		char temp[1024];
		int column = 0;
		while(fgets(temp,1024, read)){
			column = 0;
			char *value = strtok(temp, ",");
			while (value){
				if (column == 0){
					strcpy(address_book->list->name[address_book->list->si_no],value);
				}

				if (column == 1){
					strcpy(address_book->list->phone_numbers[address_book->list->si_no],value);
				}
				if (column == 2){
					strcpy(address_book->list->email_addresses[address_book->list->si_no],value);
				}
				char *value = strtok(NULL, ",");
				column++;
			}
			address_book->list->si_no = (address_book->list->si_no)+1;
			
		}
		fclose(read);
		

	}
	else
	{
		address_book->fp = NULL;
		printf("First set done");
		address_book->fp = fopen(DEFAULT_FILE, "w");
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
