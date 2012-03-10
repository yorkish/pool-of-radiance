#pragma once

#include <stack>
#include "Message.h"

class PileMessage {
	public:
		PileMessage();

		static PileMessage& getInstance();
		void pushMessage( Message message );
		void popMessage();
		Message getMessageCourant();

		~PileMessage();

	private:
		static PileMessage* singleton;

		std::stack<Message> pileMessage;
		Message* message;
};
