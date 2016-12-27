/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REQUESTSURVEYCOMMAND_H_
#define REQUESTSURVEYCOMMAND_H_

#include "server/zone/managers/resource/resourcespawner/SampleTask.h"
#include "server/zone/objects/player/sessions/survey/SurveySession.h"

class RequestSurveyCommand : public QueueCommand {
public:

	RequestSurveyCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	/**
	 * Regardless of what is entered as arguments in the client, the client
	 * sends the name of the resource surveyed for as the only argument.
	 * This is always handled by the client as long as a tool has been
	 * used during the current play session.
	 */

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {


		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->isPlayerCreature()) {

			Reference<Task*> sampletask = creature->getPendingTask("sample");
			Reference<Task*> surveytask = creature->getPendingTask("survey");

			if(surveytask != NULL)
				return SUCCESS;

			if (sampletask != NULL) {
				SampleTask* sampleTask = cast<SampleTask*>( sampletask.get());

				if (sampleTask != NULL) {
					if (!sampleTask->isCancelled()) {
						creature->sendSystemMessage("@survey:survey_sample");

						return SUCCESS;
					}
				}
			}

			ManagedReference<SurveySession*> session = creature->getActiveSession(SessionFacadeType::SURVEY).castTo<SurveySession*>();

			if(session == NULL) {
				creature->sendSystemMessage("@ui:survey_notool");
				return GENERALERROR;
			}

			session->setActiveSurveyTool(session->getOpenSurveyTool().get());
			session->startSurvey(arguments.toString());
		}

		return SUCCESS;
	}

};

#endif //REQUESTSURVEYCOMMAND_H_
