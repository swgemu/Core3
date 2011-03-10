/*
 * ContainerTemplate.h
 *
 *  Created on: Mar 9, 2011
 *      Author: polonel
 */

#ifndef CONTAINERTEMPLATE_H_
#define CONTAINERTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class ContainerTemplate : public SharedTangibleObjectTemplate {
	bool lock;

public:
	ContainerTemplate() {

	}

	~ContainerTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		lock = templateData->getByteField("locked");

    }

	inline bool getLocked() const {
		return lock;
	}

};

#endif /* CONTAINERTEMPLATE_H_ */
