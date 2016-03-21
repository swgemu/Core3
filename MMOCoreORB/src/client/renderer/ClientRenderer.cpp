/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "ClientRenderer.h"

#include "zone/Zone.h"
#include "zone/managers/object/ObjectManager.h"

#include "ClientCore.h"
#include <osgUtil/Optimizer>
#include "login/LoginSession.h"
#include "zone/templates/SharedObjectTemplate.h"
#include "zone/managers/templates/TemplateManager.h"
#include "zone/templates/tangible/SharedStructureObjectTemplate.h"
#include "zone/managers/templates/DataArchiveStore.h"
#include "zone/templates/snapshot/WorldSnapshotIff.h"
#include "zone/templates/tangible/SharedBuildingObjectTemplate.h"
#include "zone/templates/appearance/MeshAppearanceTemplate.h"
#include "zone/templates/appearance/DetailAppearanceTemplate.h"
#include "zone/templates/datatables/DataTableIff.h"
#include "conf/ConfigManager.h"
#include "zone/managers/templates/DataArchiveStore.h"
#include "zone/templates/appearance/PortalLayout.h"
#include "zone/templates/appearance/FloorMesh.h"
#include "zone/templates/appearance/PathGraph.h"
#include "tre3/TreeDirectory.h"
#include "tre3/TreeArchive.h"
#include "zone/managers/terrain/TerrainManager.h"
#include "zone/objects/terrain/TerrainGenerator.h"
#include "zone/objects/terrain/ProceduralTerrainAppearance.h"
#include "zone/objects/terrain/layer/boundaries/BoundaryRectangle.h"
#include "zone/objects/terrain/layer/boundaries/BoundaryPolygon.h"
#include <osgGA/TerrainManipulator>

#include <osgTerrain/Terrain>
#include <osgTerrain/TerrainTile>
#include <osgTerrain/GeometryTechnique>
#include <osgTerrain/DisplacementMappingTechnique>
#include <osgTerrain/Layer>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osgGA/StateSetManipulator>

ClientRenderer::ClientRenderer(ClientCore *core, Zone* zone, Vector3 startPosition, osgViewer::Viewer* v) : Logger("ClientRenderer") {
	setInfoLogLevel();
	floorMeshGroup = NULL;
	viewer = v;
	this->zone = zone;
	this->startPosition = startPosition;
}

void ClientRenderer::initialize() {
	info("starting up renderer..");
}

class CustomNodeVisitor : public osg::NodeVisitor {
public:
	CustomNodeVisitor() : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) {
		
	}
	void apply(osg::Geode& geode) {
		osg::Matrix mat = osg::computeLocalToWorld(this->getNodePath());
		
		
	}
};

void ClientRenderer::loadSnapshotNode(WorldSnapshotNode *node, WorldSnapshotIff *wsiff, HashTable<uint32, String> &crcTable) {
	
	uint64 objectID = node->getObjectID();
	String templateName = wsiff->getObjectTemplateName(node->getNameID());
	SceneObject* sceno = zone->getObjectManager()->createObject(templateName.hashCode(), objectID);
	sceno->loadSnapshotNode(node);
	if(sceno != NULL)
		root->addChild(sceno);
	
	//Load child nodes
	for (int i = 0; i < node->getNodeCount(); ++i) {
		WorldSnapshotNode* childNode = node->getNode(i);
		
		if (childNode == NULL) {
			info("Null childNode", true);
			continue;
		}
		
		loadSnapshotNode(childNode, wsiff, crcTable);
	}

	
}


