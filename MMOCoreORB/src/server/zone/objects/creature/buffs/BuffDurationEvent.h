/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BUFFDURATIONEVENT_H_
#define BUFFDURATIONEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/buffs/Buff.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace creature {
    namespace buffs {

		class BuffDurationEvent : public Task {
			ManagedWeakReference<CreatureObject*> creatureObject;
			ManagedWeakReference<Buff*> buffObject;

		public:
			BuffDurationEvent(CreatureObject* creature, Buff* buff) : Task((int64) buff->getBuffDuration() * 1000) {
				creatureObject = creature;
				buffObject = buff;
			}

			void run() {
				ManagedReference<CreatureObject*> creature = creatureObject.get();
				ManagedReference<Buff*> buff = buffObject.get();

				if (creature == NULL || buff == NULL)
					return;

				Locker locker(creature);
				Locker clocker(buff, creature);

				if (buff->checkRenew()) {
					creature->renewBuff(buff->getBuffCRC(), buff->getBuffDuration());
				} else {
					creature->removeBuff(buff);
				}

			}

			void setBuffObject(Buff* buff) {
				buffObject = buff;
			}

		};

    }
   }
  }
 }
}

using namespace server::zone::objects::creature::buffs;

#endif /* BUFFDURATIONEVENT_H_ */
