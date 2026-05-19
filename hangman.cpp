/**
 * Author: Jason Miller
 * Function: A game of hangman, using a CLI. Picks from a list of random words
 * and prompts user input to guess a letter or space.
 * Date: 18 May 2026
 */

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

class PlayerData {
    private:
        //This is where we will store all guessed letters the user inputs.
        //Sets the last value to a null character for comparison purposes.
        //In hindsight, it would have been a lot easier to keep this in the public scope.
        std::vector<char> guessedLetters = {'\0'}; 
    public:
        //this variable keeps track of the remaining failures
        int remainingFails;

        //This function checks if the inputted guess is in your list of guesses.
        //If so, it doesn't do anything. Otherwise, it inserts it.
        bool checkIfInList(char guess) {
            //checks if the guess is already in the list
            //if it can't find it, find returns the null character at the end
            if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
                //if it's already in the list, it returns an error.
                return true;
            } else {
                //otherwise, it inserts it and returns 0
                return false;
            }
        }

        //This function goes through each character in the word and checks if you've guessed it.
        //If you did, it reveals it. Otherwise, it keeps it hidden via '_'
        std::string makeHintVisual(std::string theWord) {
            std::string workingLine = ""; 
            for (int i = 0; i < theWord.size(); i++) {
                //checks if the character at the current index is in the guessedLetters vector
                if (find(guessedLetters.begin(), guessedLetters.end(), theWord.at(i)) != guessedLetters.end()) {
                    //If it's in the vector, it prints the character
                    workingLine.push_back(theWord.at(i));
                } else {
                    //otherwise, it prints an underscore
                    workingLine.push_back('_');
                }
            }
            return workingLine;
        }

        //This function checks if every character in the word is in your list of guessed characters.
        //It does this by checking if the visual hint is equal to the word.
        bool checkIfWon(std::string theWord) {
            if (makeHintVisual(theWord) == theWord) {
                return true;
            } else {
                return false;
            }
        }

        //Creates a string of previously guessed letters.
        std::string printGuessedLetters() {
            std::string letterList = "";
            for (char x : guessedLetters) {
                letterList.push_back(x);
                letterList.append(", ");
            }
            letterList.erase((letterList.size() - 3), letterList.size()); //erases the last 3 characters for void and off by 1
            return letterList;
        }

        //Takes your guess (which has already been validated) and inserts it into the private list.
        int insertGuess(char guess) {
            guessedLetters.insert(guessedLetters.begin(), guess);
            return 0;
        }
};

//Prints a little visualizer for the amount of fails left. 
//There are 6 states, including a losing state.
void printAscii(PlayerData game) {
    switch(game.remainingFails) {
        case 6:
            std::cout <<
            "  +---+\n"
            "  |   |\n"
            "      |\n"
            "      |\n"
            "      |\n"
            "      |\n"
            "=========\n";
            break;
        case 5:
            std::cout <<
            "  +---+\n"
            "  |   |\n"
            "  0   |\n"
            "      |\n"
            "      |\n"
            "      |\n"
            "=========\n";
            break;
        case 4:
            std::cout <<
            "  +---+\n"
            "  |   |\n"
            "  0   |\n"
            "  |   |\n"
            "      |\n"
            "      |\n"
            "=========\n";
            break;
        case 3:
            std::cout <<
            "  +---+\n"
            "  |   |\n"
            "  0   |\n"
            " /|   |\n"
            "      |\n"
            "      |\n"
            "=========\n";
            break;
        case 2:
            std::cout <<
            "  +---+\n"
            "  |   |\n"
            "  0   |\n"
            " /|\\  |\n"
            "      |\n"
            "      |\n"
            "=========\n";
            break;
        case 1:
            std::cout <<
            "  +---+\n"
            "  |   |\n"
            "  0   |\n"
            " /|\\  |\n" //escape escape
            " /    |\n"
            "      |\n"
            "=========\n";
            break;
        case 0:
            std::cout <<
            "  +---+\n"
            "  |   |\n"
            "  0   |\n"
            " /|\\  |\n"
            " / \\  |\n"
            "      |\n"
            "=========\n";
            break;
    }
}

