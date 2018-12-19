#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
#include "cards.h"
void print_hand(deck_t * hand){
  size_t i=0;
  print_card(*hand->cards[i++]);
  while(i<hand->n_cards){
    printf(" ");
    print_card(*hand->cards[i++]);
  }
  /*printf(" ");*/
}

int deck_contains(deck_t * d, card_t c) {
  for(int i=0;i<d->n_cards;i++){
    if(c.value==d->cards[i]->value && c.suit==d->cards[i]->suit){
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  size_t m=random()%6;
  for(size_t i=0;i<m;i++){
    size_t low=i*(d->n_cards / m);
    size_t high=(i+1)*(d->n_cards / m);
    for(size_t j=low;j<high;j++){
      card_t *temp=d->cards[j];
      size_t n=(random()*random()) % d->n_cards;
      d->cards[j]=d->cards[n];
      d->cards[n]=temp;
    }
  }
  /*Another Shuffle*/
  for(size_t j=0; j<d->n_cards; j++){
    card_t *temp=d->cards[j];
    size_t n=(random()*random()) % d->n_cards;
    d->cards[j]=d->cards[n];
    d->cards[n]=temp;
  }
}
  
void assert_full_deck(deck_t * d) {
  unsigned rep[52]={0};
  for(unsigned i=0;i<52;i++){
    if(deck_contains(d,card_from_num(i))){
      rep[i]++;
    }
  }
  for(unsigned i=0;i<52;i++){
    if(rep[i]>1){
      assert(rep[i]>1);
    }
  }
}

void add_card_to(deck_t * deck, card_t c){
  deck->cards=realloc(deck->cards,(deck->n_cards+1)*sizeof(*deck->cards));
  assert(deck->cards!=NULL);
  deck->n_cards++;
  deck->cards[deck->n_cards-1]=malloc(sizeof(**deck->cards));
  assert(deck->cards[deck->n_cards-1]!=NULL);
  deck->cards[deck->n_cards-1]->value=c.value;
  deck->cards[deck->n_cards-1]->suit=c.suit;
}

card_t * add_empty_card(deck_t * deck){
  card_t c={0,NUM_SUITS};
  add_card_to(deck,c);
  return deck->cards[deck->n_cards-1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards){
  deck_t *ans=malloc(sizeof(*ans));
  assert(ans!=NULL);
  ans->cards=NULL;
  ans->n_cards=0;
  for(unsigned i=0;i<52;i++){
    card_t c=card_from_num(i);
    if(!deck_contains(excluded_cards,c)){
      add_card_to(ans,c);
    }
  }
  return ans;
}

void free_deck(deck_t * deck);

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands){
  deck_t *excluded=malloc(sizeof(*excluded));
  assert(excluded!=NULL);
  excluded->cards=NULL;
  excluded->n_cards=0;
  for(size_t i=0;i<n_hands;i++){
    for(size_t j=0;j<hands[i]->n_cards;j++){
      add_card_to(excluded,*hands[i]->cards[j]);
    }
  }
  deck_t *ans=make_deck_exclude(excluded);
  free_deck(excluded);
  return ans;
}

void free_deck(deck_t * deck){
  if(deck!=NULL){
    for(size_t i=0;i<deck->n_cards;i++){
      free(deck->cards[i]);
    }
    free(deck->cards);
    free(deck);
  }
}
