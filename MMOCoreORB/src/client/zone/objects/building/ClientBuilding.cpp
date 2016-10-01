#include "ClientBuilding.h"
#include "Client/zone/objects/appearance/ClientAppearance.h"
#include "client/zone/objects/building/ClientCell.h"
#include "templates/appearance/PortalLayout.h"
#include "templates/appearance/CellProperty.h"
#include "templates/manager/TemplateManager.h"
#include "templates/building/SharedBuildingObjectTemplate.h"
#include "client/zone/managers/object/ObjectManager.h"
#include "templates/building/InteriorLayoutTemplate.h"
#include "client/zone/objects/appearance/ClientMeshAppearance.h"

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
	if (layout == NULL)
		return;
	
	cells.removeAll();
	
	pathGraph = layout->getPathGraph();
	
	for (int i=0; i<layout->getAppearanceTemplatesSize(); i++) {
		containerVolumeLimit++;
		Reference<ClientCell*> cell = new ClientCell(layout->getCellProperty(i));
		cell->addToScene();
		
		cellMap.put(cell->getCellTemplate()->getName(), cell);
		cells.add(cell);
		transferObject(cell, -1);
		
	}
	
	portalLayout = layout;
}

void ClientBuilding::addToScene() {
	
	for (int i=0; i<containerObjects.size(); i++) {
		Reference<SceneObject*> sceno = containerObjects.elementAt(i).getValue();
		transform->addChild(sceno->getGroup());
	}
	
	
	if (cells.size() > 0) {
		
		ClientCell *cell = cells.get(0);
		
		const CellProperty* tmpl = cell->getCellTemplate();
		
		for (int i=0; i<tmpl->getNumberOfPortals(); i++) {
			CellPortal* portal = tmpl->getPortal(i);
			const MeshData* mesh = portalLayout->getPortalGeometry(portal->getGeometryIndex());
			
			//Reference<MeshData*> barrier = new MeshData(*mesh); // make a copy
			
			if(portal->hasDoorTransform()) {
				
				osg::ref_ptr<osg::MatrixTransform> childTransform  = new osg::MatrixTransform( );
				
				Matrix4 ourTransform = portal->getDoorTransform();
				
				osg::Matrix matrix(ourTransform[0][0], ourTransform[1][0], ourTransform[2][0], ourTransform[3][0],
								   ourTransform[0][1], ourTransform[1][1], ourTransform[2][1], ourTransform[3][1],
								   ourTransform[0][2], ourTransform[1][2], ourTransform[2][2], ourTransform[3][2],
								   0, 0, 0, 1);
				
				
				childTransform->setMatrix(matrix);
				childTransform->addChild(ClientMeshAppearance::createMeshGeometry(mesh));
				transform->addChild(childTransform);
			} else {
				transform->addChild(ClientMeshAppearance::createMeshGeometry(mesh));
			}
		}
	} else {
		// Some static buildings do not have portal layouts
		SceneObject::addToScene();
	}
	
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
			ClientCell *cell = cellMap.get(node->getCellName());
			if (cell != NULL) {
				cell->transferObject(sceno, -1, true);
			} else
				error("Cell not found: " + node->getCellName());
			
			osg::ref_ptr<osg::MatrixTransform> transform  = new osg::MatrixTransform( );
			
			Matrix4 ourTransform = node->getTransform();
			
			osg::Matrix matrix(ourTransform[0][0], ourTransform[1][0], ourTransform[2][0], ourTransform[3][0],
							   ourTransform[0][1], ourTransform[1][1], ourTransform[2][1], ourTransform[3][1],
							   ourTransform[0][2], ourTransform[1][2], ourTransform[2][2], ourTransform[3][2],
							   0, 0, 0, 1);
			
			matrix(0, 2) = -matrix(0, 2);
			matrix(1, 2) = -matrix(1, 2);
			matrix(2, 0) = -matrix(2, 0);
			matrix(2, 1) = -matrix(2, 1);
			matrix(3, 2) = -matrix(3, 2);
			
			
			transform->setMatrix(matrix);
			sceno->setTransform(transform);
			sceno->setPosition(ourTransform[0][3], ourTransform[1][3], ourTransform[2][3]);
			sceno->addToScene();
		} else {
			error("Failed to load scene object: " + node->getTemplateFile());
		}
	}
}

Vector<Reference<MeshData*> > ClientBuilding::getTransformedMeshData(const Matrix4& parentTransform) {
	Vector<Reference<MeshData*> > data;
	const Matrix4 transform = getMatrix4Transform();
	
//	for (int i=0; i<containerObjects.size(); i++) {
//		SceneObject *sceno = containerObjects.get(i);
//
//		if(sceno == NULL) {
//			
//			return data;
//		}
//		
//		Vector<Reference<MeshData*> > meshes = sceno->getTransformedMeshData();
//		for(int i=0; i<meshes.size(); i++) {
//			Matrix4 transform = getMatrix4Transform();
//			meshes.get(i)->transformMeshData(transform);
//		}
//		data.addAll(meshes);
//	}

	
	//;
	
	if (cells.size() > 0) {
		
		ClientCell *cell = cells.get(0);
		
		Vector<Reference<MeshData*> > cellData = cell->getTransformedMeshData(transform * parentTransform);
//		for (int i=0; i<cellData.size(); i++) {
//			cellData.get(i)->transformMeshData(transform);
//		}
		
		data.addAll(cellData);
		
		const CellProperty* tmpl = cell->getCellTemplate();
		
		for (int i=0; i<tmpl->getNumberOfPortals(); i++) {
			CellPortal* portal = tmpl->getPortal(i);
			const MeshData* mesh = portalLayout->getPortalGeometry(portal->getGeometryIndex());
			
			if(portal->hasDoorTransform()) {
				Matrix4 doorTransform = portal->getDoorTransform();
				doorTransform.swapLtoR();
				data.add(MeshData::makeCopyNegateZ(mesh, (doorTransform * transform) * parentTransform));
			} else
				data.add(MeshData::makeCopyNegateZ(mesh, transform * parentTransform));
		}
	}
	
	data.addAll(SceneObject::getTransformedMeshData(parentTransform));
	
	return data;
}
