/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FEIGNDEATHCOMMAND_H_
#define FEIGNDEATHCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class FeignDeathCommand : public QueueCommand {
public:

	FeignDeathCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		Vector<uint32> observerTypes;
		observerTypes.add(ObserverEventType::DAMAGERECEIVED);

		ManagedReference<SingleUseBuff*> buff = new SingleUseBuff(creature, STRING_HASHCODE("private_feign_buff"), std::numeric_limits<float>::max(), BuffType::OTHER, getNameCRC());
		Locker blocker(buff, creature);

		buff->init(&observerTypes);

		creature->addBuff(buff);

		return SUCCESS;
	}

	void handleBuff(SceneObject* creature, ManagedObject* object, int64 param) {
		ManagedReference<CreatureObject*> creo = creature->asCreatureObject();
		if(creo == NULL)
			return;

		if(creo->canFeignDeath()) {
			creo->sendSystemMessage("You've successfully feigned death.");
			creo->feignDeath();
		} else {
			creo->sendSystemMessage("You've failed to feign death.");
		}

		creo->removeBuff(STRING_HASHCODE("private_feign_buff"));
	}

};

#endif //FEIGNDEATHCOMMAND_H_
