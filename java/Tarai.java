class Tarai {
  public static int tarai(int x, int y, int z){
    return (x <= y)? y: tarai(tarai(x-1,y,z), tarai(y-1,z,x), tarai(z-1,x,y));
  }

  public static void main(String[] args) {
    int n = tarai(12,6,0);
    System.out.println(n);
  }
}