#pragma once

#include <vector>

#include "EtatJeu.h"

class GameStateMachine
{
public:
    
    GameStateMachine() {}
    ~GameStateMachine() {}
    
    void update(TInfoTouches& keysInfo);
    void render();
    void checkMessages();
    
    void pushState(EtatJeu* pState);
    void changeState(EtatJeu* pState);
    void popState();
    
    void clean();

	std::vector<EtatJeu*>& getGameStates() { return stateStack; }
    
private:
    std::vector<EtatJeu*> stateStack;
};
