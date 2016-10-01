/*
 * CellProperty.h
 *
 *  Created on: Apr 19, 2015
 *      Author: TheAnswer
 */

#ifndef CELLPROPERTY_H_
#define CELLPROPERTY_H_

#include "engine/engine.h"

#include "templates/IffTemplate.h"
#include "templates/collision/BaseBoundingVolume.h"

class AppearanceTemplate;
class FloorMesh;

class CellPortal : public Object {
	bool solid;
	int geometryIndex;
	bool winding;
	int targetCell;
	String doorName;
	bool transformFlag;
	Matrix4 doorTransform;
public:
	
	void readObject(IffStream *iff);
	void load_0004(IffStream *iff);
	
	bool isSolid() {
		return solid;
	}
	
	int getGeometryIndex() {
		return geometryIndex;
	}
	
	bool isWindingCCW() {
		return winding;
	}
	
	int getTargetCellIndex() {
		return targetCell;
	}
	
	String getDoorTemplate() {
		return doorName;
	}
	
	bool hasDoorTemplate() {
		return doorName.isEmpty() == false;
	}
	
	bool hasDoorTransform() {
		return transformFlag;
	}
	
	const Matrix4& getDoorTransform() {
		return doorTransform;
	}

};

class CellProperty : public IffTemplate, public Logger {
protected:
	String name;
	int numberOfPortals;
	FloorMesh* floorMesh;
	AppearanceTemplate* appearanceTemplate;
	int cellID;
	BaseBoundingVolume *boundingVolume;
	Vector<Reference<CellPortal*> > portals;

public:
	CellProperty();
	CellProperty(int cellID);
	CellProperty(const CellProperty& c);

	CellProperty& operator=(const CellProperty& c);

	void readObject(IffStream* iffStream);

	AppearanceTemplate* getAppearanceTemplate() {
		return appearanceTemplate;
	}

	FloorMesh* getFloorMesh() {
		return floorMesh;
	}

	const String& getName() const {
		return name;
	}

	int getCellID() const {
		return cellID;
	}

	int getNumberOfPortals() const {
		return numberOfPortals;
	}
	
	CellPortal* getPortal(int idx) const {
		return portals.get(idx);
	}

	
	int getNumberOfPortals() {
		return numberOfPortals;
	}
	
	CellPortal* getPortal(int idx) {
		return portals.get(idx);
	}
	void load_0004(IffStream* iffStream);
	void load_0005(IffStream* iffStream);
};


#endif /* CELLPROPERTY_H_ */
