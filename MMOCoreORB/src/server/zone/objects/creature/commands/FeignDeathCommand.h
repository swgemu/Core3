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

		if(creature->isInCombat() == false) {
			creature->sendSystemMessage("@combat_effects:feign_no_combat");
			return GENERALERROR;
		}

		Vector<uint32> observerTypes;
		observerTypes.add(ObserverEventType::DAMAGERECEIVED);

		ManagedReference<SingleUseBuff*> buff = new SingleUseBuff(creature, STRING_HASHCODE("private_feign_buff"), std::numeric_limits<float>::max(), BuffType::OTHER, getNameCRC());

		Locker locker(buff, creature); // buff->init requires buff to be locked
		buff->init(&observerTypes);
		buff->setSkillModifier("private_defense", -99999999);

		creature->addBuff(buff);


		creature->sendSystemMessage("@cbt_spam:feign_get_hit_single");

		return SUCCESS;
	}

	void handleBuff(SceneObject* creature, ManagedObject* object, int64 param) {
		ManagedReference<CreatureObject*> creo = creature->asCreatureObject();

		if(creo == NULL)
			return;

		Locker lock(creo);

		if(creo->canFeignDeath()) {
			creo->feignDeath();
		} else {
			creo->sendSystemMessage("@cbt_spam:feign_fail_single");
		}

		creo->removeBuff(STRING_HASHCODE("private_feign_buff"));

	}

};

#endif //FEIGNDEATHCOMMAND_H_
