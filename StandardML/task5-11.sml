fun y (_, _, 0) = 1.0         (* N=0 => y0 *)
|   y (x, _, 1) = x / 5.0     (* N=1 => y1 *)
|   y (x, e, N) =             (* otherwise - evaluate i-term *)
      let
        fun estimation a b = abs (a - b) < e
        (* yNext returns i-term *)
        (* yPrev and yPrevPrev are i-1 and i-2 terms respectively *)
        fun yNext yPrev yPrevPrev i =
          if estimation yPrev yPrevPrev then yPrev
          else
            let              
              val yCur = (x - 1.0) * (yPrev / N) + yPrevPrev
            in              
              if i >= N then yCur
              else yNext yCur yPrev (i + 1)
            end
      in        
        yNext (y (x, e, 1)) (y (x, e, 0)) 2
      end;