#include "bitset.h"
#include <stdlib.h>

// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size) {
    struct bitset *result;
    result = malloc(sizeof(struct bitset));
    int bits_per_word = sizeof(uint64_t)*8;
    result -> size_in_words = (size / bits_per_word) + (((size % bits_per_word) == 0) ? 0 : 1);
    result -> universe_size = size;
    result -> bits = malloc(sizeof(uint64_t) * result -> size_in_words);
	  for (int i = 0; i < result -> size_in_words; i++){
		  result -> bits[i] = 0;
	  }
    return result;
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset * this) {
    return this -> universe_size;
}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset * this){
    int count = 0;
    for(int i=0; i < this -> universe_size; i++){
      count += bitset_lookup(this, i);
    }
    return count;
}

// check to see if an item is in the set
int bitset_lookup(struct bitset * this, int item){
    int bits_per_word = sizeof(uint64_t)*8;
    int array_index = item / bits_per_word;
    int word_index = item % bits_per_word;
    uint64_t mask = 1ULL << word_index;
    uint64_t result = this -> bits[array_index] & mask;
    return result >> word_index;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset * this, int item) {
    int bits_per_word = sizeof(uint64_t)*8;
    int array_index = item / bits_per_word;
    int word_index = item % bits_per_word;
    uint64_t mask = 1ULL << word_index;
    this -> bits[array_index] = this -> bits[array_index] | mask;
}

// remove an item with number 'item' from the set
void bitset_remove(struct bitset * this, int item) {
    int bits_per_word = sizeof(uint64_t)*8;
    int array_index = item / bits_per_word;
    int word_index = item % bits_per_word;
    uint64_t mask = 1ULL << word_index;
    this -> bits[array_index] = this -> bits[array_index] ^ mask;
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset * dest, struct bitset * src1, struct bitset * src2) {
    if((dest -> universe_size == src1 -> universe_size) && (src2 -> universe_size == src1 -> universe_size)){
      for(int i=0; i < dest -> size_in_words; i++){
          dest -> bits[i] = dest -> bits[i] | (src1 -> bits[i] | src2 -> bits[i]);
      }
    }
}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset * dest, struct bitset * src1, struct bitset * src2) {
    if((dest -> universe_size == src1 -> universe_size) && (src2 -> universe_size == src1 -> universe_size)){
      for(int i=0; i < dest -> size_in_words; i++){
          dest -> bits[i] = dest -> bits[i] | (src1 -> bits[i] & src2 -> bits[i]);
      }
    }
}
