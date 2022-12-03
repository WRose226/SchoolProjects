#lang racket
;Wyatt Rose
;;;;;;;;;part1;;;;;;;;;;;;;;;;;
(displayln "Part 1")
;#1
(cons 1 (cons 2 (cons 3(cons 4 '()))))
;#2
(cons 1 (cons (cons 2 3) (cons 4 '())))
;#3
(cons 1 (cons 2 (cons (cons 3 (cons(cons 4 5)'()))'())))
;#4
(cons 1 (cons 2 (cons (cons 3 (cons 4 (cons 5 '()))) '())))
;#5
(cons (cons 1 2) (cons (cons 3 4) 5))

;;;;;;;;;part2;;;;;;;;;;;;;;;;;
(displayln "\nPart 2")
;#6
(cons 1 (cons 2 (cons 3 '())))
;#7
(cons 1 (cons 2 (cons 3 4)))
;#8
(cons 1 (cons 2 (cons (cons 3 4) (cons 5 6))))
;#9
(cons 1 (cons (cons '() 2) (cons 3 '())))
;#10
(cons (cons (cons 2 3) (cons 4 5)) (cons 6 7))

;;;;;;;;;part3;;;;;;;;;;;;;;;;;
(displayln "\nPart 3")
           
(define avg3(lambda (x y z) (/(+ x y z) 3)))
(avg3 2 5 7)

(define third-item(lambda (a b c . d) (displayln c)))
(third-item 1 2 7 4 5)