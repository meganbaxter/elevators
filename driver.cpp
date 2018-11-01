#include <iostream>
#include <fstream>
#include "Utility.h"
#include "Game.h"

using namespace std;

int main() {

    Game game;

    game.printWelcomeMenu();
    IntroChoice introChoice = game.getIntroChoice();

    switch (introChoice) {
        case IntroChoice::Load: {
            ifstream l(LOAD_FILENAME);
            ofstream g(GAME_INPUT_FILENAME);

            string lineItem = "";

            while(getline(l, lineItem)) {
                g << lineItem << endl;
            }
            break;
        }
        case IntroChoice::New: {
            ifstream n(NEW_FILENAME);
            ofstream g(GAME_INPUT_FILENAME);

            string lineItem = "";

            while(getline(n, lineItem)) {
                g << lineItem << endl;
            }
            break;
        }
        default:
            throw runtime_error("ERROR: Invalid menu choice detected");
            break;
    }

    bool isAIMode = game.getAIChoice() == AIChoice::AI ? true : false;
    
    game.playGame(isAIMode);

    return 0;
}
