#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// include the header files with the declarations of listset
#include "listset.h"

// create a new, empty linked list set
struct listset * listset_new() {
  struct listset * list;
  list = malloc(sizeof(struct listset));
  list -> head = NULL;
  return list;
}

/* check to see if an item is in the set
   returns 1 if in the set, 0 if not */
int listset_lookup(struct listset * this, char * item) {
  struct listnode * p;
  p = this -> head;
  for(p = this -> head; p != NULL; p = p -> next){
    if(strcmp(item, p -> str) == 0){
      return 1;
    }
  }
  return 0;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set.
// New items that are not already in the set should
// be added to the start of the list
void listset_add(struct listset * this, char * item) {
  if(!listset_lookup(this, item)){
    struct listnode * newnode = malloc(sizeof(struct listnode));
    newnode -> next = this -> head;
    this -> head = newnode;
    newnode -> str = item;
  }
  return;
}

// remove an item with number 'item' from the set
void listset_remove(struct listset * this, char * item) {
  if(this -> head == NULL){
    return;
  }
  if(strcmp(this -> head -> str, item) == 0){
    struct listnode * tmp = this -> head;
    this -> head = tmp -> next;
    free(tmp);
    return;
  }
  struct listnode * p;
  for(p = this -> head; p -> next != NULL; p = p -> next){
    if(strcmp(p -> next -> str, item) == 0){
      struct listnode * tmp = p -> next;
      p -> next = tmp -> next;
      free(tmp);
      return;
    }
  }
  return;
}
  
// place the union of src1 and src2 into dest
void listset_union(struct listset * dest, struct listset * src1,
		   struct listset * src2) {
  struct listnode * p1;
  struct listnode * p2;
  for(p1 = src1 -> head; p1 -> next != NULL; p1 = p1 -> next){
    listset_add(dest, p1 -> str);
  }
  for(p2 = src2 -> head; p2 -> next != NULL; p2 = p2 -> next){
    listset_add(dest, p2 -> str);
  }
  return;
}

// place the intersection of src1 and src2 into dest
void listset_intersect(struct listset * dest, struct listset * src1,
		       struct listset * src2) {
  struct listnode * p1;
  for(p1 = src1 -> head; p1 -> next != NULL; p1 = p1 -> next){
    if(listset_lookup(src2, p1 -> str)){
      listset_add(dest, p1 -> str);
    }
  }
  return;
}

// return the number of items in the listset
int listset_cardinality(struct listset * this) {
  int count = 0;
  struct listnode * p;
  for(p = this -> head; p != NULL; p = p -> next){
    count++;
  }
  return count;
}

// print the elements of the list set
void listset_print(struct listset * this) {
  struct listnode * p;

  for ( p = this->head; p != NULL; p = p->next ) {
    printf("%s, ", p->str);
  }
  printf("\n");
}
