fun quicksort lt lst =
  let val rec sort =
    fn [] => []
     | (x::xs) =>
        let
          val (left,right) = List.partition (fn y => lt (y, x)) xs
        in sort left @ x :: sort right
        end
  in sort lst
end