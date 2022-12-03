#lang racket
;Wyatt Rose;

(define faces '(2 3 4 5 6 7 8 9 10 J Q K A))
(define suits '(♣ ♦ ♥ ♤))
(define playerHand(list))
(define dealerHand(list))

;make-card - parameter 1: face
;          - parameter 2: suit
;    returns - cons of face and suit
(define make-card
    (lambda (face suit)
        (cons face suit)
    )  
)


;make-deck - no params
;    returns - list of cards
;    depends on global definitions of faces and suits
(define make-deck
    [let loop1 ((suit 0) (deck(list)))
        ;if suit = suits length, return deck list
        (if (equal? suit (length suits))
            ;then
            deck
            ;else - loop2
        [let loop2 ((face 0))
          ;if face < face length, 
          (if (< face (length faces))
              ;then - make-card then increment face
              [begin
                (set! deck(append deck (list(make-card (list-ref faces face) (list-ref suits suit)))))
                (loop2 (+ face 1))]
                ;else - call loop1, increment suit
              [begin
                (set! face 0)
                (loop1 (+ suit 1) deck)])
])])


(define theDeck make-deck)


;deal! - parameter: deck
;    returns - new two card hand,
;              consists of first 2 cards in deck
;    cards must be removed from deck
(define (deal! deck)
    (let ([hand(list)])
        (set! hand(append hand (list(car deck)) (list(second deck))))
        (set! theDeck(remove (car deck) theDeck))
        (set! theDeck(remove (second deck) theDeck))
      hand)
)


;eval-hand - parameter: hand (list of cards)
;    returns - best possible value of hand
(define (eval-hand hand)
  (let* ([value 0]
         [aceCtr 0]
         [numAdd (lambda (x) (when (number? (car x))
                               (set! value(+ (car x) value))))]
         [faceAdd (lambda (x)
                   (when (and (symbol? (car x)) (not (equal? (car x) 'A)))
                     (set! value (+ 10 value))))]
         [aceAdd (lambda (x)
                     (when (and (symbol? (car x)) (equal? (car x) 'A))
                       (begin
                         (set! value (+ 1 value))
                       (set! aceCtr (+ 1 aceCtr)))))]
         )

    ;add card values to value
    (for-each numAdd hand)
    (for-each faceAdd hand)
    (for-each aceAdd hand)

    ;return value if over 21
    (when (> value 21)
        value)

    ;add 10 to value per ace if value won't bust
    [let aceLoop ()
      (if (> aceCtr 0)
          ;then
          (if (> (+ value 10) 21)
              ;then
              value
              ;else
              (begin
                (set! value(+ 10 value))
                (set! aceCtr(- aceCtr 1))
                (aceLoop)))
          ;else
          value)]
))
    

;hit! - parameter 1: the deck to deal from
;     - parameter 2: the hand to deal to
;     takes top card from deck & adds to hand
;  returns - nothing
(define hit! (lambda (deck hand)
    (if (equal? hand playerHand)
        ;then - give card to playerHand
        (set! playerHand(append hand (list(car deck))))
        ;else - give card to dealerHand
        (set! dealerHand(append hand (list(car deck)))))
    ;remove card from deck  
    (set! theDeck(remove (car deck) theDeck))
               ))
    

;show-hand - parameter 1: hand to display
;          - parameter 2: 'full or 'part
;                         if part, dont show first card
;          - parameter 3: string to be displayed before the hand
;  returns - nothing
;  displays hand to screen
(define show-hand (lambda (hand how description)
    (displayln description)
    (if (equal? how 'full)
        ;then
        [begin
        (for-each display hand)
        (display "\n")
        (display "\n")]
        ;else
        [begin
        (display "***** ")
        (for-each display (cdr hand))
        (display "\n")
        (display "\n")])
))


(define start-game
  (let gameLoop ()
    
    ;Make sure there are enough cards in the deck
    (when (< (length theDeck) 10)
      (begin
        (displayln "Re-shuffling cards back into deck!")
      (set! theDeck make-deck)))
    
  ;Shuffle deck
  (set! theDeck(shuffle theDeck))
    
  ;Deal 2 cards to dealer & player
  (set! playerHand (deal! theDeck))
  (set! dealerHand (deal! theDeck))  
    
    ;Show partial dealer hand
    (show-hand dealerHand 'part "Dealer's Hand:")
    (show-hand playerHand 'full "Player's Hand:")

    
    ;Test for blackjack
    (if (not (equal? (eval-hand playerHand) 21))
        ;Then - no blackjack, receive user input and evaluate
        (let playerLoop ([userAnswer 'null])
          
        ;Ask player to hit or stand
        (display "Would you like to hit or stand? H/S: ")
        (set! userAnswer (read-line (current-input-port) 'any))
        (display "\n")

        ;If H, hit! and call playerLoop. Else, continue to dealerLoop
        (when (string-ci=? userAnswer "H")
            (begin
              (hit! theDeck playerHand)
              (displayln "Hit!")
              (sleep 1)
              (show-hand playerHand 'full "Player's Hand:")

   
          ;Test for bust and blackjack
          (cond
            ;Test for bust
            [(> (eval-hand playerHand) 21)
             (begin (displayln "BUST!: Dealer Wins!")
                    (sleep 2)
                    (displayln "\n")
                    (displayln "Play Again!")
                    (displayln "~~~~~~~~~~~~~~~~~~~~")
                    (sleep 1)
                    (gameLoop))]
            ;Test for BlackJack
            [(equal? (eval-hand playerHand) 21)
             (begin (displayln "BlackJack!: Dealer's turn!")
                    (sleep 1)
                    (displayln "Play Again!")
                    (displayln "\n")
                    (gameLoop))]
            ;Call loop
            [(< (eval-hand playerHand) 21)
             (playerLoop userAnswer)])
          ));end when
        );end let & then
    ;else
    (displayln "BlackJack!: Dealer's turn!"));end if

    (displayln "dealer's turn!")
    (displayln "\n")

    
    (let dealerLoop ()
       
       ;show dealer's hand
       (show-hand dealerHand 'full "Dealer's Hand:")

       ;If dealerHand is <17, dealer hits!, else dealer stands
      (when (< (eval-hand dealerHand) 17)
        (begin
          (displayln "Dealer Hits!")
          (sleep 1)
          (hit! theDeck dealerHand)
          (dealerLoop)))

      ;Test for dealer bust
      (when (> (eval-hand dealerHand) 21)
        (begin (displayln "BUST!: Player Wins!")
                    (sleep 2)
                    (displayln "\n")
                    (displayln "Play Again!")
                    (displayln "~~~~~~~~~~~~~~~~~~~~")
                    (sleep 1)
                    (gameLoop)))

      ;if dealer's hand is greater
       (when (> (eval-hand dealerHand) (eval-hand playerHand))
         (begin (displayln "Dealer Wins!")
         (sleep 2)
         (displayln "\n")
         (displayln "Play Again!")
         (displayln "~~~~~~~~~~~~~~~~~~~~")
         (sleep 1)
         (gameLoop)))
       
       ;If player hand is still higher, player wins
      (cond [(< (eval-hand dealerHand) (eval-hand playerHand))
             ((begin (displayln "Player Wins!")
                    (sleep 2)
                    (displayln "\n")
                    (displayln "Play Again!")
                    (displayln "~~~~~~~~~~~~~~~~~~~~")
                    (sleep 1)
                    (gameLoop)))]
       )
            
       ;If tie, draw.
            (displayln "It's a Draw!")
            (sleep 2)
            (displayln "\n")
            (displayln "Play Again!")
            (displayln "~~~~~~~~~~~~~~~~~~~~")
            (gameLoop)
     );end dealerLoop
))
  
start-game
