/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "ClientRenderer.h"

#include "client/zone/Zone.h"
#include "client/zone/managers/object/ObjectManager.h"

#include "client/ClientCore.h"
#include <osgUtil/Optimizer>
#include "client/login/LoginSession.h"
#include "templates/SharedObjectTemplate.h"
#include "templates/manager/TemplateManager.h"
#include "templates/tangible/SharedStructureObjectTemplate.h"
#include "templates/manager/DataArchiveStore.h"
#include "templates/snapshot/WorldSnapshotIff.h"
#include "templates/building/SharedBuildingObjectTemplate.h"
#include "templates/appearance/MeshAppearanceTemplate.h"
#include "templates/appearance/DetailAppearanceTemplate.h"
#include "templates/datatables/DataTableIff.h"
#include "conf/ConfigManager.h"
#include "templates/manager/DataArchiveStore.h"
#include "templates/appearance/PortalLayout.h"
#include "templates/appearance/FloorMesh.h"
#include "templates/appearance/PathGraph.h"
#include "tre3/TreeDirectory.h"
#include "tre3/TreeArchive.h"
#include "terrain/manager//TerrainManager.h"
#include "terrain/TerrainGenerator.h"
#include "terrain/ProceduralTerrainAppearance.h"
#include "terrain/layer/boundaries/BoundaryRectangle.h"
#include "terrain/layer/boundaries/BoundaryPolygon.h"
#include <osgGA/TerrainManipulator>

#include <osgTerrain/Terrain>
#include <osgTerrain/TerrainTile>
#include <osgTerrain/GeometryTechnique>
#include <osgTerrain/DisplacementMappingTechnique>
#include <osgTerrain/Layer>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osgGA/StateSetManipulator>

void ClientRenderer::initialize(ClientCore *core, Zone* zone, Vector3 startPosition, osgViewer::Viewer* v) {
	info("starting up renderer..");
	setInfoLogLevel();
	viewer = v;
	this->zone = zone;
	this->startPosition = startPosition;
	
	root = new osg::Group();
	debugRoot = new osg::Group();
	floorRoot = new osg::Group();
	collisionRoot = new osg::Group();
	pathGraphRoot = new osg::Group();
	
	root->addChild(debugRoot);
	debugRoot->addChild(floorRoot);
	debugRoot->addChild(collisionRoot);
	debugRoot->addChild(pathGraphRoot);
	
	debugRoot->setNodeMask(0x0);
	
	osg::DisplaySettings::instance()->setNumMultiSamples( 16 );
	root->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::ON );
	
	
}

class CustomNodeVisitor : public osg::NodeVisitor {
public:
	CustomNodeVisitor() : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) {
		
	}
	void apply(osg::Geode& geode) {
		osg::Matrix mat = osg::computeLocalToWorld(this->getNodePath());
	}
};

void ClientRenderer::loadSnapshotNode(WorldSnapshotNode *node, WorldSnapshotIff *wsiff) {
	
	uint64 objectID = node->getObjectID();
	String templateName = wsiff->getObjectTemplateName(node->getNameID());
	String serverTemplate = templateName.replaceFirst("shared_", "");
	SceneObject* sceno = zone->getObjectManager()->createObject(serverTemplate.hashCode(), objectID);
	if(sceno == NULL) {
		error("Failed to load " + templateName);
	} else {
		sceno->loadSnapshotNode(node);
		root->addChild(sceno);
	}
	
	//Load child nodes
	for (int i = 0; i < node->getNodeCount(); ++i) {
		WorldSnapshotNode* childNode = node->getNode(i);
		
		if (childNode == NULL) {
			info("Null childNode", true);
			continue;
		}
		
		loadSnapshotNode(childNode, wsiff);
	}

	
}


