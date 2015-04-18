/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/creature/conversation/TrainerConversationObserver.h"
#include "server/zone/objects/player/sessions/TrainerConversationSession.h"

TrainerConversationObserverImplementation::TrainerConversationObserverImplementation(ConversationTemplate* conversationTemplate) :
	ConversationObserverImplementation(conversationTemplate) {
	//Register screen handlers.
	registerScreenHandler(TrainerScreenHandlers::INFOSCREENHANDLERID, &trainerScreenHandlers.infoScreenHandler);

	registerScreenHandler(TrainerScreenHandlers::TRAINABLESKILLSSCREENHANDLERID, &trainerScreenHandlers.trainableSkillsScreenHandler);

	registerScreenHandler(TrainerScreenHandlers::NEXTSKILLSSCREENHANDLERID, &trainerScreenHandlers.nextSkillsScreenHandler);

	registerScreenHandler(TrainerScreenHandlers::SKILLINFOSCREENHANDLERID, &trainerScreenHandlers.skillInfoScreenHandler);

	registerScreenHandler(TrainerScreenHandlers::CANLEARNSKILLSCREENHANDLERID, &trainerScreenHandlers.canLearnSkillScreenHandler);

	registerScreenHandler(TrainerScreenHandlers::TRAINSKILLSCREENHANDLERID, &trainerScreenHandlers.trainSkillScreenHandler);

	registerScreenHandler(TrainerScreenHandlers::NOTENOUGHCREDITSSCREENHANDLERID, &trainerScreenHandlers.notEnoughCreditsScreenHandler);

	registerScreenHandler(TrainerScreenHandlers::NOTENOUGHSKILLPOINTSSCREENHANDLERID, &trainerScreenHandlers.notEnoughSkillPointsScreenHandler);

	registerScreenHandler(TrainerScreenHandlers::TRAINEDMASTERSCREENHANDLERID, &trainerScreenHandlers.trainedMasterScreenHandler);
}

void TrainerConversationObserverImplementation::createConversationSession(CreatureObject* conversingPlayer, CreatureObject* npc) {
	conversingPlayer->addActiveSession(SessionFacadeType::CONVERSATION, new TrainerConversationSession(npc));
}
