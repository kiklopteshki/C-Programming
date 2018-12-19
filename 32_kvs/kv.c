#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "kv.h"

void strip_line(char *line){
  char *p=strchr(line,'\n');
  assert(p!=NULL);
  if(p!=NULL){
    *p='\0';
  }
}

kvpair_t * pair_form_line(char *line){
  kvpair_t *ans=malloc(sizeof(*ans));
  if(ans!=NULL){
    strip_line(line);
    char *find_equals=strchr(line,'=');
    assert(find_equals!=NULL);
    ans->key=strndup(line,strlen(line)-strlen(find_equals));
    ans->value=strdup(find_equals+1);
  }
  return ans;
}

void kv_arr_free(kvarray_t *ans){
  for(size_t i=0;i<ans->array_lenght;i++){
    free(ans->array[i]->key);
    free(ans->array[i]->value);
    free(ans->array[i]);
  }
  free(ans->array);
  free(ans);
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE *f=fopen(fname,"r");
  if(f==NULL){
    return NULL;
  }
  
  kvarray_t *ans=malloc(sizeof(*ans));
  if(ans==NULL){
    return NULL;
  }
  ans->array_lenght=0;
  ans->array=NULL;
  
  char *line=NULL; /*start reading*/
  size_t sz=0;
  while(getline(&line,&sz,f)>=0){
    kvpair_t *pair=pair_form_line(line);
    if(pair==NULL){  
      kv_arr_free(ans);
      return NULL;
    }
    ans->array=realloc(ans->array,(ans->array_lenght+1)*sizeof(*ans->array));
    if(ans->array!=NULL){
      ans->array_lenght++;
      ans->array[ans->array_lenght-1]=pair;
      }
    else{
      kv_arr_free(ans);
      return NULL;
      }
    free(line);
    line=NULL;
    sz=0;
  }
  free(line);/*end reading*/
  
  int f_closed=fclose(f);
  assert(f_closed==0);
  return ans;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  kv_arr_free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  assert(pairs!=NULL);
  for(size_t i=0;i<pairs->array_lenght;i++){
    printf("key = '%s' value = '%s'\n",pairs->array[i]->key,pairs->array[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  assert(pairs!=NULL);
  for(size_t i=0;i<pairs->array_lenght;i++){
    if(strcmp(pairs->array[i]->key,key)==0){
      return pairs->array[i]->value;
    }
  }
  return NULL;
}
