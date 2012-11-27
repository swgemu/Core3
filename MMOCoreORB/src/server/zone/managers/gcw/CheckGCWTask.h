/*
 * CheckGCWTask.h
 *
 *  Created on: Oct 24, 2012
 *      Author: root
 */

#ifndef CHECKGCWTASK_H_
#define CHECKGCWTASK_H_
#include "engine/engine.h"
#include "GCWManager.h"

class CheckGCWTask : public Task {
	ManagedWeakReference<GCWManager*> gcwManager;

public:
	CheckGCWTask(GCWManager* manager){
		gcwManager = manager;
	}

	void run() {
		ManagedReference<GCWManager*> strongRef = gcwManager.get();

		if (strongRef == NULL){
			return;
		}

		strongRef->performGCWTasks();

	}
};




#endif /* CHECKGCWTASK_H_ */
