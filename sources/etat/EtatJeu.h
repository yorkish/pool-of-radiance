#pragma once

#include "../common/Global.h"
#include "../queue/PileMessage.h"
#include "../common/Renderer.h"

class EtatJeu
{
    public :
		EtatJeu(Renderer &renderer): renderer(renderer), oPileMessage(PileMessage::getInstance()) {}

        virtual bool onEnter() = 0;
		virtual void update(TInfoTouches& keysInfo) = 0;
        virtual void render() = 0;
        virtual void checkMessages() = 0;
        virtual bool onExit() = 0;
        virtual std::string getStateID() const = 0;
        virtual ~EtatJeu() {}

    protected:
        Renderer &renderer;
        PileMessage &oPileMessage;
};
