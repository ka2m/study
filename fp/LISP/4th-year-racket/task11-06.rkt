#lang racket
(require racket/trace)

;;quicksort
;;(define (quicksort l)
;    (let impl ((tosort l)
;                (acc '()))
;      (if (or (null? tosort)
;              (null? (cdr tosort)))
;          (append tosort acc)
;          (let* ((pivot (car tosort))
;                 (tosort (cdr tosort))
;                 (acc (append (list pivot) (quicksort (filter ((curry <=) pivot) tosort)) acc)))
;                (impl (filter ((curry >) pivot) tosort) acc)))))

(define (same-elems? l)
    (define (se-impl l cur res)
        (if (null? l)
            res
            (if (null? (cdr l))
                (eq? cur (car l))
                (se-impl (cdr l) (car l) (eq? cur (car l))))))
    (if (null? (cdr l))
        #t
        (se-impl (cdr l) (car l) #f)))

(define (quicksort l)
    (define (impl stack tosort acc)
        (if (and (null? stack)
                 (null? tosort))
            acc
            (if (null? tosort)
                (impl (if (null? (cdr stack))
                          '()
                          (cdr stack))
                      (car stack)
                      acc)
                (if (same-elems? tosort)
                    (if (null? (cdr stack))
                        (append (car stack) tosort acc)
                        (impl (cdr stack) (car stack) (append tosort acc)))
                    (impl (cons (list (car tosort)) (cons (filter ((curry >=) (car tosort)) (cdr tosort)) stack))
                          (filter ((curry <) (car tosort)) tosort)
                          acc)))))
    (trace impl)
    (impl (cons l '()) '() '()))



(trace quicksort)
(quicksort '(1 34 58 21 2 2 2 3 1 80 6))
