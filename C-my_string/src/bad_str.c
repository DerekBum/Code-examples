#include "str.h"

char* my_strcpy(char* src, char* res) {
	char* t = res;
	while (*src != '\0')
		*res++ = *src++;
	*res = '\0';
	return t;
}

char* my_strcat(char* res, char* add) {
	char* t = res;
	while (*add != '\0')
		*res++ = *add++;
	*res = '\0';
	return t;
}

int my_strcmp(char* first, char* second) {
	while (*first != '\0') {
		if (*first > *second)
			return 1;
		if (*first < *second)
			return -1;
		*first++;
	}
	return 0;
}

int my_strlen(char* str) {
	int res = 0;
	while (*str != '\0') {
		*str++;
	}
	return res;
}
