/*
 * SharedResourceContainerObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: kyle
 */

#ifndef CRAFTINGSTATIONTEMPLATE_H_
#define CRAFTINGSTATIONTEMPLATE_H_

#include "../../SharedTangibleObjectTemplate.h"

class CraftingStationTemplate : public SharedTangibleObjectTemplate {
private:

	int stationType;

public:
	CraftingStationTemplate() {

	}

	~CraftingStationTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		stationType = templateData->getIntField("stationType");
	}

	int getStationType() {
		return stationType;
	}


};

#endif /* CRAFTINGSTATIONTEMPLATE_H_ */
