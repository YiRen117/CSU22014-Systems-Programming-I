//   nybble_array.c
//   David Gregg
//   December 2021

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "nybble_array.h"


// create a new array of nybbles with space for "size"
// nybbles and initialize the values of the array to zero
struct nybble_array * nybble_array_new(int size) {
  // create a new array of nybbles
  struct nybble_array * result;
  result = malloc(sizeof(struct nybble_array*) * size);
  result -> size_in_nybbles = size;
  result -> size_in_bytes = (size % 2 == 0) ? (size/2) : (size/2 + 1);
  // create a new array of bytes
  unsigned char * bytes;
  bytes = malloc(sizeof(unsigned char) * result -> size_in_bytes);
  // set all elements in the byte array to 0
  for(int i=0; i < result -> size_in_bytes; i++){
    bytes[i] = 0;
  }
  result -> data_bytes = bytes;
  return result;
}

// return the nybble value at position index
unsigned get_nybble_value(struct nybble_array * this, int index) {
  int byte_index = index/2;      // calculate the index for the bytes
  // if the target nybble is the right one in a byte
  // create a mask "00001111" to get the right nybble value and convert it to unsigned int
  if(index % 2 == 0){
    unsigned char mask_right = 0x0F;
    return (unsigned)((this -> data_bytes[byte_index]) & mask_right);
  }
  // if the target nybble is the left one in a byte
  // create a mask "11110000" to get the left nybble value and convert it to unsigned int
  else{
    unsigned char mask_left = 0xF0;
    return (unsigned)(((this -> data_bytes[byte_index]) & mask_left) >> 4);
  }
}

// set the nybble at position index to value
void set_nybble_value(struct nybble_array * this, int index, unsigned value) {
  int byte_index = index/2;      // calculate the index for the bytes
  // if the nybble should be put at the right edge in a byte
  // convert the value to unsigned char and combine it with the current value stored in the byte array
  if(index % 2 == 0){
    this -> data_bytes[byte_index] = this -> data_bytes[byte_index] | (unsigned char)value;
  }
  // if the nybble should be put at the left edge in a byte
  // convert the value to unsigned char, shift it to the left edge of a byte
  // and combine it with the current value stored in the byte array
  else{
    this -> data_bytes[byte_index] = this -> data_bytes[byte_index] | (((unsigned char)value) << 4);
  }
}

// free the memory used by a nybble array
void nybble_array_free(struct nybble_array * this) {
  free(this -> data_bytes);  // free the memory used by the byte array
  free(this);  // free the memory used by the nybble array
}

// given an array of unsigned integers with values 0 to 15 create
// a new nybble_array with the same values
struct nybble_array * unsigned_to_nybble_array(unsigned * array, int size){
  // create a new nybble array
  struct nybble_array * result = nybble_array_new(size);
  unsigned char value;
  // set each element in the unsigned int array to the corresponding position in the new nybble array
  for(int i=0; i<size; i++){
    value = array[i];
    set_nybble_value(result, i, value);
  }
  return result;
}

// given an array of nybbles, create a new array of unsigned integers
// with the same values
unsigned * nybble_array_to_unsigned(struct nybble_array * this) {
  int size = this -> size_in_nybbles;
  // create a new unsigned int array
  unsigned * result = malloc(sizeof(unsigned) * size);
  // get all elements in the nybble array and put them into their corresponding positions
  // in the unsigned int array
  for(int i=0; i < size; i++){
    result[i] = get_nybble_value(this, i);
  }
  return result;
}

// print the raw byte content of the nybble array
void print_raw_bytes_nybble_array(struct nybble_array * this) {
  for ( int i = 0; i < this->size_in_bytes; i++ ) {
    printf("%x ", this->data_bytes[i]);
  }
  printf("\n");
}
