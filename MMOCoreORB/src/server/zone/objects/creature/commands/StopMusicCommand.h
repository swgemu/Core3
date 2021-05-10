/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STOPMUSICCOMMAND_H_
#define STOPMUSICCOMMAND_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"

class StopMusicCommand : public QueueCommand {
public:

	StopMusicCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<Facade*> facade = creature->getActiveSession(SessionFacadeType::ENTERTAINING);
		ManagedReference<EntertainingSession*> session = dynamic_cast<EntertainingSession*>(facade.get());

		if (session == nullptr || !session->isPlayingMusic()) {
			creature->sendSystemMessage("@performance:music_not_performing"); // You are not currently playing a song.
			return GENERALERROR;
		}

		// TODO: flourish outro

		session->stopPlayingMusic();

		return SUCCESS;
	}

};

#endif //STOPMUSICCOMMAND_H_
