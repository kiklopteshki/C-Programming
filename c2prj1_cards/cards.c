#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"

void assert_card_valid(card_t c) {
  assert((c.value>=2 && c.value<=VALUE_ACE) && (c.suit>=SPADES && c.suit<=CLUBS));
}

const char * ranking_to_string(hand_ranking_t r) {
  switch(r){
  case STRAIGHT_FLUSH: return "STRAIGHT_FLUSH";
  case FOUR_OF_A_KIND: return "FOUR_OF_A_KIND";
  case FULL_HOUSE: return "FULL_HOUSE";
  case FLUSH: return "FLUSH";
  case STRAIGHT: return "STRAIGHT";
  case THREE_OF_A_KIND: return "THREE_OF_A_KIND";
  case TWO_PAIR: return "TWO_PAIR";
  case PAIR: return "PAIR";
  case NOTHING: return "NOTHING";
  default: return "";
  }
  /*return "";*/
}

char value_letter(card_t c) {
  char x='\0';
  if(c.value>=2 && c.value<=9) { x='0'+c.value; }
  else if(c.value==10) { x='0'; }
  else if(c.value==VALUE_JACK) { x='J'; }
  else if(c.value==VALUE_QUEEN) { x='Q'; }
  else if(c.value==VALUE_KING) { x='K'; }
  else if(c.value==VALUE_ACE) { x='A'; }
  return x;
}


char suit_letter(card_t c) {
  switch(c.suit){
  case SPADES: return 's';
  case HEARTS: return 'h';
  case DIAMONDS: return 'd';
  case CLUBS: return 'c';
  default: return 'x';
  }
  /*return 'x';*/
  
}

void print_card(card_t c) {
  printf("%c%c",value_letter(c),suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  
  if(value_let>='2' && value_let<='9') { temp.value=value_let-'0'; }
  else if(value_let=='0') { temp.value=10; }
  else if(value_let=='J') { temp.value=VALUE_JACK; }
  else if(value_let=='Q') { temp.value=VALUE_QUEEN; }
  else if(value_let=='K') { temp.value=VALUE_KING; }
  else if(value_let=='A') { temp.value=VALUE_ACE; }
  else { assert((value_let>='2' && value_let<='9') && value_let=='0' && value_let=='J' && value_let=='Q' && value_let=='K' && value_let=='A'); }
  
  switch(suit_let){
  case 's': temp.suit=SPADES; break;
  case 'h': temp.suit=HEARTS; break;
  case 'd': temp.suit=DIAMONDS; break;
  case 'c': temp.suit=CLUBS; break;
  default: assert(suit_let=='s' && suit_let=='h' && suit_let=='d' && suit_let=='c');
  }
  return temp;
}

card_t card_from_num(unsigned c) {
  /*card_t temp;
  assert(c>=0 && c<52);
  temp.value=2+c%13;
  temp.suit=c%NUM_SUITS;
  return temp;*/
  assert(c>=0 && c<52);
  card_t ans={0,0};
  ans.suit=c%4;
  if(c>7){
    ans.value=c/4;
  }
  else{
    ans.value=(52+c)/4;
  }
  return ans;
}
