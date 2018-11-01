#ifndef _BUILDING_STATE_H_
#define _BUILDING_STATE_H_

#include "Utility.h"

//////////////////////////////////////////////////////////////////////
// BuildingState                                                    //
// ----------------                                                 //
// These structs will contain public state information              //
// to be passed to the AI for further use                           //
//////////////////////////////////////////////////////////////////////

struct _Person {
    int angerLevel = 0;
};

struct _Floor {
    int floorNum = 0;
    int numPeople = 0;
    bool hasUpRequest = false;
    bool hasDownRequest = false;
    _Person people[MAX_PEOPLE_PER_FLOOR];
};

struct _Elevator {
    int elevatorId = 0;
    int targetFloor = 0;
    int currentFloor = 0;
    bool isServicing = false;
};


struct BuildingState {
    int turn = 0;
    _Floor floors[NUM_FLOORS];
    _Elevator elevators[NUM_ELEVATORS];
};

#endif
