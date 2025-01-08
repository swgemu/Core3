/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/objects/ship/ai/ShipCapitalObject.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/conversation/ConversationObserver.h"
#include "server/zone/managers/conversation/ConversationManager.h"

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/StartNpcConversation.h"
#include "server/zone/packets/object/StringList.h"
#include "server/zone/managers/stringid/StringIdManager.h"

float ShipCapitalObjectImplementation::getOutOfRangeDistance() const {
	return ZoneServer::SHIPCAPITALRANGE;
}

int ShipCapitalObjectImplementation::getReceiverFlags() const {
	int type = CloseObjectsVector::SHIPCAPITALTYPE;

	return type | ShipAiAgentImplementation::getReceiverFlags();
}
