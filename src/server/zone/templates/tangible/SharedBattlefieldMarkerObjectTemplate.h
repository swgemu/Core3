/*
 * SharedBattlefieldMarkerObjectTemplate.h
 *
 *  Created on: 05/05/2010
 *      Author: victor
 */

#ifndef SHAREDBATTLEFIELDMARKEROBJECTTEMPLATE_H_
#define SHAREDBATTLEFIELDMARKEROBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedBattlefieldMarkerObjectTemplate : public SharedTangibleObjectTemplate {

public:
	SharedBattlefieldMarkerObjectTemplate() {

	}

	~SharedBattlefieldMarkerObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
	}

};


#endif /* SHAREDBATTLEFIELDMARKEROBJECTTEMPLATE_H_ */
