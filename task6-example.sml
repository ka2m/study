(********************************************************
                  ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ 
 ********************************************************)

(* функция получает два списка в качестве аргументов
 * и возвращает реверсированный первый список  
 * к которому присоединен второй список  *)
fun reverseBack ([], l) = l
|   reverseBack (x :: xs, l) = reverseBack (xs, x :: l)
  
(* функция возвращает список, полученный удалением 
 * из списка SL первого элемента, 
 * удовлетворяющий условию removeCriteria
 * removeCriteria - функция, получающая один аргумент 
 * того же типа, что и элементы списка SL
 * и  возвращающая true или false *)
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

(* функция возвращает список, полученный изменением
 * в списке SL первого элемента, 
 * удовлетворяющего условию changeCriteria.
 * changeFunction - функция получающая один аргумент 
 * того же типа, что и элементы списка SL
 * и  возвращающая элемент этого же типа *)
fun changeInList (SL, changeCriteria, changeFunction) =
  let 
    fun change ([], SL') = reverseBack (SL', [])
    |   change (S' :: SL'', SL') =
          if changeCriteria S' 
          then reverseBack (SL', changeFunction (S') :: SL'')
          else change (SL'', S' :: SL')
  in
    change (SL, [])
  end  

(* функция возвращает список, полученный удалением из SL
 * всех ведущих элементов, не удовлетворяющих условию
 * searchCriteria *)
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

(* функция возвращает true если в SL
 * есть элемент удовлетворяющий условию searchCriteria *)
fun foundInList (SL, searchCriteria) = 
  not (null (clipList (SL, searchCriteria)))
  
(* функция возвращает первый элемент списка *)
fun first []     = raise Match
|   first (x::_) = x
  
(* функция возвращает элемент SL,
 * удовлетворяющий условию searchCriteria *)  
fun getFromList (SL, searchCriteria) =
  first (clipList (SL, searchCriteria))
  
(* функция возвращает список SL, отсортированный в соответствии
 * с функцией предшествования lessThan 
 * функция lessThan  каррированная функция двух аргументов 
 * того же типа, что и элементы SL, возвращающая истину, если
 * первый аргумент предшествует второму в соответствии с 
 * установленным порядком *)  
fun sort (SL, lessThan) =
  let 
    fun bubleSort (_, [], sorted) = sorted
    |   bubleSort (unsorted, [x], sorted) = 
          bubleSort ([], reverseBack (unsorted, []), x :: sorted) 
    |   bubleSort (unsorted, x :: y :: xs, sorted) = 
          if lessThan x y
          then bubleSort (x :: unsorted, y :: xs, sorted)
          else bubleSort (y :: unsorted, x :: xs, sorted)
  in 
    bubleSort ([], SL, [])
  end
  
