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
#include "server/zone/managers/stringid/StringIdManager.h"

bool SpaceStationObjectImplementation::sendConversationStartTo(SceneObject* player) {

	SceneObject* spaceStation = asSceneObject();

	if (spaceStation == nullptr || player == nullptr)
		return false;

	SceneObject* playerParent = player->getParent().get();

	ShipObject* ship = cast<ShipObject*>(playerParent);

	ShipObject* stationObject = asShipObject();

	if (ship == nullptr)
		return false;

	Locker locker(ship);

	uint64 oid = getObjectID();

	if (!ship->checkConvoInRange(spaceStation, ship)) {
		//spacestation->getConversationMessage()
		String messageString = stationObject->getConversationMessage();
		Logger::console.info(messageString);

		ship->receiveMessage(spaceStation, player, messageString, false);

		return false;
	}

	CreatureObject* playerCreature = cast<CreatureObject*>(player);

	Locker plocker(player);

	// ship->getConversationMobile()
	String mobile = stationObject->getConversationMobile();

	uint32 mobileCRC = (uint32)mobile.hashCode();

	StartNpcConversation* conv = new StartNpcConversation(playerCreature, oid, 0, "", mobileCRC);

	player->sendMessage(conv);

	//SpaceStation->getConversationTemplate();
	String convo = stationObject->getConversationTemplate();
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