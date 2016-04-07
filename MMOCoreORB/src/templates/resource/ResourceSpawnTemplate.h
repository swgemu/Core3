/*
 * SharedResourceContainerObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: kyle
 */

#ifndef RESOURCESPAWNTEMPLATE_H_
#define RESOURCESPAWNTEMPLATE_H_

#include "templates/SharedObjectTemplate.h"

class ResourceSpawnTemplate : public SharedObjectTemplate {
private:

public:
	ResourceSpawnTemplate() {

	}

	~ResourceSpawnTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedObjectTemplate::readObject(templateData);

	}
};

#endif /* RESOURCESPAWNTEMPLATE_H_ */