(********************************************************
                 ПРОМЕЖУТОЧНЫЕ ОСТАНОВКИ 
 *******************************************************/*)
 
(* тип данных - транзитная станция *)
 type stop = { name : string      (* название станции *)
             , arrivalTime : int  (* время прибытия *)
             , stopTime : int     (* время остановки *)
             }

(* конструктор остановки *)            
fun makeStop (statName, arrTime, stTime) : stop =
  { name = statName
  , arrivalTime = arrTime
  , stopTime = stTime
  }

(* набор селекторов *)  
fun stopName ({name = N, ...} : stop) = N 
fun stopArrival ({arrivalTime = aT, ...} : stop) = aT
fun stopSTime ({stopTime = sT, ...} : stop) = sT

(* функции получения новых остановок из старых  *)
fun changeStopName newName S =             
  makeStop ( newName, stopArrival S, stopSTime S ) 
fun changeStopArrival newArrivalTime S =
  makeStop ( stopName S, newArrivalTime, stopSTime S ) 
fun changeStopSTime newStopTime S =
  makeStop ( stopName S, stopArrival S, newStopTime ) 
  
(* предикаты для идентификации остановки *)
fun isStopName stopN S = stopName S = stopN
fun isStopArrival arrivalTime S = stopArrival S = arrivalTime
fun isStopSTime stopTime S = stopSTime S = stopTime

(********************************************************
                     СПИСОК ОСТАНОВОК
 ********************************************************)

 (* функция выдает новый список остановок, полученный из SL
 * добавлением остановки S по порядку возрастания
 * времени прибытия на станцию.
 * если в списке SL уже присутствует станция
 * с временем прибытия на станцию S,
 * то соответствующая станция заментяется на S *)
fun addStopToList (SL, S) =
  let
    fun insertInTime ([], SL')   = reverseBack (SL', [S])
    |   insertInTime (S' :: SL'', SL') = 
          if stopArrival S < stopArrival S' then 
            reverseBack (SL', S :: S' :: SL'')
          else if stopArrival S = stopArrival S' then
            reverseBack (SL', S :: SL'')
          else insertInTime (SL'', S' :: SL')
  in
    insertInTime (SL, [])
  end

(* функция возвращает список, полученный из SL
 * удалением остановки с названием stopN *)  
fun removeStopByName (SL, stopN) =
  removeFromList (SL, isStopName stopN)

(* функция возвращает список, полученный из SL
 * удалением остановки с временем прибытия arrivalTime *)  
fun removeStopByArrival (SL, arrivalTime) =
  removeFromList (SL, isStopArrival arrivalTime)

(* функция возвращает список, полученный из SL
 * удалением первой остановки с временем стоянки stopTime *)
fun removeStopBySTime (SL, stopTime) =
  removeFromList (SL, isStopSTime stopTime)

(* функция возвращает список, полученный из SL
 * заменой наименования остановки oldStopName на newStopName *)
fun changeStopNameInList (SL, oldStopName, newStopName) =
  changeInList (SL, isStopName oldStopName, changeStopName newStopName)

(* функция возвращает список, полученный из SL
 * заменой у остановки stopName времени прибытия на newArrival *)
fun changeStopArrivalInList (SL, stopName, newArrival) =
  changeInList (SL, isStopName stopName, changeStopArrival newArrival)

(* функция возвращает список, полученный из SL
 * заменой у остановки stopName времени стоянки на newSTime *)  
fun changeStopSTimeInList (SL, stopName, newSTime) =
  changeInList (SL, isStopName stopName, changeStopSTime newSTime)
  
(* функция возвращает остановку с названием stopName из списка SL *)
fun getStopFromList (SL, stopName) =
  getFromList (SL, isStopName stopName)  

(********************************************************
                          ПОЕЗД
 ********************************************************)  
 
 (* тип данных - поезд *)
type train = { number : int            (* номер *)
             , departStation : string  (* станция отправления *)
             , departTime : int        (* время отправления *)
             , stopList : stop list    (* список остановок *)
             } 
 
(* конструктор *) 
fun makeTrain (trainNum, trainDStation, trainDTime, trainStopL) : train =
  { number = trainNum
  , departStation = trainDStation
  , departTime = trainDTime
  , stopList = trainStopL
  }
 
(* набор селекторов *) 
fun trainNum ({number = tN, ...} : train) = tN
fun trainDStation ({departStation = dS, ...} : train) = dS
fun trainDTime ({departTime = dT, ...} : train) = dT
fun trainStopList ({stopList = SL, ...} : train) = SL

(* функции получения нового позда из старого, заменой одного из полей *)
fun changeTrainNum newNum T =
  makeTrain ( newNum
            , trainDStation T
            , trainDTime T
            , trainStopList T 
            ) 
fun changeTrainDStation newDStation T =
  makeTrain ( trainNum T
            , newDStation
            , trainDTime T
            , trainStopList T 
            )             
fun changeTrainDTime newDTime T =
  makeTrain ( trainNum T
            , trainDStation T
            , newDTime
            , trainStopList T 
            )             
fun changeTrainStopList newStopList T =
  makeTrain ( trainNum T
            , trainDStation T
            , trainDTime T
            , newStopList 
            )             

(* предикаты идентификации поезда *)            
fun isTrainNum trainN T = trainNum T = trainN
fun isTrainDStation trainDStat T = trainDStation T = trainDStat
fun isTrainDT trainDT T = trainDTime T = trainDT

(* предикат, определяющий, имеет ли поезд транзитную станцию *)
fun hasTrainTransitStop statName T = 
    foundInList (trainStopList T, isStopName statName)
(* предикат, определяющий, проходит ли поезд через станцию *)
fun hasTrainStop statName T = 
  (isTrainDStation statName T) orelse
    hasTrainTransitStop statName T
(* предикат, определяющий, можно ли попасть поездом T 
 * со станции statName1 на станцию statName2 *) 
fun goesFromTo statName1 statName2 T =
  ( isTrainDStation statName1 T andalso
    hasTrainTransitStop statName2 T ) 
  orelse
  let
    val stL = clipList (trainStopList T,  isStopName statName1)
  in
    not (null stL) andalso 
    not (null (clipList (stL,  isStopName statName2)))
  end

(* функция выдает время прибытия поезда T на станцию statName 
 * значение в минутах с момента отправления поезда с начальной станции*)    
fun trainArrivalTime statName T =
  stopArrival (getFromList (trainStopList T, isStopName statName))
(* функция выдает время прибытия поезда T на станцию statName 
 * значение в минутах от начала суток *)    
fun trainArrivalDayTime statName T =
  (trainArrivalTime statName T + trainDTime T) mod (24 * 60)
(* функция выдает время отправления поезда T со станции statName 
 * значение в минутах с момента отправления поезда с начальной станции*)    
fun trainDepartureTime statName T =
  if isTrainDStation statName T then 0
  else 
    let 
      val st = getFromList (trainStopList T, isStopName statName)
    in 
      stopArrival st + stopSTime st
    end
(* функция выдает время отправления поезда T со станции statName 
 * значение в минутах от начала суток *)        
fun trainDepartureDayTime statName T =
  (trainDepartureTime statName T +  trainDTime T) mod (24 * 60)

(* функция предшествования:
 * возвращает истину, если поезд T1 отправляется со станции statName 
 * раньше поезда T2 *)  
fun trainDepTimeLessThan statName T1 T2 =
  trainDepartureDayTime statName T1 < trainDepartureDayTime statName T2
(* функция предшествования:
 * возвращает истину, если поезд T1 прибывает на станцию statName 
 * раньше поезда T2 *)  
fun trainArrivalTimeLessThan statName T1 T2 =
  trainArrivalDayTime statName T1 < trainArrivalDayTime statName T2
 
(* вспомогательная функция для краткого вывода расписания. Выдает пятерку:
 *    1) номер поезда T, 
 *    2) станция отправления statName1 
 *    3) время отправления поезда T со станции statName1
 *    4) станция прибытия statName2 
 *    5) время прибытия поезда T на станцию statName2 
 * функция работает корректно только при условии, что поезд T
 * проходит через станции statName1 и statName2 *)
fun scheduleFromTo statName1 statName2 T =
  ( trainNum T
  , statName1
  , trainDepartureDayTime statName1 T
  , statName2
  , trainArrivalDayTime statName2 T
  )

(********************************************************
                 ОБРАБОТКА СПИСКА ПОЕЗДОВ
 ********************************************************) 

(* выдает список поездов, полученный из TL
 * удалением поезда с номером trainN *)
fun removeTrainByNum (TL, trainN) =
  removeFromList (TL, isTrainNum trainN)
(* выдает список поездов, полученный из TL
 * удалением первого поезда со станцией отправления trainDStat *)
fun removeTrainByDStation (TL, trainDStat) =
  removeFromList (TL, isTrainDStation trainDStat)
(* выдает список поездов, полученный из TL
 * удалением первого поезда с временем отправления 
 * с начальной станции trainDT *)
fun removeTrainByDT (TL, trainDT) =
  removeFromList (TL, isTrainDT trainDT)
(* выдает список поездов, полученный из TL
 * удалением первого поезда проходящего через станцию statName *)
fun removeTrainByTransitStation (TL, statName) =
  removeFromList (TL, hasTrainStop statName)
 
(* выдает список поездов, полученный из TL
 * заменой у поезда с номером oldNum номера на newNum *)
fun changeTrainNumInList (TL, oldNum, newNum) =
  changeInList (TL, isTrainNum oldNum, changeTrainNum newNum)
(* выдает список поездов, полученный из TL
 * заменой у поезда с номером trainNum 
 * станции отправления на newDStation *)
fun changeTrainDStationInList (TL, trainNum, newDStation) =
  changeInList ( TL
               , isTrainNum trainNum
               , changeTrainDStation newDStation
               )
(* выдает список поездов, полученный из TL
 * заменой у поезда с номером trainNum 
 * времени отправления с начальной станции на newDTime *)
fun changeTrainDTimeInList (TL, trainNum, newDTime) =
  changeInList ( TL
               , isTrainNum trainNum
               , changeTrainDTime newDTime
               )
(* выдает список поездов, полученный из TL
 * заменой у поезда с номером trainNum 
 * списка транзитных станций на newStopList *)
fun changeTrainStopListInList (TL, trainNum, newStopList) =
  changeInList ( TL
               , isTrainNum trainNum
               , changeTrainStopList newStopList
               )    

(* функция выдает из списка TL поезд с номером trainNum *)               
fun getTrainFromList (TL, trainNum) =
  getFromList (TL, isTrainNum trainNum)               
                         
(* функция выдает список поездов из списка TL, 
 * имеющих остановку statName *)                                        
fun transitTrains (TL, statName) =
  List.filter (hasTrainStop statName) TL
(* функция выдает список поездов из списка TL, 
 * имеющих остановку statName, 
 * отсортированных в порядке времени отправления со 
 * станции  statName *)     
fun transitTrainsByDepTime (TL, statName) =
  let 
    val tL = transitTrains (TL, statName)
  in 
    sort (tL, trainDepTimeLessThan statName)
  end
(* функция выдает список поездов из списка TL, 
 * проходящих из statName1 в statName2 *)   
fun trainsFromTo (TL, statName1, statName2) =
  List.filter (goesFromTo statName1 statName2) TL
(* функция выдает список поездов из списка TL, 
 * проходящих из statName1 в statName2, 
 * отсортированных в порядке времени отправления со 
 * станции  statName1 *)     
fun trainsFromToByDepTime (TL, statName1, statName2) =
  let 
    val tL = trainsFromTo (TL, statName1, statName2)
  in 
    sort (tL, trainDepTimeLessThan statName1)
  end
(* функция выдает список поездов из списка TL, 
 * проходящих из statName1 в statName2, 
 * отсортированных в порядке времени прибытия на 
 * станцию  statName2 *)     
fun trainsFromToByArrTime (TL, statName1, statName2) =
  let 
    val tL = trainsFromTo (TL, statName1, statName2)
  in 
    sort (tL, trainArrivalTimeLessThan statName2)
  end  

(* функция выдает список пятерок расписания
 * для поездов проходящих из statName1 в statName2.
 * Функция работает при условии что любым поездом
 * из списка TL можно попасть со станции statName1
 * на станцию statName2 *)       
fun scheduleFromValidList (TL, statName1, statName2) =
  map (scheduleFromTo statName1 statName2) TL
  
(********************************************************
                        ПРИМЕР
 ********************************************************)   

(* определение первого поезда *)
val stopList' = []
val stopList' = addStopToList (stopList', makeStop ("ATKARSK",	94,	2))
val stopList' = addStopToList (stopList', makeStop ("RTISHCHEVO", 187, 29))
val stopList' = addStopToList (stopList', makeStop ("VERTUNOVSKAIa", 244, 2))
val stopList' = addStopToList (stopList', makeStop ("TAMALA", 272, 2))
val stopList' = addStopToList (stopList', makeStop ("UMET", 292, 2))
val stopList' = addStopToList (stopList', makeStop ("KIRSANOV", 313, 2))
val stopList' = addStopToList (stopList', makeStop ("TAMBOV", 389, 5))
val stopList' = addStopToList (stopList', makeStop ("MICHURINSK", 463, 43))
val stopList' = addStopToList (stopList', makeStop ("BOGOIAVLENSK", 545, 2))
val stopList' = addStopToList (stopList', makeStop ("RANENBURG", 510, 2))
val stopList' = addStopToList (stopList', makeStop ("ZANOVO", 592, 5))
val stopList' = addStopToList (stopList', makeStop ("TROEKUROVO", 600, 1))
val stopList' = addStopToList (stopList', makeStop ("URUSOVO", 616, 1))
val stopList' = addStopToList (stopList', makeStop ("GROTOVSKII`", 627, 1))
val stopList' = addStopToList (stopList', makeStop ("MILOSLAVSK", 637, 1))
val stopList' = addStopToList (stopList', makeStop ("TOPILLY", 655, 1))
val stopList' = addStopToList (stopList', makeStop ("PAVELETC", 670, 2))
val stopList' = addStopToList (stopList', makeStop ("MIKHAI`LOV", 710, 2))
val stopList' = addStopToList (stopList', makeStop ("UZUNOVO", 751, 23))
val stopList' = addStopToList (stopList', makeStop ("MOSKVA", 922, 5))	
val T17 = makeTrain (17, "SARATOV", 1147, stopList')

(* определение второго поезда *)
val stopList' = []
val stopList' = addStopToList (stopList', makeStop ("AKSARAI`SK", 53, 2))
val stopList' = addStopToList (stopList', makeStop ("ASHULUK", 119, 2))
val stopList' = addStopToList (stopList', makeStop ("HARABALIN", 137, 2))
val stopList' = addStopToList (stopList', makeStop ("V BASKUNCHAK", 235, 19))
val stopList' = addStopToList (stopList', makeStop ("E`L`TON", 344, 2))
val stopList' = addStopToList (stopList', makeStop ("PALLASOVKA", 427, 2))
val stopList' = addStopToList (stopList', makeStop ("LEPEKHINSK", 490, 6))
val stopList' = addStopToList (stopList', makeStop ("KRASNYI` KUT", 526, 2))
val stopList' = addStopToList (stopList', makeStop ("URBAKH", 569, 2))
val stopList' = addStopToList (stopList', makeStop ("SARATOV", 676, 48))
val stopList' = addStopToList (stopList', makeStop ("ATKARSK", 816, 2))
val stopList' = addStopToList (stopList', makeStop ("RTISHCHEVO", 913, 32))
val stopList' = addStopToList (stopList', makeStop ("VERTUNOVSKAIa", 973, 2))
val stopList' = addStopToList (stopList', makeStop ("TAMALA", 1001, 2))
val stopList' = addStopToList (stopList', makeStop ("UMET", 1025, 2))
val stopList' = addStopToList (stopList', makeStop ("KIRSANOV", 1046, 2))
val stopList' = addStopToList (stopList', makeStop ("PLATONOVKA", 1095, 2))
val stopList' = addStopToList (stopList', makeStop ("TAMBOV", 1134, 20))
val stopList' = addStopToList (stopList', makeStop ("MICHURINSK", 1225, 32))
val stopList' = addStopToList (stopList', makeStop ("BOGOIAVLENSK", 1298, 19))
val stopList' = addStopToList (stopList', makeStop ("RIAZHSK", 1361, 4))
val stopList' = addStopToList (stopList', makeStop ("RIAZAN`", 1376, 23))
val stopList' = addStopToList (stopList', makeStop ("TVER`", 1716, 2))
val stopList' = addStopToList (stopList', makeStop ("V VOLOCHEK", 1793, 2))
val stopList' = addStopToList (stopList', makeStop ("BOLOGOE", 1832, 6))
val stopList' = addStopToList (stopList', makeStop ("OKULOVKA", 1891, 2))
val stopList' = addStopToList (stopList', makeStop ("MAL VISHERA", 1955, 2))
val stopList' = addStopToList (stopList', makeStop ("TORFIANOE", 2000, 69))
val stopList' = addStopToList (stopList', makeStop ("S-PETERBURG", 2178, 0))
val T109 = makeTrain (109, "ASTRAKHAN`", 1365, stopList')

(* определение третьего поезда *)
val stopList' = []
val stopList' = addStopToList (stopList', makeStop ("GRIAZI", 78, 2))
val stopList' = addStopToList (stopList', makeStop ("MICHURINSK", 118, 2))
val stopList' = addStopToList (stopList', makeStop ("RIAZAN`", 256, 2))
val stopList' = addStopToList (stopList', makeStop ("MOSKVA", 399, 2))
val T45 = makeTrain (45, "VORONEZH", 452, stopList')   

(* список вспех поездов *)
val scheduleAll = [T45, T109, T17]

(* расписание поездов из Саратова в Мичуринск *)
val schedule1 = 
  scheduleFromValidList
     ( trainsFromToByDepTime (scheduleAll, "SARATOV", "MICHURINSK")
     , "SARATOV"
     , "MICHURINSK"
     )

(* расписание поездов из Мичуринска в Рязань *)     
val schedule2 = 
  scheduleFromValidList
     ( trainsFromToByDepTime (scheduleAll, "MICHURINSK", "RIAZAN`")
     , "MICHURINSK"
     , "RIAZAN`" 
     )   

(* расписание поездов из Мичуринска в Москву *)          
val schedule3 = 
  scheduleFromValidList
     ( trainsFromToByDepTime (scheduleAll, "MICHURINSK", "MOSKVA")
     , "MICHURINSK"
     , "MOSKVA" 
     ) 
  
(* изменяем список станций поезда 109 
 * для этого сначала извлекаем старый список станций *)  
val T' = getTrainFromList (scheduleAll, 109)
val stopList' = trainStopList T'
(* добавляем в полученный список станций остановку в Москве *)
val stopList' = addStopToList (stopList', makeStop ("MOSKVA", 1491, 15))
(* удаляем из списка остановку в Кирсанове *)
val stopList' = removeStopByName (stopList', "KIRSANOV")
(* в списке поездов у поезда 109 обновляем список остановок *)
val scheduleAll = changeTrainStopListInList (scheduleAll, 109, stopList')

(* у поезда 17 изменяем время отправления с начальной станции *)
val scheduleAll = changeTrainDTimeInList (scheduleAll, 17, 1130)

(* обновленное расписание поездов из Мичуринска в Москву *)          
val schedule4 = 
  scheduleFromValidList
     ( trainsFromToByDepTime (scheduleAll, "MICHURINSK", "MOSKVA")
     , "MICHURINSK"
     , "MOSKVA" 
     ) 
  
            
