/*
 * DestroyFactionInstallationTask.h
 *
 *  Created on: Jan 30, 2013
 *      Author: root
 */

#ifndef DESTROYFACTIONINSTALLATIONTASK_H_
#define DESTROYFACTIONINSTALLATIONTASK_H_
#include "engine/engine.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/managers/gcw/GCWManager.h"


class DestroyFactionInstallationTask : public Task {
	ManagedReference<InstallationObject*> installation;

public:
	DestroyFactionInstallationTask(InstallationObject* inst) {
		installation = inst;

	}

	void run() {
		Zone* zne = installation->getZone();
		if(zne == NULL)
			return;

		GCWManager* gcwMan = zne->getGCWManager();
		if(gcwMan != NULL)
			gcwMan->notifyInstallationDestruction(installation);
	}

};

#endif /* DESTROYFACTIONINSTALLATIONTASK_H_ */
