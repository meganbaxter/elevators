#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <fstream>
#include <string>
#include "SatisfactionIndex.h"
#include "Move.h"
#include "Event.h"
#include "Building.h"
#include "BuildingState.h"
#include "Utility.h"

using namespace std;

enum class IntroChoice : int {
    Load = 1,
    New  = 2
};

enum class AIChoice : int {
    Human = 1,
    AI    = 2
};

enum class GameChoice : char {
    Quit  = 'Q',
    Save  = 'S',
    Print = 'P',
    Move  = 'e',
    Pass  = '\0',
    Invalid = '\7'
};

enum class QuitChoice : int {
    Quit = 1,
    Stay = 2
};

class Game {
private:
    Building building;
    SatisfactionIndex satisfactionIndex;
    bool isAIMode;

public:
    /**
     * Requires: nothing
     * Modifies: cout
     * Effects: prints welcome banner
     */
    void printWelcomeMenu() const;

    /**
     * Requires: nothing
     * Modifies: cout
     * Effects: prints intro choice menu
     */
    void printIntroMenu() const;

    /**
     * Requires: nothing
     * Modifies: cout
     * Effects: prints ai choice menu
     */
    void printAIMenu() const;

    /**
     * Requires: nothing
     * Modifies: cout, cin
     * Effects: prints game start prompt
     *          pauses until further input recieved
     */
    void printGameStartPrompt() const;

    /**
     * Requires: nothing
     * Modifies: cout
     * Effects: prints satisfactionIndex
     */
    void printSatisfactionIndex() const;

    /**
     * Requires: nothing
     * Modifies: cout
     * Effects: prints success ending prompt
     */
    void printSuccessEnding() const;

    /**
     * Requires: nothing
     * Modifies: cout
     * Effects: prints failure ending prompt
     */
    void printFailureEnding() const;

    /**
     * Requires: nothing
     * Modifies: cout
     * Effects: prints the exit menu
     */
    void printExitMenu() const;

    /**
     * Requires: nothing
     * Modifies: cout, cin
     * Effects: prints the intro menu
     *          reads the input from the user
     *          checks to make sure the input is within range for the menu
     *          if not, prints "Invalid menu choice!"
     *          continues to print the menu and read an input until a valid one is entered
     *          returns the users choice of menu options
     */
    IntroChoice getIntroChoice() const;

    /**
     * Requires: nothing
     * Modifies: cout, cin
     * Effects: prints the intro menu
     *          reads the input from the user
     *          checks to make sure the input is within range for the menu
     *          if not, prints "Invalid menu choice!"
     *          continues to print the menu and read an input until a valid one is entered
     *          returns the users choice of menu options
     *
     * Prompts: "Invalid menu choice!"
     */
    AIChoice getAIChoice() const;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: if ai is playing
     *              gets building state and gives to ai
     *              if ai requests pickup move, builds list of people on requested floor
     *              and gives list back to ai
     *              returns ai move
     *          else gets user move and returns it
     *
     * Note: This function has been implemented for you
     */
    Move getMove() const;

    /**
     * Requires: moveType is a valid GameChoice, move has been given a user inputted move
     * Modifies: move
     * Effects: performs user selected move
     *          returns true if move was valid
     *          returns false otherwise
     */
    bool performAndValidateMove(GameChoice moveType, Move& move) const;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: asks the user if they want to quit the game
     *          if yes, ends the game immediately
     *          otherwise returns
     */
    void performQuit() const;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: attempts to save the game
     *          if save file could not be opened,
     *              prompts "Could not open <filename>" and returns false
     *
     *          returns true on success, false otherwise
     *
     * Prompts: "Could not open <filename>"
     */
    bool performSave() const;

