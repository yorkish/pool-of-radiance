#pragma once
#include <string>

class Dice {
	public:
		Dice();
		Dice(std::string strDice);

		int throwDice();
		~Dice();

	private:
		enum Dice_e { D2, D4, D6, D8, D10, D12, D20, D100, DICE_NONE };
		Dice_e dice;

		int value;
};

