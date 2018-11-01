#include "Game.h"
#include "AI.h"
#include "Utility.h"

bool Game::saveGame(ofstream& saveFile) const {
    
    // TODO: finish saveGame
    // returning false to prevent compilation error
    return false;
}

bool Game::isValidPickupList(const string& pickupList, const int& pickupFloorNum) const {

    // TODO: finish isValidPickupList
    // returning false to prevent compilation error
    return false;
}

bool Game::performMove(Move& move) const {

    // TODO: finish performMove
    // returning false to prevent compilation error
    return false;
}

void Game::playGame(bool isAIModeIn) {

    // TODO: finish playGame
}

///////////////////////////////////////////////////////
///// DO NOT MODIFY ANY 😤 CODE BENEATH THIS LINE /////
///////////////////////////////////////////////////////

void Game::printWelcomeMenu() const {

    cout << "########################################" << endl;
    cout << "# Welcome to EECS 183 Elevator Escape! #" << endl;
    cout << "########################################" << endl << endl;
}

void Game::printIntroMenu() const {

    cout << "[1] Load saved game" << endl;
    cout << "[2] Start new game" << endl;
    cout << "Choice: ";
}

void Game::printAIMenu() const {

    cout << "[1] Play as human" << endl;
    cout << "[2] Watch AI play" << endl;
    cout << "Choice: ";
}

void Game::printGameStartPrompt() const {

    if (!isAIMode) {
        cout << endl;
        cout << "########################################" << endl;
        cout << "#                 Enter:               #" << endl;
        cout << "#               Q to Quit              #" << endl;
        cout << "#               S to Save              #" << endl;
        cout << "#      P to Print Satisfaction Index   #" << endl;
        cout << "#      At any time after this prompt   #" << endl;
        cout << "########################################" << endl;
        cout << endl;
        cout << "Press any key to continue....";

        string trash;
        getline(cin, trash);
        cout << endl;
    }
}

IntroChoice Game::getIntroChoice() const {

    if (IS_AI_OVERRIDE) {
        return IntroChoice::New;
    }

    int choice = 0;

    while ((choice < 1) || (choice > 2)) {
        printIntroMenu();
        string s_choice;
        getline(cin, s_choice);
        choice = stoi(s_choice);

        if ((choice < 1) || (choice > 2)) {
            cout << endl << "Invalid menu choice!" << endl << endl;
        }
    }

    cout << endl;

    return static_cast<IntroChoice>(choice);
}

AIChoice Game::getAIChoice() const {

    if (IS_AI_OVERRIDE) {
        return AIChoice::AI;
    }

    int choice = 0;
    printAIMenu();
    string s_choice;
    getline(cin, s_choice);
    choice = stoi(s_choice);
    while (choice != 1 && choice != 2){
        cout << endl << "Invalid menu choice!" << endl << endl;
        getline(cin, s_choice);
        choice = stoi(s_choice);
    }

    cout << endl;

    return static_cast<AIChoice>(choice);
}

void Game::printSatisfactionIndex() const {
    cout << endl << endl;
    cout << "Your hotel's current satisfaction index is: " << satisfactionIndex;
    cout << endl << endl;
}

void Game::getPeopleToPickup(Move& move) const {

    int currentFloorNum = building.getElevatorById(move.getElevatorId()).getCurrentFloor();
    Floor currentFloor = building.getFloorByFloorNum(currentFloorNum);

    if (currentFloor.getNumPeople() == 1) {
        move.setPeopleToPickup("0", currentFloorNum, currentFloor);
        return;
    }

    string peopleIndices = "";
    bool isValidPickup = false;

    while (!isValidPickup) {

        // REFACTOR put "Choices: " in printFloorPickupMenu and who to pickup prompt, ie:
        // cout << endl << endl << "Who would you like to pickup?" << endl << endl;
        currentFloor.printFloorPickupMenu(cout);
        cout << endl;
        cout << "Choices: ";
        getline(cin, peopleIndices);

        isValidPickup = isValidPickupList(peopleIndices, currentFloorNum);

        if (!isValidPickup) {
            cout << "Invalid list of people chosen!" << endl;
        }
    }

    move.setPeopleToPickup(peopleIndices, currentFloorNum, currentFloor);
}

Move Game::getMove() const {
    if (isAIMode) {
        BuildingState buildingState = building.getBuildingState();

        Move aiMove = getAIMove(buildingState);

        if (aiMove.isPickupMove()) {

            Elevator e = building.getElevatorById(aiMove.getElevatorId());
            Floor f = building.getFloorByFloorNum(e.getCurrentFloor());

            int numPeople = 0;
            Person peopleToPickup[MAX_PEOPLE_PER_FLOOR];

            for (int i = 0; i < f.getNumPeople(); ++i) {
                peopleToPickup[numPeople++] = f.getPersonByIndex(i);
            }

            setAIPickupList(aiMove, buildingState, peopleToPickup, numPeople);
        }

        return aiMove;
    }
    return getUserMove();
}

