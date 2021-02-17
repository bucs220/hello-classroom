#include "functions.h"
#include <CUnit/Basic.h>
#include <stdlib.h>

/* Functions that will be implemented in libfunctions.a after submission */
extern long _sum(int a, int b);
extern bool _isFib(int n);
extern char* _fizzbuzz(int i, char* dest, size_t n);

/* Buffer for testFIZZBUZZ */
char* actual = NULL;
char* expected = NULL;

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite_hello(void) { 
	actual = (char*) malloc(12); 
	expected = (char*) malloc(12);

	// If either malloc fails, one or both pointers will be null
	if (actual && expected) { return 0; }
	else { return 1; }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite_hello(void) { 
	free(actual); 
	free(expected);
	return 0;
}

/* Test long sum(int a, int b); */
void testSUM(void){
	CU_ASSERT_EQUAL(sum(0,0), 0);
	CU_ASSERT_EQUAL(sum(1,2), 3);
	CU_ASSERT_EQUAL(sum(5,-3), 2);
	CU_ASSERT_EQUAL(sum(-5,3), -2);
}

/* Test bool isFib(int n); */
void testISFIB(void){
	CU_ASSERT_TRUE(isFib(0));
	CU_ASSERT_TRUE(isFib(1));
	CU_ASSERT_TRUE(isFib(2));
	CU_ASSERT_TRUE(isFib(3));
	CU_ASSERT_FALSE(isFib(4));
}

/* Test char* fizzbuzz(int i, char* dest, size_t n); */
void testFIZZBUZZ(void){
  
  fizzbuzz(3, actual, 9);
  strncpy(expected, "FIZZ\0\0\0\0\0", 9);
  CU_ASSERT_STRING_EQUAL(actual, expected);

  fizzbuzz(5, actual, 9);
  strncpy(expected, "BUZZ\0\0\0\0\0", 9);
  CU_ASSERT_STRING_EQUAL(actual, expected);

  fizzbuzz(15, actual, 9);
  strncpy(expected, "FIZZBUZZ\0", 9);
  CU_ASSERT_STRING_EQUAL(actual, expected);

  fizzbuzz(16, actual, 9);
  strncpy(expected, "16\0\0\0\0\0\0\0", 9);
  CU_ASSERT_STRING_EQUAL(actual, expected);

  fizzbuzz(-16, actual, 12);
  strncpy(expected, "-16\0\0\0\0\0\0\0\0\0\0", 12);
  CU_ASSERT_STRING_EQUAL(actual, expected);

  fizzbuzz(0, actual, 9);
  strncpy(expected, "FIZZBUZZ\0", 9);
  CU_ASSERT_STRING_EQUAL(actual, expected);

}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main(int argc, char** argv) {

  CU_pSuite pSuite = NULL;

  /* Argparse to find curses or console mode */
  char curses = 0;
  char console = 0;
  size_t i;
  for (i = 0; i < argc; i++) {
    if (strcmp(argv[i], "--curses") == 0) {
      curses = 1;
      console = 0;
    }
    if (strcmp(argv[i], "--console") == 0) {
      curses = 0;
      console = 1;
    }
  }

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  pSuite = CU_add_suite("Suite_Hello", init_suite_hello, clean_suite_hello);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if ((NULL ==
       CU_add_test(pSuite, "Testing sum function ...", testSUM)) ||
      (NULL ==
       CU_add_test(pSuite, "Testing isFib function ...", testISFIB)) ||
      (NULL == CU_add_test(pSuite, "Testing fizzbuzz function ...", testFIZZBUZZ))) {

    // Adding one or more tests failed. Cleanup!
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run tests */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}

