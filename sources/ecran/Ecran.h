#pragma once

#include "../common/Global.h"
#include "../queue/PileMessage.h"

class Ecran
{
    public :
		Ecran(): oPileMessage(PileMessage::getInstance()) {}

        virtual bool init() = 0;
		virtual void handleEvent( TInfoTouches& infTouches ) = 0;
        virtual void draw() = 0;
        virtual void verifierMessages() = 0;
        virtual void release() = 0;

        virtual ~Ecran() {}

    protected:
        PileMessage& oPileMessage;
};
