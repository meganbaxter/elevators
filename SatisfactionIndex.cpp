#include "SatisfactionIndex.h"

SatisfactionIndex::SatisfactionIndex() {
    sumIndex = 0;
    sumUpRequest = 0;
    sumDownRequest = 0;
    sumExploded = 0;
    sumIdle = 0;
}

int SatisfactionIndex::getSatisfaction() const {
    return sumIndex;
}

void SatisfactionIndex::updateSumDirectionRequest(const Move& move, const Building& building) {
    
    sumIndex += move.getTotalSatisfaction();
    
    int currentElevatorFloor = building.getElevatorById(move.getElevatorId()).getCurrentFloor();
    int targetFloor = move.getTargetFloor();
    
    // Sum of times elevator "went down", NOT num people who wanted to go down
    // and were picked up
    if (currentElevatorFloor < targetFloor) {
        sumUpRequest++;
        
    } else {
        sumDownRequest++;
    }
}

void SatisfactionIndex::updateSumExploded(const int num) {
    sumExploded += num;
    sumIndex += (num * POINTS_LOST_PER_EXPLOSION);
}

void SatisfactionIndex::updateSumIdle(const Building& building) {
    
    for (int i = 0; i < NUM_ELEVATORS; ++i) {
        if (!building.getElevatorById(i).isServicing()) {
            ++sumIdle;
        }
    }
}

void SatisfactionIndex::readRawSatisfaction(istream& ins) {
    
    ins >> sumIndex >> sumUpRequest >> sumDownRequest >> sumExploded >> sumIdle;
}

void SatisfactionIndex::printRawSatisfaction(ostream& outs) const {
    outs << sumIndex << endl;
    outs << sumUpRequest << endl;
    outs << sumDownRequest << endl;
    outs << sumExploded << endl;
    outs << sumIdle << endl;
}

void SatisfactionIndex::printSatisfaction(ostream& outs, const bool isCSV) const {
    
    if (!isCSV) {
        
        outs << "sumIndex:      \t" << sumIndex << endl;
        outs << "sumUpRequest:  \t" << sumUpRequest << endl;
        outs << "sumDownRequest:\t" << sumDownRequest << endl;
        outs << "sumExploded:   \t" << sumExploded << endl;
        outs << "sumIdle:       \t" << sumIdle << endl;
        
    } else {
        
        outs << "sumIndex,sumUpRequest,sumDownRequest,sumExploded,sumIdle" << endl;
        outs << sumIndex << ',';
        outs << sumUpRequest << ',';
        outs << sumDownRequest << ',';
        outs << sumExploded << ',';
        outs << sumIdle;
    }
}

void SatisfactionIndex::save() const {
    
    ofstream result(RESULT_FILENAME);
    
    printSatisfaction(result, true);
}

ostream& operator<<(ostream& outs, const SatisfactionIndex& index) {
    index.printRawSatisfaction(outs);
    
    return outs;
}

istream& operator>>(istream& ins, SatisfactionIndex& index) {
    index.readRawSatisfaction(ins);
    
    return ins;
}
