/*
 * SyncrhonizedUiListenHarvesterTask.h
 *
 *  Created on: 14/06/2010
 *      Author: victor
 */

#ifndef SYNCRHONIZEDUILISTENHARVESTERTASK_H_
#define SYNCRHONIZEDUILISTENHARVESTERTASK_H_

#include "InstallationObject.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace installation {


class SyncrhonizedUiListenInstallationTask : public Task, public Logger {
	ManagedWeakReference<InstallationObject*> installation;
public:
	SyncrhonizedUiListenInstallationTask(InstallationObject* inso) : Task(5000), Logger("SyncrhonizedUiListenInstallationTask") {
		installation = inso;
	}

	void run() {
		ManagedReference<InstallationObject*> strongRef = installation.get();

		if (strongRef == NULL)
			return;

		Locker locker(strongRef);

		try {
			strongRef->updateInstallationWork();
			//strongRef->updateOperators();
			strongRef->verifyOperators();
			strongRef->activateUiSync();
		} catch (Exception& e) {
			error(e.getMessage());
			e.printStackTrace();
		} catch (...) {
			error("unreported exception caught");
		}

	}
};


   }
  }

 }
}

using namespace server::zone::objects::installation;

#endif /* SyncrhonizedUiListenInstallationTask_H_ */
