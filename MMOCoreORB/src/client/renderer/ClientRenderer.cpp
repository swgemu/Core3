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
#include "client/zone/objects/building/ClientBuilding.h"
#include <osgGA/TerrainManipulator>

#include <osgTerrain/Terrain>
#include <osgTerrain/TerrainTile>
#include <osgTerrain/GeometryTechnique>
#include <osgTerrain/DisplacementMappingTechnique>
#include <osgTerrain/Layer>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osgGA/StateSetManipulator>
#include "pathfinding/RecastNavMesh.h"

#include "pathfinding/recast/Recast.h"

#include "pathfinding/recast/DetourNavMesh.h"
#include "pathfinding/recast/DetourNavMeshBuilder.h"
#include "pathfinding/RecastNavMeshBuilder.h"

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

void dumpOBJ(String filename, Vector<Reference<MeshData*> > data) {
	
	File file(filename);
	FileOutputStream outputStream(&file);
	
	for(int x=0; x<data.size(); x++) {
		MeshData *mesh = data.get(x);
		Vector<Vector3> *verts = mesh->getVerts();
		Vector<MeshTriangle> *tris = mesh->getTriangles();
		
		for (int i=0; i<verts->size(); i++) {
			Vector3& vert = verts->get(i);
			float xPos = vert.getX();
			float yPos = vert.getY();
			float zPos = vert.getZ();
			outputStream.write("v " + String::valueOf(xPos) +  " " + String::valueOf(yPos)+ " " + String::valueOf(zPos) +"\n");
		}
	}
	
	int lastIndex = 1;
	for(int x=0; x<data.size(); x++) {
		MeshData *mesh = data.get(x);
		Vector<Vector3> *verts = mesh->getVerts();
		Vector<MeshTriangle> *tris = mesh->getTriangles();
		
		for (int i=0; i<tris->size(); i++) {
			MeshTriangle& tri = tris->get(i);
			outputStream.write("f " + String::valueOf(lastIndex+tri.getVerts()[0]) + " " + String::valueOf(lastIndex+tri.getVerts()[1]) + " " + String::valueOf(lastIndex+tri.getVerts()[2])+"\n");
		}
		lastIndex += verts->size();
		
	}
	outputStream.flush();
	file.close();
}