    /**
     * Requires: move has been given a user inputted move
     * Modifies: move
     * Effects: if move is not valid, returns false
     *          if move is a pickup move and a pickup can be performed
     *              gets people to be picked up
     *              otherwise returns false
     *          otherwise returns true
     */
    bool performMove(Move& move) const;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: prompts the user to enter move
     *          if user requested move is of type GameChoice::Move and is invalid
     *          prints "Invalid move!"
     *          continues to request user input until a valid move of type GameChoice::Move is given
     *          returns user input as a move
     *
     * Prompts: "Enter move: "
     *          "Invalid move!"
     */
    Move getUserMove() const;

    /**
     * Requires: move is a pickup move
     * Modifies: cout, cin, move
     * Effects: prints floor pickup menu of floor move is taken from
     *          reads the input from the user
     *          checks to make sure pickup choices are valid
     *          if not prints "Invalid list of people chosen!"
     *          continues to print menu and read an input until valid one is entered
     *          updates move to contain correct list of people to pick up
     *          updates move to contain the new target floor from the people picked up
     *
     * Prompts: "Invalid list of people chosen!"
     */
    void getPeopleToPickup(Move& move) const;

    /**
     * Requires: pickupFloorNum is the floor the pickup move was called on
     * Modifies: nothing
     * Effects: determines if pickupList is a valid
     *          list of people to pick up
     */
    bool isValidPickupList(const string& pickupList, const int& pickupFloorNum) const;

    /**
     * Requires: nothing
     * Modifies: cout, isAIMode, building, satisfactionIndex
     * Effects: prints game start prompt
     *          opens game input file
     *          if game input file cannot be open, exits with status 1
     *          else reads events from game input file
     *          if event is happening happening on current turn, updates building with event
     *          else prints building and checks if game has ended,
     *          if it hasn't yet, gets user (player or AI) move
     *          updates building with move
     *          updates satisfactionIndex
     */
    void playGame(bool isAIModeIn);

    /**
     * Requires: saveFile is in good state
     * Modifies: cout, saveFile
     * Effects: prints "Saving game..."
     *          adds current state of game to saveFile
     *          reads remaining moves from game input file
     *          if game input file cannot be opened
     *              prints Game input file could not be opened!
     *              and returns false
     *          else
     *              adds remaining move to saveFile
     *              flushes saveFile buffer
     *              prints "Saved!" when finished and returns true
     *
     * Prompts: "Saving game..."
     *          "Saved!"
     *          "Game input file could not be opened!"
     */
    bool saveGame(ofstream& saveFile) const;

    /**
     * Requires: loadFile is in good state
     * Modifies: cout, loadFile, satisfactionIndex, building
     * Effects: prints "Loading game..."
     *          reads from loadFile the state of the game
     *          updates current game to be the new state
     *          prints "Loaded!" when finished
     *
     * Prompts: "Loading game..."
     *          "Loaded!"
     */
    void initGame(ifstream& loadFile);

    /**
     * Requires: nothing
     * Modifies: cout, cin
     * Effects: prints the exit menu
     *          reads the input from the user
     *          checks to make sure the input is within range for the menu
     *          if not, prints "Invalid menu choice!"
     *          continues to print the menu and read an input until a valid one is entered
     *          returns the users choice of menu options
     *
     * Prompts: "Invalid menu choice!"
     */
    int getExitChoice() const;

    /**
     * Requires: nothing
     * Modifies: cout
     * Effects: prints "Goodbye!" and
     *          exits program with status code 0
     *
     * Prompts: "Goodbye!"
     */
    void endGame() const;

    /**
     * Requires: nothing
     * Modifies: cout
     * Effects: checks if the game has ended.
     *          If the game has ended, calls either:
     *
     *          printSuccessEnding or
     *          printFailureEnding
     *
     *          depending on how the game ended.
     *          If the game has ended, calls endGame();
     */
    void checkForGameEnd() const;

    /**
     * Requires: move is a valid move
     * Modifies: building
     * Effects: If move is a pickup move
     *              increases satisfaction index
     *              according to the people picked up
     *          calls building.tick on move
     *          reduces satisfaction index
     *          by factor of those exploded this turn (returned by tick)
     *          finally updates idle benchmark
     *          according to idle elevators
     */
    void applyMove(const Move& m);
};



#endif
