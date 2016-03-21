#ifndef CLIENTRENDERER_H_
#define CLIENTRENDERER_H_
#include "system/lang.h"
#include "engine/engine.h"
#include "templates/SharedObjectTemplate.h"
#include "templates/tangible/SharedStructureObjectTemplate.h"
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
class ClientRenderer : public Logger {
	int instances;
	osgViewer::Viewer *viewer;
	
	Zone* zone;
	TemplateManager *manager;
	TerrainManager *terrainManager;
	VectorMap<String, PathGraph*> cityGraphs;
	osg::ref_ptr<osg::Node> createRegions();

	void loadSnapshotNode(WorldSnapshotNode *node, WorldSnapshotIff *wsiff);
	osg::ref_ptr<osg::Group> root;
	osg::ref_ptr<osg::Node> createTerrain();
	Vector3 startPosition;
public:
	ClientRenderer(ClientCore *core, Zone* zone, Vector3 startPosition, osgViewer::Viewer* v);
	void initialize();
	void addObject(SceneObject* obj);
	void run();
	
	void frame() {
		viewer->frame();
	}
	
	static osg::ref_ptr<osg::Node> drawBox(AABB box);
	static osg::ref_ptr<osg::Node> drawSphere(Sphere sphere, float tesselation=0.25);
};
#endif