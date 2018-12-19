#include<stdio.h>
#include<stdlib.h>

unsigned power (unsigned x, unsigned y);
/*{
  if(x==0 && y==0){
  return 1;
  }
  else if(x==0){
  return 0;
  }
  else if(x==1 || y==0){
  return 1;
  }
  else{
  return n*power(x,y-1);
  }
} */

void run_check(unsigned x, unsigned y, unsigned expected_ans){
  if(power(x,y)!=expected_ans){
    exit(EXIT_FAILURE);
  }
}

int main(void){
  run_check(0,0,1);
  run_check(0,1,0);
  run_check(0,31,0);
  run_check(1,0,1);
  run_check(31,0,1);
  run_check(1,31,1);
  run_check(2,3,8);
  run_check(5,4,625);
  run_check(77,1,77);
  run_check(4,4,256);
  run_check(1,1,1);
  run_check(-1,0,1);
  run_check(0,-1,0);
  run_check(2,31,2147483648);
  for(int i=0;i<16;i++){
    for(int j=0; j<10; j++){
      if(power(i,j)<0 || power(-i,j)<0 || power(i,-j)<0 || power(-i,-j)<0){
	return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
