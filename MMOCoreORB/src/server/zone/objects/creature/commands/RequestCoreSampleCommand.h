/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file RequestCoreSampleCommand.h
 * \author Kyle Burkhardt
 * \date 5-27-10
 */

#ifndef REQUESTCORESAMPLECOMMAND_H_
#define REQUESTCORESAMPLECOMMAND_H_

#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/objects/player/sessions/survey/SurveySession.h"

class RequestCoreSampleCommand : public QueueCommand {
public:

	RequestCoreSampleCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature)) {
			creature->sendSystemMessage("@error_message:survey_standing");
			return INVALIDLOCOMOTION;
		}

		// We don't do anything if for some reason it isn't a player
		if (creature->isPlayerCreature()) {

			Reference<Task*> sampletask = creature->getPendingTask("sample");
			Reference<Task*> surveytask = creature->getPendingTask("survey");

			// If the sample task exists, we can't sample again
			if (sampletask != NULL) {
				Time nextExecutionTime;
				Core::getTaskManager()->getNextExecutionTime(sampletask, nextExecutionTime);
				int seconds = (int) ((nextExecutionTime.getMiliTime() - Time().getMiliTime()) / 1000.0f);
				if(seconds < 1)
					seconds = 1;

				StringIdChatParameter message("survey","tool_recharge_time");
				message.setDI(seconds);
				ChatSystemMessage* sysMessage = new ChatSystemMessage(message);
				creature->sendMessage(sysMessage);

				return SUCCESS;
			}

			// If the survey task exists, we can't sample
			if (surveytask != NULL) {
				creature->sendSystemMessage("@survey:sample_survey");

				return SUCCESS;
			}


			ManagedReference<SurveySession*> session = creature->getActiveSession(SessionFacadeType::SURVEY).castTo<SurveySession*>();

			if(session == NULL) {
				creature->sendSystemMessage("@ui:survey_notool");
				return GENERALERROR;
			}

			session->setActiveSurveyTool(session->getOpenSurveyTool().get());
			session->startSample(arguments.toString());

		}

		return SUCCESS;
	}
};

#endif //REQUESTCORESAMPLECOMMAND_H_
