/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/creature/conversation/DeliverMissionConversationObserver.h"

DeliverMissionConversationObserverImplementation::DeliverMissionConversationObserverImplementation(ConversationTemplate* conversationTemplate) :
	ConversationObserverImplementation(conversationTemplate) {
	//Register screen handler.
	registerScreenHandler(DeliverMissionScreenHandler::STARTSCREENHANDLERID, &deliverMissionScreenHandler);
}
