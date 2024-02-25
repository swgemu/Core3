#ifndef SHIPTARGETVECTOR_H_
#define SHIPTARGETVECTOR_H_

#include "server/zone/objects/tangible/TangibleObject.h"

namespace server {
	namespace zone {
		namespace objects {
			namespace ship {
				class ShipObject;
			}
		}
	}
}

class ShipTargetVector : public Object, public Logger {
public:
	const static int UPDATEINTERVAL = 2000;
	const static int TARGETVECTORMAX = 32;

	constexpr static float UPDATEMODIFIER = UPDATEINTERVAL * 0.001f;
	constexpr static float PROJECTILERANGEMAX = 512.f * UPDATEMODIFIER;

protected:
	VectorMap<float, ManagedWeakReference<ShipObject*>> targetMap;
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

	bool isTargetValid(ShipObject* ship, ShipObject* target) const;

	void removeInRangeObject(ShipObject* ship, SceneObject* target) const;

	void safeCopyTo(Vector<ManagedReference<ShipObject*>>& vector) const;

	int size() const;
};

#endif // SHIPTARGETVECTOR_H_
