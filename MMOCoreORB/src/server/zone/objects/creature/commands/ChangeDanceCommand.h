/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHANGEDANCECOMMAND_H_
#define CHANGEDANCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
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

		if (session == NULL) {
			creature->sendSystemMessage("@performance:dance_must_be_performing_self");
			return GENERALERROR;
		}

		if (session->isPlayingMusic()) {
			session->stopPlayingMusic();
		}

		if (!session->isDancing()) {
			creature->sendSystemMessage("@performance:dance_must_be_performing_self");
			return GENERALERROR;
		}

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		String args = arguments.toString();

		PerformanceManager* performanceManager = SkillManager::instance()->getPerformanceManager();

		if (args.length() < 2) {
			StartDanceCommand::sendAvailableDances(creature, ghost, SuiWindowType::DANCING_CHANGE);
			return SUCCESS;
		}

		String fullString = String("startDance") + "+" + args;

		if (!ghost->hasAbility(fullString)) {
			creature->sendSystemMessage("@performance:dance_lack_skill_self");
			return GENERALERROR;
		}

		if (!performanceManager->hasDanceAnimation(args)) {
			creature->sendSystemMessage("@performance:dance_lack_skill_self");
			return GENERALERROR;
		}

		session->sendEntertainingUpdate(creature, /*0x3C4CCCCD*/0.0125, performanceManager->getDanceAnimation(args), 0x07339FF8, 0xDD);
		session->setPerformanceName(args);

		creature->notifyObservers(ObserverEventType::CHANGEENTERTAIN, creature);

		return SUCCESS;
	}

};

#endif //CHANGEDANCECOMMAND_H_
