#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "Elevator.h"
#include "Floor.h"
#include "Event.h"
#include "Utility.h"
#include "Move.h"
#include "BuildingState.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Building {
private:
    Elevator elevators[NUM_ELEVATORS];
    Floor floors[NUM_FLOORS];
    int time;

    /*
    * Requires: move is a valid move
    * Modifies: the building member variables affected by the move
    * Effects: Applies the move to the building:
    *          If the move is a Pass Move, nothing happens
    *          If the move is a Pickup Move, copies the list
    *          of people to pickup into an array, and calls removePeople()
    *          on the appropriate floor. Calls resetFloorRequests() afterwards
    *          to make sure to update the active UP/DOWN requests.
    *          For both Pickup Moves and Service Moves, the appropriate
    *          elevator should be sent to service the targetFloor of the move
    */
	void applyMove(Move move);

    /*
    * Requires: 0 <= floorNum < NUM_FLOORS
    * Modifies: the floor object on floor floorNum
    * Effects: First, disable the UP and DOWN requests on the given floor
    *          Then, search through the people on that floor to find if there
    *          are any pending up requests or down requests. If found, mark the
    *          floor as having the appropriate request.
    *          This function is used to recalculate requests after some
    *          people on a particular floor have been picked up or have exploded.
    */
    void resetFloorRequests(int floorNum);
    
public:
    /*
    * Requires: nothing
    * Modifies: building State
    * Effects: Default constructor. Sets time to 0.
    */
    Building();

    /*
    * Requires: elevatorInfo is a well-formed info string.
    *           0 <= elevatorId < NUM_ELEVATORS
    * Modifies: building's elevator at elevatorId
    * Effects: Parses elevatorInfo and updates elevator into correct
    *          state. The elevator string will come in the form
    *          <num>[s<num>:w]
    *          Ex: 0w
    *              6s8
    *              5w
    *              9s5
    *          The first number represents the currentFloor of the elevator
    *          The 's' means that the elevator is currently servicing, with target floor
    *          being the number after the 's'
    *          The 'w' means that the elevator is waiting, so it has no target floor
    *          and is ready to service requests.
    *          This is used when reloading a game from a save file
    */
    void setElevator(string elevatorInfo, int elevatorId);

    /*
    * Requires: nothing
    * Modifies: nothing
    * Effects: Returns the current time for the building
    */
    int getTime() const;

    /*
    * Requires: timeIn >= 0
    * Modifies: nothing
    * Effects: Sets the current time for the building to timeIn
    */
    void setTime(int timeIn);

    /*
    * Requires: move is a valid move
    * Modifies: the private member variables of building
    * Effects: Increments time and calls applyMove() on the input
    *          move. Then ticks all of the elevators with the new time
    *          Next, ticks all of the buildingfloors, keeping track of
    *          new exploded people and calling resetFloorRequests() if someone
    *          exploded.
    *          Returns the total number of people that exploded in this tick in
    *          the building
    */
    int tick(Move move);

    /*
    * Requires: outs is in a good state, building is in a valid state
    * Modifies: outs
    * Effects: Prints the building state to terminal in a nice way for
    *          gameplay
    */
    void prettyPrintBuilding(ostream& outs, bool isAIMode) const;

    /*
    * Requires: newEvent is a valid Event object
    * Modifies: changes a floor in the building
    * Effects:  adds a person to the floor corresponding to startingFloor
    *           of the event. Calls floor.addPerson()
    */
    void addEvent(Event newEvent);

    /*
    * Requires: 0 <= elevatorId < NUM_ELEVATORS
    * Modifies: nothing
    * Effects: Returns an Elevator object containing the
    *          info of the elevator at index elevatorID in the building
    */
    Elevator getElevatorById(int elevatorId) const;

    /*
    * Requires: 0 <= floorNum < NUM_FLOORS
    * Modifies: nothing
    * Effects: Returns an Floor object containing the
    *          info of the floor at index floorNum in the building
    */
    Floor getFloorByFloorNum(int floorNum) const;

    /*
    * Requires: nothing
    * Modifies: nothing
    * Effects: Returns a BuildingState object for use by AI
    *          to decide its move with the same information a
    *          human player would use. See BuildingState.h for more
    *          info.
    */
    BuildingState getBuildingState() const;
};


#endif
