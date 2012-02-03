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
	StringParam terrainModificationFileName;
	StringParam interiorLayoutFileName;

	int medicalRating;

	ChildObject sign;

	bool publicStructure;

	bool alwaysPublic;


public:
	SharedBuildingObjectTemplate() {
	}

	~SharedBuildingObjectTemplate() {
	}

	void readObject(LuaObject* templateData);
	void readObject(IffStream* iffStream);

	void parseVariableData(const String& varName, LuaObject* templateData);

	void parseVariableData(const String& varName, Chunk* data);
	void parseFileData(IffStream* iffStream);

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

	inline int getMedicalRating() const {
		return medicalRating;
	}
};

#endif /* SHAREDBUILDINGOBJECTTEMPLATE_H_ */
