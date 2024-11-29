#ifndef SHIPTARGETVECTOR_H_
#define SHIPTARGETVECTOR_H_

#include "server/zone/objects/scene/SceneObject.h"

namespace server {
	namespace zone {
		namespace objects {
			namespace ship {
				class ShipObject;
			}
		}
	}
}

//#define SHIPTARGETVECTOR_DEBUG

class ShipTargetVector : public Object, public Logger {
public:
	const static int UPDATEINTERVAL = 2000;
	const static int TARGETVECTORMAX = 32;

	constexpr static float UPDATEMODIFIER = UPDATEINTERVAL * 0.001f;
	constexpr static float PROJECTILERANGEMAX = 512.f * UPDATEMODIFIER;

protected:
	VectorMap<float, ManagedWeakReference<SceneObject*>> targetMap;
	ManagedWeakReference<ShipObject*> shipRef;

	mutable ReadWriteLock targetLock;
	uint64 lastUpdateTime;

public:
	ShipTargetVector(ShipObject* ship) : Object() {
		setLoggingName("ShipTargetVector");

		shipRef = ship;
		targetMap.setAllowDuplicateInsertPlan();
		lastUpdateTime = 0;
	}

	void update();

	bool isTargetValid(ShipObject* ship, SceneObject* target) const;

	void safeCopyTo(Vector<ManagedReference<SceneObject*>>& vector) const;

	void safeCopyTo(Vector<ManagedReference<ShipObject*>>& vector) const;

	int size() const;

#ifdef SHIPTARGETVECTOR_DEBUG
	void debugTargetVector();
#endif // SHIPTARGETVECTOR_DEBUG
};

#endif // SHIPTARGETVECTOR_H_
