#include "Message.h"

Message::Message(NomObjet source, NomObjet destinataire, TypeMessage typeMessage)
{
	this->source       = source;
	this->destinataire = destinataire;
	this->typeMessage  = typeMessage;
	this->contenu      = 0;
}

Message::Message(NomObjet source, NomObjet destinataire, TypeMessage typeMessage, void* contenu)
{
	this->source       = source;
	this->destinataire = destinataire;
	this->typeMessage  = typeMessage;
	this->contenu      = contenu;
}

NomObjet Message::getSource()
{ return source; }

NomObjet Message::getDestinataire()
{ return destinataire; }

TypeMessage Message::getTypeMessage()
{ return typeMessage; }

void* Message::getContenu()
{ return contenu; }

Message::~Message()
{}
