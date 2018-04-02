#pragma once

#include <stack>
#include <vector>
#include "common/Global.h"
#include "queue/PileMessage.h"
#include "etat/EtatJeu.h"
#include "character/Character.h"
#include "SaveGameManager.h"
#include "common/Renderer.h"

class Game {
public:
	Game(Renderer &renderer);

	bool init();
	void handleEvent(TInfoTouches& keysInfo);
	void move();
	void checkMessages();
	void draw();

	bool exitRequested();

	~Game();

private:
	EtatJeu* getCurrentState();
	void pushState(EtatJeu* state);
	void popState();
	void popPushState(EtatJeu* state);

	Renderer &renderer;

	GameState gameState;
	PileMessage& messageStack;
	SaveGameManager saveGameManager;

	std::stack<EtatJeu*> stateStack;
	std::vector<Character*> lstCharacters;
};
