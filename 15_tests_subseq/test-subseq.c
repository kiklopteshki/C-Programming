#include<stdio.h>
#include<stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void){
  if(maxSeq(NULL,0)){
    return EXIT_FAILURE;
  }
  int arr_0[]={};
  if(maxSeq(arr_0,0)!=0){
    return EXIT_FAILURE;
  }
  int arr_1[]={5};
  if(maxSeq(arr_1,1)!=1){
    return EXIT_FAILURE;
  }
  int arr_3[]={5,5,5,5,5};
  if(maxSeq(arr_3,5)!=1){
    return EXIT_FAILURE;
  }
  int arr_4[]={ 1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  if(maxSeq(arr_4,10)!=4){
    return EXIT_FAILURE;
  }
  int arr_5[]={-1024,1,1,1,1,1,1,1,1,1024};
  if(maxSeq(arr_5,10)!=2){
    return EXIT_FAILURE;
    }
  int arr_6[]={-5,-4,-3,-2,-1,0};
  if(maxSeq(arr_6,6)!=6){
      return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
