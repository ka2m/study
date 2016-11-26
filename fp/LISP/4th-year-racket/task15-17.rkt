#lang racket
(require racket/trace)

(define routes (list (list 'a1 (list 'a 'b 'd))
                     (list 'a2 (list 'a 'c 'e 'f))
                     (list 'a3 (list 'd 'g 'h 'j))))

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

(define from 'a)
(define to 'b)

(define (backtrack-board)
  (map (lambda (x) (list x null))
    (remove-duplicates
      (apply append
        (map (lambda (x) (list (first x) (second x))) graph)))))

(define (set-parent board child parent by)
  (define (impl board res)
    (if (null? board)
      res
      (if (eq? (caar board) child)
          (impl (cdr board) (append res (list (list child (list parent by)))))
          (impl (cdr board) (append res (list (car board)))))))
  (impl board '()))

(define (get-parent board child)
  (let ((r (filter (lambda (x) (eq? (car x) child)) board)))
    (if (null? r) null (cadar r))))

(define (update-board board new-children parent)
  (define (impl children res)
    (if (null? children)
      res
      (impl (cdr children)
            (set-parent res
                        (first (car children))
                        parent
                        (second (car children))
                        ))))
  (impl new-children board))

(define (get-adjacent el)
  (append
    (map (lambda (x) (list (second x) (third x)))
            (filter (lambda (x) (eq? (first x) el)) graph))
          (map (lambda (x) (list (first x) (third x)))
            (filter (lambda (x) (eq? (second x) el)) graph))))

(define (bfs start)
  (define (bfs-impl queue board)
      (if (null? queue)
          board
          (let* ((elem (last queue))
                 (drop-q (drop-right queue 1))
                 (adj (get-adjacent elem))
                 (q-tail (filter (lambda (x) (null? (get-parent board x)))
                            (map first adj))))
            (if (null? q-tail)
                (bfs-impl drop-q board)
                (bfs-impl (append drop-q q-tail)
                          (update-board board
                                        (filter (lambda (x) (or (member (first x) q-tail)
                                                                (member (second x) q-tail)))
                                                adj)
                                         elem))))))
  (bfs-impl (list start) (set-parent (backtrack-board) start 'root null)))

(define (restore board start finish)
  (define (build-path cur res)
    (let ((parent (get-parent board (first cur))))
      (if (eq? (first parent) 'root)
          res
          (build-path parent (append res (list parent))))))
  (build-path (list start null) (list (list start null))))


(define (minify path)
  (define (do-min path stop-buf r-name res)
    (if (null? path)
        (append res (list (list stop-buf r-name)))
        (let* ((itm (car path)) (rest (cdr path)) (rr (second itm)))
          (if (or (null? r-name) (null? rr) (eq? rr r-name))
            (do-min rest
                    (append stop-buf (list (first itm)))
                    rr
                    res)
            (do-min rest
                    (list (last stop-buf) (first itm))
                    rr
                    (append res (list (list stop-buf r-name))))))))
  (do-min path '() null '()))

(define (create-path from to)
  (minify (restore (bfs to) from to)))

(create-path 'j 'f)
