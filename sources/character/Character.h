#pragma once
#include <vector>
#include "../common/Global.h"
#include "../queue/PileMessage.h"
#include "Race.h"
#include "Classe.h"

class Character {
	public:
		Character();

		void setRace(NodeRace& nodeRace);
		void setGender(NodeGender& nodeGender);
		void setClasse(NodeClasse& nodeClasse);
		void setAlignment(NodeAlignment& nodeAlignment);
		void generateCharacter();
		void verifierMessages();

		~Character();

	private:
		void selectTHAC_Table();
		void rollAbilities();
		bool validateAbilities(const AbilitiesTable& table);
		void bonusPerAbilities();
		void rollStartingAge();
		void rollStartingGold();
		void rollHitPoints();
		void calculateEncumbrance();

		PileMessage& oPileMessage;
		Race         oRace;

		Classe       oTabClasses[3];
		int posClasseTHAC;

		CharacterInfo info;

		int MAX_CLASSES;
};
