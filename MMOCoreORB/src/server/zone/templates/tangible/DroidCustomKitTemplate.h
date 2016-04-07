/*
 * DroidCustomKitTemplate.h
 *
 *  Created on: 11/29/2013
 *      Author: Klivian
 */

#ifndef DROIDCUSTOMKITTEMPLATE_H_
#define DROIDCUSTOMKITTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class DroidCustomKitTemplate : public SharedTangibleObjectTemplate {

public:
	DroidCustomKitTemplate() {

	}

	~DroidCustomKitTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

    }

	bool isDroidCustomKitTemplate() {
		return true;
	}

};

#endif /* DROIDCUSTOMKITTEMPLATE_H_ */
