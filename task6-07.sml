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

fun reverseBack ([], l)      = l
|   reverseBack (x :: xs, l) = reverseBack (xs, x :: l)

fun removeFromList (SL, removeCriteria) =
  let
    fun remove ([], SL')         = reverseBack (SL', [])
    |   remove (S' :: SL'', SL') =
          if removeCriteria S'
          then reverseBack (SL', SL'')
          else remove (SL'', S' :: SL')
  in
    remove (SL, [])
  end

fun count ([], res)        = res
|   count ( _ :: XS, res ) = count ( XS, res + 1 )

fun member ( x, [] )        = false
|   member ( x, (y :: ys) ) = (x = y) ? true :- member ( x, ys )

fun first (x:string, y:int) = x

fun second (x:string, y:int) = y

fun quicksort lt xs =
  let
    fun qsort []  k = k []
      | qsort [x] k = k [x]
      | qsort (p::xs) k =
    let
      val (left, right) = List.partition (fn x => lt (x, p)) xs
    in
      qsort left ( fn L => qsort right (fn L' => k (L @ [p] @ L')) )
    end
  in
    qsort xs (fn x => x)
  end

fun searchListByCriteria ( [], res, criteria )      = reverseBack (res, [])
|   searchListByCriteria ( R :: RL, res, criteria ) =
      searchListByCriteria ( RL
                              , if criteria R then R :: res else res
                              , criteria
                              )

(*****************************************************************************
                                Bus stop entity
 ****************************************************************************)

(* As stops for bus route are stored in a linked list, we can precisely
   determine, which stop comes first and which comes next. That's why I placed
   travel times between two stops inside this type *)
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
  removeFromList ( SL, isStopName stopN )

fun hasRouteStop stopName SL =
  not (null (searchListByCriteria ( SL, [], isStopName stopName )))

(* function that gets only the names from the stops list *)
fun getStopNames SL =
  let
    fun getStopNames' ([], res)        = reverseBack (res, [])
    |   getStopNames' (S' :: SL', res) =
          getStopNames' (SL', stopName S' :: res)  
  in 
    getStopNames' (SL, [])
  end

