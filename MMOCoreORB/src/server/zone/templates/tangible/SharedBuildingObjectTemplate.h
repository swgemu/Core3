/*
 * SharedBuildingObjectTemplate.h
 *
 *  Created on: 05/05/2010
 *      Author: victor
 */

#ifndef SHAREDBUILDINGOBJECTTEMPLATE_H_
#define SHAREDBUILDINGOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedBuildingObjectTemplate : public SharedTangibleObjectTemplate {
	String terrainModificationFileName;
	String interiorLayoutFileName;

public:
	SharedBuildingObjectTemplate() {

	}

	~SharedBuildingObjectTemplate() {

	}

	void readObject(LuaObject* templateData);
};

#endif /* SHAREDBUILDINGOBJECTTEMPLATE_H_ */
