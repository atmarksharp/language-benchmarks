#include <iostream>
#include <ctime>

int tarai(int x, int y, int z){
  return (x <= y)? y: tarai(tarai(x-1,y,z), tarai(y-1,z,x), tarai(z-1,x,y));
}

int main(){
  float startTime = (float)clock()/CLOCKS_PER_SEC;
  tarai(15,10,0);
  float endTime = (float)clock()/CLOCKS_PER_SEC;

  float timeElapsed = endTime - startTime;
  std::cout << std::fixed << timeElapsed;
}