void ClientRenderer::loadSnapshotNode(WorldSnapshotNode *node, WorldSnapshotIff *wsiff) {
	
	uint64 objectID = node->getObjectID();
	String templateName = wsiff->getObjectTemplateName(node->getNameID());
	
	String serverTemplate = templateName.replaceFirst("shared_", "");
	Reference<SceneObject*> sceno = zone->getObjectManager()->createObject(serverTemplate.hashCode(), objectID);
	
	
	if(sceno == NULL) {
		error("Failed to load " + templateName);
	} else {
		sceno->loadSnapshotNode(node);
		root->addChild(sceno->getGroup());
		
		for (int i=0; i<regions.size(); i++) {
			Reference<ClientRegion*> region = regions.get(i);
			for(int j=0; j<region->regionBounds.size(); j++) {
				Sphere sphere = region->regionBounds.get(j);
				Vector3 sPos = sphere.getCenter();
				Vector3 objPos = sceno->getPosition();
				Matrix4 identity;
				
				if((sPos-objPos).length() < sphere.getRadius()) {
					region->sceneData.addAll(sceno->getTransformedMeshData(identity));
				}
			}
		}
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

ObjectManager* ClientRenderer::getObjectManager() {
	return zone->getObjectManager();
}

MeshData* ClientRenderer::flattenMeshData(Vector<Reference<MeshData*>> data) {

	
	MeshData *mesh = new MeshData();
	Vector<Vector3>& newV = *mesh->getVerts();
	Vector<MeshTriangle>& newT = *mesh->getTriangles();
	
	for(int x=0; x<data.size(); x++) {
		MeshData *mesh = data.get(x);
		Vector<Vector3> *verts = mesh->getVerts();
		Vector<MeshTriangle> *tris = mesh->getTriangles();
		
		for (int i=0; i<verts->size(); i++) {
			Vector3& vert = verts->get(i);
			float xPos = vert.getX();
			float yPos = vert.getY();
			float zPos = vert.getZ();
			newV.add(Vector3(xPos, yPos, zPos));
		}
	}
	
	int lastIndex = 0;
	for(int x=0; x<data.size(); x++) {
		MeshData *mesh = data.get(x);
		Vector<Vector3> *verts = mesh->getVerts();
		Vector<MeshTriangle> *tris = mesh->getTriangles();
		
		for (int i=0; i<tris->size(); i++) {
			MeshTriangle& tri = tris->get(i);
			newT.add(MeshTriangle(lastIndex+tri.getVerts()[2], lastIndex+tri.getVerts()[1], lastIndex+tri.getVerts()[0]));
		}
		lastIndex += verts->size();
		
	}
	return mesh;
	
}


void ClientRenderer::run() {
	//root->getOrCreateStateSet()->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);

	//root->addChild(createTerrain());
	
	ProceduralTerrainAppearance* terrainAppearance = nullptr;

	terrainManager = new TerrainManager;
	terrainManager->initialize("terrain/" + zone->name + ".trn");
	terrainAppearance = terrainManager->getProceduralTerrainAppearance();

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
	AtomicInteger numActiveThreads;
	for (int i=0; i<regions.size(); i++) {
		Reference<ClientRegion*> region = regions.get(i);
		if(region->sceneData.size() > 0) {
			Vector3 center;
			
			float minx = 30000;
			float miny = 30000;
			float minz = 30000;
			
			float maxx = -30000;
			float maxy = -30000;
			float maxz = -30000;
			
			for( int s=0; s<region->regionBounds.size(); s++) {
				
				const Sphere& sphere = region->regionBounds.get(s);
				const float& radius = sphere.getRadius();
				const Vector3& vert = sphere.getCenter();
				const float& x = vert.getX();
				const float& y = vert.getY();
				const float& z = vert.getZ();
				
				if (x+radius > maxx)
					maxx = x+radius;
				
				if (y+radius > maxy)
					maxy = y+radius;
				
				if (z+radius > maxz)
					maxz = z+radius;
				
				if (x-radius < minx)
					minx = x-radius;
				
				if (y-radius < miny)
					miny = y-radius;
				
				if (z-radius < minz)
					minz = z-radius;
			 }
			
			AABB box(Vector3(minx, miny, minz), Vector3(maxx, maxy, maxz));
			
			
			center = box.center();
			
			Vector3 extents = box.extents();
			
			float longest = extents.getX();
			if(extents.getY() > longest)
				longest = extents.getY();
			if(extents.getZ() > longest)
				longest = extents.getZ();
			
			info("Building region terrain for: " + region->name, true);
			
			box = AABB(Vector3(center.getX()-longest, center.getY()-longest, center.getZ()-longest),
					   Vector3(center.getX()+longest, center.getY()+longest, center.getZ()+longest));
			
			String filename = region->name;
			filename = filename.subString(filename.lastIndexOf(':')+1);
			
			
			
			
			numActiveThreads.increment();
			Core::getTaskManager()->executeTask([=, &numActiveThreads] {
				
				region->sceneData.add(getTerrainMesh(center, longest*2, 32, 2));
				
				RecastNavMeshBuilder *builder = new RecastNavMeshBuilder(terrainManager->getProceduralTerrainAppearance()->getGlobalWaterTableHeight(), region->name);
				
				Reference<MeshData*> flattened = flattenMeshData(region->sceneData);
				
				Vector<Reference<MeshData*> > test;
				test.add(flattened);
				dumpOBJ(filename+".obj", test);
				
				builder->changeMesh(flattened);
				
				info("Building region navmesh for: " + region->name, true);
				Vector<const Boundary*> water;
				terrainManager->getProceduralTerrainAppearance()->getWaterBoundariesInAABB(box, &water);
				for(const Boundary* boundary : water) {
					const BoundaryPolygon *bPoly = dynamic_cast<const BoundaryPolygon*>(boundary);
					const BoundaryRectangle *bRect = dynamic_cast<const BoundaryRectangle*>(boundary);
					if(bPoly != NULL) {
						const Vector<Point2D*>& points = bPoly->getVertices();
						
						Reference<RecastPolygon*> poly = new RecastPolygon(points.size());
						poly->type = SAMPLE_POLYAREA_WATER;
						
						for (int i=points.size()-1; i>=0; i--) {
							const Point2D& point = *points.get(i);
							const float &x = point.getX();
							const float &z = point.getY();
							
							poly->verts[i*3+0] = x;
							poly->verts[i*3+1] = bPoly->getLocalWaterTableHeight();
							poly->verts[i*3+2] = -z;
						}
						
						poly->hmin = -FLT_MAX;
						poly->hmax = bPoly->getLocalWaterTableHeight();
						
						builder->addWater(poly);
						continue;
				
					} else if(bRect != NULL) {
						Reference<RecastPolygon*> poly = new RecastPolygon(4);
						poly->type = SAMPLE_POLYAREA_WATER;
						float tableHeight = bRect->getLocalWaterTableHeight();
						poly->verts[0] = bRect->getMinX();
						poly->verts[1] = tableHeight;
						poly->verts[2] = -bRect->getMinY();
						
						poly->verts[3] = bRect->getMaxX();
						poly->verts[4] = tableHeight;
						poly->verts[5] = -bRect->getMinY();
						
						poly->verts[6] = bRect->getMaxX();
						poly->verts[7] = tableHeight;
						poly->verts[8] = -bRect->getMaxY();
						
						poly->verts[9] = bRect->getMinX();
						poly->verts[10] = tableHeight;
						poly->verts[11] = -bRect->getMaxY();
						
						poly->hmin = -FLT_MAX;
						poly->hmax = tableHeight;
						
						builder->addWater(poly);
						continue;
					} else {
						info("BoundaryPolyCast Fail", true);
					}
				}
				
				builder->build();
				builder->saveAll(filename + ".navmesh");
				
				delete builder;
				numActiveThreads.decrement();
				
			}, "buildnavmesh");
			
		}
		
	}
	
	while(numActiveThreads.get() != 0) {
		Thread::sleep(500);
	}
	
//	for (int y=-8192; y<8192*2; y+=2048) {
//		Core::getTaskManager()->executeTask([y](){
//			Logger logger;
//			
//			for(int x=-8192; x<8192*2; x+=2048) {
//				Vector<Reference<MeshData*> > terrainArray;
//				terrainArray.add(ClientRenderer::instance()->getTerrainMesh(Vector3(x + 1024 + (x > 0 ? -1 : 1), y+1024 + (y > 0 ? -1 : 1), 0), 2048, 512, 4));
//				dumpOBJ("terrain_"+String::valueOf(x)+"_"+String::valueOf(y)+".obj", terrainArray);
//				logger.info("Finished X: " + String::valueOf(x) + " Y: " + String::valueOf(y), true);
//			}
//			
//			
//		}, "CreateTerrain");
//	}
#ifndef DISABLE_RENDER
	osg::Vec3 LookFrom, LookAt, Up;
	
	LookFrom = osg::Vec3(startPosition.getX(), startPosition.getY()-500, 2000);
	LookAt = osg::Vec3(startPosition.getX(), startPosition.getY(), 10);
	Up = osg::Vec3(0,1, 0);
	
	viewer->getCameraManipulator()->setHomePosition( LookFrom, LookAt, Up );
	
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root, 1);
	//flattener.removeTransforms(root);
	
//	CustomNodeVisitor cnv;
//
//	cnv.traverse(*root);
	viewer->setSceneData(root);
#endif

}

void ClientRenderer::addObject(SceneObject* obj) {
	Vector3 position = obj->getPosition();
	
	osg::MatrixTransform * transform  = new osg::MatrixTransform( );
	
	osg::Matrix mat = osg::Matrix::translate( osg::Vec3f(position.getX(), position.getY(), position.getZ()) ) * osg::Matrix::rotate(osg::DegreesToRadians(90.f), 1, 0, 0) * osg::Matrix::rotate(osg::DegreesToRadians(180.f), 0, 0, 1) * osg::Matrix::scale(-1, 1, 1);
	transform->setMatrix(mat);
	root->addChild(transform);

	Sphere sphere(position, 0.5);
	
	transform->addChild(drawSphere(sphere));
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
		if(zone->name == "endor" || zone->name == "dantooine"/*fuck SOE*/)
			regionName = regionName + String::valueOf(i);
		
		Reference<ClientRegion*> region = regions.get(regionName);
		
		if(region == NULL) {
			region = new ClientRegion();
			region->name = regionName;
			regions.put(regionName, region);
		}
		
		Sphere sphere(Vector3(x, terrainManager->getProceduralTerrainAppearance()->getHeight(x, y), y), radius);
		region->regionBounds.add(sphere);
	}
	return group;
}

