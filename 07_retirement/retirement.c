#include<stdio.h>
#include<stdlib.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double compute_balance(double balance, double rate, double contribution){
  return balance*(1+rate/12)+contribution;
}

void retirement (int startAge,   //in months
                       double initial, //initial savings in dollars
                       retire_info working, //info about working
		 retire_info retired){ //info about being retired
  for(int i=0;i<working.months;i++){
    printf("Age %3d month %2d you have $%.2lf\n",(startAge/12),(startAge%12),initial);
    startAge++;
    initial=compute_balance(initial,working.rate_of_return,working.contribution);
  }
  for(int i=0;i<retired.months;i++){
    printf("Age %3d month %2d you have $%.2lf\n",(startAge/12),(startAge%12),initial);
    startAge++;
    initial=compute_balance(initial,retired.rate_of_return,retired.contribution);
  }
}

int main(void){
  retire_info Working={489,1000,0.045};
  retire_info Retired={384,-4000,0.01};
  retirement(327,21345,Working,Retired);
  return EXIT_SUCCESS;
}
