/*
 * InstallationDestructionTask.h
 *
 *  Created on: Feb 18, 2013
 *      Author: root
 */

#ifndef INSTALLATIONDESTRUCTIONTASK_H_
#define INSTALLATIONDESTRUCTIONTASK_H_

#include "engine/engine.h"
#include "GCWManager.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/Zone.h"

class InstallationDestructionTask : public Task {
	ManagedWeakReference<InstallationObject*> installationObject;
public:
	InstallationDestructionTask(InstallationObject* installation) {

		installationObject = installation;
	}

	void run() {

		ManagedReference<InstallationObject*> strongRefInstallation = installationObject.get();
		if (strongRefInstallation == NULL )
			return;

		Zone* zone = strongRefInstallation->getZone();

		if(zone == NULL)
			return;

		GCWManager* gcwMan = zone->getGCWManager();

		if(gcwMan == NULL)
			return;

		gcwMan->notifyInstallationDestruction(strongRefInstallation);
	}
};





#endif /* INSTALLATIONDESTRUCTIONTASK_H_ */
