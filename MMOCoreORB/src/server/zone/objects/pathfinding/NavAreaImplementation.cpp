#include <cstdint>
#include "server/zone/objects/pathfinding/NavArea.h"
#include "server/zone/managers/collision/NavMeshManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/scene/SceneObjectType.h"

//#define NAVMESH_DEBUG

void NavAreaImplementation::destroyObjectFromWorld(bool sendSelfDestroy) {
	disableUpdates = true;

	NavMeshManager::instance()->cancelJobs(asNavArea());

	if (zone != NULL) {
		PlanetManager* planetManager = zone->getPlanetManager();

		if (planetManager != NULL)
			planetManager->dropNavArea(meshName);
	}

	ActiveAreaImplementation::destroyObjectFromWorld(sendSelfDestroy);
}

void NavAreaImplementation::notifyLoadFromDatabase() {
	//TODO: remove all this. It's just to get rid of old nav areas
	String dbName;
	uint16 tableID = (uint16)(getObjectID() >> 48);
	ObjectDatabaseManager::instance()->getDatabaseName(tableID, dbName);

	if (dbName != "navareas") {
		info("Destroying nav area that's not in navareas.db", true);
		destroyObjectFromDatabase(true);
		return;
	}

	ActiveAreaImplementation::notifyLoadFromDatabase();
}

AABB NavAreaImplementation::getBoundingBox() {
	float f = radius;
	float x = getPositionX();
	float y = getPositionY();
	Vector3 center(x, 0, y);
	Vector3 radius(f, f, f);
	return AABB(center-radius, center+radius);
}

void NavAreaImplementation::setRadius(float f) {
    ActiveAreaImplementation::setRadius(f);
    float x = getPositionX();
    float y = getPositionY();
    Vector3 center(x, 0, y);
    Vector3 radius(f, f, f);
    meshBounds = AABB(center-radius, center+radius);
}

bool NavAreaImplementation::isInRange(float x, float y, float range) {
   const Vector3& worldPos = getWorldPosition();
	float dx = worldPos.getX() - x;
	float dy = worldPos.getY() - y;
	float dist = dx * dx + dy * dy;
	float max = (range * range + radius*radius);

    if (dist <= max)
        return true;

    return false;
}

void NavAreaImplementation::updateNavMesh(const AABB& bounds) {
	Locker locker(asNavArea());

    static const RecastSettings settings;
    if (!recastNavMesh.isLoaded()) {
        NavMeshManager::instance()->enqueueJob(asNavArea(), meshBounds, settings, NavMeshManager::TileQueue);
    } else {
        NavMeshManager::instance()->enqueueJob(asNavArea(), bounds, settings, NavMeshManager::TileQueue);
    }
}

void NavAreaImplementation::initializeNavArea(Vector3& position, float radius, Zone* zone, const String& name, bool forceRebuild) {
    meshName = name;
    recastNavMesh.setName(meshName);
    setLoggingName("NavArea " + meshName);
    initializePosition(position[0], position[1], position[2]);
    setRadius(radius);
    setZone(zone);

    if (forceRebuild || !recastNavMesh.isLoaded()) {
        updateNavMesh(getBoundingBox());
    }
}

void NavAreaImplementation::initialize() {
    meshName = String::valueOf(getObjectID());
    setLoggingName("NavArea " + meshName);
}

bool NavAreaImplementation::objectInMesh(SceneObject* obj) {
	ReadLocker rlocker(&containedLock);

	return containedObjects.contains(obj->getObjectID());
}

void NavAreaImplementation::notifyEnter(SceneObject* object) {
    if (disableUpdates || NavMeshManager::instance()->isStopped())
        return;

    if (object->getParentID() != 0)
        return;

    if (object->isCreatureObject() || object->isLairObject())
        return;

    if (object->getGameObjectType() == SceneObjectType::FURNITURE)
        return;

    SharedObjectTemplate *shot = object->getObjectTemplate();

    if (shot == NULL)
        return;

    if (shot->getCollisionMaterialFlags() == 0 || shot->getCollisionMaterialBlockFlags() == 0) // soft object
        return;

    if (shot->getTemplateFileName().contains("construction_"))
    	return;

    updateNavMesh(object, false);
}

void NavAreaImplementation::notifyExit(SceneObject* object) {
    if (disableUpdates || NavMeshManager::instance()->isStopped())
        return;

    updateNavMesh(object, true);
}

void NavAreaImplementation::updateNavMesh(SceneObject *object, bool remove) {
    if (disableUpdates || NavMeshManager::instance()->isStopped()) // We check this redundantly as to not burden the zoneContainerComponent with this logic
        return;

    ReadLocker rlocker(&containedLock);

    if (remove) {
    	if (!containedObjects.contains(object->getObjectID()))
    		return;
    } else {
    	if (containedObjects.contains(object->getObjectID()))
    		return;
    }

    rlocker.release();

#ifdef NAVMESH_DEBUG
        info(object->getObjectTemplate()->getTemplateFileName() + " caused navmesh rebuild with: collisionmaterialflags " + String::valueOf(object->getObjectTemplate()->getCollisionMaterialFlags()) + "\ncollisionmaterialblockflags " + String::valueOf(object->getObjectTemplate()->getCollisionMaterialBlockFlags())+ "\ncollisionmaterialpassflags " + String::valueOf(object->getObjectTemplate()->getCollisionMaterialPassFlags()) + "\ncollisionmaterialactionflags " + String::valueOf(object->getObjectTemplate()->getCollisionActionFlags())+ "\ncollisionmaterialactionpassflags " + String::valueOf(object->getObjectTemplate()->getCollisionActionPassFlags()) + "\ncollisionmaterialactionBlockflags " + String::valueOf(object->getObjectTemplate()->getCollisionActionBlockFlags()), true);
#endif

    Vector3 position = object->getWorldPosition();
    const BaseBoundingVolume *volume = object->getBoundingVolume();
    if (volume) {

        AABB bbox = volume->getBoundingBox();
        float len = bbox.extents()[bbox.longestAxis()];
        len = (len / 32.0f) * 32;
        Vector3 extents(len, len, len);
        bbox = AABB(position-extents, position+extents);
#ifdef NAVMESH_DEBUG
        info("Rebuilding from structure extents :\n" + bbox.getMinBound()->toString() + ", " + bbox.getMaxBound()->toString(), true);
#endif
        updateNavMesh(bbox);

        Locker containerLock(&containedLock);

        if (remove) {
            containedObjects.remove(object->getObjectID());
        } else {
            containedObjects.add(object->getObjectID());
        }
    }
}

NavArea* NavAreaImplementation::asNavArea() {
    return _this.getReferenceUnsafeStaticCast();
}

bool NavAreaImplementation::containsPoint(float px, float py) {
    float dx = px - getPositionX();
    float dy = py - getPositionY();

    return ((dx * dx + dy * dy) < (radius * radius));
}
