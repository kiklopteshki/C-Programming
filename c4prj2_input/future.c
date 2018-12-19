#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "future.h"

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr){
  if(fc==NULL){
    fc=realloc(fc,sizeof(*fc));
    assert(fc!=NULL);
    fc->decks=NULL;
    fc->n_decks=0;
  }
  
  if(fc->n_decks < index+1){
    fc->decks=realloc(fc->decks,(index+1)*sizeof(*fc->decks));
    assert(fc->decks!=NULL);
    for(size_t i=fc->n_decks;i<index+1;i++){
      fc->decks[i].cards=NULL;
      fc->decks[i].n_cards=0;
    }
    fc->n_decks=index+1;
  }
    
  fc->decks[index].cards=realloc(fc->decks[index].cards,((fc->decks[index].n_cards)+1)*sizeof(*fc->decks[index].cards));
  assert(fc->decks[index].cards!=NULL);
  fc->decks[index].n_cards++;
  fc->decks[index].cards[fc->decks[index].n_cards-1]=ptr;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
  if(deck==NULL){
    fprintf(stderr,"Error: Ivalid deck!\n");
    assert(deck!=NULL);
  }
  if(fc==NULL){
    fprintf(stderr,"Error: Ivalid future cards deck!\n");
    assert(fc!=NULL);
  }
  if(deck->n_cards<fc->n_decks){
    fprintf(stderr,"Error: Deck too small\n");
    assert(deck->n_cards>=fc->n_decks);
  }
  
  for(size_t i=0;i<fc->n_decks;i++){
    if(fc->decks[i].n_cards==0){
      fprintf(stderr,"Error: Invalid future card deck at index '%ld'\n",i);
      assert(fc->decks[i].n_cards!=0);
    }
    for(size_t j=0;j<fc->decks[i].n_cards;j++){
      /*size_t index=random()%deck->n_cards;*/
      fc->decks[i].cards[j]->value=deck->cards[i]->value;
      fc->decks[i].cards[j]->suit=deck->cards[i]->suit;
    }
  }
}
