/*
 * MapLocationEntry.h
 *
 *  Created on: 18/06/2010
 *      Author: victor
 *  Updated on: Sun Oct 16 16:30:54 PDT 2011 by lordkator - resolve displayName on add in setObject()
 */

#ifndef MAPLOCATIONENTRY_H_
#define MAPLOCATIONENTRY_H_

#include "engine/engine.h"

class PlanetMapCategory;

namespace server {
namespace zone {
namespace objects {
namespace scene {

class SceneObject;

} // namespace scene

namespace creature {
	class CreatureObject;
}
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::scene;
using namespace server::zone::objects::creature;

class MapLocationEntry : public Object {
	Reference<SceneObject*> object;
	UnicodeString displayName;
	byte icon; // 0 = None, 1 = Moon, 2 = Star

public:
	MapLocationEntry() {
		icon = 0;
	}

	MapLocationEntry(SceneObject* obj) {
		setObject(obj);
	}

	MapLocationEntry(const MapLocationEntry& entry) : Object() {
		object = entry.object;
		icon = entry.icon;
		displayName = entry.displayName;
	}

	int compareTo(const MapLocationEntry& entry) const;

	bool insertToMessage(BaseMessage* message, CreatureObject* player);

	MapLocationEntry& operator=(const MapLocationEntry& entry);

	uint64 getObjectID() const;

	void setObject(SceneObject* obj);

	inline SceneObject* getObject() const {
		return object;
	}

	inline byte getIcon() const {
		return icon;
	}

	/**
	 * Sets the icon used at this location: 0 = None, 1 = Moon, 2 = Star
	 * @param ico The icon to use
	 */
	inline void setIcon(byte ico) {
		icon = ico;
	}
};


#endif /* MAPLOCATIONENTRY_H_ */
