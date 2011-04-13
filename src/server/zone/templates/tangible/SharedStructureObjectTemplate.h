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
	SortedVector<String> allowedZones;

	String constructionMarkerTemplate;
	String abilityRequired;

	int baseMaintenanceRate;
	int basePowerRate;

	uint8 lotSize;
	uint8 cityRankRequired;

public:
	SharedStructureObjectTemplate() {

	}

	~SharedStructureObjectTemplate() {

	}

	void readObject(LuaObject* templateData);

	inline uint8 getLotSize() {
		return lotSize;
	}

	inline bool isAllowedZone(const String& terrainName) {
		return allowedZones.contains(terrainName);
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
