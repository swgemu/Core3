/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file SampleTask.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#ifndef SAMPLETASK_H_
#define SAMPLETASK_H_

#include "server/zone/objects/tangible/tool/SurveyTool.h"
#include "server/zone/objects/player/sessions/survey/SurveySession.h"

class SampleTask : public Task {

protected:
	ManagedReference<CreatureObject*> playerCreature;
	ManagedReference<SurveyTool* > surveyTool;
	bool cancelled;

public:
	SampleTask(CreatureObject* play, SurveyTool* tool) {
		playerCreature = play;
		surveyTool = tool;
		cancelled = false;
	}

	void run() {
		Locker playerLocker(playerCreature);

		if (!cancelled && playerCreature->getPendingTask("sample") != NULL) {
			playerCreature->removePendingTask("sample");

			ManagedReference<SurveySession*> session = playerCreature->getActiveSession(SessionFacadeType::SURVEY).castTo<SurveySession*>();
			if(session != NULL) {
				session->reSample();
			}
			return;
		}

		playerCreature->removePendingTask("sample");
		cancelled = false;
	}


	void stopSampling() {
		cancelled = true;

	}

	bool isCancelled() {
		return cancelled;
	}

};

#endif /* SAMPLETASK_H_ */
