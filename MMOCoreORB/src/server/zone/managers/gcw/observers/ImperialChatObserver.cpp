/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
 */

#include "server/zone/managers/gcw/observers/ImperialChatObserver.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/managers/reaction/ReactionManager.h"
#include "server/zone/ZoneServer.h"

int ImperialChatObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (observable == nullptr || arg1 == nullptr)
		return 0;

	SceneObject* imperialObject = cast<SceneObject*>(observable);
	SceneObject* sourceObject = cast<SceneObject*>(arg1);

	if (imperialObject == nullptr || sourceObject == nullptr)
		return 0;

	if (!imperialObject->isAiAgent() || !sourceObject->isPlayerCreature())
		return 0;

	ManagedReference<AiAgent*> agent = imperialObject->asAiAgent();
	ManagedReference<CreatureObject*> creature = sourceObject->asCreatureObject();

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

	Locker clock(creature, agent);
	reactionManager->reactionFine(creature, agent, 3);

	return 0;
}