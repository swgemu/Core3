/*
 * SecuritySliceTask.h
 *
 *  Created on: Feb 21, 2013
 *      Author: root
 */

#ifndef SECURITYSLICETASK_H_
#define SECURITYSLICETASK_H_

#include "engine/engine.h"
#include "server/zone/managers/gcw/GCWManager.h"

class SecuritySliceTask : public Task {

	ManagedReference<TangibleObject*> terminal;
	ManagedReference<GCWManager*> gcwManager;
	ManagedReference<CreatureObject*> creature;

public:

	SecuritySliceTask(GCWManager* gcwMan, TangibleObject* term, CreatureObject* player) {
		gcwManager = gcwMan;
		terminal = term;
		creature = player;
	}

	void run() {

		if (terminal == NULL || gcwManager == NULL  )
			return;

		gcwManager->completeSecuritySlice(creature, terminal);

	}
};




#endif /* SECURITYSLICETASK_H_ */
