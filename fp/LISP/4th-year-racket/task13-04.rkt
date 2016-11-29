;; Регулярное выражение задается в следующей форме: если L1 и L2 — регуляр-
;; ные выражения, то выражения (+ L1 L2), (L1 L2), (* L1), (+ L1) представля-
;; ют соответственно объединение, конкатенацию, итерацию и положительную
;; итерацию исходных выражений. Описать функцию, получающую по регулярному
;;  выражению автоматную грамматику
#lang racket
(require racket/trace)

;; FSM definition

;; fsm format
;; (alphabet states transitions)
;; where
;; alphabet is ( (alphaName validChars) ... )
;; states is ( (starting #t #f) (s2 #f #f) (s3 #f #f) (final #f #t))
;; each state represented by (state-name is-starting is-final)
;; transitions is ( (state-name-from state-name-to  transition-by))
;; each FSM contains 2 default states (starting and final) and empty symbol eps

(define (alpha name allowed-chars) (list name allowed-chars))
(define (get-alpha-name alpha) (first alpha))
(define empty-symbol (alpha "eps" null))

(define (state name is-starting is-final) (list name is-starting is-final))
(define (state-ff name) (state name #f #f))

(define initial-state (state "begin" #t #f))
(define final-state (state "end" #f #t))

(define (get-state-name state) (first state))
(define (begin? state) (second state))
(define (end? state) (third state))

(define state-name-length 10)

(define (transition from-state to-state by-alpha) (list from-state to-state by-alpha))
(define (get-from t) (first t))
(define (get-to t) (second t))
(define (get-by t) (third t))


(define (make-fsm alphabet states transitions) (list alphabet states transitions))
(define (get-alphabet t) (first t))
(define (get-states t) (second t))
(define (get-transistions t) (third t))

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

(define (generate-simple-fsm my-alpha)
    (let* ((eps empty-symbol)
           (is initial-state)
           (fs final-state)
           (alphabet (list eps my-alpha))
           (post-is (state-ff (get-rnd-state-name)))
           (states (list is post-is fs))
           (transitions (list (transition is post-is my-alpha)
                              (transition post-is fs eps))))
          (make-fsm alphabet states transitions)))

(define (describe-fsm fsm)
    (fprintf (current-output-port)
             "alphabet: ~a\nstates: ~a\ntransitions:\n~a\n\n"
             (get-alphabet fsm)
             (get-states fsm)
             (string-join (map (lambda (x) (format "~s->~s by ~s"
                                                   (get-state-name (get-from x))
                                                   (get-state-name (get-to x))
                                                   (get-alpha-name (get-by x))))
                               (third fsm))
                          "\n")))

;; FSM Operations
(define (merge-list-unique a b) (remove-duplicates (append a b)))

(define (union fsm-a fsm-b)
    (make-fsm (merge-list-unique (get-alphabet fsm-a) (get-alphabet fsm-b))
              (merge-list-unique (get-states fsm-a) (get-states fsm-b))
              (merge-list-unique (get-transistions fsm-a) (get-transistions fsm-b))))

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

(define (iterate-transitions trans)
  (append trans
          (list (list initial-state final-state empty-symbol))
          (let* ((pre-final-states (get-pre-final-states trans))
                 (psa (get-post-start-state-and-alphas trans)))
              ; flatten cartesian product
              (map (lambda (x) (list (first x) (first (second x)) (second (second x))))
                (cartesian-product pre-final-states psa)))))

(define (positive-iterate-transitions trans)
  (append trans
          (let* ((pre-final-states (get-pre-final-states trans))
                 (psa (get-post-start-state-and-alphas trans)))
              ; flatten cartesian product
              (map (lambda (x) (list (first x) (first (second x)) (second (second x))))
                (cartesian-product pre-final-states psa)))))

(define (iterate fsm)
    (make-fsm (get-alphabet fsm)
              (get-states fsm)
              (iterate-transitions (get-transistions fsm))))

(define (positive-iterate fsm)
    (make-fsm (get-alphabet fsm)
              (get-states fsm)
              (positive-iterate-transitions (get-transistions fsm))))

(define (concat-transitions t-a t-b)
  (append (filter (lambda (x) (not (end? (get-to x)))) t-a)
          (filter (lambda (x) (not (begin? (get-from x)))) t-b)
    (let* ((pre-final-states (get-pre-final-states t-a))
           (psa (get-post-start-state-and-alphas t-b)))
           (map (lambda (x) (list (first x) (first (second x)) (second (second x))))
             (cartesian-product pre-final-states psa)))))

(define (concat fsm-a fsm-b)
    (make-fsm (merge-list-unique (get-alphabet fsm-a) (get-alphabet fsm-b))
              (merge-list-unique (get-states fsm-a) (get-states fsm-b))
              (concat-transitions (get-transistions fsm-a) (get-transistions fsm-b))))


(define (get-new-final-states transitions)
  (map get-state-name
    (map get-from
      (filter (lambda (x) (eq? (get-alpha-name (get-by x)) "eps")) transitions))))

(define (fsm-to-grammar fsm)
  (fprintf (current-output-port)
         "begin non-term: S\n,non-terms: S,~a\nterms: ~a\nproductions:\nS->begin\n~a\n~a\n"
         (string-join (map get-state-name (filter (lambda (x) (not (end? x))) (get-states fsm))) ",")
         (string-join (map get-alpha-name (filter (lambda (x) (not (eq? (get-alpha-name x) "eps"))) (get-alphabet fsm))) ",")
         (string-join (map (lambda (x) (format "~s->~s~s"
                                               (get-state-name (get-from x))
                                               (get-alpha-name (get-by x))
                                               (get-state-name (get-to x))))
                           (filter (lambda (x) (not(eq? (get-alpha-name (get-by x)) "eps"))) (get-transistions fsm)))
                      "\n")
        (string-join (map (lambda (x) (format "~s->eps" x)) (get-new-final-states (get-transistions fsm))) "\n")))

(define aFsm (generate-simple-fsm (alpha "myAlpha" '('a))))
(define bFsm (generate-simple-fsm (alpha "myBeta" '('b))))
(define cFsm (generate-simple-fsm (alpha "myCharlie" '('c))))
(define uFsm (union aFsm bFsm))

(describe-fsm aFsm)
(describe-fsm bFsm)
(describe-fsm cFsm)
(describe-fsm uFsm)
(describe-fsm (iterate uFsm))
(describe-fsm (iterate cFsm))
(define fFsm (concat (iterate uFsm) (iterate cFsm)))
(describe-fsm fFsm)
(fsm-to-grammar fFsm)
