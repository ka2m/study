
(*****************************************************************************
                                Bus stop entity
 ****************************************************************************)

(* As stops for bus route are stored in a linked list, we can precisely
   determine, which stop comes first and which comes next. That's why I placed
   trael times between two stops inside this type *)
type stop = { name : string  (* stop name *)
            , fwTime : int   (* travel time between stops in one direction *)
            , bwTime : int   (* travel time in opposite diretion *)
            }

(*****************************************************************************
                                Bus route entity
 ****************************************************************************)

 type route = { number : int      (* route name *)
              , stops : stop list
              , startTime: int    (* opeartion start from midnight in mins *)
              , endTime: int      (* opeartion end from midnight in mins *)
              , interval: int     (* opeartion interval in mins: how often does
                                     new bus depart from the first bus stop *)
              }
