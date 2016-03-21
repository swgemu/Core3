#include "ClientCell.h"
#include "client/zone/managers/appearance/AppearanceManager.h"
#include "templates/appearance/FloorMesh.h"
ClientCell::ClientCell(CellProperty tmpl) : SceneObject(NULL) {
	cellTemplate = tmpl;
	floorMesh = tmpl.getFloorMesh();
	appearance = AppearanceManager::instance()->getAppearance(tmpl.getAppearanceTemplate());
	static int cellId = 0x1000;
	objectID = ++cellId;
	transform = new osg::MatrixTransform();
}

void ClientCell::addToScene() {
	SceneObject::addToScene();
	
	floorGroup = new osg::Group();
	mainGroup = new osg::Group();
	if (appearance != NULL) {
		
		mainGroup->addChild(appearance->draw());
	}
	

	addChild(mainGroup);
	addChild(floorGroup);
	
	if(floorMesh != NULL) {
		mainGroup->addChild(ClientRenderer::drawFloorMesh(floorMesh));
		PathGraph*graph = floorMesh->getPathGraph();
		if (graph != NULL)
			mainGroup->addChild(ClientRenderer::drawPathGraph(graph));
	}
}

Vector<Reference<MeshData*> > ClientCell::getTransformedMeshData() {
	
		Vector<Reference<MeshData*> > data;
		for (int i=0; i<containerObjects.size(); i++) {
			SceneObject *sceno = containerObjects.get(i);
			
			if(sceno == NULL) {
				
				return data;
			}
			
			Vector<Reference<MeshData*> > meshes = sceno->getTransformedMeshData();
			for(int i=0; i<meshes.size(); i++) {
				Matrix4 transform = getMatrix4Transform();
				meshes.get(i)->transformMeshData(transform);
			}
			data.addAll(meshes);
		}
		
		
		data.addAll(appearance->getTransformedMeshData());
		
		return data;
}