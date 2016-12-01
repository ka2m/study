#lang racket
(require racket/trace)

;(define routes (list (list 'r1 (list 'a 'b 'c))
;                     (list 'r2 (list 'b 'd 'e))))
(define routes (list (list 'r1 (list 'm 'z 'x 'a 'b 'c 'd 'g))
                     (list 'r2 (list 'b 'a 'e 'l 'm))
                     (list 'r3 (list 'j 'i 'h 'g 'f 'b))
                     (list 'r4 (list 'l 'k 'e 'b))))

(define (route->graph route)
  (define (rtg stop-list r-name from res)
    (if (null? stop-list)
        res
        (rtg (cdr stop-list)
             r-name
             (car stop-list)
             (append res
                     (list (list from (car stop-list) r-name))))))
  (rtg (cdr (second route)) (first route) (car (second route)) '()))

(define (routes->graph routes)
  (define (impl routesList res)
    (if (null? routesList)
        res
        (impl (cdr routesList) (append res (route->graph (car routesList))))))
  (impl routes '()))

(define graph (routes->graph routes))
(define total-stops
        (remove-duplicates
            (foldl append '()
                (map (lambda (x) (list (first x) (second x))) graph))))
(define total-stops-count (length total-stops))

(define from 'a)
(define to 'b)

(define (flatten1 l) (foldl append '() l))
(define (uflatten1 l) (remove-duplicates (flatten1 l)))

(define (get-adjacent-edges v)
  (filter (lambda (x) (or (eq? (first x) v) (eq? (second x) v))) graph))

(define (get-other e v)
  (if (eq? (first e) v)
      (second e)
      (first e)))

(define (filter-old-paths oldp new-adjs)
  (filter (lambda (x) (eq? (member x oldp) #f)) new-adjs))

(define (get-next-edges traversal)
  (let* ((last-v (last (second traversal)))
         (adjacents (get-adjacent-edges last-v))
         (ft (if (list? (first (first traversal))) (first traversal) (list (first traversal))))
         (new-adjs (filter-old-paths ft adjacents)))
    (if (null? new-adjs)
        (list traversal)
        (map (lambda (x) (list (append ft (list x))
                                         (append (second traversal) (list (get-other x last-v))))) new-adjs))))

(define (inital-traversal from)
  (let* ((adjacents (get-adjacent-edges from)))
    (map (lambda (x) (list x (list from (get-other x from)))) adjacents)))

(define (check-incompleteness traversal)
  (let* ((last-v (last (second traversal)))
        (adjacents-count (length (filter (lambda (x) (eq? (member (get-other x last-v) (second traversal)) #f)) (get-adjacent-edges last-v)))))
    (not (eq? adjacents-count 0))))

(define (get-all-paths from)
  (define (impl paths)
      (if (null? (filter check-incompleteness paths))
          paths
          (impl (flatten1 (map get-next-edges paths)))))
  (impl (inital-traversal from)))

(define (normalize-path path from)

  (define (do-normal p res)
    (if (null? p)
        res
        (do-normal (cdr p)
                   (append res
                           (if (eq? (second (last res)) (first (car p)))
                               (list (car p))
                               (list (list (second (car p))
                                                 (first (car p))
                                                 (third (car p)))))))))
    (if (<= (length path) 1)
        path
        (do-normal (cdr path) (if (eq? from (first (car path)))
                                  (list (car path))
                                  (list (list (second (car path))
                                              (first (car path))
                                              (third (car path))))))))

(define (stopAt path at)
  (define (impl path at res)
    (if (or (eq? (second (car path)) at)
            (eq? (first (car path)) at))
        (append res (list (car path)))
        (impl (cdr path) at (append res (list (car path))))))
  (impl path at '()))

(define (off-on? path)
  (define (impl p prev used-r)
    (if (null? p)
        #f
        (if (and (member (third (car p)) used-r)
                 (and (not (null? prev)) (not (eq? prev (third (car p))))))
            #t
            (impl (cdr p) (third (car p)) (append used-r (list (third (car p))))))))
  (trace impl)
  (impl path null '()))


(define (get-possible-paths from to)
  (filter (lambda (x) (not (off-on? x)))
  (map (lambda (x) (normalize-path x from))
    (remove-duplicates
      (map (lambda (x) (stopAt x to))
        (map first
          (filter (lambda (x) (and (member from (second x))
                                (member to (second x)))) (get-all-paths from))))))))

(fprintf (current-output-port)
       "~a\n\n"
       (string-join
         (map (lambda (z) (string-join z ""))
              (map (lambda (x) (map (lambda (y) (format "~s -> ~s by ~s\n" (first y) (second y) (third y))) x))
        (get-possible-paths 'm 'a))) "\n"))
