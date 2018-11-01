#include "Elevator.h"

void Elevator::tick(int currentTime) {

	// TODO: finish tick
}

void Elevator::serviceRequest(int floorNum) {
    
    // TODO: finish serviceRequest
}

///////////////////////////////////////////////////////
///// DO NOT MODIFY ANY 😤 CODE BENEATH THIS LINE /////
///////////////////////////////////////////////////////

Elevator::Elevator() {
    currentFloor = 0;
    servicing = false;
	targetFloor = 0;
}

void Elevator::setCurrentFloor(int currentFloorIn) {
    currentFloor = currentFloorIn;
}

bool Elevator::isServicing() const {
	return servicing;
}

int Elevator::getCurrentFloor() const {
    return currentFloor;
}

int Elevator::getTargetFloor() const {
    return targetFloor;
}
