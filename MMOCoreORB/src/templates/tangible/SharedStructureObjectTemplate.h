/*
 * SharedStructureObjectTemplate.h
 *
 *  Created on: May 22, 2010
 *      Author: crush
 */

#ifndef SHAREDSTRUCTUREOBJECTTEMPLATE_H_
#define SHAREDSTRUCTUREOBJECTTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

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

public:
	SharedStructureObjectTemplate() {
		baseMaintenanceRate = 0;
		basePowerRate = 0;

		lotSize = 0;
		cityRankRequired = 0;

		uniqueStructure = false;

		//If it has a maintenance rate, then it is a civic structure.
		cityMaintenanceBase = 0;
		cityMaintenanceRate = 0;
	}

	~SharedStructureObjectTemplate() {

	}

	void readObject(LuaObject* templateData);

	inline uint8 getLotSize() const {
		return lotSize;
	}

	inline bool isAllowedZone(const String& zoneName) {
		return allowedZones.contains(zoneName);
	}

	inline bool isCivicStructure() const {
		return (cityMaintenanceBase > 0);
	}

	inline bool isCommercialStructure() const {
		return (baseMaintenanceRate > 0 && cityRankRequired > 0);
	}

	inline bool isUniqueStructure() const {
		return uniqueStructure;
	}

	inline int getCityMaintenanceBase() const {
		return cityMaintenanceBase;
	}

	inline int getCityMaintenanceRate() const {
		return cityMaintenanceRate;
	}

	inline int getCityMaintenanceAtRank(int rank) const {
		return cityMaintenanceBase + cityMaintenanceRate * rank;
	}

	inline int getTotalAllowedZones() const {
		return allowedZones.size();
	}

	inline String getAllowedZone(int i) const {
		return allowedZones.get(i);
	}

	inline int getBaseMaintenanceRate() const {
		return baseMaintenanceRate;
	}

	inline int getBasePowerRate() const {
		return basePowerRate;
	}

	inline const String& getAbilityRequired() const {
		return abilityRequired;
	}

	inline uint8 getCityRankRequired() const {
		return cityRankRequired;
	}

	inline const String& getConstructionMarkerTemplate() const {
		return constructionMarkerTemplate;
	}

	inline virtual bool isPublicStructure() const {
		return false;
	}

	virtual bool isSharedStructureObjectTemplate() {
		return true;
	}
};

#endif /* SHAREDSTRUCTUREOBJECTTEMPLATE_H_ */
