/*
 * ZoneRenderer.cpp
 *
 *  Created on: Mar 27, 2016
 *      Author: theanswer
 */

#include "ZoneRenderer.h"

#include <osg/Node>
#include <osgViewer/Viewer>

#include <osg/Geometry>
#include <osg/Notify>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osg/PolygonMode>
#include <osg/LineWidth>
#include <osg/Billboard>
#include <osg/ShapeDrawable>
#include <osgTerrain/Terrain>
#include <osgTerrain/TerrainTile>

#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/TerrainManipulator>

#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>

#include <osgViewer/ViewerEventHandlers>

#include <osgDB/Registry>
#include <osgDB/ReadFile>

#include <osgText/Font>

#include <osgUtil/LineSegmentIntersector>

#include "server/zone/Zone.h"

#include "server/zone/objects/scene/SceneObject.h"

#include "server/zone/templates/appearance/PortalLayout.h"
#include "server/zone/templates/appearance/MeshAppearanceTemplate.h"

#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/terrain/TerrainManager.h"

#include "server/zone/objects/terrain/ProceduralTerrainAppearance.h"

//#include "system/util/SynchronizedLinkedList.h"

#define INITIAL_X_SIZE 640 * 2
#define INITIAL_Y_SIZE 480

using namespace server::zone;
using namespace server::zone::objects::scene;

ZoneRenderer::ZoneRenderer(Zone* zone) : zone(zone), insertObjects(nullptr), rendererCenterPoint(-4974, 4122.3, 0), rendererRange(256) {
	assert(zone);

	root = new osg::Group();

	root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);

	setLogging(true);
	setLoggingName("ZoneRenderer[" + zone->getZoneName() + "]");
}

osg::ref_ptr<osgViewer::Viewer> ZoneRenderer::createViewer() {
	info("creating renderer viewer", true);

	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	viewer->setUpViewInWindow(0, 0, INITIAL_X_SIZE, INITIAL_Y_SIZE);

	osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator();

	keyswitchManipulator->addMatrixManipulator('1', "Trackball", new osgGA::TrackballManipulator());
	keyswitchManipulator->addMatrixManipulator('2', "Flight", new osgGA::FlightManipulator());
	keyswitchManipulator->addMatrixManipulator('3', "Drive", new osgGA::DriveManipulator());
	keyswitchManipulator->addMatrixManipulator('4', "Terrain", new osgGA::TerrainManipulator());

	viewer->setCameraManipulator(keyswitchManipulator.release());

	viewer->addEventHandler(new osgViewer::StatsHandler());
	viewer->addEventHandler(new osgViewer::LODScaleHandler());
	viewer->addEventHandler(new PickHandler(this));

	viewer->setSceneData(root);

	root->addChild(createHUD().release());

	auto trn = createTerrain();

	if (trn.get() != nullptr) {
		root->addChild(trn.release());
	}

	return viewer;
}

osg::ref_ptr<osg::Node> ZoneRenderer::createHUD() {
	// create the hud. derived from osgHud.cpp
	// adds a set of quads, each in a separate Geode - which can be picked individually
	// eg to be used as a menuing/help system!
	// Can pick texts too!
	updateText = new osgText::Text();
	updateText->setDataVariance(osg::Object::DYNAMIC);

	objectText = new osgText::Text();
	objectText->setDataVariance(osg::Object::DYNAMIC);

	osg::MatrixTransform* modelview_abs = new osg::MatrixTransform;
	modelview_abs->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	modelview_abs->setMatrix(osg::Matrix::identity());

	osg::ref_ptr<osg::Projection> projection = new osg::Projection;

	projection->setMatrix(osg::Matrix::ortho2D(0, INITIAL_X_SIZE, 0, INITIAL_Y_SIZE));
	projection->addChild(modelview_abs);

	// turn lighting off for the text and disable depth test to ensure its always ontop.
	osg::Vec3 position(15.0f,INITIAL_Y_SIZE - 25, 0.0f);
	static const osg::Vec3 delta(0.0f, -10.0f, 0.0f);

	static const osg::Vec4 fontColor(1.0f, 1.0f, 0.0f, 1.0f);
	static const float fontSize = 10.f;
	static const char* font = ""; //"fonts/arial.ttf";

	// this displays what has been selected
	osg::Geode* geode = new osg::Geode();
	osg::StateSet* stateset = geode->getOrCreateStateSet();
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	geode->setName("The text label");
	geode->addDrawable(updateText);
	geode->addDrawable(objectText);
	modelview_abs->addChild(geode);

	updateText->setCharacterSize(fontSize);
	updateText->setFont(font);
	updateText->setColor(fontColor);
	updateText->setText(zone->getZoneName().toCharArray());
	updateText->setPosition(position);

	position += delta;

	objectText->setCharacterSize(fontSize);
	objectText->setFont(font);
	objectText->setColor(fontColor);
	objectText->setText(zone->getZoneName().toCharArray());
	objectText->setPosition(position);

	return projection;
}

