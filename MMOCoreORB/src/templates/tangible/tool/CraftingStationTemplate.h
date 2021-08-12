/*
 * SharedResourceContainerObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: kyle
 */

#ifndef CRAFTINGSTATIONTEMPLATE_H_
#define CRAFTINGSTATIONTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class CraftingStationTemplate : public SharedTangibleObjectTemplate {
private:
	int stationType;
	int complexityLevel;

public:
	CraftingStationTemplate() : stationType(0), complexityLevel(0) {
	}

	~CraftingStationTemplate() {
	}

	void readObject(LuaObject* templateData) override {
		SharedTangibleObjectTemplate::readObject(templateData);

		stationType = templateData->getIntField("stationType");
		complexityLevel = templateData->getIntField("complexityLevel");
	}

	int getStationType() const {
		return stationType;
	}

	int getComplexityLevel() const {
		return complexityLevel;
	}

	bool isCraftingStationTemplate() const override {
		return true;
	}
};

#endif /* CRAFTINGSTATIONTEMPLATE_H_ */