void ClientRenderer::run() {
	
	root = new osg::Group();
	

	osg::DisplaySettings::instance()->setNumMultiSamples( 16 );
	root->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
	//root->getOrCreateStateSet()->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);


	
	root->addChild(createTerrain());
	
	manager = TemplateManager::instance();//new TemplateManager();
	

	
	HashTable<uint32, String> crcTable;
	

	
	root->addChild(createRegions());
	
	

	
	
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

	
	IffStream *snapshotStream = DataArchiveStore::instance()->openIffFile("snapshot/" + zone->name + ".ws");
	
	WorldSnapshotIff snapshot;
	snapshot.readObject(snapshotStream);
	
	for (int i = 0; i < snapshot.getNodeCount(); ++i) {
		WorldSnapshotNode* node = snapshot.getNode(i);
		loadSnapshotNode(snapshot.getNode(i), &snapshot, crcTable);
//		if(i%50 == 0)
//			viewer->frame();
	}
	for(int i=0; i<cityGraphs.size(); i++) {
		PathGraph *graph = cityGraphs.get(i);
		//graph->linkNodes();
		root->addChild(graph->draw());
	}
	
	osg::Vec3 LookFrom, LookAt, Up;
	
	LookFrom = osg::Vec3(startPosition.getX(), startPosition.getY()-500, 2000);
	LookAt = osg::Vec3(startPosition.getX(), startPosition.getY(), 10);
	Up = osg::Vec3(0,1, 0);
	
	viewer->getCameraManipulator()->setHomePosition( LookFrom, LookAt, Up );
	
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root, 1);
	//flattener.removeTransforms(root);
	CustomNodeVisitor cnv;
	
	
	cnv.traverse(*root);
	viewer->setSceneData(root);
	
//	while(true) {
//		viewer->frame();
//		sleep(100);
//	}
}

void ClientRenderer::addObject(SceneObject* obj) {
	Vector3 position = obj->getPosition();
	
	osg::MatrixTransform * transform  = new osg::MatrixTransform( );
	
	osg::Matrix mat = osg::Matrix::translate( osg::Vec3f(position.getX(), position.getY(), position.getZ()) ) * osg::Matrix::rotate(osg::DegreesToRadians(90.f), 1, 0, 0) * osg::Matrix::rotate(osg::DegreesToRadians(180.f), 0, 0, 1) * osg::Matrix::scale(-1, 1, 1);
	transform->setMatrix(mat);
	root->addChild(transform);

	Sphere sphere(position, 0.5);
	
	transform->addChild(sphere.draw());
}

void bustEdges(AABBTree *tree, PathGraph *graph, Vector3 worldPos, float rotation) {
//	for(int i=0; i<graph->pathEdges.size(); i++) {
//		PathEdge& edge = graph->pathEdges.get(i);
//		PathNode *from = graph->pathNodes.get(edge.from);
//		Pathnode *to = graph->pathNodes.get(edge.to);
//		float dist =  from->getPosition().distanceTo(to->getPosition());
//		Ray ray  = convertToModelSpace(from->getPosition(), to->getPosition, worldPos, rotation);
//		float dummy = 0;
//		Triangle* triangle = NULL;
//		if(tree->intersects(ray, dist, dummy, triangle)) {
//			from->removeChild(edge);
//			to->removeChild(edge);
//		}
//	}
}

void ClientRenderer::addObject(Vector3 position, float rotation, SharedObjectTemplate *shot, Reference<PortalLayout*> layout) {
//	PathGraph *graph = NULL;
//	if(shot == NULL)
//		return;
//	for(int i=0; i<cityGraphs.size(); i++) {
//		PathGraph *temp = cityGraphs.elementAt(i).getValue();
//		for(int j=0; j<temp->boundingSpheres.size(); j++) {
//			Sphere *sphere = temp->boundingSpheres.elementAt(j);
//			
//			if(shot->getAppearanceTemplate() != NULL) {
//				Sphere testSphere = shot->getAppearanceTemplate()->getSphere();
//				testSphere = Sphere(Vector3(testSphere.getCenter().getX(), testSphere.getCenter().getZ(), testSphere.getCenter().getY()), testSphere.getRadius());
//				if(false)//sphere->getCenter().distanceTo(testSphere.getCenter()) - sphere->getRadius() - testSphere.getRadius() > 0)
//					continue;
//				if((shot->getAppearanceTemplate() != NULL && shot->getAppearanceTemplate()->getFloorName().isEmpty() == false)) {
//					if(layout != NULL) {
//						FloorMesh *floor = layout->getFloorMesh(0);
//						
//						PathGraph *external = floor == NULL ? NULL : floor->getPathGraph();
//						Vector<PathNode*>* nodes = external->getPathNodes();
//						for (int x = 0; x<nodes->size() && x < 2; x++) {
//							temp->addPathNode(nodes->get(x));
//						}
//					}
//				CityPathNode *node = new CityPathNode(temp);
//				node->x = position.getX();
//				node->y = position.getZ();
//				node->z = position.getY();
//				node->radius = shot->getAppearanceTemplate()->getSphere().getRadius();
//				temp->addPathNode(node);
//				}
//			}
//		}
//	}
}

