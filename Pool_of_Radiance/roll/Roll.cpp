#include "Roll.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include "../common/Util.h"
#include "RollOperation.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

Roll::Roll()
{}

Roll::Roll(RollOperation roll)
{
	rolls.push_back(roll);
}

Roll::Roll(vector<RollOperation> rolls)
{
	this->rolls = rolls;
}

void Roll::appendRoll(RollOperation roll)
{
	rolls.push_back(roll);
}

void Roll::appendRoll(Roll roll)
{
	vector<RollOperation>::iterator iter;

	for(iter = roll.rolls.begin(); iter != roll.rolls.end(); iter++)
		rolls.push_back(*iter);
}

int Roll::throwDice()
{
	vector<RollOperation>::iterator iter;
	vector<int>::iterator iterResultats;
	vector<int> resultats;
	int diceResultX, diceResultY;
	int nbreLancersX  , nbreLancersY;
	int j;
	int resultat = 0;

	for(iter = rolls.begin(); iter != rolls.end(); iter++) {
		if ( (*iter).isX_SpecialOperation() ) {
			nbreLancersY = (*iter).getNbreLancersY();
			diceResultX = diceResultY = 0;

			//On exécute la fonction spéciale de l'opérande X
			diceResultX = appliquerFonctionSpeciale(resultats, iter);

			for(j = 0; j < nbreLancersY; j++)
				diceResultY += (*iter).getDiceY().throwDice();

			resultats.push_back( appliquerOperateur(diceResultX, diceResultY, (*iter).getOperateur()) );
		} else {
			nbreLancersX = (*iter).getNbreLancersX();
			nbreLancersY = (*iter).getNbreLancersY();
			diceResultX = diceResultY = 0;

			//On roule les dés
			for(j = 0; j < nbreLancersX; j++)
				diceResultX += (*iter).getDiceX().throwDice();

			for(j = 0; j < nbreLancersY; j++)
				diceResultY += (*iter).getDiceY().throwDice();

			diceResultX += (*iter).getBonusTotal();

			//cout << diceResultX << ", " << diceResultY<< "," << (*iter).getOperateur() << "    ";
			resultats.push_back( appliquerOperateur(diceResultX, diceResultY, (*iter).getOperateur()) );
		}
	}

	for(iterResultats = resultats.begin(); iterResultats != resultats.end(); iterResultats++) {
		//cout << *iterResultats << "+";
		resultat += *iterResultats;
	}
	//cout << " = " << resultat << endl;

	return resultat;
}

bool decroissant (int i, int j) { return ( i > j ); }

int Roll::appliquerFonctionSpeciale(vector<int>& resultats, vector<RollOperation>::iterator& iter)
{
	int temp;

	if ( (*iter).isX_OperationMAX() ) {
		//Utilise la fonction de trie par défaut (ordre croissant);
		sort(resultats.begin(), resultats.end());

		temp = resultats.back();
		resultats.clear();
		return temp;

	} else if ( (*iter).isX_OperationRES() ) {
		temp = resultats.back();
		resultats.pop_back();
		return temp;

	} else if ( (*iter).isX_OperationBEST3() ) {
		//Utilise la fonction de trie par défaut (ordre croissant);
		sort(resultats.begin(), resultats.end(), decroissant);

		//On garde les 3 plus grand lancer de dés
		int nbreElem = resultats.size() - 3;
		for (int i = 0; i < nbreElem; i++)
			resultats.pop_back();

		return 0;
	}

	return 0;
}

int Roll::appliquerOperateur(int x, int y, char operateur)
{
	switch (operateur) {
	case '+': return x + y;
	case '-': return x - y;
	case '*': return x * y;
	case '/': return ceil((double) x / y);
	default:  return 0;
	}
}

void Roll::reset()
{
	rolls.clear();
}

Roll::~Roll() {}
