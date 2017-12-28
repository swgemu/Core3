/*
 * CityManageMilitiaSuiCallback.h
 *
 *  Created on: Feb 13, 2012
 *      Author: xyborn
 */

#ifndef CITYMANAGEMILITIASUICALLBACK_H_
#define CITYMANAGEMILITIASUICALLBACK_H_

#include "engine/core/ManagedWeakReference.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/region/CityRegion.h"
#include "system/platform.h"

namespace server {
namespace zone {
class ZoneServer;
namespace objects {
namespace player {
namespace sui {
class SuiBox;
}  // namespace sui
}  // namespace player
}  // namespace objects
}  // namespace zone
}  // namespace server
namespace sys {
namespace lang {
class UnicodeString;
}  // namespace lang
namespace util {
template <class E> class Vector;
}  // namespace util
}  // namespace sys

namespace server {
namespace zone {
namespace objects {
namespace creature {
	class CreatureObject;
}
namespace region {
	class CityRegion;
}
}
}
}

using namespace server::zone::objects::creature;
using namespace server::zone::objects::region;

class CityManageMilitiaSuiCallback : public SuiCallback {
	ManagedWeakReference<CityRegion*> cityRegion;

public:
	CityManageMilitiaSuiCallback(ZoneServer* server, CityRegion* city)
		: SuiCallback(server) {

		cityRegion = city;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args);
};

#endif /* CITYMANAGEMILITIASUICALLBACK_H_ */
