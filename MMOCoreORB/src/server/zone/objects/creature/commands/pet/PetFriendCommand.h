
#ifndef PETFRIENDCOMMAND_H_
#define PETFRIENDCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/managers/creature/PetManager.h"

class PetFriendCommand : public QueueCommand {
public:
	PetFriendCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().castTo<PetControlDevice*>();
		if (controlDevice == NULL)
			return GENERALERROR;

		ManagedReference<AiAgent*> pet = cast<AiAgent*>(creature);
		if( pet == NULL )
			return GENERALERROR;

		if (pet->hasRidingCreature())
			return GENERALERROR;

		// Check if droid has power
		if( controlDevice->getPetType() == PetManager::DROIDPET ){
			ManagedReference<DroidObject*> droidPet = cast<DroidObject*>(pet.get());
			if( droidPet == NULL )
				return GENERALERROR;

			if( !droidPet->hasPower() ){
				pet->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
				return GENERALERROR;
			}
		}

		Reference<CreatureObject*> player = server->getZoneServer()->getObject(target, true).castTo<CreatureObject*>();
		if (player == NULL || !player->isPlayerCreature() || player->isAttackableBy(pet)) {
			pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			return GENERALERROR;
		}

		Locker clocker(controlDevice, creature);
		controlDevice->toggleFriend(player->getObjectID());

		return SUCCESS;
	}

};


#endif /* PETFRIENDCOMMAND_H_ */