void ZoneRenderer::runViewer(osgViewer::Viewer* viewer) {
	viewer->realize();

	while (!viewer->done()) {
		mutex.lock();

		auto stolenObjects = this->insertObjects;

		insertObjects = nullptr;

		WMB();

		mutex.unlock();

		if (stolenObjects != nullptr) {
			for (int i = 0; i < stolenObjects->size(); ++i) {
				auto node = stolenObjects->get(i);

				root->addChild(node);

				node->unref();
			}

			delete stolenObjects;
		}

		viewer->frame();
	}
}

osg::ref_ptr<osg::Node> ZoneRenderer::createTerrain() {
	int minTerrainX = rendererCenterPoint.getX() - rendererRange;
	int minTerrainY = rendererCenterPoint.getY() - rendererRange;
	int maxTerrainX = rendererCenterPoint.getX() + rendererRange;
	int maxTerrainY = rendererCenterPoint.getY() + rendererRange;

	ProceduralTerrainAppearance* terrainAppearance = nullptr;

	auto planetManager = zone->getPlanetManager();

	if (planetManager != nullptr) {
		TerrainManager* manager = planetManager->getTerrainManager();

		if (manager != NULL)
			terrainAppearance = manager->getProceduralTerrainAppearance();
	}

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
			terrainTile->setTerrain(trnMesh);

			trnMesh->addChild(terrainTile);
		}
	}

	trnMesh->setBlendingPolicy(osgTerrain::TerrainTile::ENABLE_BLENDING);
	trnMesh->setName("TerrainMesh");

	info("terrain generated", true);

	return trnMesh;
}

void ZoneRenderer::setWireframe(osg::Node* node, osg::PolygonMode::Face mode) {
	osg::StateSet* state = node->getOrCreateStateSet();
	state->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	osg::PolygonMode* polygonMode = dynamic_cast<osg::PolygonMode*>(state->getAttribute(osg::StateAttribute::POLYGONMODE));

	if (polygonMode == NULL ) {
		polygonMode = new osg::PolygonMode;

		state->setAttribute(polygonMode);
	}

	polygonMode->setMode(mode, osg::PolygonMode::LINE);
}

void ZoneRenderer::addSceneObject(SceneObject* scno) {
	auto worldPosition = scno->getWorldPosition();
	worldPosition.setZ(0);

	if (worldPosition.distanceTo(rendererCenterPoint) > rendererRange)
		return;

	CreatureObject* creo = scno->asCreatureObject();

	if (creo != NULL) {
		addCreatureObject(creo);

		return;
	}

	/*if (objectCount > 100)
		return;*/

	SharedObjectTemplate* templateObject = scno->getObjectTemplate();

	if (templateObject == NULL)
		return;

	PortalLayout* portalLayout = templateObject->getPortalLayout();

	Vector<MeshAppearanceTemplate*> appearances;

	if (portalLayout != NULL) {
		if (scno->isBuildingObject()) {
			for (int i = 0; i < portalLayout->getAppearanceTemplatesSize(); ++i) {
				MeshAppearanceTemplate* mesh = portalLayout->getMeshAppearanceTemplate(i);

				appearances.add(mesh);
			}
		} else {
			MeshAppearanceTemplate* mesh = portalLayout->getMeshAppearanceTemplate(0);

			appearances.add(mesh);
		}
	} else {
		AppearanceTemplate* appTemplate = templateObject->getAppearanceTemplate();

		if (appTemplate == NULL)
			return;

		MeshAppearanceTemplate* mesh = dynamic_cast<MeshAppearanceTemplate*>(appTemplate->getFirstMesh());

		appearances.add(mesh);
	}

	if (appearances.size() == 0)
		return;

	auto newTrans = getTransform(scno);

	for (int i = 0; i < appearances.size(); ++i) {
		MeshAppearanceTemplate* mesh = appearances.get(i);

		osg::ref_ptr<osg::Node> baseMesh = mesh->draw();

		newTrans->addChild(baseMesh);
	}

	setWireframe(newTrans);

	queueInsert(newTrans, scno);
}

