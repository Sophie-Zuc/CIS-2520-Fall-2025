/*
Name: Sophie Zuccolo
Login: szuccolo
Student ID: 1293676
Date: 09/26/25
*/

//Including header files
#include "list.h"
#include "mem.h"

//list_new definition
struct list *list_new( void ){

  //Creating pointer to a struct list and dynamically allocating memory
  struct list * listPtr;
  listPtr = malloc(sizeof(struct list));
  //Initializing struct contents to 0
  listPtr->head = 0;
  listPtr->current = 0;
  return listPtr;

}

//list_start definition
void list_start( struct list *list ){

  //Setting current to head of list
  list->current = list->head;

}

//list_next definition
void list_next( struct list *list ){

  //Incrementing current to the following address in the list
  int nextAddr = get_next(list->current);
  list->current = nextAddr;

}

//list_get definition
int list_get( struct list *list ){

  //Returning the value at the current address
  return get_value(list->current);

}

//list_push definition
void list_push( struct list *list, int value ){

  //Allocating memory for a new node and giving it the value
  int newNode = mem_alloc(1);
  set_value(newNode, value);
  //Setting the new node to point to the head and making the new node the new head of the list
  set_next(newNode, list->head);
  list->head = newNode;

}

//list_append definition
void list_append( struct list *list, int value ){

  int curAddr = list->head;

  //Allocating memory for a new node and giving it the value
  int newNode = mem_alloc(1);
  set_value(newNode, value);
  //Setting the new node to point to null, keeping the list null terminated
  set_next(newNode, 0);

  //If the list is empty, the new node becomes the head
  if (list->head == 0){

    list->head = newNode;

  }
  else{

    int nextAddr;

    //Navigating through the list until the last node that points to null
    while ((nextAddr = get_next(curAddr)) != 0){

      curAddr = nextAddr;

    }

    //Changing the last node in the list to point to the new node
    set_next(curAddr, newNode);

  }

}

//list_pop definition
void list_pop( struct list *list ){

  //The list is not popped if it is empty, there's no nodes to remove
  if (list->head != 0){

    int toFree = list->head;
    int newHead = get_next(list->head);

    //If there's only one node in the list, the node is freed and the head is set to null
    if (newHead == 0){

      mem_free(toFree);
      list->head = 0;

    }
    else{

      //The second node in the list becomes the new head and the first node is freed
      list->head = newHead;
      mem_free(toFree);

    }

  }

}

//list_truncate definition
void list_truncate( struct list *list ){

  int curAddr = list->head;
  int nextAddr;

  //The list is not truncated if there's no nodes in the list
  if (list->head == 0){

    return;

  }
  else if ((nextAddr = get_next(curAddr)) == 0){

    //If there's one node in the list, it is freed and the head is set to null
    mem_free(curAddr);
    list->head = 0;

  }
  else{

    //Navigating through the list until the second to last node is reached
    while (get_next(nextAddr) != 0){

      curAddr = nextAddr;
      nextAddr = get_next(nextAddr);

    }

    //Freeing the last node and setting the second to last node to point to null, making the list null terminated
    mem_free(nextAddr);
    set_next(curAddr, 0);

  }

}

//list_free definition
void list_free( struct list *list ){

  //Base case, if the list is empty the struct list pointer is freed and recursion stops
  if (list->head == 0){

    free(list);
    return;

  }

  //Removing a node from the list
  list_pop(list);
  //Recursive call
  list_free(list);

}

