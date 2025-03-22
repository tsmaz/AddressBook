#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include "unity.h"
#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"
#include "test_address_book.h"

/* Function to create test input file */
void create_test_input(const char* input) {
    FILE* fp = fopen("./test_input.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "%s", input);
        fclose(fp);
    }
}

/* Function to restore stdin */
void restore_stdin(int original_stdin) {
    dup2(original_stdin, STDIN_FILENO);
    close(original_stdin);
}

void setUp(void) {
    /* Setup code if needed */
}

void tearDown(void) {
    /* Remove test input file */
    unlink("test_input.txt");
}

void test_add_contact(void) {
    /* Test Input */
    const char* test_input = 
        "1\n"           /* Choose to add name */
        "John\n"        /* Enter name */
        "2\n"           /* Choose to add phone */
        "1234567890\n"  /* Enter phone */
        "3\n"           /* Choose to add email */
        "john@test.com\n" /* Enter email */
        "0\n";          /* Save and exit */

    create_test_input(test_input);

    /* Save original stdin */
    int original_stdin = dup(STDIN_FILENO);
    
    /* Redirect stdin to test input file */
    int test_input_fd = open("test_input.txt", O_RDONLY);
    dup2(test_input_fd, STDIN_FILENO);
    close(test_input_fd);

    /* Test Case */
    AddressBook book;
    book.count = 0;
    book.list = (ContactInfo *)malloc(sizeof(ContactInfo) * 100);
    TEST_ASSERT_NOT_NULL(book.list);
    memset(book.list, 0, sizeof(ContactInfo) * 100);

    /* Test adding a contact */
    Status result = add_contacts(&book);
    TEST_ASSERT_EQUAL(e_success, result);

    /* Verify the contact was added correctly */
    TEST_ASSERT_EQUAL(1, book.count);
    TEST_ASSERT_EQUAL_STRING("John", book.list[0].name[0]);
    TEST_ASSERT_EQUAL_STRING("1234567890", book.list[0].phone_numbers[0]);
    TEST_ASSERT_EQUAL_STRING("john@test.com", book.list[0].email_addresses[0]);

    /* Clean up */
    if (book.list != NULL) {
        free(book.list);
    }
}

void test_add_contact_multiple(void) {
    /* Test Input */
    const char* test_input = 
        "1\n"           /* Add Contact */
        "1\n"           /* Choose to add name */
        "John\n"        /* Enter name */
        "2\n"           /* Choose to add phone */
        "1234567890\n"  /* Enter phone */
        "3\n"           /* Choose to add email */
        "john@test.com\n" /* Enter email */
        "0\n"           /* Save and exit */
        "1\n"           /* Add another contact */
        "1\n"           /* Choose to add name */
        "John\n"        /* Enter name */
        "2\n"           /* Choose to add phone */
        "1234567890\n"  /* Enter phone */
        "3\n"           /* Choose to add email */
        "john@test.com\n" /* Enter email */
        "0\n"           /* Save and exit */
        "0\n"           /* Exit menu */
        "Y\n";          /* Confirm save */

    create_test_input(test_input);

    /* Save original stdin */
    int original_stdin = dup(STDIN_FILENO);
    
    /* Redirect stdin to test input file */
    int test_input_fd = open("test_input.txt", O_RDONLY);
    dup2(test_input_fd, STDIN_FILENO);
    close(test_input_fd);

    /* Test Case */
    AddressBook book;
    book.count = 0;
    book.list = (ContactInfo *)malloc(sizeof(ContactInfo) * 100);
    TEST_ASSERT_NOT_NULL(book.list);
    memset(book.list, 0, sizeof(ContactInfo) * 100);

    /* Test adding multiple contacts */
    Status result = menu(&book);
    TEST_ASSERT_EQUAL(e_success, result);

    /* Verify contacts were added correctly */
    TEST_ASSERT_EQUAL(2, book.count);

    /* Clean up */
    if (book.list != NULL) {
        free(book.list);
    }
}

void test_search_contact(void) {
    /* Implementation for search contact test */
}

#ifdef TESTING
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_add_contact);
    RUN_TEST(test_add_contact_multiple);
    return UNITY_END();
}
#endif