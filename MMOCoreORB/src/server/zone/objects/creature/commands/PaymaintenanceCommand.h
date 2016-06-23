/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PAYMAINTENANCECOMMAND_H_
#define PAYMAINTENANCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PaymaintenanceCommand : public QueueCommand {
public:

	PaymaintenanceCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->getCashCredits() <= 0) {
			creature->sendSystemMessage("@player_structure:no_money"); //You do not have any money to pay maintenance.
			return GENERALERROR;
		}

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		uint64 targetid = target;
		if(targetid <= 0)
			targetid = creature->getTargetID();

		ManagedReference<SceneObject*> obj = playerManager->getInRangeStructureWithAdminRights(creature, targetid);

		ManagedReference<SceneObject*> currenttarget = server->getZoneServer()->getObject(target);

		if (creature->getTargetID() == 0 || !currenttarget->isStructureObject()) {
			creature->sendSystemMessage("You must TARGET the actual STRUCTURE before you can execute that command upon it.");
			return INVALIDTARGET;
		}

		if (obj->getObjectID() != creature->getTargetID()) {
			creature->sendSystemMessage("You must move closer to the currently targeted structure before performing that action.");
			return GENERALERROR;
		}

		if (obj == NULL || !obj->isStructureObject())
			return INVALIDTARGET;

		StructureObject* structure = cast<StructureObject*>(obj.get());

		Locker clocker(structure, creature);

		ManagedReference<Zone*> zone = structure->getZone();

		if (zone == NULL)
			return INVALIDPARAMETERS;

		if (structure->isCivicStructure()) {
			creature->sendSystemMessage("@player_structure:civic_structure_alert"); // Civic structure: Maintenance handled by city.
			return INVALIDTARGET;
		}

		if (structure->isGCWBase()) {
			return INVALIDTARGET;
		}

		StructureManager* structureManager = StructureManager::instance();

		try {
			UnicodeTokenizer tokenizer(arguments);
			int amount = tokenizer.getIntToken();

			if (amount > 0)
				structureManager->payMaintenance(structure, creature, amount);
		} catch (Exception& e) {
			structureManager->promptPayMaintenance(structure, creature);
		}

		return SUCCESS;
	}

};

#endif //PAYMAINTENANCECOMMAND_H_