osg::ref_ptr<osg::MatrixTransform> ZoneRenderer::getTransform(SceneObject* scno) {
	osg::Quat nodeQuat(scno->getDirectionX(), scno->getDirectionY(), scno->getDirectionZ(), scno->getDirectionW());

	osg::ref_ptr<osg::MatrixTransform> newTrans = new osg::MatrixTransform();

	static const osg::Matrix switchZYAxis = osg::Matrix::rotate(osg::DegreesToRadians(90.f), 1, 0, 0)
	* osg::Matrix::rotate(osg::DegreesToRadians(180.f), 0, 0, 1)
	* osg::Matrix::scale(-1, 1, 1);

	newTrans->setMatrix(osg::Matrix::rotate(nodeQuat) *
			osg::Matrix::translate(osg::Vec3f(scno->getWorldPositionX(), scno->getWorldPositionZ(), scno->getWorldPositionY())) *
			switchZYAxis);

	return newTrans;
}

void ZoneRenderer::addCreatureObject(CreatureObject* scno) {
	auto transform = getTransform(scno);

	osg::Sphere* unitSphere = new osg::Sphere(osg::Vec3(0, 0, 0), 1);
	osg::ShapeDrawable* unitSphereDrawable = new osg::ShapeDrawable(unitSphere);

	if (scno->isPlayerCreature()) {
		unitSphereDrawable->setColor(osg::Vec4(1.f, 0.f, 0.f, .5f));
	} else {
		unitSphereDrawable->setColor(osg::Vec4(0.f, 0.f, 1.f, .5f));
	}

	osg::Geode* unitSphereGeode = new osg::Geode();
	unitSphereGeode->addDrawable(unitSphereDrawable);

	transform->addChild(unitSphereGeode);

	transform->setUpdateCallback(new CreatureObjectNodeCallback(scno));

	queueInsert(transform, scno);
}

void ZoneRenderer::removeSceneObject(SceneObject* object) {

}

void ZoneRenderer::queueInsert(const osg::ref_ptr<osg::Node>& node, SceneObject* object) {
	Locker guard(&mutex);

	/*if (objectCount >= 1)
		return;*/

	if (insertObjects == nullptr) {
		insertObjects = new Vector<osg::Node*>(100, 100);
	}

	node.get()->ref();

	insertObjects->add(node);

	/*if (object != nullptr) {
		node->ref();

		objectTransforms.put(object, node);
	}*/

	++objectCount;
}

PickHandler::PickHandler(ZoneRenderer* renderer) : renderer(renderer) {

}

bool PickHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) {
	switch (ea.getEventType()) {
	case (osgGA::GUIEventAdapter::FRAME):
	case (osgGA::GUIEventAdapter::MOVE): {
		osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);

		if (view) {
			printIntersections(ea.getX(), ea.getY(), view);
		}

		return true;
	}
	default:
		break;
	}

	return osgGA::GUIEventHandler::handle(ea, aa);
}

void PickHandler::printIntersections(float x, float y, osgViewer::View* view) {
	osgUtil::LineSegmentIntersector::Intersections intersections;

	if (view->computeIntersections(x, y, intersections)) {
		for (auto hitr = intersections.begin();
				hitr != intersections.end(); ++hitr) {
			osg::Node* node = hitr->nodePath.empty() ? nullptr : hitr->nodePath.back();

			if (!node)
				continue;

			auto intersect = hitr->getWorldIntersectPoint();

			StringBuffer data;
			data << "world coords (x:" << (float) intersect.x() << " z:" << (float) intersect.z() << " y:" << (float) intersect.y() << endl;

			renderer->getUpdateText()->setText(data.toString().toCharArray());
		}
	}
}


CreatureObjectNodeCallback::CreatureObjectNodeCallback(CreatureObject* creature) : creature(creature) {

}

void CreatureObjectNodeCallback::operator()(osg::Node* node, osg::NodeVisitor* nv) {
	Vector3 worldPosition = creature->getWorldPosition();

	osg::Transform* transform = node->asTransform();

	if (!transform)
		return;

	osg::MatrixTransform* matrixTransform = transform->asMatrixTransform();

	if (!matrixTransform)
		return;

	matrixTransform->setMatrix(osg::Matrix::translate(osg::Vec3f(worldPosition.getX(),
			worldPosition.getY(), worldPosition.getZ())));
}

