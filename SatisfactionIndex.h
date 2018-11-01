#ifndef _SATISFACTION_INDEX_H_
#define _SATISFACTION_INDEX_H_

#include <iostream>
#include <fstream>

#include "Utility.h"
#include "Building.h"
#include "Move.h"

class SatisfactionIndex {
private:
    
    int sumIndex;
    int sumUpRequest;
    int sumDownRequest;
    int sumExploded;
    int sumIdle;
    
public:
    
    /**
     * Requires: nothing
     * Modifies: sumIndex,
     *           sumUpRequest,
     *           sumDownRequest,
     *           sumExploded,
     *           sumIdle
     * Effects: sets all modified to be 0
     */
    SatisfactionIndex();
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns sumIndex
     */
    int getSatisfaction() const;
    
    /**
     * Requires: move and building are valid
     * Modifies: sumUpRequest, sumDownRequest
     * Effects: if moves causes elevator to go down,
     *              increments sumDownRequest
     *          if moves causes elevator to go up,
     *              increments sumUpRequest
     */
    void updateSumDirectionRequest(const Move&, const Building&);

    /**
     * Requires: nothing
     * Modifies: sumIndex, sumExploded
     * Effects: increments sumExploded by num
     *          increments sumIndex by num * POINTS_LOST_PER_EXPLOSION
     */
    void updateSumExploded(const int);
    
    /**
     * Requires: building is valid
     * Modifies: sumIdle
     * Effects: increments sumIdle by 1 for each idle elevator in building
     */
    void updateSumIdle(const Building&);
    
    /**
     * Requires: nothing
     * Modifies: sumIndex,
     *           sumUpRequest,
     *           sumDownRequest,
     *           sumExploded,
     *           sumIdle
     * Effects: reads modified in order from ins
     */
    void readRawSatisfaction(istream& ins);
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: prints sumIndex, sumUpRequest
     *                 sumDownRequest, sumExploded
     *                 sumIdle in order, separated
     *                 by newline
     */
    void printRawSatisfaction(ostream& outs) const;
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: prints sumIndex, sumUpRequest
     *                 sumDownRequest, sumExploded
     *                 sumIdle in order, separated
     *                 by newline with header for display value
     */
    void printSatisfaction(ostream& outs, const bool isCSV = false) const;
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: prints sumIndex, sumUpRequest
     *                 sumDownRequest, sumExploded
     *                 sumIdle in csv format to RESULT_FILENAME
     */
    void save() const;
};

ostream& operator<<(ostream& outs, const SatisfactionIndex& index);

istream& operator>>(istream& ins, SatisfactionIndex& index);


#endif
