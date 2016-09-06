/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/creature/conversation/DeliverMissionConversationObserver.h"

DeliverMissionConversationObserverImplementation::DeliverMissionConversationObserverImplementation(uint32 convoTemplateCRC) :
	ConversationObserverImplementation(convoTemplateCRC) {
	//Register screen handler.
	registerScreenHandler(DeliverMissionScreenHandler::STARTSCREENHANDLERID, &deliverMissionScreenHandler);
}
