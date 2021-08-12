/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COMBATMODECHECKCOMMAND_H_
#define COMBATMODECHECKCOMMAND_H_

#include "server/zone/managers/gcw/GCWManager.h"

class CombatModeCheckCommand : public QueueCommand {
public:

	CombatModeCheckCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		auto zone = creature->getZone();
		if (zone != nullptr) {
			auto gcwManager = zone->getGCWManager();
			if (gcwManager != nullptr) {
				creature->sendSystemMessage(gcwManager->getCrackdownInfo(creature));
				return SUCCESS;
			} else {
				creature->sendSystemMessage("No GCWManager available.");
			}
		} else {
			creature->sendSystemMessage("No zone available.");
		}
		return GENERALERROR;
	}

};

#endif //COMBATMODECHECKCOMMAND_H_
