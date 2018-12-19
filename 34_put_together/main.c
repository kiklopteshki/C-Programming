#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t *c=createCounts();
  FILE *f=fopen(filename,"r");
  if(f==NULL){
    fprintf(stderr,"Can not open file '%s'!\n",filename);
    return NULL;
  }
  char *key=NULL;
  size_t sz=0;
  while(getline(&key,&sz,f)>=0){
    char *p=strchr(key,'\n');
    *p='\0';
    addCount(c,lookupValue(kvPairs,key));
    free(key);
    sz=0;
  }
  free(key);
  fclose(f);
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  if(argc<3){
    fprintf(stderr,"%s : Invalid number of arguments!\n",argv[0]);
    return EXIT_FAILURE;
  }
  kvarray_t *kv=readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)
  for(int i=2;i<argc;i++){
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t *c=countFile(argv[i],kv);
    //compute the output file name from argv[i] (call this outName)
    char *outName=malloc(strlen(argv[i])+strlen(".counts")+1);
    if(outName==NULL){
      fprintf(stderr,"%s : Invalid memory allocation!\n",argv[0]);
      return EXIT_FAILURE;
    }
    outName[0]='\0';
    outName=strcat(outName,argv[i]);
    outName=strcat(outName,".counts");
    //open the file named by outName (call that f)
    FILE *f=fopen(outName,"w");
    if(f==NULL){
      fprintf(stderr,"%s : Can not open file '%s'!\n",argv[0],outName);
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    printCounts(c,f);
    //close f
    if(fclose(f)!=0){
      fprintf(stderr,"%s : Can not close file '%s'!\n",argv[0],outName);
      return EXIT_FAILURE;
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
