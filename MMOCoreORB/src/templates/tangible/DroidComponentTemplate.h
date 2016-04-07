/*
 * DroidComponentTemplate.h
 *
 *  Created on: Aug 21, 2014
 *      Author: washu
 */

#ifndef DROIDCOMPONENTTEMPLATE_H_
#define DROIDCOMPONENTTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class DroidComponentTemplate : public SharedTangibleObjectTemplate {

public:
	DroidComponentTemplate() {

	}

	~DroidComponentTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
    }

	bool isDroidComponentTemplate() {
		return true;
	}

};

#endif /* DROIDCOMPONENTTEMPLATE_H_ */
