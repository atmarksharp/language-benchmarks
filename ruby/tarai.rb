def tarai(x, y, z)
  if x <= y
    y
  else
    tarai(tarai(x-1,y,z), tarai(y-1,z,x), tarai(z-1,x,y))
  end
end

startTime = Time.now
tarai(12,6,0)
endTime = Time.now

timeElapsed = (endTime - startTime) * 1000.0

puts timeElapsed