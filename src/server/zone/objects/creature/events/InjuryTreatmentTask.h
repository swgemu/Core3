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
	StringIdChatParameter message;
	String pendingTask;

public:
	InjuryTreatmentTask(CreatureObject* creo, const StringIdChatParameter& msg, const String& task) {
		creature = creo;
		message = msg;
		pendingTask = task;
	}

	void run() {
		Locker locker(creature);

		creature->removePendingTask(pendingTask);
		//creature->sendSystemMessage("healing_response", "healing_response_58"); //You are now ready to heal more damage.
		creature->sendSystemMessage(message);
	}
};

#endif /* INJURYTREATMENTTASK_H_ */
