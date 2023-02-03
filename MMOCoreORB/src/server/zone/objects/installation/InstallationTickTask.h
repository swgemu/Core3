#ifndef INSTALLATIONTICKTASK_H_
#define INSTALLATIONTICKTASK_H_

#include "server/zone/objects/installation/InstallationObject.h"

namespace server {
namespace zone {
namespace objects {
namespace installation {

class InstallationTickTask : public Task, public Logger {
	ManagedWeakReference<InstallationObject*> installation;

public:
	InstallationTickTask(InstallationObject* inso) : Task(5000), Logger("InstallationTickTask") {
		installation = inso;
	}

	inline const Time& getNextExecutionTime() const {
		return Task::getNextExecutionTime();
	}

	void run() {
		ManagedReference<InstallationObject*> strongRef = installation.get();

		if (strongRef == nullptr)
			return;

		Locker locker(strongRef);

		try {
			if (strongRef->getZone() == nullptr)
				return;

			strongRef->doTick();
		} catch (Exception& e) {
			error(e.getMessage());
			e.printStackTrace();
		}
	}
};

} // namespace installation
} // namespace objects

} // namespace zone
} // namespace server

using namespace server::zone::objects::installation;

#endif /* INSTALLATIONTICKTASK_H_ */