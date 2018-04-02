#include <iostream>
#include "etat/EtatIntro.h"
#include "etat/EtatMenu.h"
#include "queue/Message.h"
#include "common/Donnees.h"
#include "Game.h"

using std::cout;

Game::Game(Renderer &renderer) :
		renderer(renderer), gameState(GAME_STATE_UNDEFINED), messageStack(PileMessage::getInstance()) {
}

bool Game::init() {
	pushState(new EtatIntro(renderer));
	_gblMemory.push_back(InfoAlloc('N', __FILE__, __LINE__));
	gameState = INTRO;

	return true;
}

void Game::handleEvent(TInfoTouches& keysInfo) {
	getCurrentState()->handleEvent(keysInfo);
}

void Game::move() {
}

void Game::draw() {
	getCurrentState()->draw();
}

void Game::checkMessages() {
	Message unMessage = messageStack.getMessageCourant();

	if (unMessage.getDestinataire() == OBJ_JEU) {
		switch (unMessage.getTypeMessage()) {
		case GM_INTRO_FINI:
			popPushState(new EtatMenu(renderer));
			_gblMemory.push_back(InfoAlloc('N', __FILE__, __LINE__));
			gameState = MENU;
			break;

		case GM_NOUVEAU_PERSONNAGE:
			lstCharacters.push_back(new Character());
			_gblMemory.push_back(InfoAlloc('N', __FILE__, __LINE__));
			break;

		case GM_ANNULER_PERSONNAGE:
			delete lstCharacters.back();
			_gblMemory.push_back(InfoAlloc('D', __FILE__, __LINE__));
			lstCharacters.pop_back();
			break;

		case GM_QUITTER:
			gameState = EXIT_REQUESTED;
			break;

		default:
			break;
		}
		messageStack.popMessage();
	}

	if (lstCharacters.size() != 0)
		lstCharacters.back()->verifierMessages();

	getCurrentState()->verifierMessages();
	saveGameManager.verifierMessages();
}

bool Game::exitRequested() {
	return (gameState == EXIT_REQUESTED);
}

EtatJeu* Game::getCurrentState() {
	if (!stateStack.empty())
		return stateStack.top();
	else
		return 0;
}

void Game::pushState(EtatJeu* state) {
	// set current state
	stateStack.push(state);
	stateStack.top()->init();
}

void Game::popState() {
	if (stateStack.empty())
		return;

	stateStack.top()->release();

	delete stateStack.top();
	_gblMemory.push_back(InfoAlloc('D', __FILE__, __LINE__));

	stateStack.pop();
}

void Game::popPushState(EtatJeu* state) {
	// set current state
	popState();
	pushState(state);
}

Game::~Game() {
	while (getCurrentState() != 0)
		popState();
}
