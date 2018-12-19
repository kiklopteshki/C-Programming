#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

char letter_most_freq(size_t *letter_freq, int n){
  char most_freq=0;
  for(char i=1;i<n;i++){
    if(letter_freq[most_freq]<letter_freq[i]){
      most_freq=i;
    }
  }
  return most_freq+'a';
}

int main(int argc, char **argv){
  if(argc!=2){
    fprintf(stderr,"Usage: Invalid arguments!\n");
    return EXIT_FAILURE;
  }
  FILE *f=fopen(argv[1],"r");
  if(f==NULL){
    fprintf(stderr,"Could not open file '%s'\n",argv[1]);
    return EXIT_FAILURE;
  }
  size_t letter_freq[26]={0};
  int c=0;
  while((c=fgetc(f))!=EOF){
    if(isalpha(c)){
      letter_freq[c-'a']++;
    }
  }
  c=letter_most_freq(letter_freq,26);
  int key=c-'e';
  if(key>=0){
    fprintf(stdout,"%d\n",key);
  }
  else{
    fprintf(stdout,"%d\n",26+key);
  }
  if(fclose(f)!=0){
    perror("Failed to close the input file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
