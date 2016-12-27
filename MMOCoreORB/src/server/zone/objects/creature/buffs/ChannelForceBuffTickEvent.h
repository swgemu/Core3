/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHANNELFORCEBUFFTICKEVENT_H_
#define CHANNELFORCEBUFFTICKEVENT_H_

#include "server/zone/objects/creature/buffs/ChannelForceBuff.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace buffs {

class ChannelForceBuffTickEvent : public Task {
	ManagedWeakReference<ChannelForceBuff*> buffObject;

public:
	ChannelForceBuffTickEvent(ChannelForceBuff* buff) : Task() {
		buffObject = buff;
	}

	void run() {
		ManagedReference<ChannelForceBuff*> buff = buffObject.get();

		if (buff == NULL)
			return;

		Locker locker(buff);

		buff->doHamTick();

	}

};

}
}
}
}
}

using namespace server::zone::objects::creature::buffs;

#endif /* */
