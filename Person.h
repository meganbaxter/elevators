#ifndef _PERSON_H_
#define _PERSON_H_

#include "Utility.h"

class Person {
private:
    int angerLevel;
    int targetFloor;

public:

    /**
     * Requires: nothing
     * Modifies: targetFloor, angerLevel
     * Effects: sets targetFloor and angerLevel to 0
     */
    Person();

    /**
     * Requires: targetFloorIn, angerLevelIn are valid
     * Modifies: targetFloor, angerLevel
     * Effects: sets targetFloor to be targetFloorIn
     *          sets angerLevel to be angerLevelIn
     */
    Person(int targetFloorIn, int angerLevelIn);

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: Returns the anger level of the person.
     */
    int getAngerLevel() const;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: Returns the target floor of the person.
     */
    int getTargetFloor() const;


    /**
     * Requires: nothing
     * Modifies: Anger level of the person
     * Effects: Every TICKS_PER_ANGER_INCREASE, this function increases the
     *          person's anger level by 1. If, after increasing, the person already has an anger
     *          level of MAX_ANGER, the
     *          function will return true. If the person has an anger level
     *          less than MAX_ANGER, the function will return false.
     */
    bool tick(int currentTime);
};

#endif
