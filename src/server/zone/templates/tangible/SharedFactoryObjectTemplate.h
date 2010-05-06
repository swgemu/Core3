/*
 * SharedFactoryObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDFACTORYOBJECTTEMPLATE_H_
#define SHAREDFACTORYOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedFactoryObjectTemplate : public SharedTangibleObjectTemplate {

public:
	SharedFactoryObjectTemplate() {

	}

	~SharedFactoryObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
	}
};


#endif /* SHAREDFACTORYOBJECTTEMPLATE_H_ */
