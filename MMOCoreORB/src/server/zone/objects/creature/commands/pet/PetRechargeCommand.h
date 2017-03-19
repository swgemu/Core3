
#ifndef PETRECHARGECOMMAND_H_
#define PETRECHARGECOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/ai/DroidObject.h"

class PetRechargeCommand : public QueueCommand {
public:
	PetRechargeCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().get().castTo<PetControlDevice*>();

		if (controlDevice == NULL)
			return GENERALERROR;

		// Droid specific command
		if( controlDevice->getPetType() != PetManager::DROIDPET )
			return GENERALERROR;

		ManagedReference<DroidObject*> droidPet = cast<DroidObject*>(creature);
		if( droidPet == NULL )
			return GENERALERROR;

		ManagedReference< CreatureObject*> player = droidPet->getLinkedCreature().get();
		if( player == NULL )
			return GENERALERROR;

		// Recharge
		Locker plocker(player, creature);
		droidPet->rechargeFromBattery(player);

		return SUCCESS;
	}

};


#endif /* PETRECHARGECOMMAND_H_ */
