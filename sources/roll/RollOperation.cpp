#include <stdlib.h>
#include "RollOperation.h"
#include "../common/Util.h"

using std::string;

RollOperation::RollOperation(): x(""), y(""), operateur(' '), posD_x(string::npos), posD_y(string::npos), nbreLancersX(1), nbreLancersY(1), bonusPerDie(0)
{}

RollOperation::RollOperation(string x, string y, char operateur): posD_x(string::npos), posD_y(string::npos), nbreLancersX(1), nbreLancersY(1), bonusPerDie(0)
{
	Util::toUpperCase(x);
	Util::toUpperCase(y);

	this->x = x;
	this->y = y;
	this->operateur = operateur;

	setNbreLancers();
	setDices();
}

void RollOperation::setNbreLancers()
{
	if (x == "" || y == "")
		return;

	nbreLancersX = nbreLancersY = 1;

	// nbLancerX
	posD_x = x.find_first_of('D');

	if ( posD_x != string::npos) {
		string temp = x.substr(0, posD_x);
		nbreLancersX = atoi(temp.c_str());
	}

	// nbLancerY
	posD_y = y.find_first_of('D');

	if (posD_y != string::npos) {
		string temp = y.substr(0, posD_y);
		nbreLancersY = atoi(temp.c_str());
	}
}

void RollOperation::setDices()
{
	if (posD_x != string::npos)
		diceX = Dice( x.substr(posD_x) );
	else if ( !isX_SpecialOperation() )
		diceX = Dice( x );

	if (posD_y != string::npos)
		diceY = Dice( y.substr(posD_y) );
	else
		diceY = Dice( y );
}

bool RollOperation::isX_SpecialOperation()
{
	return (isX_OperationMAX()   ||
			isX_OperationRES()   ||
			isX_OperationBEST3()    );
}

bool RollOperation::isX_OperationMAX()  { return (x.compare("MAX")  == 0); }
bool RollOperation::isX_OperationRES()  { return (x.compare("RES")  == 0); }
bool RollOperation::isX_OperationBEST3() { return (x.compare("BEST3") == 0); }

void RollOperation::setX(string x)
{
	Util::toUpperCase(x);
	this->x = x;

	if (x != "" || y != "") {
		setNbreLancers();
		setDices();
	}
}

void RollOperation::setY(string y)
{
	Util::toUpperCase(y);
	this->y = y;

	if (x != "" || y != "") {
		setNbreLancers();
		setDices();
	}
}

char RollOperation::getOperateur() const { return operateur; }
void RollOperation::setOperateur(char operateur) { this->operateur = operateur; }
void RollOperation::setOperateur(string operateur) { this->operateur = operateur[0]; }

int  RollOperation::getNbreLancersX() const { return nbreLancersX; }
int  RollOperation::getNbreLancersY() const { return nbreLancersY; }

void RollOperation::addToY(int valeur)
{
	if (posD_y == string::npos) {
		valeur += diceY.throwDice();
		y = Util::toStr(valeur);
		diceY = Dice(y);
	}
}

Dice RollOperation::getDiceX() const { return diceX; }
Dice RollOperation::getDiceY() const { return diceY; }

string RollOperation::getStringRep()
{
	string temp;

	temp = x;

	if ( y.compare("0") != 0)
		temp += operateur + y;

	return temp;
}

//Le bonus est calculé selon le nombre de lancers en X
int RollOperation::getBonusTotal()
{
	return nbreLancersX * bonusPerDie;
}

void RollOperation::setBonusPerDie(int bonusPerDie) { this->bonusPerDie = bonusPerDie; }

//Copy constructor
RollOperation::RollOperation(const RollOperation& object)
{
	x = object.x;
	y = object.y;
	operateur = object.operateur;

	posD_x = object.posD_x;
	posD_y = object.posD_y;

	nbreLancersX = object.nbreLancersX;
	nbreLancersY = object.nbreLancersY;

	bonusPerDie = object.bonusPerDie;

	diceX = object.diceX;
	diceY = object.diceY;
}

RollOperation::~RollOperation()
{}
