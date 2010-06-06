/*
 * SharedBuildingObjectTemplate.h
 *
 *  Created on: 05/05/2010
 *      Author: victor
 */

#ifndef SHAREDBUILDINGOBJECTTEMPLATE_H_
#define SHAREDBUILDINGOBJECTTEMPLATE_H_

#include "SharedStructureObjectTemplate.h"
#include "StructureTerminalLocation.h"

class SharedBuildingObjectTemplate : public SharedStructureObjectTemplate {
	String terrainModificationFileName;
	String interiorLayoutFileName;

	uint8 cityRankRequired;

	StructureTerminalLocation* structureTerminalLocation;


public:
	SharedBuildingObjectTemplate() {
		structureTerminalLocation = NULL;
	}

	~SharedBuildingObjectTemplate() {
		if (structureTerminalLocation != NULL) {
			delete structureTerminalLocation;
			structureTerminalLocation = NULL;
		}
	}

	void readObject(LuaObject* templateData);

	virtual bool isSharedBuildingObjectTemplate() {
		return true;
	}

	inline StructureTerminalLocation* getStructureTerminalLocation() {
		return structureTerminalLocation;
	}
};

#endif /* SHAREDBUILDINGOBJECTTEMPLATE_H_ */
