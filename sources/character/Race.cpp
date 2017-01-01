#include "Race.h"
#include "../common/Donnees.h"

using std::vector;

Race::Race()
{}

vector<NodeClasse> Race::getAllowedClasses()
{
	return Donnees::getInstance().getAllowedClasses(race);
}

Race_e Race::getRace() { return race; }

void Race::setRace(NodeRace& nodeRace)
{
	RaceInfo raceInfo;

	//On va chercher les informations rattachées à la race choisie
	race              = nodeRace.val;
	raceInfo          = Donnees::getInstance().getRaceInfo(race);
	movementRate      = raceInfo.baseMovementRate;
	mClassRestriction = raceInfo.mClassRestriction;
	iconSize          = raceInfo.iconSize;
}

int Race::getMovementRate() { return movementRate; }

MClassRestiction_e Race::getMClassRestiction() { return mClassRestriction; }

AbilitiesTable Race::getAbilitiesTable()
{
	return Donnees::getInstance().getAbilitiesTable(race);
}

Size_e Race::getIconSize() { return iconSize; }

Race::~Race()
{}
