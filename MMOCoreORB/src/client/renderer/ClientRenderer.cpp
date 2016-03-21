/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "ClientRenderer.h"

#include "zone/Zone.h"
#include "zone/managers/object/ObjectManager.h"

#include "ClientCore.h"

#include "login/LoginSession.h"
#include "zone/templates/SharedObjectTemplate.h"
#include "zone/managers/templates/TemplateManager.h"
#include "zone/managers/templates/DataArchiveStore.h"
#include "zone/templates/snapshot/WorldSnapshotIff.h"

#include "conf/ConfigManager.h"

#include "zone/templates/appearance/PortalLayout.h"
#include "zone/templates/appearance/FloorMesh.h"
#include "zone/templates/appearance/PathGraph.h"
#include "tre3/TreeDirectory.h"
#include "tre3/TreeArchive.h"

ClientRenderer::ClientRenderer(ClientCore *core, Zone* zone) : Core("log/renderer.log"), Logger("ClientRenderer") {
	setInfoLogLevel();
	floorMeshGroup = NULL;
}

void ClientRenderer::initialize() {
	info("starting up renderer..");
}

osg::ref_ptr<osg::Node> ClientRenderer::createFloorMesh(FloorMesh* floorMesh) {

 
	osg::Group* group = floorMeshGroup;
 
	for (int i = 0; i < floorMesh->getTriangleCount(); ++i) {
		FloorMeshTriangleNode* triangle = floorMesh->getTriangle(i);
		
		osg::Geode* geode = new osg::Geode();
		//geode->setName(name.toStdString() + ":FloorTriangleNode" + QString::number(i).toStdString());
		osg::Geometry* geometry( new osg::Geometry() );
		osg::Vec3Array* vertices( new osg::Vec3Array() );
		
		for (int j = 0; j < 3; ++j) {
			Vector3 vertex = triangle->getVertex(j);
			
			vertices->push_back(osg::Vec3f(vertex.getX(), vertex.getY(), vertex.getZ()));
		}
		
		geometry->setVertexArray(vertices);
		geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, vertices->size()));
		
		geode->addDrawable( geometry );
		group->addChild(geode);
	}
 
 
 
	
	 PathGraph* pathGraph = floorMesh->getPathGraph();
	 
	 
	 if (pathGraph != NULL) {
		 Vector<PathNode*>* pathNodes = pathGraph->getPathNodes();
		 
		 osg::Geode* geode = new osg::Geode();
		 geode->setName("PathGraph");
		 osg::Geometry* geometry( new osg::Geometry() );
		 osg::Vec3Array* vertices( new osg::Vec3Array() );
		 
		 Vector<PathEdge>* pathEdges = pathGraph->getPathEdges();
		 
		 for (int i = 0; i < pathEdges->size(); ++i) {
			 PathEdge* pathEdge = &(pathEdges->get(i));
			 
			 int from = pathEdge->getFromConnection();
			 int to = pathEdge->getToConnection();
			 
			 PathNode* fromNode = pathNodes->get(from);
			 PathNode* toNode = pathNodes->get(to);
			 
			 vertices->push_back(osg::Vec3f(-fromNode->getX(), fromNode->getY(), fromNode->getZ() + 0.5));
			 vertices->push_back(osg::Vec3f(-toNode->getX(), toNode->getY(), toNode->getZ() + 0.5));
		 }
		 
		 geometry->setVertexArray(vertices);
		 geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, vertices->size()));
		 
		 osg::Vec4Array* colors( new osg::Vec4Array() );
		 colors->push_back( osg::Vec4( 0.0f, 0.0f, 1.0f, 0.5f ) );
		 geometry->setColorArray( colors );
		 geometry->setColorBinding( osg::Geometry::BIND_OVERALL );
		 
		 geode->addDrawable( geometry );
			 
		 osg::MatrixTransform * transform0  = new osg::MatrixTransform( );
		 
		 
		 osg::MatrixTransform * transform1  = new osg::MatrixTransform( );
		 osg::MatrixTransform * transform2  = new osg::MatrixTransform( );
		 transform1->setMatrix( osg::Matrix::rotate( M_PI*0.5, 1, 0, 0 ) );
		 //transform0->setMatrix( osg::Matrix::rotate( M_PI, 0, 1, 0 ) );
		 transform0->setMatrix( osg::Matrix::rotate( M_PI, 0, 0, 1 ) );
		 
		 transform1->addChild(geode);
		 transform2->addChild(transform2);
		 transform0->addChild(transform1);
		 
		 
		 group->addChild(transform0);
		 
		 osg::StateSet* state = geode->getOrCreateStateSet();
		 
		 state->setMode(GL_LIGHTING, false);
	 }
	
 
	return group;
}

