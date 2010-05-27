/*
 * SharedStaticObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDSTATICOBJECTTEMPLATE_H_
#define SHAREDSTATICOBJECTTEMPLATE_H_


#include "SharedObjectTemplate.h"
#include "tangible/SharedBuildingObjectTemplate.h"


class SharedStaticObjectTemplate : public SharedObjectTemplate {
protected:


public:
	SharedStaticObjectTemplate() {

	}

	~SharedStaticObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedObjectTemplate::readObject(templateData);
	}

};


#endif /* SHAREDSTATICOBJECTTEMPLATE_H_ */
