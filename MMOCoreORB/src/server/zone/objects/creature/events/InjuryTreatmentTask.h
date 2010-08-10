/*
 * InjuryTreatmentTask.h
 *
 *  Created on: 09/08/2010
 *      Author: victor
 */

#ifndef INJURYTREATMENTTASK_H_
#define INJURYTREATMENTTASK_H_

#include "../CreatureObject.h"

class InjuryTreatmentTask : public Task {
	ManagedReference<CreatureObject*> creature;
	ParameterizedStringId message;

public:
	InjuryTreatmentTask(CreatureObject* creo, const ParameterizedStringId& msg) {
		creature = creo;
		message = msg;
	}

	void run() {
		Locker locker(creature);

		creature->removePendingTask("injuryTreatment");
		//creature->sendSystemMessage("healing_response", "healing_response_58"); //You are now ready to heal more damage.
		creature->sendSystemMessage(message);
	}
};

#endif /* INJURYTREATMENTTASK_H_ */
