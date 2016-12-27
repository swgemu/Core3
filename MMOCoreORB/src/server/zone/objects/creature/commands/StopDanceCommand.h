/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STOPDANCECOMMAND_H_
#define STOPDANCECOMMAND_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"

class StopDanceCommand : public QueueCommand {
public:

	StopDanceCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<Facade*> facade = creature->getActiveSession(SessionFacadeType::ENTERTAINING);
		ManagedReference<EntertainingSession*> session = dynamic_cast<EntertainingSession*>(facade.get());

		if (session == NULL)
			return GENERALERROR;

		if (!session->isDancing())
			return GENERALERROR;

		session->stopDancing();

		return SUCCESS;
	}

};

#endif //STOPDANCECOMMAND_H_
