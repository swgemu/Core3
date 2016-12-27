/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

/**
 * \file ImageDesignTimeoutEvent.h
 * \author Polonel
 * \date 02.07.2011
 */

#ifndef IMAGEDESIGNTIMEOUTEVENT_H_
#define IMAGEDESIGNTIMEOUTEVENT_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class ImageDesignTimeoutEvent: public Task {
	ManagedWeakReference<ImageDesignSession*> idSession;

public:
	ImageDesignTimeoutEvent(ImageDesignSession* session) {
		idSession = session;
	}

	void run() {
		ManagedReference<ImageDesignSession*> session = idSession.get();

		if (session == NULL)
			return;

		session->sessionTimeout();
	}

};

}
}
}
}
}

#endif /* IMAGEDESIGNTIMEOUTEVENT_H_ */
