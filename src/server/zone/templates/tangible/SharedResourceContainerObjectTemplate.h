/*
 * SharedResourceContainerObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDRESOURCECONTAINEROBJECTTEMPLATE_H_
#define SHAREDRESOURCECONTAINEROBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedResourceContainerObjectTemplate : public SharedTangibleObjectTemplate {

public:
	SharedResourceContainerObjectTemplate() {

	}

	~SharedResourceContainerObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
	}
};

#endif /* SHAREDRESOURCECONTAINEROBJECTTEMPLATE_H_ */
