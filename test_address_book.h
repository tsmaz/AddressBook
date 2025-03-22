#ifndef TEST_ADDRESS_BOOK_H
#define TEST_ADDRESS_BOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "address_book.h"

// Test helper function declarations
void create_test_input(const char* input);
void restore_stdin(int original_stdin);

// Test function declarations
void setUp(void);
void tearDown(void);
void test_add_contact(void);
void test_add_contact_multiple(void);
void test_search_contact(void);

#endif /* TEST_ADDRESS_BOOK_H */ 