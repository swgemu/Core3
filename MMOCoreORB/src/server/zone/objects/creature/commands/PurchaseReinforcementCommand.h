/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PURCHASEREINFORCEMENTCOMMAND_H_
#define PURCHASEREINFORCEMENTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PurchaseReinforcementCommand : public QueueCommand {
public:

	PurchaseReinforcementCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif //PURCHASEREINFORCEMENTCOMMAND_H_
