/*
 * SharedBuildingObjectTemplate.h
 *
 *  Created on: 05/05/2010
 *      Author: victor
 */

#ifndef SHAREDBUILDINGOBJECTTEMPLATE_H_
#define SHAREDBUILDINGOBJECTTEMPLATE_H_

#include "SharedStructureObjectTemplate.h"
#include "../ChildCreatureObject.h"
#include "server/zone/templates/tangible/SignTemplate.h"

class SharedBuildingObjectTemplate : public SharedStructureObjectTemplate {
	StringParam terrainModificationFileName;
	StringParam interiorLayoutFileName;

	Vector<ChildCreatureObject> childCreatureObjects;
	int medicalRating;

	ChildObject sign;

	bool publicStructure;

	bool alwaysPublic;

	Vector3 ejectionPoint;

	int factionBaseType;

	Vector<SignTemplate> shopSigns;

public:
	SharedBuildingObjectTemplate() : medicalRating(0), publicStructure(false), alwaysPublic(false), factionBaseType(0) {
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

	inline int getChildCreatureObjectsSize(){
		return childCreatureObjects.size();
	}

	inline ChildCreatureObject* getChildCreatureObject(int indx){
		return &childCreatureObjects.get(indx);
	}

	inline String getTerrainModificationFile() {
		return terrainModificationFileName.get();
	}

	inline Vector3 getEjectionPoint() {
		return ejectionPoint;
	}

	inline int getFactionBaseType() {
		return factionBaseType;
	}

	inline int getShopSignsSize() {
		return shopSigns.size();
	}

	inline SignTemplate* getShopSign(int idx) {
		return &shopSigns.get(idx);
	}
};

#endif /* SHAREDBUILDINGOBJECTTEMPLATE_H_ */
