#ifndef _EVENT_H_
#define _EVENT_H_

#include <string>
using namespace std;

class Event{
private:
    int turn;
    int startingFloor;
    int targetFloor;
    int angerLevel;

public:
    /*
     * Requires: nothing
     * Modifies: turn, startingFloor, targetFloor, angerLevel
     * Effects:  Parses the eventString to set member variables
     */
    Event(string eventString);

    /*
     * Requires: nothing
     * Modifies: nothing
     * Effects:  Returns turn
     */
    int getTurn() const;

    /*
     * Requires: nothing
     * Modifies: nothing
     * Effects:  Returns startingFloor
     */
    int getStartingFloor() const;

    /*
     * Requires: nothing
     * Modifies: nothing
     * Effects:  Returns targetFloor
     */
    int getTargetFloor() const;

    /*
     * Requires: nothing
     * Modifies: nothing
     * Effects:  Returns angerLevel
     */
    int getAngerLevel() const;
};


#endif
