let rec tarai x y z =
  if x <= y then
    y
  else
    tarai (tarai (x-1) y z) (tarai (y-1) z x) (tarai (z-1) x y)
;;


let _ =
  let n = tarai 12 6 0 in
  print_int n
;;