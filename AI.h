#ifndef _AI_H_
#define _AI_H_

#include <iostream>
#include "Utility.h"
#include "Move.h"
#include "BuildingState.h"
#include "Person.h"
using namespace std;


/*
* Requires: buildingState is a valid state representing the current building
* Modifies: Nothing
* Effects: Returns a valid move that represents the decision the AI makes given the
*         current state of the building, which it reads from the input object.
*/
Move getAIMove(const BuildingState& buildingState);

/*
* Requires: buildingState is a valid state representing the current building
*           move is a pickup move that was decided by getAIMove()
*           people[] represents the current people on the pickup floor
*           size represents the number of people on the pickup floor
* Modifies: move
* Effects: modifies the provided move object and decides which indexes to select
*          to pickup. Populates the peopleToPickup[] and numPeopletoPickup fields
*          by calling move.setPeopleToPickup(). Resulting move must be a valid move 
*/
void setAIPickupList(Move& move, const BuildingState& buildingState, const Floor& floorToPickup);

#endif
