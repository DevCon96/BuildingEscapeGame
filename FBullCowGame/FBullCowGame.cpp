//
// Created by Connor Jones on 2019-04-07.
//

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// Inlcude the map functionality
#include <map>
#define TMap std::map

//Type Aliases
using int32 = int;
using FString = std::string;

// Constructor to initialise the game
FBullCowGame::FBullCowGame() { Reset(); }

// Public interface to the game
// Getter functions (return the values of the private member variables
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return (int) MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }
FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord;}

// Get the number of tries for the given word length
int32 FBullCowGame::GetMaxTries() const
{
    // Generate the map to map the word length and number of tries
    // Difficulty management.
    TMap <int32, int32> DifficultyWordLength { {3,4}, {4,7}, {5,10}, {6,15}, {7,20}};

    return DifficultyWordLength[MyHiddenWord.length()];
}

// Reset the game to some initial values.
void FBullCowGame::Reset()
{
    // Function constants
    const FString HIDDEN_WORD = "curtain";

    // Initialise the member variable
    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    bGameWon = false;
    return;
}

// Check the guess submitted is valid
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    // if the guess isnt an isgoram, return an error
    if (!IsIsogram(Guess))   //TODO write function
    {
        return EGuessStatus::Not_Isogram;
    }
    // it the guess isn't all lowercase return error
    else if (! IsLowercase(Guess))  //TODO write function
    {
        return EGuessStatus::Not_Lowercase;
    }
    // if the guess is the wrong length return error
    else if (Guess.length() != GetHiddenWordLength())
    {
        return EGuessStatus::Wrong_Length;
    }
    // otherwise return ok
    else
    {
        return EGuessStatus::OK;
    }

}

// Receives a Valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    // increments the turn number
    MyCurrentTry++;

    // setup a return structure
    FBullCowCount BullCowCount;
    int32 WordLength = (int) MyHiddenWord.length();   // Assuming the guess is same length

    // loop through all letters in the hidden word
    for(int32 HWChar = 0; HWChar < WordLength; HWChar++)
    {
        // Testing actual guess word character
        for(int32 GChar = 0; GChar <= WordLength; GChar++)
        {
            // Is guess[GChar] inside the hidden word at all?
            if(Guess[GChar] == MyHiddenWord[HWChar])
            {
                if(HWChar == GChar) {
                    // Matches and in the same location
                    BullCowCount.Bulls++;
                }
                else
                {
                    // In the word but at the wrong location
                    BullCowCount.Cows++;
                }
            }

        }
    }
    // Test if the game is won
    if (BullCowCount.Bulls == WordLength)
    {
        // Game is won!
        bGameWon = true;
    }
    else
    {
        bGameWon = false;
    }
        return BullCowCount;
}

// Private methods for the class

// Test whether the argument word is an isogram
bool FBullCowGame::IsIsogram(FString Word) const
{
    // Treat 0 and 1 letter words as isograms
    if(Word.length() < 2 ) { return true; }

    // set up the map
    TMap <char, bool> LetterSeen;

    // Loop through all letters in the word
    for(auto letter: Word)
    {
        // Change the letter to lowercase
        letter = tolower(letter);

        // if the letter is in the word set the map word not isogram
        if(LetterSeen[letter])
        {
            return false;
        }
        // letter is not found in map so add it
        else
        {
            LetterSeen[letter] = true;
        }
    }
    return true;
}

// Test whether all the word is lowercase
bool FBullCowGame::IsLowercase (FString Word) const
{
    // Loop through all letters in the word
    for(auto letter:Word)
    {
        // Is the current letter lowercase?
        if(!std::islower(letter))
        {
            return false;
        }
    }
    return true;
}

void FBullCowGame::MysteryWord(int32 size)
{
    // Random arrays of words
    FString ThreeLetterWords[] = {"dog", "cat", "pot", "air", "fed", "hat", "bed", "red", "rat"};
    FString FourLetterWords[] = {"sock", "bowl", "fair", "plan", "wait", "hate","love", "blue", "bear"};
    FString FiveLetterWord[] = {"stack", "whack", "whale", "plate", "drink", "green", "spoon", "floss","tiger"};
    FString SixLetterWord[] = {"planet", "waiter", "violet", "walrus", "mantis", "washer", "market", "digest", "fiesta" };
    FString SevenLetterWord[] = {"curtain", "standby", "shafted", "handset", "therapy", "startup", "fairest", "pirates", "protest"};

    // random index generator
    const int32 Min = 0, Max = 8;
    int32 index = Min + (std::rand() % (Max - Min + 1));

    switch(size){
        case 3:
            MyHiddenWord = ThreeLetterWords[index];
            break;

        case 4:
            MyHiddenWord = FourLetterWords[index];
            break;

        case 5:
            MyHiddenWord = FiveLetterWord[index];
            break;

        case 6:
            MyHiddenWord = SixLetterWord[index];
            break;

        case 7:
            MyHiddenWord = SevenLetterWord[index];
            break;
    }
    return;
}
