#pragma once

#include <vector>
#include "../common/Global.h"

class Race {
	public:
		Race();

		Race_e getRace();
		void   setRace(NodeRace& nodeRace);

		std::vector<NodeClasse> getAllowedClasses();
		int getMovementRate();
		AbilitiesTable getAbilitiesTable();
		MClassRestiction_e getMClassRestiction();
		Size_e getIconSize();

		~Race();

	private:
		Race_e             race;
		int                movementRate;
		MClassRestiction_e mClassRestriction;
		Size_e             iconSize;
};

