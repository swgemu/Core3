/*
 * TrapTemplate.h
 *
 *  Created on: Jan 16, 2012
 *      Author: kyle
 */

#ifndef TRAPTEMPLATE_H_
#define TRAPTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class TrapTemplate: public SharedTangibleObjectTemplate {
protected:



public:
	TrapTemplate() {

	}

	~TrapTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
	}

};


#endif /* TRAPTEMPLATE_H_ */
