# C++-Hangman
Plays a random game of Hangman using a CLI (command line interface).
The program picks from a selection of 30 or so random words and chooses that as the target of play.

<img width="491" height="214" alt="image" src="https://github.com/user-attachments/assets/8bf9b8e8-6173-4bcd-9f4e-95540a9ed7fc" />
<img width="491" height="214" alt="image" src="https://github.com/user-attachments/assets/d4dadf32-63ea-4139-aaa8-8353eeea8c1b" />
<img width="491" height="214" alt="image" src="https://github.com/user-attachments/assets/f6de64b9-f08e-48b5-aba3-9dd3fc433cd6" />



## Controls
The user may input any ASCII-supported character.

## Compiling
The game is compiled via normal means (g++ worked fine). 

## Future Goals
1. I'd like to implement a user-inputted word mode, where the user may type the word, and another player can play.
2. I want to implement a 20-50-step visual progression for the titular Hang Man, and have its progression scale based on how many guessed you get.
3. I'd also like the number of guesses to change based on the length of the word. I imagine this formula would be quadratic, because it gets easier to guess letters if there are more in the word.
