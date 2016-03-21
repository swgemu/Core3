/*
 * SlicingToolTemplate.h
 *
 *  Created on: Mar 6, 2011
 *      Author: polonel
 */

#ifndef SLICINGTOOLTEMPLATE_H_
#define SLICINGTOOLTEMPLATE_H_

#include "../../SharedTangibleObjectTemplate.h"

class SlicingToolTemplate : public SharedTangibleObjectTemplate {
private:
	float effectiveness;

public:
	SlicingToolTemplate() {
		effectiveness = 0;
	}

	~SlicingToolTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		effectiveness = templateData->getFloatField("effectiveness");

	}

	float getEffectiveness() const {
		return effectiveness;
	}

};

#endif /* SLICINGTOOLTEMPLATE_H_ */
