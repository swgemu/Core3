/*
 * SharedStructureObjectTemplate.h
 *
 *  Created on: May 22, 2010
 *      Author: crush
 */

#ifndef SHAREDSTRUCTUREOBJECTTEMPLATE_H_
#define SHAREDSTRUCTUREOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"
#include "server/zone/templates/tangible/SignTemplate.h"

class SharedStructureObjectTemplate : public SharedTangibleObjectTemplate {
protected:
	SortedVector<String> allowedZones;

	String constructionMarkerTemplate;
	String abilityRequired;

	int baseMaintenanceRate;
	int basePowerRate;

	uint8 lotSize;
	uint8 cityRankRequired;

	bool uniqueStructure;

	//If it has a maintenance rate, then it is a civic structure.
	int cityMaintenanceBase;
	int cityMaintenanceRate;

	Vector<SignTemplate> shopSigns;

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

	inline bool isCivicStructure() {
		return (cityMaintenanceBase > 0);
	}

	inline bool isCommercialStructure() {
		return (baseMaintenanceRate > 0 && cityRankRequired > 0);
	}

	inline bool isUniqueStructure() {
		return uniqueStructure;
	}

	inline int getCityMaintenanceBase() {
		return cityMaintenanceBase;
	}

	inline int getCityMaintenanceRate() {
		return cityMaintenanceRate;
	}

	inline int getCityMaintenanceAtRank(int rank) {
		return cityMaintenanceBase + cityMaintenanceRate * rank;
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

	inline String& getConstructionMarkerTemplate() {
		return constructionMarkerTemplate;
	}

	inline virtual bool isPublicStructure() {
		return false;
	}

	inline int getShopSignsSize() {
		return shopSigns.size();
	}

	inline SignTemplate* getShopSign(int idx) {
		return &shopSigns.get(idx);
	}
};

#endif /* SHAREDSTRUCTUREOBJECTTEMPLATE_H_ */