//Clears the screen and prints all visual menu elements.
void printMenu(PlayerData game, std::string theWord) {
    std::cout << "\x1b[2J\x1b[H" //Clears the terminal screen
        "Welcome to Hangman!" << std::endl;
    printAscii(game);
    std::cout << '\n';
    std::cout << game.makeHintVisual(theWord) << std::endl;
    std::cout << "Guessed Letters: " << game.printGuessedLetters() << std::endl;
}

//picks a random word from this list of words
std::string pickRandomWord() {
    std::srand(time(nullptr));
    std::string listOfWords[] = {
        "bodies", "blood", "farewell", "goodbye", "corpse", "the beatles",
        "severed", "goodnight", "murder", "homicide", "artery", "vein",
        "decapitated", "combust", "knife", "revolver", "arson", "tax evasion",
        "death sentence", "unwell", "bad", "pulverize", "blend", "death",
        "uneasy", "watching", "pneumonoultramicroscopicsilicovolcanoconiosis",
        "eyeball", "innards", "epidermis", "ambulance", "investigation", "surgery",};
    int arraySize = sizeof(listOfWords) / sizeof(listOfWords[0]); //gets the actual size of the array
    int randomWordIndex = (std::rand() % arraySize); // picks a random word from the above list
    return listOfWords[randomWordIndex];
}

//Takes input and validates it for char.
//Then, if it's valid, it checks if you've already guessed it.
//If not, then it adds it to the list of guessed characters and returns the guess.
char inputAndValidateGuess(PlayerData& game) {
    //validates for string with size 1
    std::string userInput = "";
    while (true) {
        if (!std::getline(std::cin, userInput)) {
            std::cin.clear();
            std::cout << "Input error! Guess again: ";
            continue;
        }
        if (userInput.length() != 1) {
            std::cout << "Invalid input! Guess again: ";
            continue;
        }
        break;
    }
    
    //converts uppercase letters to lowercase letters
    for (char &c : userInput) {
        if (c >= 'A' && c <= 'Z') {
          	// adds 32 to the ascii value
            c += 32;
        }
    }

    //then, it checks if that has already been inputted
    if (game.checkIfInList(userInput.at(0)) == 1) { //must do at first index because it is string
        std::cout << "You've already guessed that! Guess again: ";
        return inputAndValidateGuess(game);
    } else {
        return userInput.at(0);
    }
}

int main() {
    PlayerData game;
    const std::string theWord = pickRandomWord();
    game.remainingFails = 6;

    //Runs this while the win condition is false, and while remainingFails is positive.
    while ((game.checkIfWon(theWord) == false) && game.remainingFails > 0) {
        printMenu(game, theWord);
        std::cout << "Guess a letter (spaces count): ";
        char guess = inputAndValidateGuess(game);
        game.insertGuess(guess);

        bool inWord = false;
        //goes through every character in the word and checks if it's in the list
        for (int i = 0; i < theWord.size(); i++) {
            std::cout << theWord.at(i) << " " << guess << std::endl;
            if (theWord.at(i) == guess) {
                std::cout << "It's in the word!" << std::endl;
                inWord = true;
                break;
            } 
        }
        if (inWord == 0) {
            game.remainingFails -= 1;
        }
    }

    //This is the game end state. It prints the menu again and tells the user if they won or lost.
    printMenu(game, theWord);
    if (game.remainingFails == 0) {
        std::cout << "Womp womp, you lost!\n" 
            << "The word was: " << theWord << std::endl;
    } else {
        std::cout << "You won!" << std::endl;
    }


    //asks if the user wants to go again
    std::string userExit;
    std::cout << "Go again? [y/n]: ";
    getline(std::cin, userExit);
    if ((userExit == "n") || (userExit == "no") || 
        (userExit == "N") || (userExit == "NO")) {
            std::cout << "Exiting..." << std::endl;
        } else {
            main();
        }
}
