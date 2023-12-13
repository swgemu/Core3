
#ifndef PETSTORECOMMAND_H_
#define PETSTORECOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/intangible/tasks/PetControlDeviceStoreTask.h"

class PetStoreCommand : public QueueCommand {
public:
	PetStoreCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().get().castTo<PetControlDevice*>();

		if (controlDevice == nullptr)
			return GENERALERROR;

		ManagedReference<AiAgent*> pet = cast<AiAgent*>(creature);

		if (pet == nullptr)
			return GENERALERROR;

		ManagedReference<CreatureObject*> player = pet->getLinkedCreature().get();

		if (player == nullptr || !player->isPlayerCreature()) {
			return GENERALERROR;
		}

		PetControlDeviceStoreTask* storeTask = new PetControlDeviceStoreTask(controlDevice, player, false);

		if (storeTask != nullptr)
			storeTask->execute();

		return SUCCESS;
	}
};

#endif /* PETSTORECOMMAND_H_ */
