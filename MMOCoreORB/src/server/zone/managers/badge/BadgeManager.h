#ifndef BADGEMANAGER_H_
#define BADGEMANAGER_H_

#include "engine/engine.h"
#include "BadgeList.h"

#include "server/zone/objects/player/badges/Badge.h"

namespace server {
namespace managers {
namespace badge {

class BadgeManager : public Singleton<BadgeManager>, public Logger, public Object {
	BadgeList list;

public:
	BadgeManager();
	~BadgeManager(){}


	/**
	 * Lodas the badge data and initializes the BadgeList
	 */
	void loadData();

	/**
	 * Retrieves the badge with badgeId
	 * returns NULL if the badge wasn't found
	 */
	const Badge* get(const uint32 badgeId);

	/**
	 * Retreives the badge with the given key
	 */
	const Badge* get(const String& key);

	/**
	 * Returns a (idx, Badge*) VectorMap with all badges
	 */
	VectorMap<unsigned int, const Badge*>* getMap();
};
}
}
}

using namespace server::managers::badge;

#endif
