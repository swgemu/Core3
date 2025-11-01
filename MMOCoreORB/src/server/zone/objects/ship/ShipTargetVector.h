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

class ShipTargetVector : public Object, public Logger {
public:
	const static int UPDATE_INTERVAL = 2000;
	const static int TARGETVECTORMAX = 32;

	const static int TARGET_DISTANCE_MAX = 2048;
	const static int TARGET_DISTANCE_SQR = TARGET_DISTANCE_MAX * TARGET_DISTANCE_MAX;

protected:
	VectorMap<float, ManagedWeakReference<SceneObject*>> targetMap;
	uint64 serverTime;

	mutable ReadWriteLock targetLock;

public:
	ShipTargetVector(ShipObject* ship) : Object() {
		setLoggingName("ShipTargetVector");
		serverTime = 0;
	}

	void update(ShipObject* ship);

	void safeCopyTo(Vector<ManagedReference<SceneObject*>>& vector) const;

	void safeCopyTo(Vector<ManagedReference<ShipObject*>>& vector) const;

	int size() const;

private:
	float getTargetDistanceSqr(ShipObject* ship, SceneObject* target) const;

	bool isTargetValid(ShipObject* ship, SceneObject* target) const;

	bool isScheduled() const {
		return (System::getMiliTime() - serverTime) >= UPDATE_INTERVAL;
	}

	void setServerTime() {
		serverTime = System::getMiliTime();
	}

	bool isCollidableType(uint32 objectType) const {
		switch (objectType) {
			case SceneObjectType::SHIPCAPITAL:
			case SceneObjectType::SPACESTATION:
			case SceneObjectType::ASTEROID:
			case SceneObjectType::SPACEOBJECT: {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	String toDebugString() const {
		StringBuffer msg;
		msg << "ShipTargetVector: " << targetMap.size() << endl;

		for (int i = 0; i < targetMap.size(); ++i) {
			auto entry = targetMap.elementAt(i).getValue().get();

			if (entry != nullptr) {
				continue;
			}

			float distance = sqrtf(targetMap.elementAt(i).getKey());
			msg << i << " distance: " << distance << " entry: " << entry->getDisplayedName();
		}

		return msg.toString();
	}
};

#endif // SHIPTARGETVECTOR_H_
