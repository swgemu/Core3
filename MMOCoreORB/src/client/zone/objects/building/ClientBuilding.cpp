#include "ClientBuilding.h"
#include "client/zone/objects/building/ClientCell.h"
#include "templates/appearance/PortalLayout.h"
#include "templates/appearance/CellProperty.h"


ClientBuilding::ClientBuilding(SharedObjectTemplate *tmpl) : SceneObject(tmpl) {
	pathGraph = NULL;
	initializePortalLayout(tmpl->getPortalLayout());
	
}

void ClientBuilding::initializePortalLayout(PortalLayout *layout) {
	if (layout == NULL || cells.size() > 0)
		return;
	
	pathGraph = layout->getPathGraph();
	
	for (int i=0; i<layout->getAppearanceTemplatesSize(); i++) {
		
		Reference<ClientCell*> cell = new ClientCell(layout->getCellProperty(i));
		cells.add(cell);
		cell->addToScene();
	}
}

void ClientBuilding::addToScene() {
//	if(cells.size() > 0) {
//		for(int i=0; i < cells.size(); i++) { //cells.size(); i++) {
//			transform->addChild(cells.get(i));
//		}
//	} else {
//		SceneObject::addToScene();
//	}
	
	if(pathGraph != NULL)
		transform->addChild(ClientRenderer::drawPathGraph(pathGraph));
	
}