void ClientRenderer::loadSnapshotNode(WorldSnapshotNode *node, WorldSnapshotIff *wsiff, HashTable<uint32, String> &crcTable) {
	
	uint64 objectID = node->getObjectID();
	String templateName = wsiff->getObjectTemplateName(node->getNameID());
	
//	if (ConfigManager::instance()->isProgressMonitorActivated())
//		printf("\r\tLoading snapshot objects: [%d] / [?]\t", totalObjects);
	
	//String serverTemplate = templateName.replaceFirst("shared_", "");
	Vector3 position = node->getPosition();
	
	SharedObjectTemplate *shot = manager->getTemplate(templateName.hashCode());
	
//	
//	//object = zoneServer->createClientObject(serverTemplate.hashCode(), objectID);
//	
//	Locker locker(object);
//	
//	object->initializePosition(position.getX(), position.getZ(), position.getY());
//	object->setDirection(node->getDirection());
//	
//	if (parentObject != NULL && parentObject->isBuildingObject() && object->isCellObject()) {
//		CellObject* cell = cast<CellObject*>(object.get());
//		BuildingObject* building = cast<BuildingObject*>(parentObject.get());
//		
//		Locker clocker(building, object);
//		
//		building->addCell(cell, node->getCellID());
//	}
//	
//	if (parentObject != NULL)
//		parentObject->transferObject(object, -1);
//	else if (node->getParentID() != 0)
//		error("parent id " + String::valueOf(node->getParentID()));
//	
//	if (parentObject == NULL) {
//		//object->insertToZone(zone);
//		Locker clocker(object);
//		
//		zone->transferObject(object, -1, true);
//	}
	
	//Load child nodes
	for (int i = 0; i < node->getNodeCount(); ++i) {
		WorldSnapshotNode* childNode = node->getNode(i);
		
		if (childNode == NULL)
			continue;
		
		loadSnapshotNode(childNode, wsiff, crcTable);
	}
	
	
	
//	if(node->getUnknown2() != 0) {
//		if(node->getNameID() != 0) {
//			uint32 hash = wsiff->getObjectTemplateName(node->getNameID());
//			SharedObjectTemplate *tmpl = manager->getTemplate(hash);
//			if(tmpl != NULL)
//				info("Loadedsnapshot object :" + tmpl->getTemplateFileName(), true);
//		}
//	}
//	for (int i = 0; i < node->getNodeCount(); ++i) {
//
//		loadSnapshotNode(node->getNode(i), crcTable);
//	}
	
}
void ClientRenderer::run() {
	
	
	ConfigManager::instance()->loadConfigData();
	DataArchiveStore::instance()->loadTres(ConfigManager::instance()->getTrePath(), ConfigManager::instance()->getTreFiles());
	
	HashTable<uint32, String> crcTable;
	
	TreeDirectory *directory = DataArchiveStore::instance()->getTreeArchive()->getTreeDirectory("appearance");
	for(int i=0; i<directory->size(); i++) {
		Reference<TreeFileRecord*> record = directory->get(i);
		String recordName = "appearance/" + record->getRecordName();
		//info("adding" + recordName + " with hashcode " + String::valueOf(recordName.hashCode()), true);
		crcTable.put(recordName.hashCode(), recordName);
	}
	manager = new TemplateManager();
	
	manager->loadLuaTemplates();
	
	IffStream *snapshotStream = DataArchiveStore::instance()->openIffFile("snapshot/naboo.ws");
	
	WorldSnapshotIff snapshot;
	snapshot.readObject(snapshotStream);
	
	for (int i = 0; i < snapshot.getNodeCount(); ++i) {
		WorldSnapshotNode* node = snapshot.getNode(i);
		loadSnapshotNode(snapshot.getNode(i), &snapshot, crcTable);
//		SceneObject* object = loadSnapshotObject(node, &wsiff, totalObjects);
//		
//		if (object != NULL)
//			objects.add(object);
	}
	
	IffStream *stream = DataArchiveStore::instance()->openIffFile("appearance/poi_all_bunker_allum_mine.pob");
	PortalLayout *layout = new PortalLayout();
	layout->parse(stream);
	
	if (floorMeshGroup == NULL)
		floorMeshGroup = new osg::Group();
	
	osg::Group *root = new osg::Group();
	
	osg::Geode* geode = new osg::Geode();
	
	osg::Geometry* geoZ = new osg::Geometry();
	// define some vertices
	osg::Vec3Array* z = new osg::Vec3Array;
	
	z->push_back(osg::Vec3f(0, 0, 0));
	z->push_back(osg::Vec3f(0, 0, 100));
	
	// draw lines
	geoZ->setVertexArray(z);
	
	geoZ->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2, 1));
	
	osg::Geometry* geoY = new osg::Geometry();
	// define some vertices
	osg::Vec3Array* y = new osg::Vec3Array;
	
	y->push_back(osg::Vec3f(0, 0, 0));
	y->push_back(osg::Vec3f(100, 0, 0));
	
	// draw lines
	geoY->setVertexArray(y);
	
	geoY->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2, 1));
	
	
	osg::Geometry* geoX = new osg::Geometry();
	
	// define some vertices
	osg::Vec3Array* x = new osg::Vec3Array;
	
	x->push_back(osg::Vec3f(0, 0, 0));
	x->push_back(osg::Vec3f(100, 0, 0));
	
	// draw lines
	geoX->setVertexArray(x);
	
	geoX->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2, 1));
	
	geode->addDrawable(geoZ);
	geode->addDrawable(geoY);
	geode->addDrawable(geoX);
	root->addChild(geode);
	
	
	for(int i=0; i<layout->getFloorMeshNumber(); i++) {
		root->addChild(createFloorMesh(layout->getFloorMesh(i)));
	}
	osgViewer::Viewer viewer;
	
	root->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
	//root->getOrCreateStateSet()->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
	viewer.setSceneData(root);
	
	viewer.run();
}
