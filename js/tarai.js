function tarai(x, y, z){
  return (x <= y)? y: tarai(tarai(x-1,y,z), tarai(y-1,z,x), tarai(z-1,x,y));
}

var n = tarai(12,6,0);
console.log(n)