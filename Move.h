#ifndef _MOVE_H_
#define _MOVE_H_
#include <string>
#include "Utility.h"
#include "Floor.h"
#include "Elevator.h"
using namespace std;

class Move {
private:
    int elevatorId;
    int targetFloor;
    int peopleToPickup[MAX_PEOPLE_PER_FLOOR];
    int numPeopleToPickup;
    int totalSatisfaction;
	bool isPass; //just hitting enter is a move
    bool isPickup;

public:
    /**
     * Requires: nothing
     * Modifies: Move object
     * Effects: initializes a Move object
     *
     */
    Move();

    /**
     * Requires: moveString is a valid string
     * Modifies: Move object
     * Effects: creates a Move object based on
     *          the value of moveString
     */
    Move(string moveString);

    /**
     * Requires: elevators represents the elevator servicing states
     * Modifies: nothing
     * Effects: determines whether the move is valid
     *          based on the Move member variables
     */
    bool isValidMove(Elevator elevators[NUM_ELEVATORS]) const;

    /**
     * Requires: nothing
     * Modifies: nothings
     * Effects: returns the value of isPass
     *
     */
	bool isPassMove() const;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns the value of isPickup
     *
     */
    bool isPickupMove() const;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns the elevatorId
     *
     */
    int getElevatorId() const;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns the targetFloor
     *
     */
    int getTargetFloor() const;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns the number of people being picked up by this move (-1 if not pickup move)
     *
     */
    int getNumPeopleToPickup() const;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns totalSatisfaction
     *
     */
    int getTotalSatisfaction() const;

    /**
     * Requires: inTargetFloor is a valid floor
     * Modifies: targetFloor
     * Effects: sets the targetFloor to inTargetFloor
     *
     */
    void setTargetFloor(int inTargetFloor);

    /**
     * Requires: newList is a valid array
     * Modifies: newList
     * Effects: copies peopleToPickup into newList
     */
    void copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const;

    /**
     * Requires: pickupList is a valid list of indices
     *           currentFloor is the floor of the pickup request
     *           pickupFloor is the floor of the pickup request
     * Modifies: numPeopleToPickup, peopleToPickup, totalSatisfaction, targetFloor
     * Effects: sets numPeopleToPickup and totalSatisfaction to 0
     *          adds the indices of people to pickup to peopleToPickup
     *          increments numPeopleToPickup by 1 for each person being picked up
     *          adds satisfaction gained from each person picked up to totalSatisfaction
     *          sets targetFloor to be the most extreme floor of those being picked up (furthest up or down)
     */
    void setPeopleToPickup(const string& pickupList, const int& currentFloor, const Floor& pickupFloor);
};



#endif
