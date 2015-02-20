#include <stdio.h>

int tarai(int x, int y, int z){
  return (x <= y)? y: tarai(tarai(x-1,y,z), tarai(y-1,z,x), tarai(z-1,x,y));
}

int main(){
  int n = tarai(12,6,0);
  printf("%d", n);
}