Reference<MeshData*> ClientRenderer::getTerrainMesh(Vector3 position, float terrainSize, float chunkSize, float distanceBetweenHeights) {
	
	float centerX = position.getX();
	float centerY = position.getZ();
	
	float originX = centerX + (-terrainSize / 2);
	float originY = centerY + (-terrainSize / 2);
	
	unsigned int numRows = static_cast<unsigned int>( terrainSize / chunkSize );
	unsigned int numColumns = numRows;
	
	float oneChunkRows = chunkSize / distanceBetweenHeights + 1 ;
	float oneChunkColumns = chunkSize / distanceBetweenHeights + 1;
	
	int chunkNumRows = terrainSize / chunkSize;
	int chunkNumColumns = chunkNumRows;
	
	Reference<MeshData*> mesh = new MeshData();
	
	Vector<Vector3>* verts = mesh->getVerts();
	Vector<MeshTriangle>* tris = mesh->getTriangles();
	int numCells = terrainSize/distanceBetweenHeights;
	for (int x=0; x<numCells; x++) {
		for (int y=0; y<numCells; y++) {
			float xPos = originX + x*distanceBetweenHeights;
			float yPos = originY + y*distanceBetweenHeights;
			verts->add(Vector3(xPos, terrainManager->getProceduralTerrainAppearance()->getHeight(xPos, yPos), -yPos));
		}
	}
	
	
	for (int x=0; x<numCells-1; x++) {
		for (int y=0; y<numCells-1; y++) {
			MeshTriangle tri;
			tri.set(0, x+y*(numCells));
			tri.set(1, x+1 + y*(numCells));
			tri.set(2, x+1 + (y+1) * (numCells)); // top right tri

			tris->add(tri);
			
			tri.set(0, x+1 + (y+1) * (numCells)); // bottom left tri
			tri.set(1, x + (y+1) * (numCells));
			tri.set(2, x + y * (numCells));
			tris->add(tri);
		}
	}
	
	return mesh;
}
//
//osg::ref_ptr<osg::Node> ClientRenderer::createTerrain() {
//	Vector3 rendererCenterPoint = Vector3(startPosition.getX(), startPosition.getY(), 0);
//	float rendererRange = 512;
//	int minTerrainX = rendererCenterPoint.getX() - rendererRange;
//	int minTerrainY = rendererCenterPoint.getY() - rendererRange;
//	int maxTerrainX = rendererCenterPoint.getX() + rendererRange;
//	int maxTerrainY = rendererCenterPoint.getY() + rendererRange;
//	
//	ProceduralTerrainAppearance* terrainAppearance = nullptr;
//	
//	terrainManager = new TerrainManager;
//	terrainManager->initialize("terrain/" + zone->name + ".trn");
//	terrainAppearance = terrainManager->getProceduralTerrainAppearance();
//
//	FileOutputStream outputStream(new File("Test.obj"));
//	
//	if (terrainAppearance == nullptr)
//		return nullptr;
//	
//	String centerString;
//	StringBuffer stream;
//	stream << "minX:" << minTerrainX << " maxX:" << maxTerrainX << " minY:" << minTerrainY << " maxY:" << maxTerrainY;
//	
//	info(stream.toString(), true);
//	
//	float centerX = minTerrainX + ((maxTerrainX - minTerrainX) / 2);
//	float centerY = minTerrainY + ((maxTerrainY - minTerrainY) / 2);
//	
//	float terrainSize = rendererRange * 2;
//	
//	float originX = centerX + (-terrainSize / 2);
//	float originY = centerY + (-terrainSize / 2);
//	
//	float chunkSize = 64;
//	float distanceBetweenHeights = 32;
//	
//	unsigned int numRows = static_cast<unsigned int>( terrainSize / chunkSize );
//	unsigned int numColumns = numRows;
//	
//	float oneChunkRows = chunkSize / distanceBetweenHeights + 1 ;
//	float oneChunkColumns = chunkSize / distanceBetweenHeights + 1;
//	
//	osg::ref_ptr<osgTerrain::Terrain> trnMesh(new osgTerrain::Terrain()) ;
//	trnMesh->setSampleRatio(0.25 / distanceBetweenHeights);
//	
//	int chunkNumRows = terrainSize / chunkSize;
//	int chunkNumColumns = chunkNumRows;
//	
//	for (int row = 0; row < chunkNumRows; ++row) {
//		float currentY = originY + (chunkSize * row);
//		
//		for (int col = 0; col < chunkNumColumns; ++col) {
//			float currentX = originX + (chunkSize * col);
//			
//			osg::ref_ptr<osgTerrain::TerrainTile> terrainTile = new osgTerrain::TerrainTile();
//			
//			osg::HeightField* tileGrid = new osg::HeightField();
//			tileGrid->allocate(oneChunkRows, oneChunkColumns);
//			tileGrid->setName("HeightField grid");
//			
//			tileGrid->setXInterval(distanceBetweenHeights);
//			tileGrid->setZInterval(distanceBetweenHeights);
//			
//			for (int i = 0; i < oneChunkRows; ++i) {
//				for (int j = 0; j < oneChunkColumns; ++j) {
//					float workX = currentX + (i * distanceBetweenHeights);
//					float workY = currentY + (j * distanceBetweenHeights);
//					tileGrid->setHeight(i, terrainAppearance->getHeight(workX, workY), j);
//				}
//			}
//			
//			
//			osg::ref_ptr<osgTerrain::Locator> tileLocator = new osgTerrain::Locator();
//			tileLocator->setCoordinateSystemType( osgTerrain::Locator::PROJECTED );
//			
//			tileLocator->setTransformAsExtents(currentX, currentY , currentX + chunkSize, currentY + chunkSize);
//			
//			osg::ref_ptr<osgTerrain::HeightFieldLayer> heightFieldLayerTile = new osgTerrain::HeightFieldLayer(tileGrid);
//			heightFieldLayerTile->setLocator(tileLocator.get());
//			
//			terrainTile->setElevationLayer(heightFieldLayerTile.get());
//			
//			trnMesh->addChild(terrainTile);
//		}
//	}
//
//	trnMesh->setBlendingPolicy(osgTerrain::TerrainTile::ENABLE_BLENDING);
//	trnMesh->setName("TerrainMesh");
//	
//	info("terrain generated", true);
//	trnMesh->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::ON );
//	return trnMesh;
//}

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
		
		vertices->push_back(osg::Vec3f(fromNode->getX(), fromNode->getZ()+0.5, -fromNode->getY()));
		//direction = -1 * direction;
		vertices->push_back(osg::Vec3f(toNode->getX(), toNode->getZ()+0.5, -toNode->getY()));
	}
	
	
	for (int i=0; i < pathNodes->size(); i++) {
		PathNode *node = pathNodes->get(i);
		
		osg::TessellationHints* hints = new osg::TessellationHints;
		hints->setDetailRatio(0.25f);
		osg::Geode* geode2 = new osg::Geode();
		osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable( new osg::Sphere(osg::Vec3(node->getX(), node->getZ()+0.5, -node->getY()), node->getRadius()), hints );
		geode2->addDrawable( shape );
		
//		switch(node->getType()) {
//			case PathNode::CellWaypoint:
//				shape->setColor( osg::Vec4( 1.0f, 1.0f, 1.0f, 0.5f ));
//				break;
//			case PathNode::CellPOI:
//				shape->setColor( osg::Vec4( 1.0f, 0.9f, 0.1f, 0.5f ));
//				break;
//			case PathNode::BuildingEntrance:
//				shape->setColor( osg::Vec4( 0.0f, 0.0f, 1.0f, 0.5f ));
//				break;
//			case PathNode::BuildingCell:
//				shape->setColor( osg::Vec4( 0.0f, 1.0f, 0.0f, 0.5f ));
//				break;
//			case PathNode::BuildingPortal:
//				shape->setColor( osg::Vec4( 0.0f, 1.0f, 1.0f, 0.5f ));
//				break;
//			case PathNode::CityBuildingEntrance:
//				shape->setColor( osg::Vec4( 1.0f, 0.0f, 0.0f, 0.5f ));
//				break;
//			case PathNode::BuildingCellPart:
//				shape->setColor( osg::Vec4( 1.0f, 0.0f, 1.0f, 0.5f ));
//				break;
//		};
		
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
	osg::Geometry* geometry( new osg::Geometry() );
	
	osg::Vec3Array* vertices( new osg::Vec3Array() );
	
	for (int i = 0; i < mesh->getTriangleCount(); ++i) {
		FloorMeshTriangleNode* triangle = mesh->getTriangle(i);
		
		for (int j = 2; j >=0; j--) {
			Vector3 vertex = triangle->getVertex(j);
			
			vertices->push_back(osg::Vec3f(vertex.getX(), vertex.getY()+0.2f, -vertex.getZ()));
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
