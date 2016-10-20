#include "NavMeshJob.h"
#include "pathfinding/RecastNavMesh.h"
#include "pathfinding/RecastNavMeshBuilder.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "NavMeshManager.h"


NavMeshJob::NavMeshJob() :queue(NavMeshManager::TileQueue) {
    zone = NULL;
    region = NULL;
}

void NavMeshJob::addArea(const AABB& area) {
    float size = area.extents().getX() * area.extents().getZ();

    Locker locker(&mutex);

    if(areas.size() > 0) {
        for (int i = areas.size() - 1; i >= 0; i--) {
            const AABB& existing = areas.get(i);
            float existingSize = existing.extents().getX() * existing.extents().getZ();

            if (existingSize > size) {
                // check to see if an existing AABB completely encompasses the one we are adding
                if(NavMeshManager::AABBEncompasessAABB(existing, area))
                    return;
            } else if(NavMeshManager::AABBEncompasessAABB(area, existing)) {
                // Check to see if the AABB we are adding encompasses one already in the list
                areas.remove(i);
                continue;
            }
        }
    }

    areas.add(area);
}

bool NavMeshJob::toBinaryStream(ObjectOutputStream* stream) {
    TypeInfo<RecastSettings>::toBinaryStream(&settings, stream);
    TypeInfo<ManagedReference<NavMeshRegion*>>::toBinaryStream(&region, stream);
    TypeInfo<ManagedWeakReference<Zone*>>::toBinaryStream(&zone, stream);
	TypeInfo<Vector<AABB>>::toBinaryStream(&areas, stream);
    return true;
}

bool NavMeshJob::parseFromBinaryStream(ObjectInputStream* stream) {
    TypeInfo<RecastSettings>::parseFromBinaryStream(&settings, stream);
    TypeInfo<ManagedReference<NavMeshRegion*>>::parseFromBinaryStream(&region, stream);
    TypeInfo<ManagedWeakReference<Zone*>>::parseFromBinaryStream(&zone, stream);
	TypeInfo<Vector<AABB>>::parseFromBinaryStream(&areas, stream);
    return true;
}