#include "PileMessage.h"

// Initialisation du singleton à NULL
PileMessage* PileMessage::singleton = 0;

PileMessage::PileMessage() {}

PileMessage& PileMessage::getInstance() {
	if (singleton == 0)
		singleton = new PileMessage();

	return *singleton;
}

void PileMessage::pushMessage( Message message )
{
	pileMessage.push( message );
}

void PileMessage::popMessage()
{
    if ( !pileMessage.empty() )
    	pileMessage.pop();
}

Message PileMessage::getMessageCourant()
{
	if (!pileMessage.empty())
		return pileMessage.top();
	else
		return Message(OBJ_NONE, OBJ_NONE, GM_NONE);
}

PileMessage::~PileMessage()
{
    if ( !pileMessage.empty() )
    	pileMessage.pop();

	if (singleton != 0)
		delete singleton;
}

