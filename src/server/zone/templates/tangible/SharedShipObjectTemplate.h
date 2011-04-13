/*
 * SharedShipObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDSHIPOBJECTTEMPLATE_H_
#define SHAREDSHIPOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedShipObjectTemplate : public SharedTangibleObjectTemplate {

public:
	SharedShipObjectTemplate() {

	}

	~SharedShipObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
	}
};

#endif /* SHAREDSHIPOBJECTTEMPLATE_H_ */
