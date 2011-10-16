/*
 * PlanetTravelPointList.h
 *
 *  Created on: May 13, 2011
 *      Author: crush
 */

#ifndef PLANETTRAVELPOINTLIST_H_
#define PLANETTRAVELPOINTLIST_H_

#include "engine/engine.h"
#include "PlanetTravelPoint.h"

class PlanetTravelPointList : public VectorMap<String, Reference<PlanetTravelPoint*> >, public ReadWriteLock {
	String zoneName;
public:

	PlanetTravelPointList() : VectorMap<String, Reference<PlanetTravelPoint*> >() {
		setNoDuplicateInsertPlan();
		setNullValue(NULL);
	}

	void insertToMessage(BaseMessage* message) {
		rlock();

		int totalPoints = size();

		message->insertInt(totalPoints);

		for (int i = 0; i < totalPoints; ++i)
			message->insertAscii(get(i)->getPointName());

		message->insertInt(totalPoints);

		for (int i = 0; i < totalPoints; ++i) {
			Reference<PlanetTravelPoint*> ptp = get(i);
			message->insertFloat(ptp->getArrivalPositionX());
			message->insertFloat(ptp->getArrivalPositionZ());
			message->insertFloat(ptp->getArrivalPositionY());
		}

		message->insertInt(totalPoints);

		for (int i = 0; i < totalPoints; ++i)
			message->insertInt(0); //TODO: Implement taxes.

		message->insertInt(totalPoints);

		for (int i = 0; i < totalPoints; ++i)
			message->insertByte((byte) get(i)->isInterplanetary());

		runlock();
	}

	void readLuaObject(LuaObject* luaObject) {
		wlock();

		if (!luaObject->isValidTable())
			return;

		for (int i = 1; i <= luaObject->getTableSize(); ++i) {
			lua_State* L = luaObject->getLuaState();
			lua_rawgeti(L, -1, i);

			LuaObject planetTravelPointEntry(L);

			Reference<PlanetTravelPoint*> ptp = new PlanetTravelPoint(zoneName);
			ptp->readLuaObject(&planetTravelPointEntry);

			put(ptp->getPointName(), ptp);

			planetTravelPointEntry.pop();
		}

		unlock();
	}

	inline void setZoneName(const String& name) {
		zoneName = name;
	}
};

#endif /* PLANETTRAVELPOINTLIST_H_ */
