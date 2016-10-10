/*
 * SharedBuildingObjectTemplate.h
 *
 *  Created on: 05/05/2010
 *      Author: victor
 */

#ifndef SHAREDBUILDINGOBJECTTEMPLATE_H_
#define SHAREDBUILDINGOBJECTTEMPLATE_H_

#include "templates/tangible/SharedStructureObjectTemplate.h"
#include "templates/ChildCreatureObject.h"
#include "templates/building/SignTemplate.h"

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

	inline bool isPublicStructure() const {
		if (alwaysPublic)
			return true;

		return publicStructure;
	}

	inline bool isAlwaysPublic() const {
		return alwaysPublic;
	}

	inline ChildObject* getSign() {
		return &sign;
	}

	inline int getMedicalRating() const {
		return medicalRating;
	}

	inline int getChildCreatureObjectsSize() const  {
		return childCreatureObjects.size();
	}

	inline ChildCreatureObject* getChildCreatureObject(int indx){
		return &childCreatureObjects.get(indx);
	}

	inline String getTerrainModificationFile() const {
		return terrainModificationFileName.get();
	}

	inline String getInteriorLayoutFileName() const {
		return interiorLayoutFileName.get();
	}

	inline const Vector3& getEjectionPoint() const {
		return ejectionPoint;
	}

	inline int getFactionBaseType() const {
		return factionBaseType;
	}

	inline int getShopSignsSize() const {
		return shopSigns.size();
	}

	inline SignTemplate* getShopSign(int idx) const {
		return &shopSigns.get(idx);
	}
};

#endif /* SHAREDBUILDINGOBJECTTEMPLATE_H_ */
