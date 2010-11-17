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

	StructureTerminalLocation* structureTerminalLocation;

	bool publicStructure;

	bool alwaysPublic;


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

	inline bool isPublicStructure() {
		if (alwaysPublic)
			return true;

		return publicStructure;
	}

	inline bool isAlwaysPublic() {
		return alwaysPublic;
	}
};

#endif /* SHAREDBUILDINGOBJECTTEMPLATE_H_ */