osg::ref_ptr<osg::Node> ClientRenderer::createRegions() {
	info("Loading client regions", true);
	osg::Group *group = new osg::Group;
	
	TemplateManager* templateManager = TemplateManager::instance();
	
	IffStream* iffStream = templateManager->openIffFile("datatables/clientregion/" + zone->name + ".iff");
	if(iffStream == NULL)
		return NULL;
	
	DataTableIff dtiff;
	dtiff.readObject(iffStream);
	
	
	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		String regionName;
		float x, y, radius;
		
		DataTableRow* row = dtiff.getRow(i);
		row->getValue(0, regionName);
		row->getValue(1, x);
		row->getValue(2, y);
		row->getValue(3, radius);
		
		int radSq = radius*radius;
		int nodeDist = 15;
		
		
		PathGraph* graph = cityGraphs.get(regionName);
		bool needsMerge = false;
		if(graph==NULL) {
			graph = new PathGraph();
			cityGraphs.put(regionName, graph);
			needsMerge = true;
		}
		
		graph->boundingSpheres.add(new Sphere(Vector3(x, y, terrainManager->getHeight(x, y)), radius));
		
//		for (int i=0; i<radius; i+=nodeDist) {
//			for (int j=0; j<sqrt((int)(radSq-(i^2))); j+=nodeDist) {
//				if(i > 0) {
//
//					{
//						CityPathNode *node = new CityPathNode(graph);
//						node->x = -i+x;
//						node->z = j+y;
//						node->y = terrainManager->getHeight(-i+x, j+y);
//						node->radius = 10.0f;
//						graph->addPathNode(node);
//						
//					}
//					{
//						CityPathNode *node = new CityPathNode(graph);
//						node->x = -i+x;
//						node->z = -j+y;
//						node->y = terrainManager->getHeight(-i+x, -j+y);
//						node->radius = 10.0f;
//						graph->addPathNode(node);
//					}
//				}
//				{
//					CityPathNode *node = new CityPathNode(graph);
//					node->x = i+x;
//					node->z = j+y;
//					node->y = terrainManager->getHeight(i+x, j+y);
//					node->radius = 10.0f;
//					graph->addPathNode(node);
//				}
//				{
//					CityPathNode *node = new CityPathNode(graph);
//					node->x = i+x;
//					node->z = -j+y;
//					node->y = terrainManager->getHeight(i+x, -j+y);
//					node->radius = 10.0f;
//					graph->addPathNode(node);
//				}
//			}
//		}
		
//		// create high detail sphere and add to our lod
//		osg::TessellationHints* hints = new osg::TessellationHints;
//		hints->setDetailRatio(2.0f);
//		osg::Geode* geode2 = new osg::Geode();
//		geode2->addDrawable( new osg::ShapeDrawable( new osg::Sphere(osg::Vec3(x, y, terrainManager->getHeight(x, y)), radius), hints ) );
//		
//		geode2->getOrCreateStateSet()->setAttribute( new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE) );
//		group->addChild(geode2);
	}
	
//	for(int i=0; i<cityGraphs.size(); i++) {
//		PathGraph *graph = cityGraphs.get(i);
//		graph->linkNodes();
//		group->addChild(graph->draw());
//	}
	return group;
}

