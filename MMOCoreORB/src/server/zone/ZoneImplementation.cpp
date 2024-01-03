/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/Zone.h"

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/space/SpaceManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/components/ComponentManager.h"
#include "server/zone/packets/player/GetMapLocationsResponseMessage.h"

#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "templates/SharedObjectTemplate.h"

#include "server/zone/managers/structure/StructureManager.h"
#include "terrain/ProceduralTerrainAppearance.h"
#include "server/zone/managers/collision/NavMeshManager.h"
#include "server/zone/ActiveAreaQuadTree.h"

ZoneImplementation::ZoneImplementation(ZoneProcessServer* serv, const String& name) {
	setZoneProcessServer(serv);
	setZoneServer(processor->getZoneServer());

	setZoneName(name);
	setZoneCRC(name.hashCode());

	objectMap = new ObjectMap();

	mapLocations = new MapLocationTable();

	managersStarted = false;
	zoneCleared = false;
}

/*

	Zone Management

*/

void ZoneImplementation::createContainerComponent() {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

void ZoneImplementation::initializePrivateData() {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

void ZoneImplementation::finalize() {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

void ZoneImplementation::initializeTransientMembers() {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

void ZoneImplementation::startManagers() {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

void ZoneImplementation::stopManagers() {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

void ZoneImplementation::clearZone() {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

/*

	Object Management in Zone

*/

void ZoneImplementation::insert(TreeEntry* entry) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

void ZoneImplementation::remove(TreeEntry* entry) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

void ZoneImplementation::update(TreeEntry* entry) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

void ZoneImplementation::inRange(TreeEntry* entry, float range) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

void ZoneImplementation::updateActiveAreas(TangibleObject* tano) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

void ZoneImplementation::addSceneObject(SceneObject* object) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

void ZoneImplementation::dropSceneObject(SceneObject* object)  {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

/*

	Object Tracking

*/

int ZoneImplementation::getInRangeSolidObjects(float x, float z, float y, float range, SortedVector<ManagedReference<TreeEntry*> >* objects, bool readLockZone) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return 0;
}

int ZoneImplementation::getInRangeObjects(float x, float z, float y, float range, SortedVector<ManagedReference<TreeEntry*> >* objects, bool readLockZone, bool includeBuildingObjects) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return 0;
}

int ZoneImplementation::getInRangeObjects(float x, float z, float y, float range, InRangeObjectsVector* objects, bool readLockZone, bool includeBuildingObjects) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return 0;
}

int ZoneImplementation::getInRangePlayers(float x, float z, float y, float range, SortedVector<ManagedReference<TreeEntry*> >* players) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return 0;
}

int ZoneImplementation::getInRangeActiveAreas(float x, float z, float y, SortedVector<ManagedReference<ActiveArea*> >* objects, bool readLockZone) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return 0;
}

int ZoneImplementation::getInRangeActiveAreas(float x, float z, float y, ActiveAreasVector* objects, bool readLockZone) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return 0;
}

/*

	Quadtree

*/

float ZoneImplementation::getHeight(float x, float y) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return 0;
}

float ZoneImplementation::getHeightNoCache(float x, float y) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return 0;
}

Reference<SceneObject*> ZoneImplementation::getNearestPlanetaryObject(SceneObject* object, const String& mapCategory, const String& mapSubCategory) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return nullptr;
}

int ZoneImplementation::getInRangeNavMeshes(float x, float y, SortedVector<ManagedReference<NavArea*> >* objects, bool readlock) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return 0;
}

SortedVector<ManagedReference<SceneObject*> > ZoneImplementation::getPlanetaryObjectList(const String& mapCategory) {
	SortedVector<ManagedReference<SceneObject*> > retVector;
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return retVector;
}

void ZoneImplementation::registerObjectWithPlanetaryMap(SceneObject* object) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

void ZoneImplementation::unregisterObjectWithPlanetaryMap(SceneObject* object) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

bool ZoneImplementation::objectIsValidPlanetaryMapPerformanceLocation(SceneObject* object) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return false;
}

bool ZoneImplementation::isObjectRegisteredWithPlanetaryMap(SceneObject* object) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return false;
}

void ZoneImplementation::updatePlanetaryMapIcon(SceneObject* object, byte icon) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

void ZoneImplementation::sendMapLocationsTo(CreatureObject* player) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

float ZoneImplementation::getMinX() {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return 0.f;
}

float ZoneImplementation::getMaxX() {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return 0.f;
}

float ZoneImplementation::getMinY() {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return 0.f;
}

float ZoneImplementation::getMaxY() {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return 0.f;
}

void ZoneImplementation::updateCityRegions() {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
}

/*

	Octree

*/



/*

	Shared Functions

*/

bool ZoneImplementation::isWithinBoundaries(const Vector3& position) {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return false;
}

float ZoneImplementation::getBoundingRadius() {
	error() << "Zone Abstract Function Called: " << __LINE__ << " : " << __FUNCTION__;
	return 0.f;
}
