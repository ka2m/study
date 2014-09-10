fun reverseBack ([], l) = l
|   reverseBack (x :: xs, l) = reverseBack (xs, x :: l)


fun removeFromList (SL, removeCriteria) =
  let
    fun remove ([], SL') = reverseBack (SL', [])
    |   remove (S' :: SL'', SL') =
          if removeCriteria S' 
          then reverseBack (SL', SL'')
          else remove (SL'', S' :: SL')
  in
    remove (SL, [])
  end

(*****************************************************************************
                                Bus stop entity
 ****************************************************************************)

(* As stops for bus route are stored in a linked list, we can precisely
   determine, which stop comes first and which comes next. That's why I placed
   trael times between two stops inside this type *)
type stop = { name : string  (* stop name *)
            , nextTime: int   (* travel time between stops *)            
            }

(* constructor *)
fun makeStop (aName, aNextTime) : stop =
  { name = aName
  , nextTime = aNextTime
  }

(* selectors *)
fun stopName ({name = N, ...} : stop) = N 
fun stopNextTime ({nextTime = nt, ...} : stop) = nt

(* setters *)
fun changeStopName newName S =             
  makeStop ( newName, stopNextTime S ) 
fun changeStopNextTime newNextTime S =
  makeStop ( stopName S, newNextTime ) 

(* identifying predicate *)
fun isStopName stopN S = stopName S = stopN

fun removeStopByName (SL, stopN) =
  removeFromList (SL, isStopName stopN)

(*****************************************************************************
                                Bus route entity
 ****************************************************************************)

type route = {  number : int      (* route name *)
              , fwStopList: stop list
              , bwStopList: stop list  
              , beginTime: int    (* opeartion start from midnight in mins *)
              , endTime: int      (* opeartion end from midnight in mins *)
              , interval: int     (* opeartion interval in mins: how often does
                                     new bus depart from the first bus stop *)
              }

(* constructor *)
fun makeRoute ( routeNumber, routeFWSList, routeBWSList, routeBeginTime,
                routeEndTime, routeInterval ) =
  { number = routeNumber
  , fwStopList = routeFWSList
  , bwStopList = routeBWSList
  , beginTime = routeBeginTime
  , endTime = routeEndTime
  , interval = routeInterval
  }

(* selectors *)
fun routeNumber ({number = N, ...} : route) = N
fun routeFWSList ({fwStopList = fws, ...} : route)  = fws
fun routeBWSList ({bwStopList = bws, ...} : route)  = bws
fun routeBeginTime ({beginTime = bt, ...} : route)  = bt
fun routeEndTime ({endTime = et, ...} : route)  = et
fun routeInterval ({interval = i, ...} : route)  = i

(* setters *)
fun changeRouteNumber newRouteNumber R =
  makeRoute ( newRouteNumber
            , routeFWSList R
            , routeBWSList R
            , routeBeginTime R
            , routeEndTime R
            , routeInterval R
            )

(* identifying predicate *)
fun isRouteNum routeN R = routeNumber R = routeN

(*****************************************************************************
                                Example
 ****************************************************************************)
val fStopList = []
val fStopList = makeStop("Staduium", 2) :: fStopList
val fStopList = makeStop("Church", 4) :: fStopList
val fStopList = makeStop("Train College", 1) :: fStopList
val fStopList = makeStop("Park", 5) :: fStopList 
val fStopList = makeStop("Duke St.", 7) :: fStopList
val fStopList = makeStop("Flower St.", 3) :: fStopList
val fStopList = makeStop("Johnson Ave.", 4) :: fStopList
val fStopList = makeStop("Railway", 12) :: fStopList
val fStopList = reverseBack(fStopList, [])

val bStopList = []
val bStopList = makeStop("Staduium", 4) :: bStopList
val bStopList = makeStop("Port", 8) :: bStopList
val bStopList = makeStop("John St.", 4) :: bStopList
val bStopList = makeStop("Apple Ave.", 8) :: bStopList
val bStopList = makeStop("Lordy Ave.", 3) :: bStopList
val bStopList = makeStop("Pond", 5) :: bStopList
val bStopList = makeStop("Pilot School", 2) :: bStopList
val bStopList = makeStop("Mosque", 3) :: bStopList
val bStopList = reverseBack(bStopList, [])
val R10 = makeRoute (10, fStopList, bStopList, 180, 1410, 10)
