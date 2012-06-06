/*
 * SurveyToolApproveRadioactiveSuiCallback.h
 *
 *  Created on: may 22, 2012
 *      Author: kyle
 */

#ifndef SURVEYTOOLAPPROVERADIOACTIVECALLBACK_H_
#define SURVEYTOOLAPPROVERADIOACTIVECALLBACK_H_


#include "server/zone/objects/tangible/tool/SurveyTool.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class SurveyToolApproveRadioactiveSuiCallback : public SuiCallback {
public:
	SurveyToolApproveRadioactiveSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (cancelPressed)
			return;

		ManagedReference<SurveyTool*> surveyTool = cast<SurveyTool*>(suiBox->getUsingObject().get().get());

		if(surveyTool == NULL)
			return;

		Locker _lock(surveyTool);
		surveyTool->consentRadioactiveSample(player);
	}
};

#endif /* SURVEYTOOLAPPROVERADIOACTIVECALLBACK_H_ */
