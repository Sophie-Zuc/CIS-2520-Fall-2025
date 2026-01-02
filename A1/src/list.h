/*
Name: Sophie Zuccolo
Login: szuccolo
Student ID: 1293676
Date: 09/26/25
*/

//ifndef macro
#ifndef _LIST_H
#define _LIST_H

//Including preexisting libraries
#include <stdio.h>
#include <stdlib.h>

//Structure definition
struct list {
  int head;
  int current;
};

//Function prototypes
struct list *list_new( void );
void list_start( struct list *list );
void list_next( struct list *list );
int list_get( struct list *list );
void list_push( struct list *list, int value );
void list_append( struct list *list, int value );
void list_pop( struct list *list );
void list_truncate( struct list *list );
void list_free( struct list *list );

#endif
