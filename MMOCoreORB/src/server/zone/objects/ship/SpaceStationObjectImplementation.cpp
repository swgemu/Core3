/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/chat/StringIdChatParameter.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/conversation/ConversationObserver.h"
#include "server/zone/managers/conversation/ConversationManager.h"
#include "server/zone/objects/ship/SpaceStationObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/NpcConversationMessage.h"
#include "server/zone/packets/object/StartNpcConversation.h"
#include "server/zone/packets/object/StringList.h"

bool SpaceStationObjectImplementation::sendConversationStartTo(SceneObject* player) {

	SceneObject* spaceStation = this->asSceneObject();

	if (spaceStation == nullptr)
		Logger::console.info(true) << "SpaceStationObjectImplementation::sendConversationStartTo " << spaceStation->getDisplayedName() << " is nullptr.";

	CreatureObject* playerCreature = cast<CreatureObject*>(player);

	uint64 oid = getObjectID();

	String mobile = spaceStation->getObjectTemplate()->getConversationMobile();

	uint32 mobileCRC = (uint32)mobile.hashCode();
	Logger::console.info(true) << spaceStation->getObjectTemplate()->getConversationMobile();
	Logger::console.info(true) << String::valueOf(oid);

	StartNpcConversation* conv = new StartNpcConversation(playerCreature, oid, "test", mobileCRC);

	player->sendMessage(conv);

	String convo = spaceStation->getObjectTemplate()->getConversationTemplate();
	uint32 convoCRC = (uint32) convo.hashCode();

	ConversationTemplate* conversationTemplate = CreatureTemplateManager::instance()->getConversationTemplate(convoCRC);

	SortedVector<ManagedReference<Observer*> > observers = getObservers(ObserverEventType::STARTCONVERSATION);

	for (int i = 0; i < observers.size(); ++i) {
		if (dynamic_cast<ConversationObserver*>(observers.get(i).get()) != nullptr)
			return true;
	}

	ConversationObserver* conversationObserver = ConversationManager::instance()->getConversationObserver(convoCRC);

	if (conversationObserver != nullptr) {
		registerObserver(ObserverEventType::CONVERSE, conversationObserver);
		registerObserver(ObserverEventType::STARTCONVERSATION, conversationObserver);
		registerObserver(ObserverEventType::SELECTCONVERSATION, conversationObserver);
		registerObserver(ObserverEventType::STOPCONVERSATION, conversationObserver);
	} else {
		error("Could not create conversation observer for Space Station.");
		return false;
	}

	return true;

}

bool SpaceStationObject::isSpaceStationObject() {
	return true;
}

bool SpaceStationObjectImplementation::isSpaceStationObject() {
	return true;
}