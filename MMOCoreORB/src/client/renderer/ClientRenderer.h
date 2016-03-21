#ifndef CLIENTRENDERER_H_
#define CLIENTRENDERER_H_
#include "system/lang.h"
#include "engine/engine.h"
#include "templates/SharedObjectTemplate.h"
#include "templates/tangible/SharedStructureObjectTemplate.h"
#include "templates/appearance/MeshAppearanceTemplate.h"
#include <osg/Node>
#include <osg/Geometry>
#include <osg/Notify>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osgViewer/Viewer>


#include <osg/LineWidth>
#include <osg/Billboard>

#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>

#include <osgDB/Registry>
#include <osgDB/ReadFile>

class Zone;
class ClientCore;
class FloorMesh;
class WorldSnapshotNode;
class TemplateManager;
class WorldSnapshotIff;
class ProceduralTerrainAppearance;
class TerrainManager;
class PathGraph;
class PortalLayout;
class SceneObject;

class ClientRegion : public Object {
public:
	String name;
	Vector<Sphere> regionBounds;
	Vector<Reference<MeshData*> > sceneData;
};
class ClientRenderer : public Logger, public Singleton<ClientRenderer>, public Object {
	int instances;
	osg::ref_ptr<osgViewer::Viewer> viewer;
	
	Zone* zone;
	TemplateManager *manager;
	TerrainManager *terrainManager;
	VectorMap<String, PathGraph*> cityGraphs;
	osg::ref_ptr<osg::Node> createRegions();

	void loadSnapshotNode(WorldSnapshotNode *node, WorldSnapshotIff *wsiff);
	osg::ref_ptr<osg::Group> root;
	osg::ref_ptr<osg::Group> collisionRoot;
	osg::ref_ptr<osg::Group> floorRoot;
	osg::ref_ptr<osg::Group> pathGraphRoot;
	osg::ref_ptr<osg::Group> debugRoot;
	osg::ref_ptr<osg::Node> createTerrain();
	Vector3 startPosition;
	Vector<Reference<MeshData*> > sceneData;
	VectorMap<String, Reference<ClientRegion*> > regions;
	
	Reference<MeshData*> getTerrainMesh(Vector3 position, float terrainSize, float chunkSize, float distanceBetweenHeights);

public:
	ClientRenderer() : Logger("ClientRenderer") {
		
	}
	
	osg::ref_ptr<osg::Group> getRootNode() {
		return root;
	}
	osg::ref_ptr<osg::Group> getCollisionRootNode() {
		return collisionRoot;
	}
	osg::ref_ptr<osg::Group> getFloorRootNode() {
		return floorRoot;
	}
	osg::ref_ptr<osg::Group> getPathGraphRootNode() {
		return pathGraphRoot;
	}
	osg::ref_ptr<osg::Group> getDebugRootNode() {
		return debugRoot;
	}
	
	void enableDebugPathGraphs() {
		pathGraphRoot->setNodeMask(0xFFFF);
	}
	
	void enableDebugCollision() {
		collisionRoot->setNodeMask(0xFFFF);
	}
	
	void enableFloors() {
		floorRoot->setNodeMask(0xFFFF);
	}
	
	void enableDebug() {
		debugRoot->setNodeMask(0xFFFF);
	}
	
	void disableDebugPathGraphs() {
		pathGraphRoot->setNodeMask(0x0);
	}
	
	void disableDebugCollision() {
		collisionRoot->setNodeMask(0x0);
	}
	
	void disableFloors() {
		floorRoot->setNodeMask(0x0);
	}
	
	void disableDebug() {
		debugRoot->setNodeMask(0x0);
	}
	
	void initialize(ClientCore *core, Zone* zone, Vector3 startPosition, osgViewer::Viewer* v);
	void addObject(SceneObject* obj);
	void run();
	
	void frame() {
		viewer->frame();
	}
	
	static osg::ref_ptr<osg::Node> drawBox(AABB box);
	static osg::ref_ptr<osg::Node> drawSphere(Sphere sphere, float tesselation=0.25);
	static osg::ref_ptr<osg::Node> drawPathGraph(PathGraph* graph);
	static osg::ref_ptr<osg::Node> drawFloorMesh(FloorMesh *mesh);

};
#endif