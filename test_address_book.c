#include "unity.h"
#include "address_book.h"
#include "address_book_fops.h"

//Set up (runs before each test)
void setUp(void) {}

//Tear down (runs after each test)
void tearDown(void) {}

//Test add contact
void test_add_contact(void) {
    AddressBook book;
	initialize_address_book(&book); //Initialize an address book for testing

    int result = add_contact(&book, "Vincent");
    TEST_ASSERT_EQUAL(e_success, result); //Check if adding was successful

    //Check if they were actually added
    ContactInfo *found = search_contact_by_name(&book, "Vincent");
    TEST_ASSERT_NOT_NULL(found); //Check if it does exist
    TEST_ASSERT_EQUAL_STRING("Vincent", found->name[0]); //Check if name was stored

}

//Test search contact
void test_search_contact(void) {

}

//Test edit contact
void test_edit_contact(void) {

}

//Test delete contact
void test_delete_contact(void) {

}

//Test list contacts
void test_list_contact(void) {

}

//Test saving address book
void test_save_address_book(void) {

}

//Test exiting the application
void test_exit(void) {

}

//Run tests
int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_add_contact);
    RUN_TEST(test_search_contact);
    RUN_TEST(test_edit_contact);
    RUN_TEST(test_delete_contact);
    RUN_TEST(test_list_contact);
    RUN_TEST(test_save_address_book);
    RUN_TEST(test_exit);

    UNITY_END();
}