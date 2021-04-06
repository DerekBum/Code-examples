#include "assert.h"
#include "string.h"
#include "str.h"
#include "test_str.h"

void test_strcpy() {
	char a[20];
	*a = 'h';
	*(a + 1) = 'e';
	*(a + 2) = 'l';
	*(a + 3) = 'l';
	*(a + 4) = 'o';
	*(a + 5) = '\0';
	char* b = "world";
	char* a2 = strdup(a);
	char* b2 = strdup(b);
	char* res = my_strcpy(a, b);
	char* true_res = strcpy(a2, b2);
	assert(strcmp(res, true_res) == 0 && "strcpy ERROR");
}

void test_strcat() {
	char a[9] = "hi,\0";
	char b[9] = "hi,\0";
	assert(strcmp(my_strcat(a, "world"), strcat(b, "world")) == 0 && "strcat ERROR");
}

void test_strcmp() {
	assert(my_strcmp("hello", "world") == strcmp("hello", "world") && "strcmp ERROR");
	assert(my_strcmp("hello", "aworld") == strcmp("hello", "aworld") && "strcmp ERROR");
	assert(my_strcmp("hello", "hello") == strcmp("hello", "hello") && "strcmp ERROR");
	assert(my_strcmp("", "hello") == strcmp("", "hello") && "strcmp ERROR");
	assert(my_strcmp("hello", "") == strcmp("hello", "") && "strcmp ERROR");
	assert(my_strcmp("", "") == strcmp("", "") && "strcmp ERROR");
	assert(my_strcmp("", "ab") == strcmp("", "ab") && "strcmp ERROR");
}

void test_strlen() {
	assert(my_strlen("hello") == strlen("hello") && "strlen ERROR");
	assert(my_strlen("") == strlen("") && "strlen ERROR");
	assert(my_strlen("123") == strlen("123") && "strlen ERROR");
	assert(my_strlen("world") == strlen("world") && "strlen ERROR");
	assert(my_strlen("hello, world") == strlen("hello, world") && "strlen ERROR");
}
