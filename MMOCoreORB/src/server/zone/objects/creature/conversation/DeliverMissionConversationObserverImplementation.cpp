/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/creature/conversation/ConversationObserver.h"
#include "server/zone/objects/creature/conversation/DeliverMissionConversationObserver.h"
#include "server/zone/objects/creature/conversation/screenhandlers/DeliverMissionScreenHandler.h"
#include "system/platform.h"

DeliverMissionConversationObserverImplementation::DeliverMissionConversationObserverImplementation(uint32 convoTemplateCRC) :
	ConversationObserverImplementation(convoTemplateCRC) {
	//Register screen handler.
	registerScreenHandler(DeliverMissionScreenHandler::STARTSCREENHANDLERID, &deliverMissionScreenHandler);
}
