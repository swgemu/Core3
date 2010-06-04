/*
 * SharedInstallationObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDINSTALLATIONOBJECTTEMPLATE_H_
#define SHAREDINSTALLATIONOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedInstallationObjectTemplate : public SharedTangibleObjectTemplate {

public:
	SharedInstallationObjectTemplate() {

	}

	~SharedInstallationObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
	}

	virtual bool isSharedInstallationObjectTemplate() {
		return true;
	}
};


#endif /* SHAREDINSTALLATIONOBJECTTEMPLATE_H_ */
