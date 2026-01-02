/*
Name: Sophie Zuccolo
Login: szuccolo
Student ID: 1293676
Date: 09/26/25
*/

//ifndef macro
#ifndef _ARRAY_H
#define _ARRAY_H

//Including preexisting libraries
#include <stdio.h>
#include <stdlib.h>

//Structure definition
struct array {
  int elements;
  int addr;
};

//Function prototypes
struct array *array_new( int size );
int array_get( struct array *ptr, int index );
void array_push( struct array *ptr, int value );
void array_append( struct array *ptr, int value );
void array_pop( struct array *ptr );
void array_truncate( struct array *ptr );
void array_free( struct array *ptr );

#endif
