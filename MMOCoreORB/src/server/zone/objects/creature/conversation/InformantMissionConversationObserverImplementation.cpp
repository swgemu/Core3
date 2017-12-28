/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/creature/conversation/ConversationObserver.h"
#include "server/zone/objects/creature/conversation/InformantMissionConversationObserver.h"
#include "server/zone/objects/creature/conversation/screenhandlers/InformantMissionScreenHandler.h"
#include "system/platform.h"

InformantMissionConversationObserverImplementation::InformantMissionConversationObserverImplementation(uint32 convoTemplateCRC) :
	ConversationObserverImplementation(convoTemplateCRC) {
	//Register screen handler.
	registerScreenHandler(InformantMissionScreenHandler::STARTSCREENHANDLERID, &informantMissionScreenHandler);
}
