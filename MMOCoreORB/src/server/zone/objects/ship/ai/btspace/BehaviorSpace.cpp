/*
 * BehaviorSpace.cpp
 */

#include "server/zone/objects/ship/ai/btspace/BehaviorSpace.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"

#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"

using namespace server::zone::objects::ship::ai::btspace;

BehaviorSpace::BehaviorSpace(const String& className, const uint32 id, const LuaObject& args) : Object(), className(className), id(id), parent() {}

bool BehaviorSpace::checkConditions(ShipAiAgent* agent) const {
	if (agent == nullptr)
		return false;

	ZoneServer* zoneServer = agent->getZoneServer();

	if (zoneServer == nullptr || zoneServer->isServerLoading())
		return false;

	auto spaceZone = agent->getZone();

	if (spaceZone == nullptr || !spaceZone->isSpaceZone())
		return false;

	if (zoneServer->isServerShuttingDown()) {
		agent->wipeBlackboard();
		agent->cancelBehaviorEvent();

		return false;
	}

	return true;
}

BehaviorSpace::Status BehaviorSpace::doAction(ShipAiAgent* agent) const {
#ifdef DEBUG_SHIP_AI
	if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true) {
		StringBuffer msg;

		msg << "0x" << hex << id << " " << print().toCharArray();
		agent->info(true) << agent->getDisplayedName() << " ID: " << agent->getObjectID() << " - " << msg.toString();
	}
#endif // DEBUG_SHIP_AIs

	if (!checkConditions(agent)) {
		return INVALID;
	}

	// Step 1:	check if this behavior is in the running chain
	//			If it isn't, call start()
	//			We can assume here that if we are running here, that this is the
	//			leaf that is actually running because all other running states
	//			will be composites and would have a different reaction to being
	//			in the running vector
	if (!agent->isRunningBehavior(id))
		this->start(agent);
	else
		agent->popRunningChain();

	// Step 2:	evaluate the action result (method to do this will be abstract
	//			and implemented in the concrete behaviors)
	BehaviorSpace::Status result = this->execute(agent);

#ifdef DEBUG_SHIP_AI
	if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true) {
		StringBuffer msg;
		msg << "0x" << hex << id << " " << print() << " result: " << result;

		agent->info(true) << agent->getDisplayedName() << " ID: " << agent->getObjectID() << " - " << msg.toString();
	}
#endif // DEBUG_SHIP_AI

	// Step 3:	If the result is RUNNING, clear the agent's run chain and and
	//			add this->id to the front. As the chain unwinds, the composite
	//			parents will push_front to the chain until the root node
	if (result == RUNNING) {
		if (!isSocketSpace())
			agent->clearRunningChain();

		agent->addRunningID(id);
	} else
		this->end(agent);

	// Step 4:	If the result is anything else (TODO: SUSPEND?) just return that
	//			value; the parent will deal with the next action based on the
	//			type of parent.
	return result;
}
