;; Регулярное выражение задается в следующей форме: если L1 и L2 — регуляр-
;; ные выражения, то выражения (+ L1 L2), (L1 L2), (* L1), (+ L1) представля-
;; ют соответственно объединение, конкатенацию, итерацию и положительную
;; итерацию исходных выражений. Описать функцию, получающую по регулярному
;;  выражению автоматную грамматику
#lang racket
(require racket/trace)

(define ns (variable-reference->namespace (#%variable-reference)))
;; FSM entities
;; STATES
(define (state name is-starting is-final) (list name is-starting is-final))
(define (state-ff name) (state name #f #f))

(define state-name-length 5)
(define initial-state (state "BEGIN" #t #f))
(define final-state (state "END" #f #t))

(define (get-state-name state) (first state))
(define (begin? state) (second state))
(define (end? state) (third state))

(define (random-string a b n)
  (let* ([aint (char->integer a)]
         [lint (- (char->integer b) aint)])
    (define (iter i rez)
      (if (= i n) rez
          (iter (+ i 1) (append
                         rez
                         (list (integer->char (+ (random lint) aint)))))))
    (list->string (iter 0 '()))))

(define (get-rnd-state-name) (random-string #\A #\Z state-name-length))

;; TRANSITION (actually the only fsm definition we preserve)
(define (transition from-state to-state by-alpha) (list from-state to-state by-alpha))
(define (get-from t) (first t))
(define (get-to t) (second t))
(define (get-by t) (third t))

;; FSM Operations
;; Create new one, simple, with one alpha
(define (simplefsm my-alpha)
    (let* ((is initial-state)
           (fs final-state)
           (post-is (state-ff (get-rnd-state-name))))
       (list (transition is post-is my-alpha)
             (transition post-is fs 'eps))))

;; Utility to merge two lists
(define (merge-list-unique a b) (remove-duplicates (append a b)))

(define (unite fsm-a fsm-b) (merge-list-unique fsm-a fsm-b))

(define (get-pre-final-states transitions)
   (map (lambda (x) (get-from x))
        (filter (lambda (x) (end? (get-to x))) transitions)))

(define (get-post-start-states transitions)
   (map (lambda (x) (get-to x))
     (filter (lambda (x) (begin? (get-from x))) transitions)))

(define (get-post-start-state-and-alphas transitions)
         (map (lambda (x) (list (get-to x) (get-by x)))
           (filter (lambda (x) (begin? (get-from x))) transitions)))

(define (cartesian-product . lists)
 (foldr (lambda (a b)
          (append-map (compose1 (curryr map b) (curry cons))
                      a))
        '(())
        lists))

(define (iterate trans)
 (append trans
         (list (transition initial-state final-state 'eps))
         (let* ((pre-final-states (get-pre-final-states trans))
                (psa (get-post-start-state-and-alphas trans)))
             ; flatten cartesian product
             (map (lambda (x) (list (first x) (first (second x)) (second (second x))))
               (cartesian-product pre-final-states psa)))))

(define (piterate trans)
 (append trans
         (let* ((pre-final-states (get-pre-final-states trans))
                (psa (get-post-start-state-and-alphas trans)))
             ; flatten cartesian product
             (map (lambda (x) (list (first x) (first (second x)) (second (second x))))
               (cartesian-product pre-final-states psa)))))

(define (concat t-a t-b)
  (append (filter (lambda (x) (not (end? (get-to x)))) t-a)
          (filter (lambda (x) (not (begin? (get-from x)))) t-b)
    (let* ((pre-final-states (get-pre-final-states t-a))
           (psa (get-post-start-state-and-alphas t-b)))
           (map (lambda (x) (list (first x) (first (second x)) (second (second x))))
             (cartesian-product pre-final-states psa)))))

(define (eliminite-eps fsm)
  (let* ((new-finals (map get-state-name
                        (map get-from
                          (filter (lambda (x) (and (eq? (get-state-name (get-to x)) "END")
                                              (eq? (get-by x) 'eps))) fsm))))
         (shrinked-trans (filter (lambda (x) (not (eq? (get-state-name (get-to x)) "END"))) fsm)))
   (map (lambda (x) (if (not (member (get-state-name (get-from x)) new-finals))
                        x
                        (transition (state (get-state-name (get-from x))
                                           (begin? (get-from x))
                                           #t)
                                    (get-to x)
                                    (get-by x))))
      (map (lambda (x) (if (not (member (get-state-name (get-to x)) new-finals))
                           x
                           (transition (get-from x)
                                       (state (get-state-name (get-to x))
                                              (begin? (get-to x))
                                              #t)
                                        (get-by x))))
                        shrinked-trans))))

(define (describe-fsm fsm)
   (fprintf (current-output-port)
            "transitions:\n~a\n"
            (string-join (map (lambda (x) (format "~s->~s by ~s"
                                                  (get-state-name (get-from x))
                                                  (get-state-name (get-to x))
                                                  (get-by x)))
                              fsm)
                         "\n")))

(define (regex->fsm reg)
    (define (proc rest fsm)
        (if (null? rest)
            fsm
            (let ((symbol (car rest))
                  (rr (cdr rest)))
              (cond
                ((eq? symbol '+) (proc rr (append fsm (list 'unite))))
                ((eq? symbol '*) (proc rr (append fsm (list 'iterate))))
                ((eq? symbol '?) (proc rr (append fsm (list 'piterate))))
                ((list? symbol)
                  (if (null? fsm)
                        (proc rr
                              (append fsm
                                      (list 'concat
                                            (proc symbol '()))))
                        (proc rr
                              (append fsm
                                      (list (proc symbol '()))))))
                (else
                  (if (null? fsm)
                          (proc rr
                                (append fsm
                                        (list 'concat
                                              (list 'simplefsm symbol))))
                          (proc rr
                                (append fsm
                                        (list (list 'simplefsm symbol))))))))))
  ;(trace proc)
   (proc reg '()))


(define (process-char cur ch rfsm)
  (map get-to
    (filter (lambda (x) (let* ((f (get-state-name (get-from x)))
                               (a (get-by x)))
                            (and (eq? cur f) (eq? ch a) ))) rfsm)))

(define (begin-final? rfsm)
  (not
    (null?
      (filter (lambda (x) (and (begin? x) (end? x)))
        (remove-duplicates (append (map get-from rfsm) (map get-to rfsm)))))))

(define (get-begin-states rfsm)
  (remove-duplicates
    (map get-state-name
      (map get-from
        (filter (lambda (x) (begin? (get-from x))) rfsm)))))

(define (flatten1 l) (foldl append '() l))

(define (check-string str rfsm)
  (define (go-thru rest cur-states idx cnt valid?)
    (if (null? rest)
        (list valid? cnt)
        (let* ((next (car rest))
               (new-states
                 (remove-duplicates
                   (flatten1 (map (lambda (x) (process-char x next rfsm)) cur-states))))
               (only-names (map get-state-name new-states)))
          (if (null? (filter end? new-states))
              (go-thru (cdr rest) only-names (+ idx 1) cnt valid?)
              (go-thru (cdr rest) only-names (+ idx 1) (+ idx 1) #t)))))
    (go-thru (string->list str) (get-begin-states rfsm) 0 0 (begin-final? rfsm)))

(define (collect-nonterminals rfsm)
  (remove-duplicates (map get-state-name
                          (append (map get-from rfsm) (map get-to rfsm)))))

(define (get-terminals rfsm)
  (string-join (map (lambda (x) (string x #\ )) (remove-duplicates (map get-by rfsm))) ""))

(define (get-rules rfsm)
  (filter (lambda (rrr) (not (null? rrr)))
    (map
      (lambda (nt) (let ((aRule (string-join
                                  (map (lambda (y) (format "~a ~a" (get-by y) (get-state-name (get-to y))))
                                    (filter (lambda (x) (eq? (get-state-name (get-from x)) nt))
                                        rfsm)) "|")))
                  (if (eq? (string-length aRule) 0)
                      null
                      (format "~a->~a" nt aRule))))
       (collect-nonterminals pregex))))

(define (get-final-rules rfsm)
  (map (lambda (x) (format "~a->eps" (get-state-name x)))
    (filter end?
      (remove-duplicates (append (map get-from rfsm) (map get-to rfsm))))))

(define (describe-grammar rfsm)
  (fprintf (current-output-port)
    "Terminals: ~a\nNon-Terminals:~a\nProductions:~a\n~a\nStartSymbol:BEGIN\n"
    (get-terminals rfsm)
    (string-join (collect-nonterminals rfsm) " ")
    (string-join (get-rules rfsm) "\n")
    (string-join (get-final-rules rfsm) "\n")))


;; (a|b)c
;(define pregex (eliminite-eps (eval (regex->fsm '((+ #\a #\b) #\c)) ns)))
;(print pregex)
;(describe-fsm pregex)
;(check-string "ac" pregex)

;; ((00|11)* ( (01|10) (00|11)* (01|10) (00|11)*)*)
(define rfsm
  (regex->fsm
  '(  (* (+ (#\0 #\0) (#\1 #\1)))
      (* (((
            (+ (#\0 #\1) (#\1 #\0))
            (* (+ (#\0 #\0) (#\1 #\1))))
          (+ (#\0 #\1) (#\1 #\0)))
         (* (+ (#\0 #\0) (#\1 #\1)))))) ))

(define pregex (eliminite-eps (eval rfsm ns)))
;(get-rules pregex)
(describe-grammar pregex)

;(check-string "010101" pregex)
