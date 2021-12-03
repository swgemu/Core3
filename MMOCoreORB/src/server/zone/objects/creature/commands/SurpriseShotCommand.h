/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SURPRISESHOTCOMMAND_H_
#define SURPRISESHOTCOMMAND_H_

class SurpriseShotCommand : public CombatQueueCommand {
public:

	SurpriseShotCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->hasState(CreatureState::COVER))
			return GENERALERROR;

		ZoneServer* zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject*> targetObject = zoneServer->getObject(target);

		if (targetObject == nullptr)
			return GENERALERROR;

		if (targetObject->isCreatureObject()) {
			CreatureObject* tarCreo = targetObject->asCreatureObject();

			if (tarCreo == nullptr)
				return GENERALERROR;

			/* TODO: Implement check against alertness for either failure chance or damage bonus. This was broken Pre-CU */

			return doCombatAction(creature, target);
		} else {
			return doCombatAction(creature, target);
		}
	}

};

#endif //SURPRISESHOTCOMMAND_H_
