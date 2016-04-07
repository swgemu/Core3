/*
 * FireworkObjectTemplate.h
 *
 *  Created on: May 7, 2010
 *      Author: swgemu
 */

#ifndef FIREWORKOBJECTTEMPLATE_H_
#define FIREWORKOBJECTTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class FireworkObjectTemplate : public SharedTangibleObjectTemplate {
	String fireworkObject;
	bool isShow;

public:
	FireworkObjectTemplate() {
		isShow = false;
	}

	~FireworkObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		fireworkObject = templateData->getStringField("fireworkObject");
		isShow = templateData->getBooleanField("showPackage");
	}

    inline String getFireworkObject() const {
       return fireworkObject;
    }

    bool isFireworkShow() {
    	return isShow;
    }

	bool isFireworkObjectTemplate() {
		return true;
	}
};



#endif /* FIREWORKOBJECTTEMPLATE_ */