void Game::performQuit() const {
    QuitChoice quitChoice = static_cast<QuitChoice>(getExitChoice());
    switch (quitChoice) {
        case QuitChoice::Quit:
            endGame();
            break;
        case QuitChoice::Stay:
            return;
            break;
    }
}

bool Game::performSave() const {
    ofstream saveFile(LOAD_FILENAME);
    if (!saveFile.is_open()) {
        cout << "Could not open " << LOAD_FILENAME << endl;
        return false;
    }
    return saveGame(saveFile);
}

bool Game::performAndValidateMove(GameChoice moveType, Move& move) const {

    switch (moveType) {
        case GameChoice::Quit: {
            performQuit();
            return true;
            break;
        }
        case GameChoice::Save: {
            return performSave();
            break;
        }
        case GameChoice::Print: {
            printSatisfactionIndex();
            return true;
            break;
        }
        case GameChoice::Pass:
        case GameChoice::Move: {
            return performMove(move);
        }
        case GameChoice::Invalid:
        default:
            return false;
            break;
    }
}


Move Game::getUserMove() const {

    Move moveObj;
    string move = "";
    bool isValid = false;
    GameChoice choiceCapture = GameChoice::Invalid;

    do {
        cout << "Enter move: ";

        getline(cin, move);
        moveObj = Move(move);
        choiceCapture = static_cast<GameChoice>(move[0]);

        switch (choiceCapture) {
            case GameChoice::Quit:
            case GameChoice::Save:
            case GameChoice::Print:
            case GameChoice::Pass:
            case GameChoice::Move:
                break;
            default:
                choiceCapture = GameChoice::Invalid;
                break;
        }

        isValid = performAndValidateMove(choiceCapture, moveObj);

        if (!isValid &&
            ((choiceCapture == GameChoice::Move) || (choiceCapture == GameChoice::Invalid))) {

            cout << endl << "Invalid move!" << endl << endl;
        }

    } while(!isValid);

    return moveObj;
}

void Game::initGame(ifstream& loadFile) {
    cout << endl << "Loading game..." << endl;

    loadFile >> satisfactionIndex;

    int tempTime;
    loadFile >> tempTime;

    building.setTime(tempTime);

    string elvState;
    for (int i = 0; i < NUM_ELEVATORS; i++) {
        loadFile >> elvState;
        building.setElevator(elvState, i);
    }

    cout << "Loaded!" << endl << endl;
}

void Game::printExitMenu() const {
    cout << endl;
    cout << "Are you sure you want to quit?" << endl;
    cout << "[1] Yes, I'm sure!" << endl;
    cout << "[2] No, keep playing!" << endl;
    cout << "Choice: ";
}

int Game::getExitChoice() const {

    int exitChoice = 0;

    while ((exitChoice < 1) || (exitChoice > 2)) {
        printExitMenu();

        string choice = "";
        getline(cin, choice);
        exitChoice = stoi(choice);

        if ((exitChoice < 1) || (exitChoice > 2)) {
            cout << endl << "Invalid menu choice!" << endl << endl;
        }
    }

    cout << endl;

    return exitChoice;
}

void Game::endGame() const {
    cout << endl << "Goodbye!" << endl;
    satisfactionIndex.save();
    exit(0);
}

void Game::printSuccessEnding() const {
    cout << endl << endl;
    cout << "Time is up! Your final score is: " << endl;
    satisfactionIndex.printSatisfaction(cout);
}

void Game::printFailureEnding() const {

    cout << endl << endl;
    cout << "Uh oh! Your hotel has gone out of business!" << endl;
    cout << "Better luck next time!" << endl << endl;
    cout << "Your final achievement:" << endl << endl;
    satisfactionIndex.printSatisfaction(cout);
}

void Game::checkForGameEnd() const {

    if (building.getTime() >= MAX_TURNS) {

        printSuccessEnding();
        endGame();

    } else if (satisfactionIndex.getSatisfaction() < 0) {

        printFailureEnding();
        endGame();
    }
}

void Game::applyMove(const Move& m) {
    if (m.isPickupMove()) {
        satisfactionIndex.updateSumDirectionRequest(m, building);
    }

    // Decrement satisfaction index by numExploded. 10 points lost per explosion
    satisfactionIndex.updateSumExploded(building.tick(m));

    if (building.getTime() % 2) {
        satisfactionIndex.updateSumIdle(building);
    }
}
