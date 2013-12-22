
#ifndef PETRECHARGEOTHERCOMMAND_H_
#define PETRECHARGEOTHERCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/DroidObject.h"

class PetRechargeOtherCommand : public QueueCommand {
public:
	PetRechargeOtherCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().castTo<PetControlDevice*>();

		if (controlDevice == NULL)
			return GENERALERROR;

		// Droid specific command
		if( controlDevice->getPetType() != PetManager::DROIDPET )
			return GENERALERROR;

		ManagedReference<DroidObject*> droidPet = cast<DroidObject*>(creature);
		if( droidPet == NULL )
			return GENERALERROR;

		// Target must be a droid
		Reference<DroidObject*> targetDroid = server->getZoneServer()->getObject(target, true).castTo<DroidObject*>();
		if (targetDroid == NULL || !targetDroid->isDroidObject() ) {
			droidPet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			return GENERALERROR;
		}

		// Check range between droids
		if (!droidPet->isInRange(targetDroid, 30.0f)){ // Same range as auto-repair
			droidPet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			return GENERALERROR;
		}

		// Target can't be this droid
		if (droidPet == targetDroid ) {
			droidPet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			return GENERALERROR;
		}

		// Check if droid has power
		if( !droidPet->hasPower() ){
			droidPet->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			return GENERALERROR;
		}

		// Recharge other droid
		Locker clocker(targetDroid, droidPet);
		droidPet->rechargeOtherDroid( targetDroid );

		return SUCCESS;
	}

};


#endif /* PETRECHARGEOTHERCOMMAND_H_ */
