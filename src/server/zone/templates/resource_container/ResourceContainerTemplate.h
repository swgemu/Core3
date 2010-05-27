/*
 * ResourceContainerTemplate
 *
 *  Created on: 06/05/2010
 *      Author: kyle
 */

#ifndef RESOURCECONTAINERTEMPLATE_H_
#define RESOURCECONTAINERTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class ResourceContainerTemplate : public SharedTangibleObjectTemplate {
private:

public:
	ResourceContainerTemplate() {

	}

	~ResourceContainerTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
	}
};

#endif /* RESOURCECONTAINERTEMPLATE_H_ */
