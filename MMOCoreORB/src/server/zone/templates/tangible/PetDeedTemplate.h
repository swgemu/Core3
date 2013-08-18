/*
 * PetDeedTemplate.h
 *
 *  Created on: August 17, 2013
 *      Author: washu
 */

#ifndef PETDEEDTEMPLATE_H_
#define PETDEEDTEMPLATE_H_

#include "DeedTemplate.h"

class PetDeedTemplate : public DeedTemplate {

public:
	PetDeedTemplate() {

	}

	~PetDeedTemplate() {

	}

	void readObject(LuaObject* templateData) {
		DeedTemplate::readObject(templateData);
    }
};


#endif /* PETDEEDTEMPLATE_H_ */
