(deffunction ask-question (?question $?allowed-values)
   (printout t ?question)
   (bind ?answer (read))
   (if (lexemep ?answer)
       then (bind ?answer (lowcase ?answer)))
   (while (not (member ?answer ?allowed-values)) do
      (printout t ?question)
      (bind ?answer (read))
      (if (lexemep ?answer)
          then (bind ?answer (lowcase ?answer))))
   ?answer)

(deffunction yes-or-no-p (?question)
   (bind ?response (ask-question ?question yes no y n))
   (if (or (eq ?response yes) (eq ?response y))
       then TRUE
       else FALSE))

(defrule determine-working-state ""
	(not (working-state player ?))
	(not (repair ?))
	=>
	(if (yes-or-no-p "Плеер работает (yes/no)? ")
		then (if (yes-or-no-p " Плеер работает стабильно (yes/no)? ")
			 then (assert (working-state player normal))
			 else (assert (working-state player unstable)))
		else (assert (working-state player disenabled))))

(defrule determine-battery-working ""
    (working-state player disenabled)
    (not (repair ?))
    =>
    (if (yes-or-no-p "Батарея заряжена (yes/no)? ")
        then (assert (repair "Механическое повреждение. Отнесите плеер в сервисный центр"))
        else (assert (repair "Зарядите батарею"))
        ))

(defrule is-music-playing ""
    (working-state player unstable)
    (not (repair ?))
    =>
    (if (yes-or-no-p "Музыка проигрывается (yes/no)? ")
        then (assert (music-playing TRUE))
        else (assert (music-playing FALSE))))

(defrule has-songs ""
    (working-state player unstable)
    (display on)
    (music-playing FALSE)
    (not (repair ?))
    =>
    (if (yes-or-no-p "Закачаны ли треки (yes/no)? ")
        then (assert (has-songs TRUE))
        else (assert (repair "Закачайте треки"))))

(defrule is-jack-ok ""
    (working-state player unstable)
    (music-playing FALSE)
    (has-songs TRUE)
    (not (repair ?))
    =>
    (if (yes-or-no-p "Аудиовыход в порядке (yes/no)? ")
        then (assert (repair "Сбой ПО. Подключите к ПК, синхронизируйте и переустановите ПО"))
        else (assert (repair "Механическое повреждение. Отнесите плеер в сервисный центр"))))

(defrule is-display-on ""
    (working-state player unstable)
    (not (repair ?))
    =>
    (if (yes-or-no-p "Экран работает (yes/no)? ")
        then (assert (display on))
        else (assert (repair "Механическое повреждение. Отнесите плеер в сервисный центр"))))

(defrule is-player-sane ""
    (working-state player unstable)
    (display on)
    (music-playing TRUE)
    (not (repair ?))
    =>
    (if (yes-or-no-p "Вывод на дисплей нормальный (yes/no)? ")
       then (if (not (yes-or-no-p "Музыка играет корректно (yes/no)? "))
                then (assert (repair "Подключите к ПК. Проверьте память")))
       else (assert (repair "Сбой ПО. Подключите к ПК, синхронизируйте и переустановите ПО"))))

(defrule normal-state-conclusions ""
   (declare (salience 10))
   (working-state player normal)
   =>
   (assert (repair "Ремонт не нужен.")))     ; ремонт не нужен

;;;********************************************************************
;;;   Запуск и завершение программы
;;;********************************************************************
;;; Правило no-repairs запускается в случае, если ни одно из
;;; диагностических правил не способно определить неисправность.
;;; Правило корректно прерывает выполнение экспертной системы и
;;; предлагает пройти более тщательную проверку (см. правило 13).
(defrule no-repairs ""
  (declare (salience -10))
  (not (repair ?))
  =>
  (assert (repair "Обратитесь в  службу поддержки.")))

(defrule print-repair ""
  (declare (salience 10))
  (repair ?item)
  =>
  (printout t crlf crlf)
  (printout t "Рекомендации по ремонту:")
  (printout t crlf crlf)
  (format t " %s%n%n%n" ?item))

(defrule system-banner ""
  (declare (salience 10))
  =>
  (printout t crlf crlf)
  (printout t "ЭКСПЕРТНАЯ СИСТЕМА PlayerExpert")
  (printout t crlf crlf)
)
