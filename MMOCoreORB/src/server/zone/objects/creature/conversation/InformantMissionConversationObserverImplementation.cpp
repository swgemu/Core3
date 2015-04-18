/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/creature/conversation/InformantMissionConversationObserver.h"

InformantMissionConversationObserverImplementation::InformantMissionConversationObserverImplementation(ConversationTemplate* conversationTemplate) :
	ConversationObserverImplementation(conversationTemplate) {
	//Register screen handler.
	registerScreenHandler(InformantMissionScreenHandler::STARTSCREENHANDLERID, &informantMissionScreenHandler);
}
