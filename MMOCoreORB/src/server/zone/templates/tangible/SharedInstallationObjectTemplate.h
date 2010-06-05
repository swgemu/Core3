/*
 * SharedInstallationObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDINSTALLATIONOBJECTTEMPLATE_H_
#define SHAREDINSTALLATIONOBJECTTEMPLATE_H_

#include "SharedStructureObjectTemplate.h"

class SharedInstallationObjectTemplate : public SharedStructureObjectTemplate {
public:
	SharedInstallationObjectTemplate() {

	}

	~SharedInstallationObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedStructureObjectTemplate::readObject(templateData);
	}

	virtual bool isSharedInstallationObjectTemplate() {
		return true;
	}
};


#endif /* SHAREDINSTALLATIONOBJECTTEMPLATE_H_ */
