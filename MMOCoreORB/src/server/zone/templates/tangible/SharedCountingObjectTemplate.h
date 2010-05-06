/*
 * SharedCountingObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDCOUNTINGOBJECTTEMPLATE_H_
#define SHAREDCOUNTINGOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedCountingObjectTemplate : public SharedTangibleObjectTemplate {

public:
	SharedCountingObjectTemplate() {

	}

	~SharedCountingObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
	}
};


#endif /* SHAREDCOUNTINGOBJECTTEMPLATE_H_ */
