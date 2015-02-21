def tak (x, y, z):
  if x <= y:
    return y
  else:
    return tak(tak(x - 1, y, z), tak(y - 1, z, x), tak(z - 1, x, y))

n = tak(12,6,0)
print (n)