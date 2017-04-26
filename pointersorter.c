#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***
 *CS 214 Systems Programming
 *Assignment 0: String Sorting
 *
 *@author Thurgood Kilper
 *@author Andrew Pagano
 */

/***
 *using linked list to store input strings
 */
typedef struct stringnode{
char* string;
struct stringnode * next;
}stringnode;

stringnode * sortedList;

/***
 *insert string nodes into sorted position
 */
stringnode * stringInsert(stringnode * head, char *in)
{
/*** 
 *check empty list
 */
    if(head==NULL){
        stringnode *newnode = malloc(sizeof(stringnode));
        newnode->string=malloc(strlen(in)+1);
        strcpy(newnode->string, in);
        newnode->next=NULL;
        head=newnode;
        return head;
    }
/***
 *check head node insertion
 */
    if(stringCompare(in, head->string)<0 || stringCompare(in, head->string)==0){
        stringnode *newnode = malloc(sizeof(stringnode));
        newnode->string=malloc(strlen(in)+1);
        strcpy(newnode->string, in);
        newnode->next=head;
        return newnode;
    }
    stringnode *current = head;
    stringnode *cnext = head->next;

/***
 *iterate through list and insert
 */
    while(cnext != NULL){
        if(stringCompare(in, cnext->string)<0 || stringCompare(in, cnext->string)==0){
            stringnode *newnode = malloc(sizeof(stringnode));
            newnode->string=malloc(strlen(in)+1);
            strcpy(newnode->string, in);
            newnode->next=cnext;
            current->next=newnode;
            return head;
        }else if(stringCompare(in, cnext->string)>0){
            current=cnext;
            cnext=current->next;
        }
    }

/***
 *check last node insertion
 */
    if(stringCompare(in, current->string)>0){
        stringnode *newnode = malloc(sizeof(stringnode));
        newnode->string=malloc(strlen(in)+1);
        strcpy(newnode->string, in);
        newnode->next=NULL;
        current->next=newnode;
    }

    return head;
}

/***
 *compare string nodes for sorting
 */
int stringCompare(char *s1, char *s2){
    /**placeholder*/
    return strcmp(s1, s2);
}

/***
 *print the list
 */
void printList(stringnode * listhead) {
    stringnode * current = listhead;

    while (current != NULL) {
        printf("%s\n", current->string);
        current = current->next;
    }
}

/***
 *iterates through list and frees allocated memory
 */
void cleanList(stringnode * listhead){

	stringnode * current;

	while (listhead != NULL) {
		current = listhead;
		listhead = listhead->next;
		free(current->string);
		free(current);
	}
}

int main(int argc, char **argv){
	sortedList = NULL;

/***
 *Checks for input.
 */
	if(argv[1]==NULL){
		return 0;
	}

	if(argv[2]!=NULL){
		printf("Usage: [String]\nInput single string to be sorted.\n");
		return 0;
	}
	
/***
 *Find length of input, and turns input into a useable string.
 */
	int length = strlen(argv[1]);
	char * string = (char *) calloc(length+1, sizeof(char));
	memset(string, '\0', length+1);
	strncpy(string,argv[1],length);

/***
 *Length of individual words inside input.
 */
	int wordLength = 0;
	int stop = 5;

	while(string[wordLength]!= '\0' && length>0){
/***
 *Finds valid word inside string and length of word.
 */
		while(string[wordLength] >= 65 && string[wordLength] <=90 || string[wordLength] >=97 && string[wordLength] <=122){
			wordLength++;
		}
/***
 *Turns word from master string into a valid string in order to sort. 
 */
		char *word;
		word =(char*)calloc(wordLength+1,  sizeof(char));
		memset(word, '\0', wordLength+1);
		strncpy(word, string, wordLength);
/***
 *Creates temporary holder of remaining master string in order to loop again to find more words.
 */
		char * stringHolder;
		stringHolder = string;
		length-=wordLength+1;
		strcpy(string,stringHolder+1+wordLength);
/***
 *Puts word into Linked list and sorts.
 */
		if(wordLength>0){
			sortedList=stringInsert(sortedList, word);
		}
		wordLength = 0;

		free(word);
	}
		free(string);

   		printList(sortedList);
		cleanList(sortedList);
	
	return 0;
}