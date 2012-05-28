/*
 * SurveyGMinigameSuiCallback.h
 *
 *  Created on: may 22, 2012
 *      Author: kyle
 */

#ifndef SURVEYGMINIGAMESUICALLBACK_H_
#define SURVEYGMINIGAMESUICALLBACK_H_


#include "server/zone/objects/tangible/tool/SurveyTool.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/survey/SurveySession.h"

class SurveyGMinigameSuiCallback : public SuiCallback {
public:
	SurveyGMinigameSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (cancelPressed)
			return;

		ManagedReference<SurveySession*> session = cast<SurveySession*>(player->getActiveSession(SessionFacadeType::SURVEY));
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
