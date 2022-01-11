
#ifndef PETHARVESTCOMMAND_H_
#define PETHARVESTCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/tangible/components/droid/DroidHarvestModuleDataComponent.h"

class PetHarvestCommand : public QueueCommand {
public:
	PetHarvestCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& targetID, const UnicodeString& arguments) const {
		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().get().castTo<PetControlDevice*>();
		if (controlDevice == nullptr)
			return GENERALERROR;

		ManagedReference<AiAgent*> pet = cast<AiAgent*>(creature);

		if (pet == nullptr)
			return GENERALERROR;

		if (pet->hasRidingCreature())
			return GENERALERROR;

		ManagedReference<CreatureObject*> owner = pet->getLinkedCreature().get();

		if (owner == nullptr) {
			return GENERALERROR;
		}

		Locker lock(owner);

		ManagedReference<DroidObject*> droid = cast<DroidObject*>(creature);

		if (droid == nullptr)
			return GENERALERROR;

		Locker clock(droid, owner);

		// Check droid states, droids cant harvest while in combat
		if (droid->isDead() || droid->isIncapacitated() || droid->isInCombat()) {
			return GENERALERROR;
		}

		// Droid must have power
		if (!droid->hasPower()) {
			droid->showFlyText("npc_reaction/flytext", "low_power", 204, 0, 0); // "*Low Power*"
			return GENERALERROR;
		}

		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		SceneObject* targetObject = zoneServer->getObject(targetID, true);

		if (targetObject == nullptr || !targetObject->isCreature()) {
			owner->sendSystemMessage("@pet/droid_modules:invalid_harvest_target");
			return GENERALERROR;
		}

		CreatureObject* tarCreo = targetObject->asCreatureObject();

		if (tarCreo == nullptr)
			return GENERALERROR;

		if (!tarCreo->isDead()) {
			owner->sendSystemMessage("@pet/droid_modules:invalid_harvest_target");
			return GENERALERROR;
		}

		if (!tarCreo->isInRange(owner, 64.f)) {
			pet->showFlyText("npc_reaction/flytext", "confused", 204, 0, 0); // "?!!?!?!"
			return GENERALERROR;
		}

		auto module = droid->getModule("harvest_module").castTo<DroidHarvestModuleDataComponent*>();

		if (module == nullptr) {
			return GENERALERROR;
		}

		pet->showFlyText("npc_reaction/flytext", "threaten", 204, 0, 0);

		module->addHarvestTarget(targetID, true);

		return SUCCESS;
	}
};

#endif /* PETHARVESTCOMMAND_H_ */
