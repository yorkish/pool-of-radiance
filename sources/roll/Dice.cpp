#include "Dice.h"
#include <iostream>
#include <stdlib.h>

using std::string;
using std::cout;
using std::endl;

Dice::Dice(): dice(DICE_NONE), value(0)
{}

Dice::Dice(string strDice): dice(DICE_NONE), value(0)
{
	int diceType;
	string temp;
	size_t pos;

	pos = strDice.find('D');

	if (pos != string::npos) {
		temp = strDice.substr( pos+1, strDice.length() );
		if (temp.length() != 0) {
			diceType = atoi( temp.c_str() );

			switch(diceType) {
			case 2  : dice = D2;  		break;
			case 4  : dice = D4;  		break;
			case 6  : dice = D6;  		break;
			case 8  : dice = D8;  		break;
			case 10 : dice = D10; 		break;
			case 12 : dice = D12;  		break;
			case 20 : dice = D20;  		break;
			case 100: dice = D100; 		break;
			default:  dice = DICE_NONE; break;
			}
		}
	} else
		value = atoi( strDice.c_str() );
}

int Dice::throwDice()
{
	int result;

	switch (dice)
	{
	case D2:        result = (int) (rand() % 2   + 1); break;
	case D4:        result = (int) (rand() % 4   + 1); break;
	case D6:        result = (int) (rand() % 6   + 1); break;
	case D8:        result = (int) (rand() % 8   + 1); break;
	case D10:       result = (int) (rand() % 10  + 1); break;
	case D12:       result = (int) (rand() % 12  + 1); break;
	case D20:       result = (int) (rand() % 20  + 1); break;
	case D100:      result = (int) (rand() % 100 + 1); break;
	case DICE_NONE: result =  value; 				   break;
	}

	//cout << result << endl;
	return result;
}

Dice::~Dice() {}
