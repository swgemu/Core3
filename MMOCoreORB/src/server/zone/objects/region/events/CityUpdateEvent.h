/*
 * CityUpdateEvent.h
 *
 *  Created on: Feb 19, 2012
 *      Author: xyborn
 */

#ifndef CITYUPDATEEVENT_H_
#define CITYUPDATEEVENT_H_

#include "engine/core/ManagedReference.h"
#include "engine/core/ManagedWeakReference.h"
#include "engine/core/Task.h"
#include "engine/engine.h"
#include "server/zone/ZoneServer.h"

namespace server {
namespace zone {
	class ZoneServer;

namespace objects {
namespace region {
	class CityRegion;
}
}
}
}

using namespace server::zone;
using namespace server::zone::objects::region;

namespace server {
 namespace zone {
  namespace objects {
   namespace region {
    namespace events {

		class CityUpdateEvent : public Task {
			ManagedReference<ZoneServer*> zoneServer;
			ManagedWeakReference<CityRegion*> cityRegion;

		public:
			CityUpdateEvent(CityRegion* city, ZoneServer* zserv);

			void run();
		};

    }
   }
  }
 }
}

using namespace server::zone::objects::region::events;

#endif /* CITYUPDATEEVENT_H_ */
