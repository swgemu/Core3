/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef FLOURISHCOMMAND_H_
#define FLOURISHCOMMAND_H_

#include "server/zone/objects/player/sessions/EntertainingSession.h"

class FlourishCommand: public QueueCommand {
public:

	FlourishCommand(const String& name, ZoneProcessServer* server) :
		QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target,
			const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<Facade*> facade = creature->getActiveSession(
				SessionFacadeType::ENTERTAINING);
		ManagedReference<EntertainingSession*> session =
				dynamic_cast<EntertainingSession*> (facade.get());

		if (session == NULL) {
			creature->sendSystemMessage("@performance:flourish_not_performing");
			return GENERALERROR;
		}

		if (!session->isDancing() && !session->isPlayingMusic()) {
			creature->sendSystemMessage("@performance:flourish_not_performing");
			return GENERALERROR;
		}

		String args = arguments.toString();

		int mod = Integer::valueOf(args);

		Reference<PlayerObject*> ghost =
						creature->getSlottedObject(
								"ghost").castTo<PlayerObject*> ();

		String fullString = String("flourish") + "+" + args;

		if (!ghost->hasAbility(fullString)) {
			creature->sendSystemMessage("@performance:flourish_not_valid");
			return GENERALERROR;
		}

		session->doFlourish(mod, true);

		return SUCCESS;
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		ManagedReference<Facade*> facade = object->getActiveSession(
				SessionFacadeType::ENTERTAINING);
		ManagedReference<EntertainingSession*> session =
				dynamic_cast<EntertainingSession*> (facade.get());

		if (session == NULL)
			return 0.0f;

		int knowledgeSkillMod = 0;
		if (session->isPlayingMusic()) {
			knowledgeSkillMod = object->getSkillMod("healing_music_ability");
		} else if (session->isDancing()) {
			knowledgeSkillMod = object->getSkillMod("healing_dance_ability");
		} else {
			return 0.0f;
		}

		//calculating cooldown as defaultTime(5s) - 1s per 30 skill mod val
		//gives a minimum time of 2s at master
		float duration = defaultTime - (knowledgeSkillMod / 30.0f);
		return duration;
	}

};

#endif //FLOURISHCOMMAND_H_
