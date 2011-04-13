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
	uint32 installationType;
public:
	SharedInstallationObjectTemplate() {
		installationType = 0;
	}

	~SharedInstallationObjectTemplate() {
	}

	void readObject(LuaObject* templateData) {
		SharedStructureObjectTemplate::readObject(templateData);

		installationType = templateData->getIntField("installationType");
	}

	virtual bool isSharedInstallationObjectTemplate() {
		return true;
	}

	inline uint32 getInstallationType() {
		return installationType;
	}
};


#endif /* SHAREDINSTALLATIONOBJECTTEMPLATE_H_ */
