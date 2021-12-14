
#ifndef PETSTAYCOMMAND_H_
#define PETSTAYCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "templates/params/ObserverEventType.h"
#include "server/zone/managers/creature/PetManager.h"

class PetStayCommand : public QueueCommand {
public:
	PetStayCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().get().castTo<PetControlDevice*>();
		if (controlDevice == nullptr)
			return GENERALERROR;

		ManagedReference<AiAgent*> pet = cast<AiAgent*>(creature);
		if (pet == nullptr)
			return GENERALERROR;

		if (pet->hasRidingCreature())
			return GENERALERROR;

		if (pet->isInCombat())
			CombatManager::instance()->attemptPeace(pet);

		Vector3 home = pet->getWorldPosition();

		pet->setHomeLocation(home.getX(), home.getZ(), home.getY());
		pet->setOblivious();
		pet->storeFollowObject();

		pet->notifyObservers(ObserverEventType::STARTCOMBAT, pet->getLinkedCreature().get());

		return SUCCESS;
	}
};

#endif /* PETSTAYCOMMAND_H_ */
