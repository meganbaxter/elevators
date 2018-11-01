#ifndef _ELEVATOR_H_
#define _ELEVATOR_H_

#include "Utility.h"
#include "Person.h"

class Elevator {
private:
    int currentFloor;
    bool servicing;
    int targetFloor;

public:
    /**
     * Requires: currentTime is valid
     * Modifies: servicing
     * Effects: changes the value of the current floor if
     *          the currentTime is divisible by TICKS_PER_ELEVATOR_MOVE
     *          if current floor is the target floor,
     *          servicing is set to false
     */
    void tick(int currentTime);

    /**
     * Requires: nothing
     * Modifies: this Elevator object
     * Effects: creates an Elevator object
     *          with initial values
     */
    Elevator();

    /**
     * Requires: 0 <= floorNum <= MAXFLOORNUM
     * Modifies: currentFloor
     * Effects: sets the currentFloor
     */
    void setCurrentFloor(int currentFloorIn);

    /**
     * Requires: 0 <= floorNum <= MAXFLOORNUM
     * Modifies: targetFloor, servicing
     * Effects: sets the targetFloor and servicing
     *          values of the Elevator object
     */
    void serviceRequest(int floorNum);

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns whether the elevator is servicing
     *
     */
	bool isServicing() const;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns the currentFloor value
     *          of the Elevator object
     */
    int getCurrentFloor() const;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns the targetFloor
     */
    int getTargetFloor() const;
};

#endif
