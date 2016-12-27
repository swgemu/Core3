#include "NavMeshJob.h"
#include "NavMeshManager.h"

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
