/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHANNELFORCEBUFFTICKEVENT_H_
#define CHANNELFORCEBUFFTICKEVENT_H_

#include "server/zone/objects/creature/buffs/ChannelForceBuff.h"
#include "server/zone/objects/creature/buffs/Buff.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace buffs {

class ChannelForceBuffTickEvent : public Task {
	ManagedWeakReference<Buff*> buffObject;

public:
	ChannelForceBuffTickEvent(Buff* buff) : Task() {
		buffObject = buff;
	}

	void run() {
		ManagedReference<Buff*> buff = buffObject.get();

		if (buff == NULL)
			return;

		ChannelForceBuff* cFbuff = buff.castTo<ChannelForceBuff*>();

		Locker locker(cFbuff);

		cFbuff->doHamTick();

	}

};

}
}
}
}
}

using namespace server::zone::objects::creature::buffs;

#endif /* */
