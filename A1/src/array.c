/*
Name: Sophie Zuccolo
Login: szuccolo
Student ID: 1293676
Date: 09/26/25
*/

//Including header files
#include "array.h"
#include "mem.h"

//array_new definition
struct array *array_new( int size ){

  //Allocating memory space for the array structure
  struct array * arrayPtr = malloc(sizeof(struct array));
  //Initializing contents of the struct
  arrayPtr->elements = 0;
  arrayPtr->addr = mem_alloc(size);
  return arrayPtr;

}

//array_get defintion
int array_get( struct array *ptr, int index ){

  //Returning the value at the requested index in the array
  return get_value((ptr->addr)+index);

}

//array_push definition
void array_push( struct array *ptr, int value ){

  int cur, i;

  //Loop to shift all elements forward by 1
  for (i = (ptr->elements)-1; i >= 0; i--){

    cur = get_value((ptr->addr)+i);
    set_value((ptr->addr)+i+1, cur);

  }

  //Adding the new value at the beginning and incrementing elements
  set_value(ptr->addr,value);
  (ptr->elements)++;

}

//array_append definition
void array_append( struct array *ptr, int value ){

  //Adding the new value to the end and incrementing elements
  set_value((ptr->addr)+(ptr->elements), value);
  (ptr->elements)++;

}

//array_pop definition
void array_pop( struct array *ptr ){

  int cur, i;

  //Returning if there are no elements to remove
  if ((ptr->elements) == 0){

    return;

  }

  //Shifting every element back by 1
  for (i = 1; i < (ptr->elements); i++){

    cur = get_value((ptr->addr)+i);
    set_value((ptr->addr)+i-1, cur);

  }

  //Decremeting elements
  (ptr->elements) = (ptr->elements) - 1;

}

//array_truncate definition
void array_truncate( struct array *ptr ){

  //Decrementing elements by 1 only if there are any currently in the array
  if ((ptr->elements) > 0){

    (ptr->elements) = (ptr->elements) - 1;

  }

}

//array_free definition
void array_free( struct array *ptr ){

  //Freeing the memory allocated for the array and for the struct array pointer
  mem_free(ptr->addr);
  free(ptr);

}

