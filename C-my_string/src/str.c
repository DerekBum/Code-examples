#include "str.h"

char* my_strcpy(char* res, char* src) {
	char* t = res;
	while (*src != '\0')
		*res++ = *src++;
	*res = '\0';
	return t;
}

char* my_strcat(char* res, char* add) {
	char* t = res;	
	while (*res != '\0')
		res++;
	while (*add != '\0')
		*res++ = *add++;
	*res = '\0';
	return t;
}

int my_strcmp(char* first, char* second) {
	while (*first != '\0' && *second != '\0' && *first == *second) {
		*first++;
		*second++;
	}
	if (*first == '\0' && *second == '\0')
		return 0;
	if (*first == '\0')
		return -1;
	if (*second == '\0')
		return 1;
	if (*first < *second)
		return -1;
	return 1;
}

int my_strlen(char* str) {
	int res = 0;
	while (*str != '\0') {
		*str++;
		res++;
	}
	return res;
}
