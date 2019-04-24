//
// Created by Connor Jones on 2019-04-07.
//
#pragma once
#ifndef WORDGAME_FBULLCOWGAME_H
#define WORDGAME_FBULLCOWGAME_H

#include <string>

// Type Aliases. Used to match Unreal engine
using int32 = int;
using FString = std::string;

// Check words validity and assigne status to it
enum class EGuessStatus
{
    Invalid,          // The status is invalid, used for initialisation
    OK,               // The Guess is OK and has passed all validation tests
    Not_Isogram,      // The guess is not an isogram
    Wrong_Length,     // The guess is the wrong length
    Not_Lowercase     // The gues is not all lowercase letters
};

enum class EResetStatus
{
    OK,
    No_Hidden_Word
};
// Holds the number of bulls and cows in the guess
// All values are
struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

// The class that contains the entire game
class FBullCowGame
{
public:
    // Constructor
    FBullCowGame();

    // Getter functions
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    FString GetHiddenWord() const;

    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;

    // Setter Functions
    void Reset();
    FBullCowCount SubmitValidGuess(FString);
    void MysteryWord(int32 size);



private:
    // See the constructor for initialisation
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameWon;

    // Helper methods
    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;
    // List of words

};


#endif //WORDGAME_FBULLCOWGAME_H
