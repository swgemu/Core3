/*
 * EntertainingSessionTask.h
 *
 *  Created on: 27/09/2010
 *      Author: victor
 */

#ifndef ENTERTAININGSESSIONTASK_H_
#define ENTERTAININGSESSIONTASK_H_

#include "engine/engine.h"

#include "server/zone/objects/player/sessions/EntertainingSession.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {


class EntertainingSessionTask : public Task {
	ManagedWeakReference<EntertainingSession*> session;
public:
	EntertainingSessionTask(EntertainingSession* sess) {
		session = sess;
	}

	void run() {
		ManagedReference<EntertainingSession*> strongRef = session.get();

		if (strongRef == NULL)
			return;

		strongRef->activateAction();
	}
};


}
}
}
}
}

using namespace server::zone::objects::player::events;

#endif /* ENTERTAININGSESSIONTASK_H_ */
