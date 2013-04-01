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
		bool incomingAllowed[totalPoints];
		int insertionPoints = totalPoints;

		for (int i = 0; i < totalPoints; ++i) {
			Reference<PlanetTravelPoint*> ptp = get(i);
			incomingAllowed[i] = ptp->isIncomingAllowed();
			if (!incomingAllowed[i])
				insertionPoints--;
		}

		message->insertInt(insertionPoints);

		for (int i = 0; i < totalPoints; ++i) {
			if (incomingAllowed[i])
				message->insertAscii(get(i)->getPointName());
		}

		message->insertInt(insertionPoints);

		for (int i = 0; i < totalPoints; ++i) {
			if (incomingAllowed[i]) {
				Reference<PlanetTravelPoint*> ptp = get(i);
				message->insertFloat(ptp->getArrivalPositionX());
				message->insertFloat(ptp->getArrivalPositionZ());
				message->insertFloat(ptp->getArrivalPositionY());
			}
		}

		message->insertInt(insertionPoints);

		for (int i = 0; i < totalPoints; ++i){
			if (incomingAllowed[i]) {
				Reference<PlanetTravelPoint*> ptp = get(i);
				ManagedReference<CreatureObject*> shuttle = ptp->getShuttle();
				if(shuttle == NULL){
					message->insertInt(0);
					continue;
				}

				if(shuttle->getCityRegion() == NULL){
					message->insertInt(0);
					continue;
				}
				ManagedReference<CityRegion*> city = shuttle->getCityRegion().get();

				message->insertInt(city->getTax(CityRegion::TAX_TRAVEL));
			}
		}

		message->insertInt(insertionPoints);

		for (int i = 0; i < totalPoints; ++i) {
			if (incomingAllowed[i])
				message->insertByte((byte) get(i)->isInterplanetary());
		}

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

	void addPlayerCityTravelPoint(PlanetTravelPoint* planetTravelPoint){
		wlock();

		put(planetTravelPoint->getPointName(), planetTravelPoint);

		unlock();
	}

	void removePlayerCityTravelPoint(const String& pointName){
		wlock();

		drop(pointName);

		unlock();
	}
};

#endif /* PLANETTRAVELPOINTLIST_H_ */
