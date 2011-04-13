/*
 * FireworkObjectTemplate.h
 *
 *  Created on: May 7, 2010
 *      Author: swgemu
 */

#ifndef FIREWORKOBJECTTEMPLATE_H_
#define FIREWORKOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class FireworkObjectTemplate : public SharedTangibleObjectTemplate {
	String fireworkObject;

public:
	FireworkObjectTemplate() {

	}

	~FireworkObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		fireworkObject = templateData->getStringField("fireworkObject");
    }

    inline String getFireworkObject() const {
       return fireworkObject;
    }

	bool isFireworkObjectTemplate() {
		return true;
	}
};



#endif /* FIREWORKOBJECTTEMPLATE_ */
