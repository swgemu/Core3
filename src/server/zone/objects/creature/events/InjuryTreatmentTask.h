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

public:
	InjuryTreatmentTask(CreatureObject* creo) {
		creature = creo;
	}

	void run() {
		Locker locker(creature);

		creature->removePendingTask("injuryTreatment");
		creature->sendSystemMessage("healing_response", "healing_response_58"); //You are now ready to heal more damage.
	}
};

#endif /* INJURYTREATMENTTASK_H_ */
