//   playing_cards.c
//   David Gregg
//   December 2020

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "playing_cards.h"



// pack the playing card structures into bytes of memory
unsigned char * pack_playing_cards(struct playing_card * cards,
				   int number_of_cards) {
  unsigned char * result;
  result = malloc(sizeof(unsigned char));
  int char_index = 0;
  int suit_index, val_index;
  unsigned char suit, val;
  for(int i = 0; i < number_of_cards; i++){
    int mod_of_card = i % 4;
    switch(mod_of_card){
      case 0:
        suit_index = 6;
        val_index = 2;
        suit = ((unsigned char)(cards[i].suit)) << suit_index;
        val = ((unsigned char)(cards[i].value)) << val_index;
        result[char_index] = suit | val;
        break;
      case 1:
        suit = (unsigned char)cards[i].suit;
        result[char_index] = result[char_index] | suit;
        char_index++;
        val_index = 4;
        val = ((unsigned char)cards[i].value) << val_index;
        result[char_index] = val;
        break;
      case 2:
        suit_index = 2;
        val_index = 2;
        suit = ((unsigned char)cards[i].suit) << suit_index;
        val = ((unsigned char)cards[i].value) >> val_index;
        result[char_index] = (result[char_index] | suit) | val;
        char_index++;
        val_index = 6;
        val = ((unsigned char)cards[i].value) << val_index;
        result[char_index] = val;
        break;
      case 3:
        suit_index = 4;
        suit = ((unsigned char)cards[i].suit) << suit_index;
        val = (unsigned char)cards[i].value;
        result[char_index] = (result[char_index] | suit) | val;
        break;
    }
  }
  return result;
}




// unpack bytes of memory containing card data into playing card structures
struct playing_card * unpack_playing_cards(unsigned char * packed_cards,
					   int number_of_cards) {
    
}


