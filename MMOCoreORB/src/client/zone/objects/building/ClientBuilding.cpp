#include "ClientBuilding.h"
#include "Client/zone/objects/appearance/ClientAppearance.h"
#include "client/zone/objects/building/ClientCell.h"
#include "templates/appearance/PortalLayout.h"
#include "templates/appearance/CellProperty.h"
#include "templates/manager/TemplateManager.h"
#include "templates/building/SharedBuildingObjectTemplate.h"
#include "client/zone/managers/object/ObjectManager.h"
#include "templates/building/InteriorLayoutTemplate.h"

ClientBuilding::ClientBuilding(SharedObjectTemplate *tmpl) : SceneObject(tmpl) {
	pathGraph = NULL;
	interiorLayoutTemplate = NULL;
	
	initializePortalLayout(tmpl->getPortalLayout());
	
	SharedBuildingObjectTemplate *sbot = cast<SharedBuildingObjectTemplate*>(tmpl);
	if(sbot != NULL) {
		String filename = sbot->getInteriorLayoutFileName();
		if (!filename.isEmpty())
			interiorLayoutTemplate = TemplateManager::instance()->getInteriorLayout(filename);
	}
	
	
	createChildObjects();
}

void ClientBuilding::initializePortalLayout(PortalLayout *layout) {
	if (layout == NULL || cells.size() > 0)
		return;
	
	pathGraph = layout->getPathGraph();
	
	for (int i=0; i<layout->getAppearanceTemplatesSize(); i++) {
		containerVolumeLimit++;
		Reference<ClientCell*> cell = new ClientCell(layout->getCellProperty(i));
		cell->addToScene();
		
		cells.put(cell->getCellTemplate()->getName(), cell);
		transferObject(cell, -1);
		
	}
}

void ClientBuilding::addToScene() {
//	SceneObject::addToScene();
	
//	//works
//	for (int i=0; i<containerObjects.size(); i++) {
//		Reference<ClientCell*> sceno = containerObjects.elementAt(i).getValue().castTo<ClientCell*>();
//		transform->addChild(sceno.get());
//		osg::Group* test = dynamic_cast<osg::Group*>(sceno.get());
//		info("Works: " + String::hexvalueOf((int64)test), true);
//	}
	
	//doesnt work...
	for (int i=0; i<containerObjects.size(); i++) {
		Reference<SceneObject*> sceno = containerObjects.elementAt(i).getValue();
		transform->addChild(sceno.get());
	}

//	for(int i=0; i < cells.size(); i++) { //cells.size(); i++) {
//		transform->addChild(cells.get(i));
//	}
	
	if(pathGraph != NULL)
		transform->addChild(ClientRenderer::drawPathGraph(pathGraph));
}

void ClientBuilding::createChildObjects() {
	if(interiorLayoutTemplate == NULL)
		return;
	
	Vector<Reference<InteriorNode*> >& children = interiorLayoutTemplate->getChildren();
	for (int i=0; i<children.size(); i++) {
		
		
		
		InteriorNode *node = children.get(i);
		
		String serverTemplate = node->getTemplateFile().replaceFirst("shared_", "");
		
		Reference<SceneObject*> sceno = ClientRenderer::instance()->getObjectManager()->createObject(serverTemplate.hashCode(), objectID);
		if (sceno != NULL) {
			ClientCell *cell = cells.get(node->getCellName());
			if (cell != NULL) {
				cell->transferObject(sceno, -1, true);
			} else
				error("Cell not found: " + node->getCellName());
			
			osg::ref_ptr<osg::MatrixTransform> transform  = new osg::MatrixTransform( );
			
			Matrix4 ourTransform = node->getTransform();
			
			osg::Matrix matrix(ourTransform[0][0], ourTransform[1][0], ourTransform[2][0], 0,
							   ourTransform[0][1], ourTransform[1][1], ourTransform[2][1], 0,
							   ourTransform[0][2], ourTransform[1][2], ourTransform[2][2], 0,
							   ourTransform[0][3], ourTransform[1][3], ourTransform[2][3], 1);
			
			
			transform->setMatrix(transform->getMatrix() * matrix);
			sceno->setTransform(transform);
			sceno->setPosition(ourTransform[0][3], ourTransform[1][3], ourTransform[2][3]);
			
			sceno->addToScene();
		} else {
			error("Failed to load scene object: " + node->getTemplateFile());
		}
	}
}

Vector<Reference<MeshData*> > ClientBuilding::getTransformedMeshData() {
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

	
	//data.addAll(SceneObject::getTransformedMeshData());
	
	return data;
}
