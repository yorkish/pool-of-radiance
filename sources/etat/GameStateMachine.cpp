#include "GameStateMachine.h"

#include <iostream>

void GameStateMachine::clean() {
	if (!stateStack.empty()) {
		stateStack.back()->onExit();

		delete stateStack.back();
		_gblMemory.push_back(InfoAlloc('D', __FILE__, __LINE__));

		stateStack.clear();
	}
}

void GameStateMachine::update(TInfoTouches& keysInfo) {
	if (!stateStack.empty()) {
		stateStack.back()->update(keysInfo);
	}
}

void GameStateMachine::render() {
	if (!stateStack.empty()) {
		stateStack.back()->render();
	}
}

void GameStateMachine::checkMessages() {
	if (!stateStack.empty()) {
		stateStack.back()->checkMessages();
	}
}

void GameStateMachine::pushState(EtatJeu *pState) {
	stateStack.push_back(pState);
	stateStack.back()->onEnter();
}

void GameStateMachine::popState() {
	if (!stateStack.empty()) {
		if (stateStack.back()->onExit()) {
			delete stateStack.back();
			_gblMemory.push_back(InfoAlloc('D', __FILE__, __LINE__));
			stateStack.pop_back();
		}
	}
}

void GameStateMachine::changeState(EtatJeu *pState) {
	if (!stateStack.empty()) {
		if (stateStack.back()->getStateID() == pState->getStateID()) {
			return; // do nothing
		}

		popState();
	}

	// initialise it
	pState->onEnter();

	// push back our new state
	stateStack.push_back(pState);
}
