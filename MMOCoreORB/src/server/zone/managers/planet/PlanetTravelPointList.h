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

class PlanetTravelPointList : public SortedVector<PlanetTravelPoint>, public ReadWriteLock {
private:
	int compare(PlanetTravelPoint& o1, const PlanetTravelPoint& o2) const {
		return o1.compareTo(o2);
	}

	int compare(PlanetTravelPoint& o1, const String& name) const {
		return o1.compareTo(name);
	}

public:
	PlanetTravelPointList() : SortedVector<PlanetTravelPoint>() {
	}

	int find(const String& name) const {
	    int l = 0, r = Vector<PlanetTravelPoint>::elementCount - 1;
	    int m = 0, cmp = 0;

	    while (l <= r) {
        	m = (l + r) / 2;

        	PlanetTravelPoint& obj = Vector<PlanetTravelPoint>::elementData[m];
        	cmp = compare(obj, name);

        	if (cmp == 0)
            	return m;
        	else if (cmp > 0)
	            l = m + 1;
        	else
	            r = m - 1;
	    }

    	return -1;
	}

	void insertToMessage(BaseMessage* message) {
		rlock();

		int totalPoints = size();

		message->insertInt(totalPoints);

		for (int i = 0; i < totalPoints; ++i)
			message->insertAscii(get(i).getPointName());

		message->insertInt(totalPoints);

		for (int i = 0; i < totalPoints; ++i) {
			PlanetTravelPoint ptp = get(i);
			message->insertFloat(ptp.getX());
			message->insertFloat(ptp.getZ());
			message->insertFloat(ptp.getY());
		}

		message->insertInt(totalPoints);

		for (int i = 0; i < totalPoints; ++i)
			message->insertInt(0); //TODO: Implement taxes.

		message->insertInt(totalPoints);

		for (int i = 0; i < totalPoints; ++i)
			message->insertByte((byte) get(i).isInterplanetary());

		runlock();
	}

	void readLuaObject(LuaObject* luaObject) {
		if (!luaObject->isValidTable())
			return;

		for (int i = 1; i <= luaObject->getTableSize(); ++i) {
			lua_State* L = luaObject->getLuaState();
			lua_rawgeti(L, -1, i);

			LuaObject planetTravelPointEntry(L);

			PlanetTravelPoint ptp;
			ptp.readLuaObject(&planetTravelPointEntry);

			put(ptp);

			planetTravelPointEntry.pop();
		}
	}
};

#endif /* PLANETTRAVELPOINTLIST_H_ */
