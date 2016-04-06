/*
 * CellProperty.h
 *
 *  Created on: Apr 19, 2015
 *      Author: TheAnswer
 */

#ifndef SRC_SERVER_ZONE_TEMPLATES_APPEARANCE_CELLPROPERTY_H_
#define SRC_SERVER_ZONE_TEMPLATES_APPEARANCE_CELLPROPERTY_H_

#include "engine/engine.h"

#include "templates/IffTemplate.h"

class MeshAppearanceTemplate;
class FloorMesh;

class CellProperty : public IffTemplate, public Logger {
protected:
	String name;
	bool canSeeParentCell;
	int numberOfPortals;
	FloorMesh* floorMesh;
	MeshAppearanceTemplate* appearanceTemplate;
	int cellID;

public:
	CellProperty();
	CellProperty(int cellID);
	CellProperty(const CellProperty& c);

	CellProperty& operator=(const CellProperty& c);

	void readObject(IffStream* iffStream);

	MeshAppearanceTemplate* getAppearanceTemplate() {
		return appearanceTemplate;
	}

	bool isCanSeeParentCell() const {
		return canSeeParentCell;
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

};


#endif /* SRC_SERVER_ZONE_TEMPLATES_APPEARANCE_CELLPROPERTY_H_ */
