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

		PerformanceManager* performanceManager = SkillManager::instance()->getPerformanceManager();

		ManagedReference<EntertainingSession*> session = creature->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();

		if (session == nullptr || !session->isPlayingMusic()) {
			performanceManager->performanceMessageToSelf(creature, nullptr, "performance", "music_not_performing"); // You are not currently playing a song.
			return GENERALERROR;
		}

		session->stopMusic(false);

		return SUCCESS;
	}

};

#endif //STOPMUSICCOMMAND_H_
