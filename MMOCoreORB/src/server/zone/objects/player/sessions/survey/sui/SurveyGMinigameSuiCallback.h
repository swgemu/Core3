/*
 * SurveyGMinigameSuiCallback.h
 *
 *  Created on: may 22, 2012
 *      Author: kyle
 */

#ifndef SURVEYGMINIGAMESUICALLBACK_H_
#define SURVEYGMINIGAMESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/survey/SurveySession.h"

class SurveyGMinigameSuiCallback : public SuiCallback {
public:
	SurveyGMinigameSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed)
			return;

		if(player->getPosture() > CreaturePosture::CROUCHED){
				player->sendSystemMessage("@error_message:survey_standing");  // "You must be standing to take a survey or samples.");
				return;
		}

		ManagedReference<SurveySession*> session = player->getActiveSession(SessionFacadeType::SURVEY).castTo<SurveySession*>();
		if(session == NULL) {
			return;
		}

		if (args->size() < 1)
			return;

		int value = Integer::valueOf(args->get(0).toString());

		session->surveyGnodeMinigame(value);

	}
};

#endif /* SURVEYMINIGAMESUICALLBACK_H_ */
