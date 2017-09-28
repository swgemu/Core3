/*
 * ContainerTemplate.h
 *
 *  Created on: Mar 9, 2011
 *      Author: polonel
 */

#ifndef CONTAINERTEMPLATE_H_
#define CONTAINERTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class ContainerTemplate : public SharedTangibleObjectTemplate {
	bool lock;
	int lockChance;

public:
	ContainerTemplate() : lock(false) {
		lockChance = 0;
	}

	~ContainerTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		lock = templateData->getByteField("locked");
		lockChance = templateData->getIntField("lockChance");

    }

	inline bool getLocked() const {
		return lock;
	}

	inline int getLockChance() const {
		return lockChance;
	}

};

#endif /* CONTAINERTEMPLATE_H_ */
