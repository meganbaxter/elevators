#include <cmath>
#include "Move.h"

Move::Move(string moveString) {

    // TODO: finish non-default constructor
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {

    // TODO: finish isValidMove
    // Returning false to avoid compilation error
	return false;
}

void Move::setPeopleToPickup(const string& pickupList, const int& currentFloor, const Floor& pickupFloor) {
	
	// TODO: finish setPeopleToPickup
}

///////////////////////////////////////////////////////
///// DO NOT MODIFY ANY 😤 CODE BENEATH THIS LINE /////
///////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}

void Move::setPersonToPickUpAtIndex(int setIndex, int personIndex, int personSatisfaction) {
    peopleToPickup[setIndex] = personIndex;
    ++numPeopleToPickup;
    totalSatisfaction += personSatisfaction;
}