osg::ref_ptr<osg::Node> ClientRenderer::createTerrain() {
	Vector3 rendererCenterPoint = Vector3(startPosition.getX(), startPosition.getY(), 0);
	float rendererRange = 512;
	int minTerrainX = rendererCenterPoint.getX() - rendererRange;
	int minTerrainY = rendererCenterPoint.getY() - rendererRange;
	int maxTerrainX = rendererCenterPoint.getX() + rendererRange;
	int maxTerrainY = rendererCenterPoint.getY() + rendererRange;
	
	ProceduralTerrainAppearance* terrainAppearance = nullptr;
	
	terrainManager = new TerrainManager;
	terrainManager->initialize("terrain/" + zone->name + ".trn");
	terrainAppearance = terrainManager->getProceduralTerrainAppearance();

	
	if (terrainAppearance == nullptr)
		return nullptr;
	
	String centerString;
	StringBuffer stream;
	stream << "minX:" << minTerrainX << " maxX:" << maxTerrainX << " minY:" << minTerrainY << " maxY:" << maxTerrainY;
	
	info(stream.toString(), true);
	
	float centerX = minTerrainX + ((maxTerrainX - minTerrainX) / 2);
	float centerY = minTerrainY + ((maxTerrainY - minTerrainY) / 2);
	
	float terrainSize = rendererRange * 2;
	
	float originX = centerX + (-terrainSize / 2);
	float originY = centerY + (-terrainSize / 2);
	
	float chunkSize = 8;
	float distanceBetweenHeights = 2;
	
	unsigned int numRows = static_cast<unsigned int>( terrainSize / chunkSize );
	unsigned int numColumns = numRows;
	
	float oneChunkRows = chunkSize / distanceBetweenHeights + 1 ;
	float oneChunkColumns = chunkSize / distanceBetweenHeights + 1;
	
	osg::ref_ptr<osgTerrain::Terrain> trnMesh(new osgTerrain::Terrain()) ;
	trnMesh->setSampleRatio(1.0 / distanceBetweenHeights);
	
	int chunkNumRows = terrainSize / chunkSize;
	int chunkNumColumns = chunkNumRows;
	Vector<Vector3> verts;
	Vector<uint32> indicies;
	
	for (int x=0; x<terrainSize/distanceBetweenHeights; x++) {
		for (int y=0; y<terrainSize/distanceBetweenHeights; y++) {
			float xPos = originX + x*(terrainSize/distanceBetweenHeights);
			float yPos = originY + y*(terrainSize/distanceBetweenHeights);
			verts.add(Vector3(xPos, yPos, terrainAppearance->getHeight(xPos, yPos)));
		}
	}
	
	for (int x=0; x<terrainSize/distanceBetweenHeights-1; x++) {
		for (int y=0; y<terrainSize/distanceBetweenHeights-1; y++) {
			indicies.add(x+y*terrainSize);
			indicies.add(x+1 + y*terrainSize);
			indicies.add(x+1 + (y+1) * terrainSize); // top right tri
			
			indicies.add(x+1 + (y+1) * terrainSize); // bottom left tri
			indicies.add(x + (y+1) * terrainSize);
			indicies.add(x + y * terrainSize);
		}
	}
	
	Offst
	
	
	
	for (int row = 0; row < chunkNumRows; ++row) {
		float currentY = originY + (chunkSize * row);
		
		for (int col = 0; col < chunkNumColumns; ++col) {
			float currentX = originX + (chunkSize * col);
			
			osg::ref_ptr<osgTerrain::TerrainTile> terrainTile = new osgTerrain::TerrainTile();
			
			osg::HeightField* tileGrid = new osg::HeightField();
			tileGrid->allocate(oneChunkRows, oneChunkColumns);
			tileGrid->setName("HeightField grid");
			
			tileGrid->setXInterval(distanceBetweenHeights);
			tileGrid->setYInterval(distanceBetweenHeights);
			
			for (int i = 0; i < oneChunkRows; ++i) {
				for (int j = 0; j < oneChunkColumns; ++j) {
					float workX = currentX + (i * distanceBetweenHeights);
					float workY = currentY + (j * distanceBetweenHeights);
					
					float height = terrainAppearance->getHeight(workX, workY);
					
					
					tileGrid->setHeight(i, j, height);
				}
			}
			
			
			osg::ref_ptr<osgTerrain::Locator> tileLocator = new osgTerrain::Locator();
			tileLocator->setCoordinateSystemType( osgTerrain::Locator::PROJECTED );
			
			tileLocator->setTransformAsExtents(currentX, currentY , currentX + chunkSize, currentY + chunkSize);
			
			osg::ref_ptr<osgTerrain::HeightFieldLayer> heightFieldLayerTile = new osgTerrain::HeightFieldLayer(tileGrid);
			heightFieldLayerTile->setLocator(tileLocator.get());
			
			terrainTile->setElevationLayer(heightFieldLayerTile.get());
			
			trnMesh->addChild(terrainTile);
		}
	}

for (int i = 0; i < oneChunkRows-1; ++i) {
	for (int j = 0; j < oneChunkColumns-1; ++j) {
		indicies.add(j+oneChunkColumns*i);
		indicies.add((j+1)+oneChunkColumns*i);
		indicies.add(j+oneChunkColumns*(j+1));
	}
}

	trnMesh->setBlendingPolicy(osgTerrain::TerrainTile::ENABLE_BLENDING);
	trnMesh->setName("TerrainMesh");
	
	info("terrain generated", true);
	trnMesh->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::ON );
	return trnMesh;
}


