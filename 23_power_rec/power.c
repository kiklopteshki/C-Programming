unsigned power(unsigned x, unsigned y){
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
    return x*power(x,y-1);
  }
}
