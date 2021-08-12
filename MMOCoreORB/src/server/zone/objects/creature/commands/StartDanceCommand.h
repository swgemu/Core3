/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef STARTDANCECOMMAND_H_
#define STARTDANCECOMMAND_H_

#include "server/zone/objects/player/sessions/EntertainingSession.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/managers/skill/PerformanceManager.h"

class StartDanceCommand: public QueueCommand {

public:
	StartDanceCommand(const String& name, ZoneProcessServer* server) :
		QueueCommand(name, server) {

	}

	static void startDance(CreatureObject* creature, int performanceIndex) {
		ManagedReference<Facade*> facade = creature->getActiveSession(SessionFacadeType::ENTERTAINING);
		ManagedReference<EntertainingSession*> session = dynamic_cast<EntertainingSession*> (facade.get());

		if (session == nullptr) {
			session = new EntertainingSession(creature);
			creature->addActiveSession(SessionFacadeType::ENTERTAINING, session);
		}

		session->startDancing(performanceIndex);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<Facade*> facade = creature->getActiveSession(SessionFacadeType::ENTERTAINING);
		ManagedReference<EntertainingSession*> session = dynamic_cast<EntertainingSession*> (facade.get());

		if (session != nullptr && (session->isPlayingMusic() || session->isDancing())) {
			creature->sendSystemMessage("@performance:already_performing_self"); // You are already performing.
			return GENERALERROR;
		}

		Reference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		String args = arguments.toString();

		PerformanceManager* performanceManager = SkillManager::instance()->getPerformanceManager();

		if (args.length() < 1) {
			performanceManager->sendAvailablePerformances(creature, PerformanceType::DANCE, false);
			return SUCCESS;
		}

		int performanceIndex = performanceManager->getPerformanceIndex(PerformanceType::DANCE, args, 0);

		if (performanceIndex == 0) {
			creature->sendSystemMessage("@performance:dance_unknown_self"); // You do not know that dance.
			return GENERALERROR;
		}

		if (!performanceManager->canPerformDance(creature, performanceIndex)) {
			creature->sendSystemMessage("@performance:dance_lack_skill_self"); // You do not have the skill to perform the dance.
			return GENERALERROR;
		}

		startDance(creature, performanceIndex);

		return SUCCESS;
	}

};

#endif //STARTDANCECOMMAND_H_
