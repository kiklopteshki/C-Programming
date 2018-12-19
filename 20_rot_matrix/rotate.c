#include<stdio.h>
void rotate(char matrix[10][10]){
  if(matrix!=NULL){
    char rotMatrix[10][10];
    for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
	rotMatrix[j][10-1-i]=matrix[i][j];
      }
    }
    for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
	matrix[i][j]=rotMatrix[i][j];
      }
    }
  }
}
