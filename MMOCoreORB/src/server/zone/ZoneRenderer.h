/*
 * ZoneRenderer.h
 *
 *  Created on: Mar 27, 2016
 *      Author: theanswer
 */

#ifndef SRC_SERVER_ZONE_ZONERENDERER_H_
#define SRC_SERVER_ZONE_ZONERENDERER_H_

#include "engine/engine.h"

#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/PolygonMode>

#include <osgText/Text>

#include <osgViewer/Viewer>

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

namespace server {
 namespace zone {

 class Zone;

 class ZoneRenderer : public Logger, public Object {
 	server::zone::Zone* zone;

 	osg::ref_ptr<osg::Group> root;
 	osg::ref_ptr<osgText::Text> updateText;
 	osg::ref_ptr<osgText::Text> objectText;

 	ReadWriteLock mutex;
 	int objectCount = 0;

 	Vector<osg::Node*>* insertObjects;
 	//Vector<osg::Node*>* removeObjects;

 	//HashTable<Reference<SceneObject*>, osg::Node*> objectTransforms;

 	const Vector3 rendererCenterPoint;

 	const int rendererRange;

 protected:
 	void queueInsert(const osg::ref_ptr<osg::Node>& node, SceneObject* object);
 	osg::ref_ptr<osg::Node> createTerrain();

 public:
 	ZoneRenderer(Zone* zone);

 	osg::ref_ptr<osgViewer::Viewer> createViewer();
 	osg::ref_ptr<osg::Node> createHUD();

 	void runViewer(osgViewer::Viewer* viewer);

 	void addSceneObject(SceneObject* object);
 	void addCreatureObject(CreatureObject* creature);

 	void removeSceneObject(SceneObject* object);

 	osg::ref_ptr<osg::MatrixTransform> getTransform(SceneObject* object);
 	static void setWireframe(osg::Node* node, osg::PolygonMode::Face mode = osg::PolygonMode::FRONT_AND_BACK);

 	osgText::Text* getUpdateText() {
 		return updateText.get();
 	}
 };


 class PickHandler : public osgGA::GUIEventHandler {
 	ZoneRenderer* renderer;

 public:
 	PickHandler(ZoneRenderer* renderer);

 	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

 	void printIntersections(float x, float y, osgViewer::View* view);
 };

 class CreatureObjectNodeCallback : public osg::NodeCallback {
	 Reference<CreatureObject*> creature;
 public:
	 CreatureObjectNodeCallback(CreatureObject* creature);

	 void operator()(osg::Node* node, osg::NodeVisitor* nv);
 };

 }
}

using namespace server::zone;

#endif /* SRC_SERVER_ZONE_ZONERENDERER_H_ */