void ClientRenderer::run() {
	
	
	
	//root->getOrCreateStateSet()->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);


	
	root->addChild(createTerrain());
	
	manager = TemplateManager::instance();//new TemplateManager();
	
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
		TemplateManager::instance()->addClientTemplate(crc, recordName);
	}

	
	IffStream *snapshotStream = DataArchiveStore::instance()->openIffFile("snapshot/" + zone->name + ".ws");
	
	WorldSnapshotIff snapshot;
	snapshot.readObject(snapshotStream);
	
	for (int i = 0; i < snapshot.getNodeCount(); ++i) {
		WorldSnapshotNode* node = snapshot.getNode(i);
		loadSnapshotNode(snapshot.getNode(i), &snapshot);
//		if(i%50 == 0)
//			viewer->frame();
	}
	for(int i=0; i<cityGraphs.size(); i++) {
		PathGraph *graph = cityGraphs.get(i);
		//graph->linkNodes();
		//root->addChild(graph->draw());
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
			return NULL;
//			graph = new PathGraph();
//			cityGraphs.put(regionName, graph);
//			needsMerge = true;
		}
		
		//graph->boundingSpheres.add(new Sphere(Vector3(x, y, terrainManager->getHeight(x, y)), radius));
		
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
	float distanceBetweenHeights = 8;
	
	unsigned int numRows = static_cast<unsigned int>( terrainSize / chunkSize );
	unsigned int numColumns = numRows;
	
	float oneChunkRows = chunkSize / distanceBetweenHeights + 1 ;
	float oneChunkColumns = chunkSize / distanceBetweenHeights + 1;
	
	osg::ref_ptr<osgTerrain::Terrain> trnMesh(new osgTerrain::Terrain()) ;
	trnMesh->setSampleRatio(0.25 / distanceBetweenHeights);
	
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

	trnMesh->setBlendingPolicy(osgTerrain::TerrainTile::ENABLE_BLENDING);
	trnMesh->setName("TerrainMesh");
	
	info("terrain generated", true);
	trnMesh->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::ON );
	return trnMesh;
}

osg::ref_ptr<osg::Node> ClientRenderer::drawBox(AABB box) {
	
	Vector3 boxCenter = box.center();
	Vector3 boxExtents = box.extents();
	osg::Geode* geode = new osg::Geode();
	geode->addDrawable( new osg::ShapeDrawable( new osg::Box(osg::Vec3(boxCenter.getX(), boxCenter.getY(), boxCenter.getZ()), boxExtents.getX()*2, boxExtents.getY()*2, boxExtents.getZ()*2)) );
	
	geode->getOrCreateStateSet()->setAttribute( new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE) );
	
	return geode;
}

osg::ref_ptr<osg::Node> ClientRenderer::drawSphere(Sphere sphere, float tesselation) {
	osg::TessellationHints* hints = new osg::TessellationHints;
	hints->setDetailRatio(tesselation);
	osg::Geode* geode = new osg::Geode();
	Vector3 center = sphere.getCenter();
	geode->addDrawable( new osg::ShapeDrawable( new osg::Sphere(osg::Vec3(center.getX(), center.getY(), center.getZ()), sphere.getRadius()), hints ) );

	geode->getOrCreateStateSet()->setAttribute( new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE) );
	
	return geode;
}

