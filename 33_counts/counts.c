#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t *ans=malloc(sizeof(*ans));
  if(ans!=NULL){
    ans->array=NULL;
    ans->array_lenght=0;
  }
  return ans;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  char *str=NULL;
  if(name==NULL){
    str=strdup("unknown");
  }
  else{
    str=strdup(name);
  }

  int str_is_found=0;
  if(c->array_lenght>0){
    for(size_t i=0;i<c->array_lenght;i++){
      if(!strcmp(c->array[i]->string,str)){
	c->array[i]->count++;
	str_is_found=1;
      }
    }
  }
  
  if(!str_is_found){
    one_count_t *cnt=malloc(sizeof(*cnt));
    assert(cnt!=NULL);
    cnt->string=str;
    cnt->count=1;
    c->array=realloc(c->array,(c->array_lenght+1)*sizeof(*c->array));
    c->array_lenght++;
    c->array[c->array_lenght-1]=cnt;
  }
  else{
    free(str);
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  size_t unknown_index=c->array_lenght;
  for(size_t i=0;i<c->array_lenght;i++){
    if(!strcmp(c->array[i]->string,"unknown")){
      unknown_index=i;
      continue;
    }
    fprintf(outFile,"%s: %ld\n",c->array[i]->string,c->array[i]->count);
  }
  if(unknown_index<c->array_lenght && c->array[unknown_index]->count>0){
    fprintf(outFile,"<%s> : %ld\n",c->array[unknown_index]->string,c->array[unknown_index]->count);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for(size_t i=0;i<c->array_lenght;i++){
    free(c->array[i]->string);
    free(c->array[i]);
  }
  free(c->array);
  free(c);
}
