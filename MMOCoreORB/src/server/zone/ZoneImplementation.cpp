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

}

void ZoneImplementation::initializePrivateData() {

}

void ZoneImplementation::finalize() {

}

void ZoneImplementation::initializeTransientMembers() {

}

void ZoneImplementation::startManagers() {

}

void ZoneImplementation::stopManagers() {

}

void ZoneImplementation::clearZone() {

}

/*

	Object Management in Zone

*/

void ZoneImplementation::insert(TreeEntry* entry) {

}

void ZoneImplementation::remove(TreeEntry* entry) {

}

void ZoneImplementation::update(TreeEntry* entry) {

}

void ZoneImplementation::inRange(TreeEntry* entry, float range) {

}

void ZoneImplementation::updateActiveAreas(TangibleObject* tano) {

}

void ZoneImplementation::addSceneObject(SceneObject* object) {

}

void ZoneImplementation::dropSceneObject(SceneObject* object)  {

}

/*

	Object Tracking

*/

int ZoneImplementation::getInRangeSolidObjects(float x, float z, float y, float range, SortedVector<ManagedReference<TreeEntry*> >* objects, bool readLockZone) {

	return 0;
}

int ZoneImplementation::getInRangeObjects(float x, float z, float y, float range, SortedVector<ManagedReference<TreeEntry*> >* objects, bool readLockZone, bool includeBuildingObjects) {

	return 0;
}

int ZoneImplementation::getInRangeObjects(float x, float z, float y, float range, InRangeObjectsVector* objects, bool readLockZone, bool includeBuildingObjects) {

	return 0;
}

int ZoneImplementation::getInRangePlayers(float x, float z, float y, float range, SortedVector<ManagedReference<TreeEntry*> >* players) {

	return 0;
}

int ZoneImplementation::getInRangeActiveAreas(float x, float z, float y, SortedVector<ManagedReference<ActiveArea*> >* objects, bool readLockZone) {

	return 0;
}

int ZoneImplementation::getInRangeActiveAreas(float x, float z, float y, ActiveAreasVector* objects, bool readLockZone) {

	return 0;
}

/*

	Quadtree

*/

float ZoneImplementation::getHeight(float x, float y) {

	return 0;
}

float ZoneImplementation::getHeightNoCache(float x, float y) {

	return 0;
}

Reference<SceneObject*> ZoneImplementation::getNearestPlanetaryObject(SceneObject* object, const String& mapCategory, const String& mapSubCategory) {

	return nullptr;
}

int ZoneImplementation::getInRangeNavMeshes(float x, float y, SortedVector<ManagedReference<NavArea*> >* objects, bool readlock) {

	return 0;
}

SortedVector<ManagedReference<SceneObject*> > ZoneImplementation::getPlanetaryObjectList(const String& mapCategory) {
	SortedVector<ManagedReference<SceneObject*> > retVector;

	return retVector;
}

void ZoneImplementation::registerObjectWithPlanetaryMap(SceneObject* object) {

}

void ZoneImplementation::unregisterObjectWithPlanetaryMap(SceneObject* object) {

}

bool ZoneImplementation::objectIsValidPlanetaryMapPerformanceLocation(SceneObject* object) {

	return false;
}

bool ZoneImplementation::isObjectRegisteredWithPlanetaryMap(SceneObject* object) {

	return false;
}

void ZoneImplementation::updatePlanetaryMapIcon(SceneObject* object, byte icon) {

}

void ZoneImplementation::sendMapLocationsTo(CreatureObject* player) {

}

float ZoneImplementation::getMinX() {

	return 0.f;
}

float ZoneImplementation::getMaxX() {

	return 0.f;
}

float ZoneImplementation::getMinY() {

	return 0.f;
}

float ZoneImplementation::getMaxY() {

	return 0.f;
}

void ZoneImplementation::updateCityRegions() {

}

/*

	Octree

*/



/*

	Shared Functions

*/

bool ZoneImplementation::isWithinBoundaries(const Vector3& position) {

	return false;
}

float ZoneImplementation::getBoundingRadius() {

	return 0.5f;
}

float ZoneImplementation::getZoneObjectRange() {
	return ZoneServer::CLOSEOBJECTRANGE;
}
