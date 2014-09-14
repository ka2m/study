load "Int";
load "ListPair";
load "List";

datatype 'a ternarylikeop = TrueExpression of 'a | FalseExpression
 
fun op ? (true, y)  = TrueExpression y
  | op ? (_, y)     = FalseExpression
infix 6 ?;
 
fun op :- (TrueExpression x, _) = x
  | op :- (FalseExpression, y)  = y
infix 6 :-;

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

(* function to strip list from elements,
 * which don't match searchCriteria *)
fun clipList (SL, searchCriteria) =
  let
    fun search [] = []
    |   search (S' :: SL') =
          if searchCriteria S'
          then S' :: SL'
          else search SL'
  in
    search SL
  end

fun foundInList (SL, searchCriteria) =
  not (null (clipList (SL, searchCriteria)))

fun member ( x, [] )        = false
|   member ( x, (y :: ys) ) = (x = y) ? true :- member ( x, ys )

fun first []     = raise Match
|   first (x::_) = x

(* get first element, which matches searchCriteria *)
fun getFromList (SL, searchCriteria) =
  first (clipList (SL, searchCriteria))

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

(* function that gets only the names from the stops list *)
fun getStopNames SL =
  let
    fun getStopNames' ([], res)        = reverseBack (res, [])
    |   getStopNames' (S' :: SL', res) =
          getStopNames' (SL', stopName S' :: res)  
  in 
    getStopNames' (SL, [])
  end

(* function to count travel time (used in sorting) *)
fun getTravelTime SL =
  let 
    fun getTravelTime' ([], res) = res
    |   getTravelTime' (S' :: SL', res) =
          getTravelTime' (SL', res + (stopNextTime S'))
  in
    getTravelTime' (SL, 0)
  end

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

fun changeRouteFWSList newFWSList R =
  makeRoute ( routeNumber R
            , newFWSList R
            , routeBWSList R
            , routeBeginTime R
            , routeEndTime R
            , routeInterval R
            )

fun changeRouteBWSList newBWSList R =
  makeRoute ( routeNumber R
            , routeFWSList R
            , newBWSList R
            , routeBeginTime R
            , routeEndTime R
            , routeInterval R
            )

fun changeRouteBeginTime newBeginTime R =
  makeRoute ( routeNumber R
            , routeFWSList R
            , routeBWSList R
            , newBeginTime
            , routeEndTime R
            , routeInterval R
            )

fun changeRouteEndTime newEndTime R =
  makeRoute ( routeNumber R
            , routeFWSList R
            , routeBWSList R
            , routeBeginTime R
            , newEndTime
            , routeInterval R
            )

fun changeRouteInterval newInterval R =
  makeRoute ( routeNumber R
            , routeFWSList R
            , routeBWSList R
            , routeBeginTime R
            , routeEndTime R
            , newInterval
            )

(* identifying predicate *)
fun isRouteNum routeN R = routeNumber R = routeN

(* comparative predicates *)
fun routeNumberLessThan R1 R2 = 
  routeNumber R1 < routeNumber R2

fun routeBeginTimeLessThan R1 R2 =
  routeBeginTime R1 < routeBeginTime R2

fun routeEndTimeLessThan R1 R2 = 
  routeEndTime R1 < routeEndTime R2

fun routeIntervalLessThan R1 R2 =
  routeInterval R1 < routeEndTime R2

fun routeCountStationsLessThan SL1 SL2 =
  let
    fun count ([], res) = res
    |   count ( _ :: XS, res ) = count ( XS, res + 1 )
  in
    count (SL1, 0) < count (SL2, 0)
  end

fun routeCountTimeTravelLessThan SL1 SL2 =
  getTravelTime SL1 < getTravelTime SL2

(*****************************************************************************
                                Functions
                      Functions are taken from Dublin Bus App. 
 ****************************************************************************)

(* closes list of bus stops with its first station *)
fun makeCircularSNamesList SL =  
  let    
    val stopNames = getStopNames SL
  in
    reverseBack (hd stopNames :: reverseBack (stopNames, []), [])
  end

(* gets pairs Name-Time (string * int list) in mins since midnight for the route 
 * and its departure time from the first stop station
 *
 * only interval-confirmed (routeBeginTime + n*Interval) values for
 * currentTime is allowed, otherwise returned empty list
 *
 * isFwd changes direction (list to use: routeFWSList or routeBWSList) 
 * 
 * stopTimes creates a list of valid departure times
 *)
fun stopTimes R currentTime isFwd = 
  let  
    fun stopTimes' (res, [])      = reverseBack (res, []) 
    |   stopTimes' (res, S :: SL) =
          stopTimes' ( (hd res) + stopNextTime S :: res, SL )      

    fun intervals (res, [])      = reverseBack (res, [])
    |   intervals (res, _ :: SL) = 
          intervals ( (hd res) + routeInterval R :: res, SL )      
    
    val listByDirection = (isFwd = true) ? routeFWSList R :- routeBWSList R    
  in
    if member (currentTime, intervals( [routeBeginTime R], listByDirection ) ) 
    then ListPair.zip ( makeCircularSNamesList listByDirection, 
                        stopTimes' ( [currentTime], listByDirection ) )
    else []    
  end


(*****************************************************************************
                                Example
 ****************************************************************************)

val fStopList = []
val fStopList = makeStop("Kilo", 10) :: fStopList
val fStopList = makeStop("November", 5) :: fStopList
val fStopList = makeStop("Quebec", 2) :: fStopList
val fStopList = makeStop("Papa", 12) :: fStopList
val fStopList = makeStop("Charlie", 20) :: fStopList
val fStopList = makeStop("Hotel", 10) :: fStopList
val fStopList = reverseBack(fStopList, [])

val bStopList = []
val bStopList = makeStop("Kilo", 5) :: fStopList
val bStopList = makeStop("Lima", 10) :: fStopList
val bStopList = makeStop("Mike", 12) :: fStopList
val bStopList = makeStop("Charlie", 2) :: fStopList
val bStopList = makeStop("Alpha", 10) :: fStopList
val bStopList = makeStop("Echo", 18) :: fStopList
val bStopList = reverseBack(bStopList, [])

val R15 = makeRoute (15, fStopList, bStopList, 240, 1320, 4)

val fStopList = []
val fStopList = makeStop("Bravo", 12) :: fStopList
val fStopList = makeStop("Delta", 10) :: fStopList
val fStopList = makeStop("Zulu", 9) :: fStopList
val fStopList = makeStop("Victor", 12) :: fStopList 
val fStopList = makeStop("Golf", 15) :: fStopList
val fStopList = makeStop("Kilo", 6) :: fStopList
val fStopList = makeStop("Whiskey", 9) :: fStopList
val fStopList = makeStop("Alpha", 11) :: fStopList
val fStopList = reverseBack(fStopList, [])

val bStopList = []
val bStopList = makeStop("Bravo", 10) :: bStopList
val bStopList = makeStop("Yankee", 12) :: bStopList
val bStopList = makeStop("Uniform", 12) :: bStopList
val bStopList = makeStop("Sierra", 9) :: bStopList
val bStopList = makeStop("Echo", 6) :: bStopList
val bStopList = makeStop("Romeo", 15) :: bStopList
val bStopList = makeStop("India", 11) :: bStopList
val bStopList = makeStop("Mike", 9) :: bStopList
val bStopList = reverseBack(bStopList, [])

val R10 = makeRoute (10, fStopList, bStopList, 180, 1410, 10)


val fStopList = []
val fStopList = makeStop("Alpha", 8) :: fStopList
val fStopList = makeStop("Bravo", 12) :: fStopList
val fStopList = makeStop("Charlie", 5) :: fStopList
val fStopList = makeStop("Delta", 10) :: fStopList 
val fStopList = makeStop("Echo", 6) :: fStopList
val fStopList = makeStop("Foxtrot", 4) :: fStopList
val fStopList = reverseBack(fStopList, [])

val bStopList = []
val bStopList = makeStop("Alpha", 12) :: bStopList
val bStopList = makeStop("Zulu", 8) :: bStopList
val bStopList = makeStop("Yankee", 10) :: bStopList
val bStopList = makeStop("X-Ray", 5) :: bStopList
val bStopList = makeStop("Whiskey", 4) :: bStopList
val bStopList = makeStop("Victor", 6) :: bStopList
val bStopList = reverseBack(bStopList, [])

val R5 = makeRoute (5, fStopList, bStopList, 120, 1350, 5)

val fStopList = []
val fStopList = makeStop("Golf", 10) :: fStopList
val fStopList = makeStop("Hotel", 6) :: fStopList
val fStopList = makeStop("India", 7) :: fStopList
val fStopList = makeStop("Juliett", 5) :: fStopList 
val fStopList = makeStop("Kilo", 16) :: fStopList
val fStopList = makeStop("Lima", 20) :: fStopList
val fStopList = makeStop("Mike", 11) :: fStopList
val fStopList = reverseBack(fStopList, [])

val bStopList = []
val bStopList = makeStop("Golf", 6) :: bStopList
val bStopList = makeStop("Uniform", 10) :: bStopList
val bStopList = makeStop("Tango", 5) :: bStopList
val bStopList = makeStop("Sierra", 6) :: bStopList
val bStopList = makeStop("Romeo", 20) :: bStopList
val bStopList = makeStop("Quebec", 16) :: bStopList
val bStopList = makeStop("Papa", 8) :: bStopList
val bStopList = reverseBack(bStopList, [])

val R3 = makeRoute (3, fStopList, bStopList, 480, 1440, 8)

