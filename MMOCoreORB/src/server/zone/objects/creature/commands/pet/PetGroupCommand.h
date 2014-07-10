
#ifndef PETGROUPCOMMAND_H_
#define PETGROUPCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/AiAgent.h"

class PetGroupCommand : public QueueCommand {
public:
	PetGroupCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().castTo<PetControlDevice*>();
		if (controlDevice == NULL)
			return GENERALERROR;

		ManagedReference<AiAgent*> pet = cast<AiAgent*>(creature);
		if( pet == NULL )
			return GENERALERROR;

		ManagedReference< CreatureObject*> player = pet->getLinkedCreature().get();
		if( player == NULL )
			return GENERALERROR;

		// Check if droid has power
		if( controlDevice->getPetType() == PetManager::DROIDPET ){
			ManagedReference<DroidObject*> droidPet = cast<DroidObject*>(pet.get());
			if( droidPet == NULL )
				return GENERALERROR;

			if( !droidPet->hasPower() ){
				creature->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
				return GENERALERROR;
			}
		}

		ManagedReference<GroupObject*> group = pet->getGroup();
		if (group == NULL) {
			Locker clocker(player, pet);
			GroupManager::instance()->inviteToGroup(player, pet);
		} else
			GroupManager::instance()->leaveGroup(group, pet);

		return SUCCESS;
	}

};


#endif /* PETGROUPCOMMAND_H_ */
