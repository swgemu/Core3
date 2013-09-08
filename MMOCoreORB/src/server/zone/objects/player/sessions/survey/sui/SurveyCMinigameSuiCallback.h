/*
 * SurveyCMinigameSuiCallback.h
 *
 *  Created on: may 22, 2012
 *      Author: kyle
 */

#ifndef SURVEYCMINIGAMESUICALLBACK_H_
#define SURVEYCMINIGAMESUICALLBACK_H_


#include "server/zone/objects/tangible/tool/SurveyTool.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/survey/SurveySession.h"

class SurveyCMinigameSuiCallback : public SuiCallback {
public:
	SurveyCMinigameSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
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

		session->surveyCnodeMinigame(value);
	}
};

#endif /* SURVEYMINIGAMESUICALLBACK_H_ */
