/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
 */

#include "server/zone/managers/gcw/observers/ImperialChatObserver.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/managers/reaction/ReactionManager.h"
#include "server/zone/ZoneServer.h"

int ImperialChatObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (observable == nullptr)
		return 1;

	if (arg1 == nullptr)
		return 0;

	SceneObject* imperialObject = cast<SceneObject*>(observable);
	SceneObject* sourceObject = cast<SceneObject*>(arg1);

	if (imperialObject == nullptr || !imperialObject->isAiAgent())
		return 1;

	if (sourceObject == nullptr || !sourceObject->isPlayerCreature())
		return 0;

	AiAgent* agent = imperialObject->asAiAgent();
	CreatureObject* creature = sourceObject->asCreatureObject();

	if (agent == nullptr || creature == nullptr)
		return 0;

	if (agent->isDead())
		return 1;

	ZoneServer* zoneServer = agent->getZoneServer();

	if (zoneServer == nullptr)
		return 0;

	ReactionManager* reactionManager = zoneServer->getReactionManager();

	if (reactionManager == nullptr)
		return 0;

	reactionManager->reactionFine(creature, agent, 3);

	return 0;
}