/*
 * CustomizationDataMap.h
 *
 *  Created on: Feb 11, 2011
 *      Author: crush
 */

#ifndef CUSTOMIZATIONDATAMAP_H_
#define CUSTOMIZATIONDATAMAP_H_

#include "templates/customization/CustomizationData.h"

class CustomizationDataMap : public VectorMap<String, Vector<CustomizationData>> {
public:
	CustomizationDataMap() {
		setNoDuplicateInsertPlan();
	}

	void parseFromIffStream(IffStream* iffStream) {
	}
};

#endif /* CUSTOMIZATIONDATAMAP_H_ */
