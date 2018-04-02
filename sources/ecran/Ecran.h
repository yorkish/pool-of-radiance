#pragma once
#include <memory>
#include "../common/Global.h"
#include "../queue/PileMessage.h"
#include "../texte/ListeTexte.h"

class Ecran
{
    public :
		Ecran(Renderer &renderer): renderer(renderer), oListeTexte(std::make_unique<ListeTexte>(renderer)), oPileMessage(PileMessage::getInstance()) {}

        virtual bool init() = 0;
		virtual void handleEvent( TInfoTouches& infTouches ) = 0;
        virtual void draw() = 0;
        virtual void verifierMessages() = 0;
        virtual void release() = 0;

        virtual ~Ecran() {}

    protected:
		Renderer&   renderer;
        std::unique_ptr<ListeTexte> oListeTexte;
        PileMessage& oPileMessage;
};
