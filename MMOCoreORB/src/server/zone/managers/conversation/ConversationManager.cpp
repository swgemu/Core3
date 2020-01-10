/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "ConversationManager.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/objects/creature/conversation/DeliverMissionConversationObserver.h"
#include "server/zone/objects/creature/conversation/InformantMissionConversationObserver.h"
#include "server/zone/objects/creature/conversation/LuaConversationObserver.h"
#include "server/zone/objects/creature/conversation/PetTrainingConversationObserver.h"

ConversationManager::ConversationManager()
	: Logger("ConversationManager") {
}

ConversationManager::~ConversationManager() {
	//Do nothing.
}

ConversationObserver* ConversationManager::getConversationObserver(uint32 conversationTemplateCRC) {
	if (conversationObservers.containsKey(conversationTemplateCRC)) {
		//Observer does already exist, return it.
		return conversationObservers.get(conversationTemplateCRC).get();
	} else {
		if (CreatureTemplateManager::DEBUG_MODE)
			return nullptr;
		//No observer, create it.
		ManagedReference<ConversationObserver*> conversationObserver = nullptr;
		ConversationTemplate* conversationTemplate = CreatureTemplateManager::instance()->getConversationTemplate(conversationTemplateCRC);
		if (conversationTemplate != nullptr) {
			switch (conversationTemplate->getConversationTemplateType()) {
			case ConversationTemplate::ConversationTemplateTypeNormal:
				conversationObserver = new ConversationObserver(conversationTemplateCRC);
				break;
			case ConversationTemplate::ConversationTemplateTypeDeliverMission:
				conversationObserver = new DeliverMissionConversationObserver(conversationTemplateCRC);
				break;
			case ConversationTemplate::ConversationTemplateTypeInformantMission:
				conversationObserver = new InformantMissionConversationObserver(conversationTemplateCRC);
				break;
			case ConversationTemplate::ConversationTemplateTypeLua:
				conversationObserver = new LuaConversationObserver(conversationTemplateCRC);
				break;
			case ConversationTemplate::ConversationTemplateTypePersonality:
				conversationObserver = new PetTrainingConversationObserver(conversationTemplateCRC);
				break;
			default:
				conversationObserver = new ConversationObserver(conversationTemplateCRC);
				break;
			}

			if (conversationObserver != nullptr) {
				//Add it to the map.
				conversationObservers.put(conversationTemplateCRC, conversationObserver);
			}
		}
		return conversationObserver;
	}
}
