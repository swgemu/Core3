/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef POWERBOOSTBUFFDURATIONEVENT_H_
#define POWERBOOSTBUFFDURATIONEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/buffs/Buff.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace buffs {

class PowerBoostBuffDurationEvent : public Task {
	ManagedWeakReference<Buff*> buffObject;

public:
	PowerBoostBuffDurationEvent(Buff* buff) : Task() {
		buffObject = buff;
	}

	void run() {
		ManagedReference<Buff*> buff = buffObject.get();

		if (buff == NULL)
			return;

		ChannelForceBuff* cFbuff = buff.castTo<ChannelForceBuff*>();

		Locker locker(cFbuff);

		cfBuff->doHamTick();

	}

};

}
}
}
}
}

using namespace server::zone::objects::creature::buffs;

#endif /* POWERBOOSTBUFFDURATIONEVENT_H_ */
