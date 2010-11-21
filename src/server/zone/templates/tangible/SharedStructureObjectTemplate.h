/*
 * SharedStructureObjectTemplate.h
 *
 *  Created on: May 22, 2010
 *      Author: crush
 */

#ifndef SHAREDSTRUCTUREOBJECTTEMPLATE_H_
#define SHAREDSTRUCTUREOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedStructureObjectTemplate : public SharedTangibleObjectTemplate {
protected:
	SortedVector<unsigned int> allowedZones;

	String constructionMarkerTemplate;
	String abilityRequired;

	int baseMaintenanceRate;
	int basePowerRate;

	uint8 lotSize;
	uint8 cityRankRequired;
	uint8 length;
	uint8 width;

public:
	SharedStructureObjectTemplate() {

	}

	~SharedStructureObjectTemplate() {

	}

	void readObject(LuaObject* templateData);

	inline uint8 getLotSize() {
		return lotSize;
	}

	inline bool isAllowedZone(unsigned int zoneID) {
		return (allowedZones.find(zoneID) != -1);
	}

	inline int getBaseMaintenanceRate() {
		return baseMaintenanceRate;
	}

	inline int getBasePowerRate() {
		return basePowerRate;
	}

	inline String& getAbilityRequired() {
		return abilityRequired;
	}

	inline uint8 getLength() {
		return length;
	}

	inline uint8 getWidth() {
		return width;
	}

	inline uint8 getCityRankRequired() {
		return cityRankRequired;
	}

	inline String& getConstructionMarkerTemplate() {
		return constructionMarkerTemplate;
	}

	inline virtual bool isPublicStructure() {
		return false;
	}
};

#endif /* SHAREDSTRUCTUREOBJECTTEMPLATE_H_ */
