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
#include "zone/templates/tangible/SharedBuildingObjectTemplate.h"
#include "zone/templates/appearance/MeshAppearanceTemplate.h"
#include "zone/templates/appearance/DetailAppearanceTemplate.h"
#include "conf/ConfigManager.h"

#include "zone/templates/appearance/PortalLayout.h"
#include "zone/templates/appearance/FloorMesh.h"
#include "zone/templates/appearance/PathGraph.h"
#include "tre3/TreeDirectory.h"
#include "tre3/TreeArchive.h"

#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osgGA/StateSetManipulator>

ClientRenderer::ClientRenderer(ClientCore *core, Zone* zone) : Core("log/renderer.log"), Logger("ClientRenderer") {
	setInfoLogLevel();
	floorMeshGroup = NULL;
}

void ClientRenderer::initialize() {
	info("starting up renderer..");
}

void ClientRenderer::loadSnapshotNode(WorldSnapshotNode *node, WorldSnapshotIff *wsiff, HashTable<uint32, String> &crcTable) {
	
	uint64 objectID = node->getObjectID();
	String templateName = wsiff->getObjectTemplateName(node->getNameID());
	
	if(templateName.contains("palace")) {
		objectID = 12;
	}
//	if(node->getUnknown2()) {
//		SharedObjectTemplate *shot = manager->getTemplate(node->getUnknown2());
//		info("PortalLayout ", true);
//	}
//	if (ConfigManager::instance()->isProgressMonitorActivated())
//		printf("\r\tLoading snapshot objects: [%d] / [?]\t", totalObjects);
	
	String serverTemplate = templateName.replaceFirst("shared_", "");
	Vector3 position = node->getPosition();
	
	SharedObjectTemplate *shot = manager->getTemplate(serverTemplate.hashCode());
	
	osg::MatrixTransform * rotation  = new osg::MatrixTransform( );
	osg::MatrixTransform * transform  = new osg::MatrixTransform( );
	rotation->setMatrix( osg::Matrix::translate( osg::Vec3f(position.getX(), position.getZ(), position.getY()) ) );
	transform->setMatrix( osg::Matrix::rotate( M_PI, 0, 0, 1 ) * osg::Matrix::rotate((node->getDirection().getRadians()) , 0, 1, 0 ) );
	
	rotation->addChild(transform);
	
	root->addChild(rotation);
	
	if ( shot == NULL ) {
		error("Null SharedObjectTemplate " + serverTemplate);
		return;
	}
	
	if(node->getUnknown2() != 0) {
		String name = TemplateManager::instance()->getTemplateFile(node->getUnknown2());
		PortalLayout *layout = TemplateManager::instance()->getPortalLayout(name);
		if(layout != NULL) {
			for(int i=0; i<layout->getFloorMeshNumber(); i++) {
				if(layout->getFloorMesh(i))
					transform->addChild(layout->getFloorMesh(i)->draw());
			}
		} else {
			info("Null portal layout " + serverTemplate);
		}
	}
 
	
	
//		PortalLayout *layout = shot->getPortalLayout();
//		if(layout != NULL) {
//			transform->addChild(layout->draw());
//		}
		AppearanceTemplate *tmpl = shot->getAppearanceTemplate();
		if(tmpl) {
			{	
				if (tmpl != NULL) {
					transform->addChild(tmpl->draw());
				}
			}
		} else {
			info("Null apperance template for " + templateName, true);
		}
	

	//Load child nodes
	for (int i = 0; i < node->getNodeCount(); ++i) {
		WorldSnapshotNode* childNode = node->getNode(i);
		
		if (childNode == NULL)
			continue;
		
		loadSnapshotNode(childNode, wsiff, crcTable);
	}

	
}
void ClientRenderer::run() {
	
	root = new osg::Group();
	
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
	
	ConfigManager::instance()->loadConfigData();
	DataArchiveStore::instance()->loadTres(ConfigManager::instance()->getTrePath(), ConfigManager::instance()->getTreFiles());
	
	HashTable<uint32, String> crcTable;
	
	manager = TemplateManager::instance();//new TemplateManager();
	
	manager->loadLuaTemplates();
	
	TreeDirectory *directory = DataArchiveStore::instance()->getTreeArchive()->getTreeDirectory("appearance");
	for(int i=0; i<directory->size(); i++) {
		Reference<TreeFileRecord*> record = directory->get(i);
		String recordName = "appearance/" + record->getRecordName();
		if(recordName.contains(".pob") == false)
			continue;
		IffStream *stream = DataArchiveStore::instance()->openIffFile(recordName);
		if(stream == NULL)
			continue;
		
		uint32 crc = PortalLayout::loadCRC(stream);
		TemplateManager::instance()->addTemplate(crc, recordName);
	}

	
	IffStream *snapshotStream = DataArchiveStore::instance()->openIffFile("snapshot/naboo.ws");
	
	WorldSnapshotIff snapshot;
	snapshot.readObject(snapshotStream);
	
	for (int i = 0; i < snapshot.getNodeCount(); ++i) {
		WorldSnapshotNode* node = snapshot.getNode(i);
		loadSnapshotNode(snapshot.getNode(i), &snapshot, crcTable);
	}
	
	osgViewer::Viewer viewer;
	osg::DisplaySettings::instance()->setNumMultiSamples( 8 );

	viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	root->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
	//root->getOrCreateStateSet()->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
	viewer.setSceneData(root);
	
	viewer.run();
}
