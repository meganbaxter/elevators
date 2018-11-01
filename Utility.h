
//////////////////////////////////////////////////////////////////////
// Utility.h                                                        //
// ----------------                                                 //
// This file contains all of the global constants for the project.  //
//////////////////////////////////////////////////////////////////////


#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <string>

using namespace std;

//filenames for new game file, saved game file, and input file
const string NEW_FILENAME = "new.in";
const string LOAD_FILENAME = "save.in";
const string GAME_INPUT_FILENAME = "game.in";
const string RESULT_FILENAME = "result.csv";

//game constants
const int ELEVATOR_CAPACITY = 10;
const int NUM_FLOORS = 10;
const int FIRST_FLOOR = 0;
const int MAX_ANGER = 10;
const int NUM_ELEVATORS = 3;
const int MAX_PEOPLE_PER_FLOOR = 10;
const int MAX_TURNS = 100;

const int TICKS_PER_ANGER_INCREASE = 5;
const int TICKS_PER_ELEVATOR_MOVE = 1;

const int POINTS_LOST_PER_EXPLOSION = -10;

const bool IS_AI_OVERRIDE = false;

#endif
