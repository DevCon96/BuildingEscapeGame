#include <iostream>
#include <string>
#include "FBullCowGame.h"

// To match Unreal syntax
using Ftext = std::string;
using int32 = int;

// Create a global instance of the whole game.
FBullCowGame BCGame;

// Function prototypes to below functions
void PrintIntro();
void UsersWordLength();
void PlayGame();
Ftext GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

int main()
{
    bool bPlayAgain = true;
    Ftext Try = "";
    do {
        BCGame.Reset();
        PrintIntro();

        PlayGame();
        bPlayAgain = AskToPlayAgain();

    }
    while(bPlayAgain);

    return 0;
}

// Introdue the game to the user
void PrintIntro () {
    // Print the introduction of the game to the user.

    std::cout << "Welcome to Bulls and Cows" << std::endl;
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
    std::cout << std::endl;
    UsersWordLength();
    int32  WORD_LENGTH = BCGame.GetHiddenWordLength();
    std::cout << "Can you guess the " << WORD_LENGTH;
    std::cout << " letter isogran I'm thinking of?\n";
}

// Grab the users required word length
void UsersWordLength (){
    int32 length = 0;
    std::cout << "How long would you like the mystery word to be? - \n";
    std::cin >> length;
    BCGame.MysteryWord(length);
}
// Play the actual game from start to finish.
void PlayGame()
{
    // Create the game members for use
    int32 MaxTries = BCGame.GetMaxTries();
    Ftext Guess = "";
    FBullCowCount BullCowCount;


    // loop asking for guesses while the game is NOT won
    // and there are still tries remaining.
    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        Guess = GetValidGuess();
        // Submit valid guess to the game
        BullCowCount = BCGame.SubmitValidGuess(Guess);

        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
    }

    PrintGameSummary();

    return;
}

// Get the guess from the user
// loop continually untill the user provides a valid guess
Ftext GetValidGuess()
{
    // Get the guess from the user and store it to Guess.
    int32 CurrentTry = BCGame.GetCurrentTry();
    int32 RemainingTries = (BCGame.GetMaxTries()) - (CurrentTry - 1);

    Ftext Guess = "";
    EGuessStatus Status = EGuessStatus::Invalid;

    do {
        std::cout << "You have " << RemainingTries << " tries remaining...\n";
        std::cout << "Enter your guess: ";
        std::getline(std::cin, Guess);

        // Check the gues validity
        Status = BCGame.CheckGuessValidity(Guess);

        // Check the status of the guess.
        switch (Status) {
            case EGuessStatus::OK:
                // The guess has passed all validity checks
                break;
            case EGuessStatus::Wrong_Length:
                // The guess isn't the correct length
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
                break;
            case EGuessStatus::Not_Lowercase:
                // The guess wasn't entered in complete lowercase
                std::cout << "Please enter the guess all lowercase\n";
                break;
            case EGuessStatus::Not_Isogram:
                // The guess was not an isogram
                std::cout << "Your guess was not an isogram.\n";
                std::cout << "An isogram is a word without repeating letters.\n";
            default:
                break;
        }
        std::cout << std::endl;
    } while(Status != EGuessStatus::OK);
    return Guess;
}

// Ask the user if they want to pkay again
bool AskToPlayAgain()
{
    // Ask to play the game again.
    Ftext Response = "";
    std::cout << "Do you want to play again (y/n)?\n";
    std::getline(std::cin, Response);

    return(Response[0] == 'Y' || Response[0] == 'y');
}

void PrintGameSummary()
{
    Ftext answer = "";
    if (BCGame.IsGameWon())
    {
        std::cout << "Well done! You won the game\n";
    }
    else
    {
        std::cout << "Better luck next time...\n";
        std::cout << "Would you like to know the word? ";
        std::cin >> answer;
        if(answer[0] == 'y' || answer[0] == 'Y'){
            std::cout << "The word was " << BCGame.GetHiddenWord() << std::endl;
        }
    }
}

