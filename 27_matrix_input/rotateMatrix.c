#include<stdio.h>
#include<stdlib.h>

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

int main(int argc, char **argv){
  if(argc!=2){
    fprintf(stderr,"Invalid number of arguments!\n");
    return EXIT_FAILURE;
  }
  
  FILE *f=fopen(argv[1],"r");
  if(f==NULL){
    fprintf(stderr,"Invalid input file '%s'\n",argv[1]);
    return EXIT_FAILURE;
  }

  char matrix[10][10]={0};
  for(int i=0;i<10;i++){
    char temp[12]={0};
    if(fgets(temp,12,f)==NULL){
      fprintf(stderr,"Error: reading input file '%s'\n",argv[1]);
      return EXIT_FAILURE;
    }
    if(temp[10]=='\n'){
      for(int j=0;j<10;j++){
	if(temp[j]!='\n'){
	  matrix[i][j]=temp[j];
	}
	else{
	  fprintf(stderr,"Invalid input file '%s' format\n",argv[1]);
	  return EXIT_FAILURE;
	}
      }
    }
    else{
      fprintf(stderr,"Invalid input file '%s' format\n",argv[1]);
      return EXIT_FAILURE;
    }
  }
  int c=fgetc(f);
  if(c!=EOF){
    fprintf(stderr,"Input file '%s' is too long\n",argv[1]);
    return EXIT_FAILURE;
  }

  rotate(matrix);

  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      fprintf(stdout,"%c",matrix[i][j]);
    }
    fprintf(stdout,"\n");
  }
  
  if(fclose(f)!=0){
    fprintf(stderr,"Unable to close file '%s'\n",argv[1]);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
