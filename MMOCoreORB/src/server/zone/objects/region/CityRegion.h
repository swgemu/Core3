/*
 * CityRegion.h
 *
 *  Created on: Feb 9, 2012
 *      Author: xyborn
 */

#ifndef CITYREGION_H_
#define CITYREGION_H_

#include "engine/engine.h"
#include "server/zone/ZoneReference.h"
#include "server/zone/objects/scene/variables/StringId.h"

namespace server {
namespace zone {
namespace objects {
namespace area {
	class ActiveArea;
}
namespace creature {
	class CreatureObject;
}
}
}
}
using namespace server::zone::objects::area;
using namespace server::zone::objects::creature;

class CityRegion : public Serializable, public Logger, public ReadWriteLock {
	StringId regionName;

	ZoneReference zone;

	SortedVector<ManagedReference<ActiveArea*> > activeAreas;

	uint8 cityRank;

	String citySpecialization; //We want to implement this with skill mods.

public:
	static const uint8 RANK_CLIENT = 0;
	static const uint8 RANK_OUTPOST = 1;
	static const uint8 RANK_VILLAGE = 2;
	static const uint8 RANK_TOWNSHIP = 3;
	static const uint8 RANK_CITY = 4;
	static const uint8 RANK_METROPOLIS = 5;

public:
	CityRegion(Zone* zne, const String& name);
	CityRegion(const CityRegion& cr);

	CityRegion& operator= (const CityRegion& cr);

	void addSerializableVariables();

	void addActiveArea(float x, float y, float radius);

	void notifyEnter(CreatureObject* creature);
	void notifyExit(CreatureObject* creature);

	bool containsPoint(float x, float y);

	//Getters
	inline uint8 getCityRank() {
		return cityRank;
	}

	inline String getRegionName() {
		return regionName.getDisplayedName();
	}

	//Setters
	inline void setRegionName(const UnicodeString& name) {
		regionName.setCustomString(name);
	}

	inline void setRegionName(const String& fullPath) {
		regionName.setStringId(fullPath);
	}

	inline void setRegionName(const StringId& name) {
		regionName = name;
	}

	inline void setCityRank(uint8 rank) {
		cityRank = rank;
	}
};

#endif /* CITYREGION_H_ */
