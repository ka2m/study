;; Написать программу, заменяющую в текстовом файле f каждое вхождение строки S1 на строку S2.
;; Текст в выходном файле должен быть отформатирован по 30 символов на строке без разрыва слов.
;; Считаем, что ни одно слово в тексте не превосходит по длине 15 символов

#lang racket
(require racket/trace)


;; reverses list
;; '(a b c) -> '(c b a)
(define (rev lst)
    (define (rev-int lst res)
        (if (null? lst)
             res
            (rev-int (cdr lst)
                     (cons (car lst) res))))
    (rev-int lst '()))


;; count size of list
(define (list-size l)
    (define (impl l count)
        (if (null? l)
            count
            (impl (cdr l) (+ 1 count))))
    (impl l 0))

;; remove elements from list basing on i in [a,b] where i is index
(define (remove-from-list-range l a b)
    (define (impl l cur a b res)
        (if (null? l)
            res
            (if (> cur b)
                (impl (cdr l) (+ 1 cur) a b (cons (car l) res))
                (if (>= cur a)
                    (impl (cdr l) (+ 1 cur) a b res)
                    (impl (cdr l) (+ 1 cur) a b (cons (car l) res))))))
    (rev (impl l 0 a b '())))

(define (check-substring l s1)
    (define (impl l s1 status)
        (if (null? s1)
            status
            (if (eq? (car l) (car s1))
                (impl (cdr l) (cdr s1) #t)
                #f)))
    (impl l s1 #f))

(define (replace-newlines l)
    (define (impl l res)
        (if (null? l)
            res
            (impl (cdr l)
                  (let ((next (car l)))
                  (cons (if (eq? next #\newline)
                        #\space
                        next)
                        res)))))
    (rev (impl l '())))

(define (in-list elem match-l)
    (define (impl elem match-l res)
        (if (null? match-l)
            res
            (if (eq? elem (car match-l))
                #t
                (impl elem (cdr match-l) #f))))
    (impl elem match-l #f))

(define (make-words l delims)
    (define (impl l delims accum res)
        (if (null? l)
            res
            (let ((next (car l)))
                 (if (eq? (in-list next delims) #t)
                     (impl (cdr l)
                           delims
                           '()
                           (if (null? accum)
                             (append res
                                     (list next))
                             (append res
                                     (list (list->string (rev accum)))
                                     (list next))))
                     (impl (cdr l) delims (cons next accum) res)))))
    (impl l delims '() '()))

(define (do-replace l s1 s2)
    (define (impl l s1 s2 s1-size res)
        (if (null? l)
            (rev res)
            (if (eq? (check-substring l s1) #t)
                (impl (remove-from-list-range l 0 s1-size)
                      s1
                      s2
                      s1-size
                      (append (rev s2) res))
                (impl (cdr l)
                      s1
                      s2
                      s1-size
                      (cons (car l) res)))))
    (let* ((ll (string->list l))
          (ls1 (string->list s1))
          (ls2 (string->list s2))
          (s1-size (- (list-size ls1) 1)))
      (impl (replace-newlines ll) ls1 ls2 s1-size '())))

(define (fancy-print words delims limit)
    (define (fancy-impl words delims limit current res)
        (if (null? words)
            res
            (let* ((r (car words))
                   (next (if (char? r) (make-string 1 r) r))
                   (nl (make-string 1 #\newline))
                   (rest (cdr words))
                   (nsize (if (eq? (in-list next delims) #t)
                              1
                              (string-length next)))
                   (new-cur (+ current nsize)))
            (if (<= new-cur limit)
                (fancy-impl rest delims limit new-cur (string-append res next))
                (fancy-impl (if (eq? r #\space)
                                rest
                                words)
                            delims
                            limit
                            0
                            (string-append res nl))))))
    (fancy-impl words delims limit 0 ""))

(let* ((out "result")
       (ins (file->string "input.txt"))
       (s1 "another line")
       (s2 "my line")
       (delims '(#\space #\. #\,))
       (lng 30))
       (with-output-to-file out
             (lambda () (printf (fancy-print (make-words (do-replace ins
                                                              s1
                                                              s2)
                                                  delims)
                                      delims
                                      lng)))))
