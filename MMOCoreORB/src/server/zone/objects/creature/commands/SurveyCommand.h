/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SURVEYCOMMAND_H_
#define SURVEYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/tool/SurveyTool.h"

class SurveyCommand : public QueueCommand {
public:

	SurveyCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->isPlayerCreature()) {

			ManagedReference<SurveySession*> session = creature->getActiveSession(SessionFacadeType::SURVEY).castTo<SurveySession*>();
			if(session == NULL) {
				creature->sendSystemMessage("@ui:survey_notool");
			}
		}

		return SUCCESS;
	}

};

#endif //SURVEYCOMMAND_H_
