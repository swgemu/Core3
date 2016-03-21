#include "ClientCell.h"
#include "client/zone/managers/appearance/AppearanceManager.h"
#include "templates/appearance/FloorMesh.h"
ClientCell::ClientCell(CellProperty tmpl) : SceneObject(NULL) {
	cellTemplate = tmpl;
	floorMesh = tmpl.getFloorMesh();
	appearance = AppearanceManager::instance()->getAppearance(tmpl.getAppearanceTemplate());
}

void ClientCell::addToScene() {
	if (appearance == NULL) {
		return;
	}
	
	floorGroup = new osg::Group();
	mainGroup = new osg::Group();
	addChild(mainGroup);
	addChild(floorGroup);
	
	//mainGroup->addChild(appearance->draw());
	if(floorMesh != NULL) {
		mainGroup->addChild(ClientRenderer::drawFloorMesh(floorMesh));
		return;
		PathGraph*graph = floorMesh->getPathGraph();
		mainGroup->addChild(ClientRenderer::drawPathGraph(graph));
	}
	
	
	
	
	
}