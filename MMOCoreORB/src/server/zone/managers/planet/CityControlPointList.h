#ifndef CITYCONTROLPOINTLIST_H_
#define CITYCONTROLPOINTLIST_H_

#include "CityControlLandingPoint.h"

class CityControlPointList : public VectorMap<String, Reference<CityControlLandingPoint*> >, public ReadWriteLock {
	String zoneName;
public:

	CityControlPointList() : VectorMap<String, Reference<CityControlLandingPoint*> >() {
		setNoDuplicateInsertPlan();
		setNullValue(nullptr);
	}

	Reference<CityControlLandingPoint*> get(int index) {
		ReadLocker guard(this);

		Reference<CityControlLandingPoint*> point = VectorMap<String, Reference<CityControlLandingPoint*> >::get(index);

		return point;
	}

	Reference<CityControlLandingPoint*> get(const String& name) {
		ReadLocker guard(this);

		Reference<CityControlLandingPoint*> point = VectorMap<String, Reference<CityControlLandingPoint*> >::get(name);

		return point;
	}

	void insertToMessage(BaseMessage* message, CityControlLandingPoint* origin) {
		rlock();

		int totalPoints = size();

		for (int i = 0; i < totalPoints; ++i) {
			Reference<CityControlLandingPoint*> cclp = VectorMap<String, Reference<CityControlLandingPoint*> >::get(i);
			message->insertFloat(cclp->getLandingPositionX());
			message->insertFloat(cclp->getLandingPositionZ());
			message->insertFloat(cclp->getLandingPositionY());

		}

		runlock();
	}

	void readLuaObject(LuaObject* luaObject) {
		wlock();

		if (!luaObject->isValidTable()) {
			return;
		}

		for (int i = 1; i <= luaObject->getTableSize(); ++i) {
			lua_State* L = luaObject->getLuaState();
			lua_rawgeti(L, -1, i);

			LuaObject cityControlLandingPointEntry(L);

			Reference<CityControlLandingPoint*> cclp = new CityControlLandingPoint(zoneName);
			cclp->readLuaObject(&cityControlLandingPointEntry);

			put(cclp->getPointName(), cclp);

			cityControlLandingPointEntry.pop();
		}

		unlock();
	}

	inline void setZoneName(const String& name) {
		zoneName = name;
	}
};

#endif /* CITYCONTROLPOINTLIST_H_*/