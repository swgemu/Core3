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
#include "templates/appearance/FloorMesh.h"
#include "templates/appearance/AppearanceTemplate.h"

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

	bool isSolid() const {
		return solid;
	}

	int getGeometryIndex() const {
		return geometryIndex;
	}

	bool isWindingCCW() const {
		return winding;
	}

	int getTargetCellIndex() const {
		return targetCell;
	}

	const String& getDoorTemplate() const {
		return doorName;
	}

	bool hasDoorTemplate() const {
		return doorName.isEmpty() == false;
	}

	bool hasDoorTransform() const {
		return transformFlag;
	}

	const Matrix4& getDoorTransform() const {
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
	Reference<BaseBoundingVolume*> boundingVolume;
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

	FloorMesh* getFloorMesh() const {
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

	const CellPortal* getPortal(int idx) const {
		return portals.get(idx);
	}

	void loadVersion4(IffStream* iffStream);
	void loadVersion5(IffStream* iffStream);
};

#endif /* CELLPROPERTY_H_ */
