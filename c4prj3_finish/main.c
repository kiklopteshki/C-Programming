#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

void free_hands(deck_t **hands, size_t n_hands){
  if(hands!=NULL){
    for(size_t i=0;i<n_hands;i++){
      free_deck(hands[i]);
    }
  }
  free(hands);
}

void free_future_cards(future_cards_t *fc){
  for(size_t i=0;i<fc->n_decks;i++){
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  /*free(fc)*/;
}

size_t *create_wins_or_ties(size_t n){
  size_t *ans=malloc((n+1)*sizeof(*ans));
  if(ans!=NULL){
    for(size_t i=0;i<n+1;i++){
      ans[i]=0;
    }
  }
  return ans;
}

void Monte_Carlo_trials(size_t n_trials, deck_t **hands, size_t n_hands, future_cards_t *fc, deck_t *r_deck, size_t *wins_or_ties){
  for(size_t i=0;i<n_trials;i++){
    shuffle(r_deck);
    future_cards_from_deck(r_deck,fc);
    size_t *wt=create_wins_or_ties(n_hands);
    for(size_t j=0;j<n_hands-1;j++){
      for(size_t k=j+1;k<n_hands;k++){
	int compare=compare_hands(hands[j],hands[k]);
	if(compare>0){
	  wt[j]++;
	}
	else if(compare<0){
	  wt[k]++;
	}
	else{
	  wt[n_hands]++;
	}
      }
    }
    size_t index=0;
    for(size_t l=0; l<n_hands+1; l++){
      if(wt[index]<wt[l]){
	index=l;
      }
    }
    wins_or_ties[index]++;
    free(wt);
  }
}

void print_trials(size_t *w_or_t, size_t n_hands, size_t n_trials){
  for(size_t i=0;i<n_hands;i++){
    unsigned int wins=w_or_t[i];
    unsigned int trials=n_trials;
    double per=(w_or_t[i]/(double)trials)*100;
    printf("Hand %zu won %u / %u times (%.2f%%)\n", i, wins, trials, per);
  }
  unsigned int ties=w_or_t[n_hands];
  printf("And there were %u ties\n", ties);
}

int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE
  if(argc>3 || argc<2){
    fprintf(stderr,"%s : Invalid number of arguments!\n",argv[0]);
    return EXIT_FAILURE;
  }
  FILE *f=fopen(argv[1],"r");
  if(f==NULL){
    fprintf(stderr,"%s : Invalid input file %s!\n",argv[0],argv[1]);
    return EXIT_FAILURE;
  }
  size_t n_trials=10000;
  if(argc==3){
    if(atol(argv[2])>0){
      n_trials=atol(argv[2]);
    }
    else{
      fprintf(stderr,"%s : Invalid number of Monte Carlo trials %s!\n",argv[0],argv[2]);
      return EXIT_FAILURE;
    }
  }
  size_t n_hands=0;
  future_cards_t fc={NULL,0};
  deck_t **hands=read_input(f,&n_hands,&fc);
  deck_t *rem_deck=build_remaining_deck(hands,n_hands);
  size_t *wins_or_ties=create_wins_or_ties(n_hands);
  if(wins_or_ties==NULL){
    fprintf(stderr,"%s : Invalid memory allocation @create_wins_or_ties!\n",argv[0]);
    return EXIT_FAILURE;
  }
  
  Monte_Carlo_trials(n_trials,hands,n_hands,&fc,rem_deck,wins_or_ties);
  
  print_trials(wins_or_ties,n_hands,n_trials);
  
  free_hands(hands,n_hands);
  free_future_cards(&fc);
  free_deck(rem_deck);
  free(wins_or_ties);

  if(fclose(f)!=0){
    fprintf(stderr,"%s : Can not close %s!\n",argv[0],argv[1]);
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
