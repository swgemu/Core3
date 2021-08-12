/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHANGEDANCECOMMAND_H_
#define CHANGEDANCECOMMAND_H_

#include "StartDanceCommand.h"

class ChangeDanceCommand : public QueueCommand {
public:

	ChangeDanceCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<EntertainingSession*> session = creature->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();

		if (session == nullptr || !session->isDancing()) {
			creature->sendSystemMessage("@performance:dance_must_be_performing_self");
			return GENERALERROR;
		}

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

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

		session->sendEntertainingUpdate(creature, performanceIndex, true);

		creature->notifyObservers(ObserverEventType::CHANGEENTERTAIN, creature);

		return SUCCESS;
	}

};

#endif //CHANGEDANCECOMMAND_H_
