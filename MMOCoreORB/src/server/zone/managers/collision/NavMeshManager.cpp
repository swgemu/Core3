#include "NavMeshManager.h"
#include "pathfinding/RecastNavMesh.h"
#include "pathfinding/RecastNavMeshBuilder.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "conf/ConfigManager.h"
#include "terrain/manager/TerrainManager.h"

// Lower thread count, used during runtime
const String NavMeshManager::TileQueue = "NavMeshWorker";

// Higher thread count, used for building large static cities during initialization
const String NavMeshManager::MeshQueue = "NavMeshBuilder";

NavMeshManager::NavMeshManager() {
    maxConcurrentJobs = 4;
    Core::getTaskManager()->initializeCustomQueue(TileQueue.toCharArray(), maxConcurrentJobs);
    Core::getTaskManager()->initializeCustomQueue(MeshQueue.toCharArray(), maxConcurrentJobs*2);
}

void NavMeshManager::enqueueJob(Zone* zone, NavMeshRegion* region, AABB areaToBuild, const RecastSettings& recastConfig, const String& queue) {
    Locker locker(&jobQueueMutex);

    const String& name = region->getMeshName();
    Reference<NavMeshJob*> job = runningJobs.get(name);
    if (job) {
        job->addArea(areaToBuild);
        info("Adding area to running job " + name);
        return;
    }

    job = jobs.get(name);
    if (job == NULL) {
        job = new NavMeshJob(region, zone, recastConfig, queue);
        info("Creating new job for " + name);
    } else {
        info("Adding area to existing job " + name);
    }

    job->addArea(areaToBuild);
    jobs.put(name, job);

    Core::getTaskManager()->scheduleTask([=]{
        checkJobs();
    }, "checkJobs", 750, TileQueue.toCharArray());

}

void NavMeshManager::checkJobs() {

    Locker locker(&jobQueueMutex);

    while (jobs.size() > 0) {

        info("Popping job - CurrentSize: " + String::valueOf(jobs.size()), true);
        Reference<NavMeshJob*> job = jobs.get(0);
        const String& name = job->getRegion()->getMeshName();
        jobs.drop(name);
        if(runningJobs.contains(name)) {
            jobs.put(name, job); // push it to the back;
            return;
        }
        runningJobs.put(name, job);

        Core::getTaskManager()->executeTask([=]{
            info("Starting job task for: " + name, true);
            startJob(job);


            Locker locker(&jobQueueMutex);
            runningJobs.drop(name);
        }, "updateNavMesh", MeshQueue.toCharArray());
    }

    locker.release();
}


void NavMeshManager::startJob(Reference<NavMeshJob*> job) {

    if(job == NULL) {
        return;
    }

    Reference<Zone*> zone = job->getZone();
    if (!zone) {
        Locker locker(&jobQueueMutex);
        jobs.put(job->getRegion()->getMeshName(), job);
        return;
    }

    Locker areaLocker(job->getMutex());
    //copy and clear this vector otherwise our scene data may not be correct if a zone was added during the build process
    Vector <AABB> dirtyZones = Vector<AABB>(job->getAreas());
    job->getAreas().removeAll();
    areaLocker.release();

    NavMeshRegion *region = job->getRegion();

    const AABB& bBox = region->getBoundingBox();

    float range = bBox.extents()[bBox.longestAxis()];
    const Vector3& center = bBox.center();

    String filename = region->getMeshName();

    SortedVector <ManagedReference<QuadTreeEntry *>> closeObjects;
    zone->getInRangeSolidObjects(center.getX(), center.getZ(), range, &closeObjects, true);

    Vector <Reference<MeshData *>> meshData;

    for (int i = 0; i < closeObjects.size(); i++) {
        SceneObject *sceno = closeObjects.get(i).castTo<SceneObject *>();
        if (sceno) {
            // TODO: Figure out why we need this
            // Example: v 1393.67 3.09307e+06 -3217
            // mos entha pristine wall
            const float height = sceno->getPosition().getZ();
            if(height > 10000 || height < -10000)
                continue;

            static const Matrix4 identity;

            meshData.addAll(sceno->getTransformedMeshData(&identity));
        }
    }

    RecastNavMeshBuilder *builder = NULL;

    builder = new RecastNavMeshBuilder(zone, filename);

	builder->setRecastConfig(job->getRecastConfig());

    float poleDist = job->getRecastConfig().distanceBetweenPoles;

    if(poleDist < 1.0f)
        poleDist = zone->getPlanetManager()->getTerrainManager()->getProceduralTerrainAppearance()->getDistanceBetweenPoles();

    builder->initialize(meshData, bBox, poleDist);
    meshData.removeAll();
    // This will take a very long time to complete
    Reference<RecastNavMesh*> navmesh = region->getNavMesh();
    bool initialBuild = (navmesh == NULL || !navmesh->isLoaded());
    if (initialBuild) {
        info("Rebuilding Base Mesh", true);
        builder->build();
    } else if (dirtyZones.size() > 0) {
        info("Rebuilding area", true);
        for (int i = dirtyZones.size() - 1; i >= 0; i--) {
            const AABB &area = dirtyZones.get(i);
            builder->rebuildArea(area, navmesh);
        }
    }

    info("Region->name: " + filename);

    builder->saveAll(filename);

    if(initialBuild) {
        if(navmesh == NULL)
            navmesh = new RecastNavMesh();

        navmesh->setFileName(filename);
        navmesh->setDetourNavMesh(builder->getNavMesh());
        navmesh->setDetourNavMeshHeader(builder->getNavMeshHeader());

        Locker locker(region);
        region->setNavMesh(navmesh);
    }

    Locker locker(&jobQueueMutex);
    if(job->getAreas().size() > 0) {

        jobs.put(filename, job);
    } else {
        jobs.drop(filename);
        runningJobs.drop(filename);
    }

    locker.release();

    delete builder;

    //TODO: Fixme
    Core::getTaskManager()->scheduleTask([=]{
        checkJobs();
    }, "checkNavJobs", 1000);
}

bool NavMeshManager::AABBEncompasessAABB(const AABB& lhs, const AABB& rhs) {
    const Vector3 &lMin = *lhs.getMinBound();
    const Vector3 &lMax = *lhs.getMaxBound();

    const Vector3 &rMin = *rhs.getMinBound();
    const Vector3 &rMax = *rhs.getMaxBound();

    if (rMin[0] >= lMin[0] && rMin[2] >= lMin[2] && rMax[0] <= lMax[0] && rMax[2] <= lMax[2])
        return true;

    return false;
}
