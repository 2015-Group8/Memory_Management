#include "my_list.h"

void initial_list(my_list* head) {
	head = NULL;
}

my_list* insert_list(my_list* head, char* key, void* item) {
	my_list* curMyList;

//	curMyList = find_list(head, key);
//	if(curMyList!=NULL) return curMyList;
	
	curMyList = (my_list*) malloc (sizeof(my_list));
	
//	curMyList->key = str_malloc(key);
	curMyList->key = key;
	curMyList->item = item;

	if(head == NULL) {
		curMyList->prev = NULL;
		curMyList->next = NULL;
	} else {
		curMyList->prev = NULL;
		curMyList->next = head;
		head->prev = curMyList;
	}

	return curMyList;
}

my_list* find_list(my_list* head, char* key) {
	my_list* curMyList;
	
	curMyList = head;
	
	while(curMyList!=NULL) {
		if(strcmp(curMyList->key, key)==0) 
			return curMyList;
		curMyList = curMyList->next;
	}
	return NULL;
}

void show_list(my_list* head) {
	my_list* curMyList;
	
	curMyList = head;
	
	while(curMyList!=NULL) {
		printf("%s\n", curMyList->key);
		curMyList = curMyList->next;
	}
}

char* str_malloc(char* buf) {
	char* ptr;

	ptr = (char*) malloc (sizeof(char)*strlen(buf) + 1);
	strcpy(ptr, buf);

	return ptr;
}

