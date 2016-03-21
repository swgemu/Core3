#ifndef CLIENTRENDERER_H_
#define CLIENTRENDERER_H_
#include "system/lang.h"
#include "engine/engine.h"

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

class ClientRenderer : public Core, public Logger {
	int instances;
	
	Zone* zone;
	osg::Group* floorMeshGroup;
	TemplateManager *manager;
	
	osg::ref_ptr<osg::Node> createFloorMesh(FloorMesh* floorMesh);
	void loadSnapshotNode(WorldSnapshotNode *node, WorldSnapshotIff *wsiff, HashTable<uint32, String> &crcTable);
	
public:
	ClientRenderer(ClientCore *core, Zone* zone);
	
	void initialize();
	
	void run();
};
#endif