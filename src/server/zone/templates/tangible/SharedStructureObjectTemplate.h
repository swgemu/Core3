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

	int lotSize;

	int baseMaintenanceRate;

	int basePowerRate;

public:
	SharedStructureObjectTemplate() {

	}

	~SharedStructureObjectTemplate() {

	}

	void readObject(LuaObject* templateData);

	inline int getLotSize() {
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
};

#endif /* SHAREDSTRUCTUREOBJECTTEMPLATE_H_ */
