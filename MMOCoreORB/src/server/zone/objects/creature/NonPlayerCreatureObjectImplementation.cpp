/*
 * NonPlayerCreatureObjectImplementation.cpp
 *
 *  Created on: 23/06/2010
 *      Author: victor
 */

#include "NonPlayerCreatureObject.h"
#include "server/zone/packets/object/StartNpcConversation.h"
#include "server/zone/packets/object/StopNpcConversation.h"
#include "server/zone/templates/mobile/ConversationScreen.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/components/ComponentManager.h"
#include "server/zone/objects/creature/components/AiNPCComponent.h"

//#define DEBUG

void NonPlayerCreatureObjectImplementation::initializeTransientMembers() {
	AiAgentImplementation::initializeTransientMembers();
	aiInterfaceComponents.add(ComponentManager::instance()->getComponent<AiNPCComponent*>("AiNPCComponent"));
}

