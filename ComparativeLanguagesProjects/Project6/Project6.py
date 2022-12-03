"""
Wyatt Rose
Project 6: Hangman
Python script that inputs wordlist.txt to play Hangman
"""

import random
from os.path import exists
import sys

# GLOBAL VARIABLES #
# stores word dictionary
wordDict = dict()

"""
createDict: 
"""


def createDict():

    # Check if Wordlist is not present
    if not exists("wordlist.txt"):
        sys.exit("Wordlist not found!")

    # read file into dictionary hash, then close
    with open("wordlist.txt") as f:
        for line in f:
            # format word
            line = line.strip()
            line = line.lower()
            length = len(line)
            # if length not in wordDict, add list
            if length not in wordDict:
                wordDict[length] = [line]
            else:
                # add word to appropriate list
                wordDict[length].append(line)


"""
startGame: runs the main logic for the game; collects and responds to 
           user inputs
"""


def startGame():
    # gather user input
    maxLength = max(wordDict.keys())

    print("Welcome to Hangman")
    print(f"What length word would you like to play? (3 to {maxLength}) ==> ", end=" ")
        

    # select word from dictionary based on user length
    wordLength = input()

    # handle erroneous input from user
    try:
        wordLength = int(wordLength)
    except:
        print("Invalid input. Restarting...")
        print()
        startGame()

    # If wordLength not in wordDict, restart game
    if wordDict.get(wordLength) == None:
        print(f"Sorry, word length {wordLength} doesn't exist. Try again")
        print()
        startGame()

    # choose random word with wordLength, pull word from array
    randomWord = random.choices(wordDict[wordLength], k=1)
    randomWord = randomWord[0]

    guessNum = 2 * wordLength - 1
    guessed = []
    # loop to collect user input and check guesses
    while True:
        print()

        # check if word was guessed by single letter guess
        wordGuessed = True
        for i in range(wordLength):
            if randomWord[i] not in guessed:
                wordGuessed = False

        if wordGuessed == True:
            print("Congratulations, you guessed it!")
            print("Game over.")
            playAgain()

        # if out of guesses, exit loop
        if guessNum == 0:
            print("You didn't guess the word.")
            print("Game over.")
            playAgain()

        # print word with only revealed letters
        print("Word: ", end=" ")
        for i in range(wordLength):
            if randomWord[i] in guessed:
                print(f"{randomWord[i]}", end="")
            else:
                print("*", end="")
        print()

        print(f"You have {guessNum} guesses remaining.")
        print("Type a letter or word guess: ", end=" ")

        # receive guess from user
        guess = input()
        guessLen = len(guess)
        letterCnt = 0

        # logic to handle user guess:
        # single letter guess
        if guessLen == 1:
            if guess in guessed:
                print(f"You guessed {guess} before!")
                continue
            elif guess in randomWord:
                for i in randomWord:
                    if guess == i:
                        letterCnt += 1
                if letterCnt == 1:
                    print(f"There is 1 {guess}!")
                if letterCnt > 1:
                    print(f"There are {letterCnt} {guess}'s!")
                guessNum -= 1
                guessed.append(guess)
                continue
            else:
                print(f"Sorry, there are no {guess}'s.")
                guessNum -= 1
                guessed.append(guess)
                continue

        # invalid guesses; re-prompt
        elif guessLen == 2 or guessLen > wordLength:
            print("Invalid guess. Try again")
            continue

        # word guess
        elif guessLen >= 3:
            if guess == randomWord:
                print("Congratulations, you guessed it!")
                print("Game over.")
                playAgain()
            else:
                guessNum -= 1
                print(f"Sorry, the word is not {guess}")
                continue


"""
playAgain: prompts the user to play another game; collects user response
"""


def playAgain():

    # receive and format input from user
    print("Would you like to play again? (y/n): ", end=" ")
    choice = input()
    choice = choice.strip()
    choice = choice.lower()

    # decide what to do with user input
    if choice == "y":
        print("Play again!")
        print()
        startGame()
    elif choice == 'n':
        sys.exit("Game exiting...")
    else:
        print("Invalid input")
        playAgain()


createDict()
startGame()