(* function to count travel time (used in route sorting) *)
fun getTravelTime SL =
  let 
    fun getTravelTime' ([], res)        = res
    |   getTravelTime' (S' :: SL', res) =
          getTravelTime' (SL', res + (stopNextTime S'))
  in
    getTravelTime' (SL, 0)
  end

fun stopNamesLessThan (S1, S2) =
  stopName S1 < stopName S2

fun stopIntervalsLessThan (S1, S2) =
  stopNextTime S1 < stopNextTime S2

(* sorting *)
fun sortStopsByName SL =
  quicksort stopNamesLessThan SL

fun sortStopsByInterval SL =
  quicksort stopIntervalsLessThan SL

(*****************************************************************************
                                Bus route entity
 ****************************************************************************)

type route = {  number : int      (* route name *)
              , fwStopList: stop list (* bus stops in one direction *)
              , bwStopList: stop list (* bus stops in opposite direction *)
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
fun isRouteFWSList fws R = routeFWSList R = fws
fun isRouteBWSList bws R = routeBWSList R = bws
fun isRouteBeginTime bTime R = routeBeginTime R = bTime
fun isRouteEndTime eTime R = routeEndTime R = eTime
fun isRouteInterval it R = routeInterval R = it

(* comparative predicates *)
fun routeNumberLessThan (R1, R2) = 
  routeNumber R1 < routeNumber R2

fun routeCountStationsLessThan (SL1, SL2) =
    count (SL1, 0) < count (SL2, 0)

fun routeCountTravelTimeForwardLessThan (R1, R2) =
  getTravelTime (routeFWSList R1) < getTravelTime (routeFWSList R2)

fun routeCountTravelTimeBackwardsLessThan (R1, R2) =
  getTravelTime (routeBWSList R1) < getTravelTime (routeBWSList R2)

fun routeCountTravelTimeBothLessThan (R1, R2) =
  getTravelTime (routeFWSList R1) + getTravelTime (routeBWSList R1) < 
  getTravelTime (routeFWSList R2) + getTravelTime (routeBWSList R2)

fun routeCountStationsForwardLessThan (R1, R2) =
  routeCountStationsLessThan ( (routeFWSList R1), (routeFWSList R2) )

fun routeCountStationsBackwardsLessThan (R1, R2) =
  routeCountStationsLessThan ( (routeBWSList R1), (routeBWSList R2) )

fun routeCountStationsBothLessThan (R1, R2) =
  count ( (routeFWSList R1), 0 ) + count( (routeBWSList R1), 0 ) <
  count ( (routeFWSList R2), 0 ) + count ( (routeBWSList R2), 0 )


fun routeBeginTimeLessThan (R1, R2) =
  routeBeginTime R1 < routeBeginTime R2

fun routeEndTimeLessThan (R1, R2) = 
  routeEndTime R1 < routeEndTime R2

fun routeIntervalLessThan (R1, R2) =
  routeInterval R1 < routeEndTime R2

(* sorting *)

fun sortRoutesByName RL =
  quicksort routeNumberLessThan RL

fun sortRoutesByBeginTime RL =
  quicksort routeBeginTimeLessThan RL

fun sortRoutesByEndTime RL =
  quicksort routeEndTimeLessThan RL

fun sortRoutesByInterval RL =
  quicksort routeIntervalLessThan RL 

fun sortRoutesByStopCount RL direction =
  quicksort routeCountStationsBothLessThan RL
|   sortRoutesByStopCount RL 2         =
      quicksort routeCountStationsBackwardsLessThan RL
|   sortRoutesByStopCount RL 1         =
      quicksort routeCountStationsForwardLessThan RL

fun sortRoutesByTravelTime RL direction  = 
      quicksort routeCountTravelTimeBothLessThan RL
|   sortRoutesByTravelTime RL 2          = 
      quicksort routeCountTravelTimeBackwardsLessThan RL
|   sortRoutesByTravelTime RL 1          =
      quicksort routeCountTravelTimeForwardLessThan RL
  

(* searching *)

fun selectRouteByNumber RL number =
  let
    fun search []          = false
    |   search (R' :: RL') =
          isRouteNum number R' orelse search (RL')          
  in
    search (RL)
  end

fun findStopByName SL sName =
  let
    fun search []         = false
    |   search (S :: SL') =
      isStopName sName S orelse search (SL')
  in
    search (SL)
  end

fun selectRoutesWithStop RL sName =
  let
    fun search ([], res)       = reverseBack (res, [])
    |   search (R :: RL', res) =
          search (RL', if findStopByName (routeFWSList R) sName 
                          orelse findStopByName (routeBWSList R) sName 
                          then R :: res
                          else res)
  in
    search (RL, [])      
  end

fun selectRoutesWithBeginTime RL bTime =
  searchListByCriteria (RL, [], isRouteBeginTime bTime)

fun selectRoutesWithEndTime RL eTime =
  searchListByCriteria (RL, [], isRouteEndTime eTime)

fun selectRoutesWithFWSList RL fws =
  searchListByCriteria (RL, [], isRouteFWSList fws)

fun selectRoutesWithBWSList RL bws =
  searchListByCriteria (RL, [], isRouteBWSList bws)

fun selectRoutesInterval RL iT =
  searchListByCriteria (RL, [], isRouteInterval iT)


(*****************************************************************************
                            Extra Functions                      
 ****************************************************************************)

(* helping function: closes list of bus stops with its first station *)
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

    fun intervals res = 
          if (hd res) + (routeInterval R) <= (routeEndTime R)
          then intervals ((hd res) + routeInterval R :: res)      
          else reverseBack(res, [])  

    val listByDirection = (isFwd = true) ? routeFWSList R :- routeBWSList R    
  in
    if member (currentTime, intervals( [routeBeginTime R] ) ) 
    then ListPair.zip ( makeCircularSNamesList listByDirection, 
                        stopTimes' ( [currentTime], listByDirection ) )
    else []    
  end

(* function that prints time matrix, sorted by beginTimes + n * routeInterval 
 * with stop names, determening at what time bus arrives to the each stop *)
fun routeStopMatrix R isFwd = 
  let    
    fun intervals res = 
          if (hd res) + (routeInterval R) <= (routeEndTime R)
          then intervals ((hd res) + routeInterval R :: res)      
          else reverseBack(res, [])  

    fun row (res, [])      = reverseBack (res, [])
    |   row (res, t :: ts) = row ( (stopTimes R t isFwd) :: res, ts )
  in
    row ( [], intervals [routeBeginTime R] )
  end

fun routeSearchByPoints route departure arrival currentTime =
  let 
    fun sortOutDeparture S =
       (first S) = departure andalso currentTime - 30 <= (second S)
       andalso currentTime + 30 >= (second S)
    
    fun findTimesInList ([], res) = res
    |   findTimesInList (L, res)  =
        let 
          val suitableTimes =
            List.filter (fn y => sortOutDeparture y) L
        in
          findTimesInList ( (tl (tl L)), suitableTimes @ res )
        end

    fun findSuitableTimes ([], res)      = res
    |   findSuitableTimes (y :: ys, res) =
          findSuitableTimes ( ys, findTimesInList (y, []) @ res )
  

    fun findArrivalsInList ([], res) = res
    |   findArrivalsInList (L, res)  =
        let 
          val arrivals =
            List.filter (fn y => (first y) = arrival) L
        in
          findArrivalsInList ( tl L), arrivals :: res )
        end

    fun findArrivals ([], res)      = res
    |   findArrivals (y :: ys, res) =
          findArrivals ( ys, findArrivalsInList (y, []) @ res )
  
    (*fun correlate *)



    
    val stops = (routeStopMatrix route true) @ (routeStopMatrix route false)
    val suitableDeparture =  findSuitableTimes ( stops, [] )       
    val foundArrivals = reverseBack ( findArrivals (stops, []), [] )
  in 
    (suitableDeparture, foundArrivals)
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

val R3 = makeRoute (3, fStopList, bStopList, 180, 1440, 8)

val routes = [R5, R3, R15, R10];

routeSearchByPoints R3 "Uniform" "Romeo" 200
