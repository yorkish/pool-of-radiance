#pragma once
#include <string>
#include <vector>
#include "../roll/RollOperation.h"

class Roll {
	public:
		Roll();
		Roll(RollOperation roll);
		Roll(std::vector<RollOperation> rolls);

		void appendRoll(RollOperation roll);
		void appendRoll(Roll roll);
		int  throwDice();
		void reset();

		~Roll();

	private:
		int  appliquerOperateur(int x, int y, char operateur);
		int  appliquerFonctionSpeciale(std::vector<int>& resultats, std::vector<RollOperation>::iterator& iter);

		std::vector<RollOperation> rolls;
};

