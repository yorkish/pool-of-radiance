#pragma once
#include "queue/PileMessage.h"

class SaveGameManager {
	public:
		SaveGameManager();

		void verifierMessages();

		~SaveGameManager();

	private:
		void* getLettresSauvegardes();

		PileMessage& oPileMessage;
};

