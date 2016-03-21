/*
 * ClientBuilding.h
 *
 *  Created on: 4/10/2016
 *      Author: gslomin
 */

#ifndef CLIENTBUILDING_H_
#define CLIENTBUILDING_H_

#include "engine/engine.h"
#include "../scene/SceneObject.h"
class ClientCell;
class MeshData;
class ClientBuilding : public SceneObject {
	PathGraph *pathGraph;
	osg::ref_ptr<osg::Group> mainGroup;
	Vector<Reference<ClientCell*> > cells;
public:
	ClientBuilding(SharedObjectTemplate *tmpl);
	void initializePortalLayout(PortalLayout *layout);
	void addToScene();
	uint32 getCellCount() {
		return cells.size();
	}
	
	Vector<Reference<MeshData*> > getTransformedMeshData();
};


#endif /* CLIENTCELL_H_ */
