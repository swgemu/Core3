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

	ChildObject sign;

	bool publicStructure;

	bool alwaysPublic;


public:
	SharedBuildingObjectTemplate() {
	}

	~SharedBuildingObjectTemplate() {
	}

	void readObject(LuaObject* templateData);

	virtual bool isSharedBuildingObjectTemplate() {
		return true;
	}

	inline bool isPublicStructure() {
		if (alwaysPublic)
			return true;

		return publicStructure;
	}

	inline bool isAlwaysPublic() {
		return alwaysPublic;
	}

	inline ChildObject* getSign() {
		return &sign;
	}
};

#endif /* SHAREDBUILDINGOBJECTTEMPLATE_H_ */
