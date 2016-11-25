#lang racket
(require racket/trace)

(define (position x y) (list x y))
(define (get-x pos) (first pos))
(define (get-y pos) (second pos))

(define (equals? p1 p2)
  (eq? (and (eq? (get-x p1) (get-x p2))
            (eq? (get-y p1) (get-y p2)))
       #t))

(define starting-position (position 0 0))
(define x-dim 8)
(define y-dim 8)
(define max-visited (* x-dim y-dim))

(define possible-moves (list (position 2 1)
                             (position 2 -1)
                             (position -2 1)
                             (position -2 -1)
                             (position 1 2)
                             (position -1 2)
                             (position 1 -2)
                             (position -1 -2)))

(define (make-move from to)
    (position (+ (get-x from) (get-x to)) (+ (get-y from) (get-y to))))

(define (filter-valid-moves moves x-dim y-dim)
    (filter
        (lambda (m) (and (and (>= (get-x m) 0) (>= (get-y m) 0))
                         (and (< (get-x m) x-dim) (< (get-y m) y-dim))))
        moves))

(define (filter-visited moves visited)
    (filter
        (lambda (p) (not (member p visited)))
        moves))

(define (get-new-pos for-position)
    (define (impl ip pm res)
        (if (null? pm)
            res
            (impl ip (cdr pm) (cons (make-move ip (car pm)) res))))
    (filter-valid-moves (impl for-position possible-moves '())
                        x-dim
                        y-dim))

(define (next-pos for-position visited)
    (filter-visited (get-new-pos for-position)
                    (append (list for-position) visited)))

(define (find-best-min l)
    (define (impl l res)
      (if (null? l)
          res
          (impl (cdr l)
                (if (< (car l) res)
                    (car l)
                    res))))
    (if (null? l) 0 (impl l max-visited)))

(define (get-best-onward candidate-list visited)
    (let* ((cl (map (lambda (x) (let ((np (next-pos x visited))) (list x (length np)))) candidate-list))
           (min-lng (find-best-min (map second (filter (lambda (x) (> (second x) 0)) cl))))
          ;(min-lng (find-best-min (map second cl)))
           (res (filter (lambda (x) (eq? min-lng (second x))) cl)))
          (if (null? res) null (caar res))))

(define (forward start)
    (define (impl visited cur-pos)
        (let* ((cands (next-pos cur-pos visited))
               (best (get-best-onward cands visited)))
               (if (null? best)
                   visited
                   (impl (append visited (list best)) best))))
    (impl (list start) start))

(define (backtrack-board)
  (define (impl x y res)
      (if (< x 0)
          res
          (if (eq? y 0)
              (impl (- x 1) (- y-dim 1) (append res (list (list (position x y)
                                                       null))))
              (impl x (- y 1) (append res (list (list (position x y)
                                                       null)))))))
  (impl (- x-dim 1) (- y-dim 1) '()))

(define all-pos (map first (backtrack-board)))

(define (set-parent board child parent)
  (define (impl board res)
    (if (null? board)
      res
      (if (equals? (caar board) child)
          (impl (cdr board) (append res (list (list child parent))))
          (impl (cdr board) (append res (list (car board)))))))
  (impl board '()))

(define (get-parent board child)
  (let ((r (filter (lambda (x) (equals? (car x) child)) board)))
    (if (null? r) null (cadar r))))

(define (update-board board new-children parent)
  (define (impl children res)
    (if (null? children)
      res
      (impl (cdr children) (set-parent res (car children) parent))))
  (impl new-children board))

(define (bfs start)
    (define (bfs-impl queue board)
        (if (null? queue)
            board
            (let* ((el (last queue))
                   (nq (drop-right queue 1))
                   (nw (get-new-pos el))
                   (aq (filter (lambda (x) (null? (get-parent board x))) nw)))
              (if (null? aq)
                  (bfs-impl nq board)
                  (bfs-impl (append nq aq)
                            (update-board board aq el))))))
    (bfs-impl (list start) (backtrack-board)))

(define (restore board start finish)
  (define (do-restore cur res)
    (let ((parent (get-parent board cur)))
    (if (equals? parent finish)
      (append res (list finish))
      (do-restore parent (append res (list parent))))))
  (do-restore start '()))

(define (create-path from to)
  (restore (bfs to) from to))

(define (add-missing missing-pos from)
  (define (impl fw from res)
    (if (null? fw)
        res
        (let* ((next (car fw))
               (extra (create-path from next))
               (new-from (last extra)))
          (impl (cdr fw) new-from (append res extra)))))
  (impl missing-pos from '()))

(define (task)
  (let* ((forward-results (forward starting-position))
         (missing-pos (filter (lambda (x) (not (member x forward-results))) all-pos)))
    (if (null? missing-pos)
        (append forward-results
                (create-path (last forward-results) starting-position))
        (let* ((extra (add-missing missing-pos (last forward-results)))
               (home (create-path (last extra) starting-position)))
              (append forward-results extra home)))))

(task)
(length (remove-duplicates (task)))
