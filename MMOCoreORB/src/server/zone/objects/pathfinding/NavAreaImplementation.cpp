#include <cstdint>
#include "server/zone/objects/pathfinding/NavArea.h"
#include "server/zone/managers/collision/NavMeshManager.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/scene/SceneObjectType.h"

//#define NAVMESH_DEBUG

void NavAreaImplementation::notifyLoadFromDatabase() {
	ActiveAreaImplementation::notifyLoadFromDatabase();
	navMesh = new RecastNavMesh("navmeshes/"+meshName, false);
}

void NavAreaImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	ActiveAreaImplementation::destroyObjectFromDatabase(destroyContainedObjects);

	navMesh->deleteFile();
}

void NavAreaImplementation::destroyObjectFromWorld(bool sendSelfDestroy) {
	disableUpdates = true;

	ActiveAreaImplementation::destroyObjectFromWorld(sendSelfDestroy);
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

    RecastSettings settings;
    if (navMesh == NULL || !navMesh->isLoaded()) {
        NavMeshManager::instance()->enqueueJob(zone, asNavArea(), meshBounds, settings, NavMeshManager::TileQueue);
    } else {
        NavMeshManager::instance()->enqueueJob(zone, asNavArea(), bounds, settings, NavMeshManager::TileQueue);
    }
}

void NavAreaImplementation::initializeNavArea(Vector3& position, float radius, Zone* zone, String& name, bool buildMesh, bool forceRebuild) {

    meshName = zone->getZoneName()+"_"+name+".navmesh";
    navMesh = new RecastNavMesh("navmeshes/"+meshName, forceRebuild);
    initializePosition(position[0], position[1], position[2]);
    setRadius(radius);
    setZone(zone);

    if (!navMesh->isLoaded() && buildMesh) {
        updateNavMesh(getBoundingBox());
    }
}

void NavAreaImplementation::initialize() {
    meshName = zone->getZoneName()+"_"+String::valueOf(getObjectID())+".navmesh";
}

void NavAreaImplementation::notifyEnter(SceneObject* object) {
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

void NavAreaImplementation::notifyExit(SceneObject* object) {
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

void NavAreaImplementation::updateNavMesh(SceneObject *object, bool remove) {
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

NavArea* NavAreaImplementation::asNavArea() {
    return _this.getReferenceUnsafeStaticCast();
}

bool NavAreaImplementation::containsPoint(float px, float py) {
    float dx = px - getPositionX();
    float dy = py - getPositionY();

    return ((dx * dx + dy * dy) < (radius * radius));
}
