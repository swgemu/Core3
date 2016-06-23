/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ADDPOWERCOMMAND_H_
#define ADDPOWERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/resource/ResourceManager.h"

class AddPowerCommand : public QueueCommand {
public:

	AddPowerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		ManagedReference<SceneObject*> obj = playerManager->getInRangeStructureWithAdminRights(creature, target);

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

		StructureObject* structure = cast<StructureObject*>( obj.get());

		if (structure->getBasePowerRate() <= 0) {
			return INVALIDTARGET;
		}

		int amount = 0;

		try {
			UnicodeTokenizer tokenizer(arguments);
			amount = tokenizer.getIntToken();

		} catch (Exception& e) {
			creature->sendSystemMessage("@player_structure:unable_to_parse"); //The system was unable to parse a valid power amount.
			return INVALIDPARAMETERS;
		}

		if (amount < 0) {
			creature->sendSystemMessage("@player_structure:enter_valid_over_zero"); //Please enter a valid power amount greater than 0.
			return INVALIDPARAMETERS;
		}

		ResourceManager* resourceManager = server->getZoneServer()->getResourceManager();
		uint32 totalPower = resourceManager->getAvailablePowerFromPlayer(creature);

		if (totalPower < amount) {
			StringIdChatParameter params("@player_structure:not_enough_energy"); //You do not have %DI units of energy in your inventory!
			params.setDI(amount);

			creature->sendSystemMessage(params);
			return INVALIDPARAMETERS;
		}

		resourceManager->removePowerFromPlayer(creature, amount);

		Locker _lock(structure);

		structure->addPower(amount);

		StringIdChatParameter params("@player_structure:deposit_successful"); //You successfully deposit %DI units of energy.
		params.setDI(amount);

		creature->sendSystemMessage(params);

		return SUCCESS;
	}

};

#endif //ADDPOWERCOMMAND_H_
