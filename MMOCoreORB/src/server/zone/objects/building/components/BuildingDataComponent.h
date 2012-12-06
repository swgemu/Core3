/*
 * BuildingDataComponent.h
 *
 *  Created on: Oct 22, 2012
 *      Author: root
 */

#ifndef BUILDINGDATACOMPONENT_H_
#define BUILDINGDATACOMPONENT_H_
#include "server/zone/objects/scene/components/DataObjectComponent.h"

class BuildingDataComponent : public DataObjectComponent {

public:
	BuildingDataComponent(){
	}

	virtual ~BuildingDataComponent(){
	}

	virtual bool isGCWBaseData(){
		return false;
	}

	bool isBuildingData(){
		return true;
	}
};


#endif /* BUILDINGDATACOMPONENT_H_ */
