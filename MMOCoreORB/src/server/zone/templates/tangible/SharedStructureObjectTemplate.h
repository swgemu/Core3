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
	uint8 limitToOnePerCity;

public:
	SharedStructureObjectTemplate() {
		cityRankRequired = 0;
	}

	~SharedStructureObjectTemplate() {

	}

	void readObject(LuaObject* templateData);

	inline uint8 getLotSize() {
		return lotSize;
	}

	inline bool isAllowedZone(const String& zoneName) {
		return allowedZones.contains(zoneName);
	}

	inline int getTotalAllowedZones() {
		return allowedZones.size();
	}

	inline String getAllowedZone(int i) const {
		return allowedZones.get(i);
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

	inline uint8 getLimitToOnePerCity(){
		return limitToOnePerCity;
	}

	inline String& getConstructionMarkerTemplate() {
		return constructionMarkerTemplate;
	}

	inline virtual bool isPublicStructure() {
		return false;
	}

	//TODO: Deprecate. Use SFP
	inline int getWidth() {
		return 0;
	}

	inline int getLength() {
		return 0;
	}
};

#endif /* SHAREDSTRUCTUREOBJECTTEMPLATE_H_ */
