/*
 * ClientCell.h
 *
 *  Created on: 4/10/2016
 *      Author: gslomin
 */

#ifndef CLIENTCELL_H_
#define CLIENTCELL_H_

#include "engine/engine.h"
#include "../scene/SceneObject.h"
#include "templates/appearance/CellProperty.h"

class CellProperty;
class Appearance;
class FloorMesh;
class MeshData;

class ClientCell : public SceneObject {
	CellProperty cellTemplate;
	FloorMesh *floorMesh;
	osg::ref_ptr<osg::Group> floorGroup;
	osg::ref_ptr<osg::Group> mainGroup;
public:
	ClientCell(CellProperty tmpl);
	
	void addToScene();
	Vector<Reference<MeshData*> > getTransformedMeshData();
	
	CellProperty* const getCellTemplate() {
		return &cellTemplate;
	}
	
};


#endif /* CLIENTCELL_H_ */
