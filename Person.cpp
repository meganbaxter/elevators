#include "Person.h"

bool Person::tick(int currentTime) {

    // TODO: finish tick
    // returning false to prevent compilation error
    return false;
}

///////////////////////////////////////////////////////
///// DO NOT MODIFY ANY 😤 CODE BENEATH THIS LINE /////
///////////////////////////////////////////////////////

Person::Person() {

    angerLevel = 0;
    targetFloor = 0;
}

Person::Person(int targetFloorIn, int angerLevelIn) {

    targetFloor = targetFloorIn;
    angerLevel = angerLevelIn;
}

int Person::getAngerLevel() const {

    return angerLevel;
}

int Person::getTargetFloor() const {
    return targetFloor;
}
