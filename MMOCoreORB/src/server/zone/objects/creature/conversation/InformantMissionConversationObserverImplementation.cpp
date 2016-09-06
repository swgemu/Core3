/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/creature/conversation/InformantMissionConversationObserver.h"

InformantMissionConversationObserverImplementation::InformantMissionConversationObserverImplementation(uint32 convoTemplateCRC) :
	ConversationObserverImplementation(convoTemplateCRC) {
	//Register screen handler.
	registerScreenHandler(InformantMissionScreenHandler::STARTSCREENHANDLERID, &informantMissionScreenHandler);
}
