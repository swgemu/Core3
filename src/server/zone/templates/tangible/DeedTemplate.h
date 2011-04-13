/*
 * DeedTemplate.h
 *
 *  Created on: May 8, 2010
 *      Author: crush
 */

#ifndef DEEDTEMPLATE_H_
#define DEEDTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class DeedTemplate : public SharedTangibleObjectTemplate {
	String generatedObjectTemplate;

public:
	DeedTemplate() {

	}

	~DeedTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		generatedObjectTemplate = templateData->getStringField("generatedObjectTemplate");
    }

	inline String& getGeneratedObjectTemplate() {
		return generatedObjectTemplate;
	}
};

#endif /* DEEDTEMPLATE_H_ */
