/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/creature/conversation/PetTrainingConversationObserver.h"

PetTrainingConversationObserverImplementation::PetTrainingConversationObserverImplementation(ConversationTemplate* conversationTemplate) :
	ConversationObserverImplementation(conversationTemplate) {
	//Register screen handler.
	registerScreenHandler(PetTrainingScreenHandler::STARTSCREENHANDLERID, &screenHandler);
	registerScreenHandler(PetTrainingScreenHandler::PETATTACKCOMMAND, &screenHandler);
	registerScreenHandler(PetTrainingScreenHandler::PETCLEARPOINTSCOMMAND, &screenHandler);
	registerScreenHandler(PetTrainingScreenHandler::PETCOMMANDREPAIR, &screenHandler);
	registerScreenHandler(PetTrainingScreenHandler::PETFOLLOWCOMMAND, &screenHandler);
	registerScreenHandler(PetTrainingScreenHandler::PETFOLLOWOTHERCOMMAND, &screenHandler);
	registerScreenHandler(PetTrainingScreenHandler::PETFORMATION1COMMAND, &screenHandler);
	registerScreenHandler(PetTrainingScreenHandler::PETFORMATION2COMMAND, &screenHandler);
	registerScreenHandler(PetTrainingScreenHandler::PETFRIENDCOMMAND, &screenHandler);
	registerScreenHandler(PetTrainingScreenHandler::PETGETPOINTSCOMMAND, &screenHandler);
	registerScreenHandler(PetTrainingScreenHandler::PETGROUPCOMMAND, &screenHandler);
	registerScreenHandler(PetTrainingScreenHandler::PETGUARDCOMMAND, &screenHandler);
	registerScreenHandler(PetTrainingScreenHandler::PETPATROLCOMMAND, &screenHandler);
	registerScreenHandler(PetTrainingScreenHandler::PETRELEASECOMMAND, &screenHandler);
	registerScreenHandler(PetTrainingScreenHandler::PETSTAYCOMMAND, &screenHandler);
	registerScreenHandler(PetTrainingScreenHandler::PETTRANSFERCOMMAND, &screenHandler);
}
