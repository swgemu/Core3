
#ifndef PETSTAYCOMMAND_H_
#define PETSTAYCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/scene/ObserverEventType.h"

class PetStayCommand : public QueueCommand {
public:
	PetStayCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		ManagedReference<AiAgent*> pet = cast<AiAgent*>(creature);
		if( pet == NULL )
			return GENERALERROR;

		if (pet->hasRidingCreature())
			return GENERALERROR;

		pet->setOblivious();

		pet->interrupt(pet->getLinkedCreature().get(), ObserverEventType::STARTCOMBAT);

		return SUCCESS;
	}

};


#endif /* PETSTAYCOMMAND_H_ */
