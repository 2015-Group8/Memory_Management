#ifndef MY_LIST_H__
#define MY_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _my_list {
	char* key;
	void* item;
	struct _my_list *prev;
	struct _my_list *next;
} my_list;

void initial_list(my_list* head);
my_list* insert_list(my_list* head, char* key, void* item);
my_list* find_list(my_list* head, char* key);
void show_list(my_list* head);

char* str_malloc(char* buf);

#endif
