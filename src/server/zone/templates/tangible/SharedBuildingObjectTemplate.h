/*
 * SharedBuildingObjectTemplate.h
 *
 *  Created on: 05/05/2010
 *      Author: victor
 */

#ifndef SHAREDBUILDINGOBJECTTEMPLATE_H_
#define SHAREDBUILDINGOBJECTTEMPLATE_H_

#include "SharedStructureObjectTemplate.h"

class SharedBuildingObjectTemplate : public SharedStructureObjectTemplate {
	String terrainModificationFileName;
	String interiorLayoutFileName;

public:
	SharedBuildingObjectTemplate() {

	}

	~SharedBuildingObjectTemplate() {

	}

	void readObject(LuaObject* templateData);

	virtual bool isSharedBuildingObjectTemplate() {
		return true;
	}
};

#endif /* SHAREDBUILDINGOBJECTTEMPLATE_H_ */
