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
	if (player == nullptr || !player->isPlayerCreature())
		return false;

	CreatureObject* playerCreature = player->asCreatureObject();

	if (playerCreature == nullptr)
		return false;

	SceneObject* playerParent = nullptr;

	if (playerCreature->hasState(CreatureState::PILOTINGSHIP)) {
		playerParent = playerCreature->getParent().get();
	} else if (playerCreature->hasState(CreatureState::PILOTINGPOBSHIP)) {
		playerParent = playerCreature->getRootParent();
	}

	if (playerParent == nullptr || !playerParent->isShipObject())
		return false;

	ShipObject* playerShip = playerParent->asShipObject();

	if (playerShip == nullptr)
		return false;

	uint64 oid = getObjectID();

	if (!playerShip->checkInConvoRange(asShipObject())) {
		String messageString = getConversationMessage();

		playerCreature->sendSpaceConversation(asShipObject(), messageString, false);

		return false;
	}

	String mobile = getConversationMobile();
	uint32 mobileCRC = mobile.hashCode();

	StartNpcConversation* conv = new StartNpcConversation(playerCreature, oid, 0, "", mobileCRC);

	playerCreature->sendMessage(conv);

	String convo = getConversationTemplate();
	uint32 convoCRC = convo.hashCode();

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