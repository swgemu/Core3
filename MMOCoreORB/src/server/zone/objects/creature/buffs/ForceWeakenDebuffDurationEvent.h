
#ifndef FORCEWEAKENDEBUFFDURATIONEVENT_H_
#define FORCEWEAKENDEBUFFDURATIONEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/buffs/Buff.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace creature {
    namespace buffs {

		class ForceWeakenDebuffDurationEvent : public Task {
			ManagedWeakReference<CreatureObject*> creatureObject;
			ManagedWeakReference<Buff*> buffObject;

		public:
			ForceWeakenDebuffDurationEvent(CreatureObject* creatureTarget, Buff* buff) : Task((int) buff->getBuffDuration() * 1000) {
				creatureObject = creatureTarget;
				buffObject = buff;
			}

			void run() {
				ManagedReference<CreatureObject*> creatureTarget = creatureObject.get();
				ManagedReference<Buff*> buff = buffObject.get();

				if (creatureTarget == NULL || buff == NULL)
					return;

				Locker locker(creatureTarget);
				Locker clocker(buff, creatureTarget);

				buff->deactivate(false);

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

#endif /* FORCEWEAKENDEBUFFDURATIONEVENT_H_ */