osg::ref_ptr<osg::Node> ClientRenderer::drawPathGraph(PathGraph *graph) {
	osg::Group* group = new osg::Group();
	osg::Geode* geode = new osg::Geode();
	geode->setName("PathGraph");
	osg::Geometry* geometry( new osg::Geometry() );
	osg::Vec3Array* vertices( new osg::Vec3Array() );
	
	Vector<PathEdge> *pathEdges = graph->getPathEdges();
	Vector<PathNode*>* pathNodes = graph->getPathNodes();
	for (int i = 0; i < pathEdges->size(); ++i) {
		PathEdge* pathEdge = &(pathEdges->get(i));
		
		int from = pathEdge->getFromConnection();
		int to = pathEdge->getToConnection();
		
		PathNode* fromNode = pathNodes->get(from);
		PathNode* toNode = pathNodes->get(to);
		
		Vector3 direction = toNode->getPosition() - fromNode->getPosition();
		direction.normalize();
		
		vertices->push_back(osg::Vec3f(fromNode->getX(), fromNode->getZ()+0.5, fromNode->getY()));
		//direction = -1 * direction;
		vertices->push_back(osg::Vec3f(toNode->getX(), toNode->getZ()+0.5, toNode->getY()));
	}
	
	
	for (int i=0; i < pathNodes->size(); i++) {
		PathNode *node = pathNodes->get(i);
		
		/*		CellPortal           = 0,
		 CellWaypoint         = 1,
		 CellPOI              = 2,
		 
		 BuildingEntrance     = 3,
		 BuildingCell         = 4,
		 BuildingPortal       = 5,
		 
		 CityBuildingEntrance = 6,
		 CityWaypoint         = 7,
		 CityPOI              = 8,
		 CityBuilding         = 9,
		 CityEntrance         = 10,
		 
		 BuildingCellPart     = 11,*/
		

		
		// create high detail sphere and add to our lod
		osg::TessellationHints* hints = new osg::TessellationHints;
		hints->setDetailRatio(0.25f);
		osg::Geode* geode2 = new osg::Geode();
		osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable( new osg::Sphere(osg::Vec3(node->getX(), node->getZ()+0.5, node->getY()), node->getRadius()), hints );
		geode2->addDrawable( shape );
		
		switch(node->getType()) {
			case PathNode::CellWaypoint:
				shape->setColor( osg::Vec4( 1.0f, 1.0f, 1.0f, 0.5f ));
				break;
			case PathNode::CellPOI:
				shape->setColor( osg::Vec4( 1.0f, 0.9f, 0.1f, 0.5f ));
				break;
			case PathNode::BuildingEntrance:
				shape->setColor( osg::Vec4( 0.0f, 0.0f, 1.0f, 0.5f ));
				break;
			case PathNode::BuildingCell:
				shape->setColor( osg::Vec4( 0.0f, 1.0f, 0.0f, 0.5f ));
				break;
			case PathNode::BuildingPortal:
				shape->setColor( osg::Vec4( 0.0f, 1.0f, 1.0f, 0.5f ));
				break;
			case PathNode::CityBuildingEntrance:
				shape->setColor( osg::Vec4( 1.0f, 0.0f, 0.0f, 0.5f ));
				break;
			case PathNode::BuildingCellPart:
				shape->setColor( osg::Vec4( 1.0f, 0.0f, 1.0f, 0.5f ));
				break;
		};
		
		//geode2->getOrCreateStateSet()->setAttribute( new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE) );
		group->addChild(geode2);
		
	}
	
	geometry->setVertexArray(vertices);
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, vertices->size()));
	
	osg::Vec4Array* colors( new osg::Vec4Array() );
	colors->push_back( osg::Vec4( 0.0f, 0.0f, 1.0f, 0.5f ) );
	geometry->setColorArray( colors );
	geometry->setColorBinding( osg::Geometry::BIND_OVERALL );
	
	geode->addDrawable( geometry );
	
	group->addChild(geode);
	
	osg::StateSet* state = geode->getOrCreateStateSet();
	
	state->setMode(GL_LIGHTING, false);
	
 
	return group;
}

osg::ref_ptr<osg::Node> ClientRenderer::drawFloorMesh(FloorMesh *mesh) {
	
	osg::Group* group = new osg::Group();
	osg::Geode* geode = new osg::Geode();
	//geode->setName(name.toStdString() + ":FloorTriangleNode" + QString::number(i).toStdString());
	osg::Geometry* geometry( new osg::Geometry() );
	
	osg::Vec3Array* vertices( new osg::Vec3Array() );
	
	for (int i = 0; i < mesh->getTriangleCount(); ++i) {
		FloorMeshTriangleNode* triangle = mesh->getTriangle(i);
		
		
		
		for (int j = 2; j >=0; j--) {
			Vector3 vertex = triangle->getVertex(j);
			
			vertices->push_back(osg::Vec3f(vertex.getX(), vertex.getY()+0.2f, vertex.getZ()));
		}
		
		
	}
 
	geometry->setVertexArray(vertices);
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, vertices->size()));
	osg::Vec4Array* colors( new osg::Vec4Array() );

	colors->push_back(osg::Vec4(255, 255, 0, 50));
	geometry->setColorArray( colors);
	geometry->setColorBinding( osg::Geometry::BIND_OVERALL );
	geode->addDrawable( geometry );
	group->addChild(geode);
	
	// TODO : boxtree
	
	
	//	for (int i=0; i<boxTree.size(); i++) {
	//		group->addChild(boxTree.get(i)->bbox.draw());
	//	}
	
	return group;
}