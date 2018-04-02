#pragma once

#include "../common/Global.h"
#include "../queue/PileMessage.h"
#include "../common/Renderer.h"

class EtatJeu
{
    public :
		EtatJeu(Renderer &renderer): renderer(renderer), oPileMessage(PileMessage::getInstance()) {}

        virtual bool init() = 0;
		virtual void handleEvent( TInfoTouches& infTouches ) = 0;
        virtual void draw() = 0;
        virtual void verifierMessages() = 0;
        virtual void release() = 0;

        virtual ~EtatJeu() {}

    protected:
        Renderer &renderer;
        PileMessage &oPileMessage;
};
