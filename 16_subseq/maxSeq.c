#include<stdio.h>
#include<stdlib.h>

size_t maxSeq(int * array, size_t n){
  if(array==NULL || n==0){
    return 0;
  }
  
  if(n==1){
    return 1;
  }
  
  size_t size_seq=1, max_seq=1;
  for(size_t i=0;i<n-1;i++){
    if(array[i]>=array[i+1]){
      size_seq=1;
    }
    else{
      size_seq++;
    }
    if(size_seq>max_seq){
      max_seq=size_seq;
    }
  }
  return max_seq;
}
