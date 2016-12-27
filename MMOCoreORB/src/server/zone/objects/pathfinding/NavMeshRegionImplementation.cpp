#include <cstdint>
#include "server/zone/objects/pathfinding/NavMeshRegion.h"
#include "server/zone/managers/collision/NavMeshManager.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/scene/SceneObjectType.h"

//#define NAVMESH_DEBUG

void NavMeshRegionImplementation::initializeTransientMembers() {

}

void NavMeshRegionImplementation::notifyLoadFromDatabase() {
	RegionImplementation::notifyLoadFromDatabase();
	navMesh = new RecastNavMesh("navmeshes/"+meshName, false);
}

void NavMeshRegionImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	RegionImplementation::destroyObjectFromDatabase(destroyContainedObjects);

	navMesh->deleteFile();
}

void NavMeshRegionImplementation::destroyObjectFromWorld(bool sendSelfDestroy) {
	disableUpdates = true;

	RegionImplementation::destroyObjectFromWorld(sendSelfDestroy);
}

AABB NavMeshRegionImplementation::getBoundingBox() {
	float f = radius;
	float x = getPositionX();
	float y = getPositionY();
	Vector3 center(x, 0, y);
	Vector3 radius(f, f, f);
	return AABB(center-radius, center+radius);
}


void NavMeshRegionImplementation::setRadius(float f) {
    RegionImplementation::setRadius(f);
    float x = getPositionX();
    float y = getPositionY();
    Vector3 center(x, 0, y);
    Vector3 radius(f, f, f);
    meshBounds = AABB(center-radius, center+radius);
}

bool NavMeshRegionImplementation::isInRange(float x, float y, float range) {
   const Vector3& worldPos = getWorldPosition();
	float dx = worldPos.getX() - x;
	float dy = worldPos.getY() - y;
	float dist = dx * dx + dy * dy;
	float max = (range * range + radius*radius);

    if (dist <= max)
        return true;

    return false;
}

void NavMeshRegionImplementation::updateNavMesh(const AABB& bounds) {
	Locker locker(asNavRegion());

    RecastSettings settings;
    if (navMesh == NULL || !navMesh->isLoaded()) {
        NavMeshManager::instance()->enqueueJob(zone, asNavRegion(), meshBounds, settings, NavMeshManager::TileQueue);
    } else {
        NavMeshManager::instance()->enqueueJob(zone, asNavRegion(), bounds, settings, NavMeshManager::TileQueue);
    }
}

void NavMeshRegionImplementation::initializeNavRegion(Vector3& position, float radius, Zone* zone, String& name, bool buildMesh, bool forceRebuild) {

    meshName = zone->getZoneName()+"_"+name+".navmesh";
    navMesh = new RecastNavMesh("navmeshes/"+meshName, forceRebuild);
    initializePosition(position[0], position[1], position[2]);
    setRadius(radius);
    setZone(zone);

    if (!navMesh->isLoaded() && buildMesh) {
        updateNavMesh(getBoundingBox());
    }
}

void NavMeshRegionImplementation::initialize() {
    meshName = zone->getZoneName()+"_"+String::valueOf(getObjectID())+".navmesh";
}

void NavMeshRegionImplementation::notifyEnter(SceneObject* object) {
    if(disableUpdates)
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

    ReadLocker rlocker(&containedLock);
    if(!containedObjects.contains(object->getObjectID()) &&  !object->getObjectTemplate()->getTemplateFileName().contains("construction_")) {
    	rlocker.release();

        updateNavMesh(object, false);
    }
}

void NavMeshRegionImplementation::notifyExit(SceneObject* object) {
    if(disableUpdates)
        return;

    ReadLocker rlocker(&containedLock);

    if(containedObjects.contains(object->getObjectID())) {
#ifdef NAVMESH_DEBUG
        info(object->getObjectTemplate()->getTemplateFileName() + " caused navmesh rebuild with: collisionmaterialflags " + String::valueOf(object->getObjectTemplate()->getCollisionMaterialFlags()) + "\ncollisionmaterialblockflags " + String::valueOf(object->getObjectTemplate()->getCollisionMaterialBlockFlags())+ "\ncollisionmaterialpassflags " + String::valueOf(object->getObjectTemplate()->getCollisionMaterialPassFlags()) + "\ncollisionmaterialactionflags " + String::valueOf(object->getObjectTemplate()->getCollisionActionFlags())+ "\ncollisionmaterialactionpassflags " + String::valueOf(object->getObjectTemplate()->getCollisionActionPassFlags()) + "\ncollisionmaterialactionBlockflags " + String::valueOf(object->getObjectTemplate()->getCollisionActionBlockFlags()), true);
#endif

        rlocker.release();
        updateNavMesh(object, true);
    }
}

void NavMeshRegionImplementation::updateNavMesh(SceneObject *object, bool remove) {
    if (disableUpdates) // We check this redundantly as to not burden the zoneContainerComponent with this logic
        return;

    Vector3 position = object->getWorldPosition();
    const BaseBoundingVolume *volume = object->getBoundingVolume();
    if(volume) {

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

NavMeshRegion* NavMeshRegionImplementation::asNavRegion() {
    return _this.getReferenceUnsafeStaticCast();
}

bool NavMeshRegionImplementation::containsPoint(float px, float py) {
    float dx = px - getPositionX();
    float dy = py - getPositionY();

    return ((dx * dx + dy * dy) < (radius * radius));
}
