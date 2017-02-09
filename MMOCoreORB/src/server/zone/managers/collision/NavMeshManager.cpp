#include "NavMeshManager.h"
#include "pathfinding/RecastNavMesh.h"
#include "pathfinding/RecastNavMeshBuilder.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "terrain/manager/TerrainManager.h"
#include "terrain/ProceduralTerrainAppearance.h"

// Lower thread count, used during runtime
const String NavMeshManager::TileQueue = "NavMeshWorker";

// Higher thread count, used for building large static cities during initialization
const String NavMeshManager::MeshQueue = "NavMeshBuilder";

//#define NAVMESH_DEBUG

NavMeshManager::NavMeshManager() : Logger("NavMeshManager") {
    maxConcurrentJobs = 4;
    stopped = false;
}

void NavMeshManager::initialize(int numThreads) {
    maxConcurrentJobs = numThreads;
    Core::getTaskManager()->initializeCustomQueue(TileQueue.toCharArray(), maxConcurrentJobs/2, false);
    Core::getTaskManager()->initializeCustomQueue(MeshQueue.toCharArray(), maxConcurrentJobs, false);
}

void NavMeshManager::enqueueJob(Zone* zone, NavMeshRegion* region, AABB areaToBuild, const RecastSettings& recastConfig, const String& queue) {
	if (stopped)
		return;

    Locker locker(&jobQueueMutex);

    const String& name = region->getMeshName();
    Reference<NavMeshJob*> job = runningJobs.get(name);
    if (job) {
        job->addArea(areaToBuild);
#ifdef NAVMESH_DEBUG
        info("Adding area to running job " + name);
#endif
        return;
    }

    job = jobs.get(name);
    if (job == NULL) {
        job = new NavMeshJob(region, zone, recastConfig, queue);
#ifdef NAVMESH_DEBUG
        info("Creating new job for " + name);
#endif
    } else {
#ifdef NAVMESH_DEBUG
        info("Adding area to existing job " + name);
#endif
    }

    job->addArea(areaToBuild);
    jobs.put(name, job);

    Core::getTaskManager()->scheduleTask([=]{
        checkJobs();
    }, "checkJobs", 750, TileQueue.toCharArray());

}

void NavMeshManager::checkJobs() {
	if (stopped)
		return;

    Locker locker(&jobQueueMutex);

    while (jobs.size() > 0) {
#ifdef NAVMESH_DEBUG
        info("Popping job - CurrentSize: " + String::valueOf(jobs.size()), true);
#endif
        Reference<NavMeshJob*> job = jobs.get(0);
        Reference<NavMeshRegion*> region = job->getRegion();

        if (region == NULL) {
        	jobs.drop(jobs.elementAt(0).getKey());
        	continue;
        }

        const String& name = region->getMeshName();
        jobs.drop(name);

        if (runningJobs.contains(name)) {
            jobs.put(name, job); // push it to the back;
            return;
        }
        runningJobs.put(name, job);

        Core::getTaskManager()->executeTask([=]{
#ifdef NAVMESH_DEBUG
            info("Starting job task for: " + name, true);
#endif
            startJob(job);


            Locker locker(&jobQueueMutex);
            runningJobs.drop(name);
        }, "updateNavMesh", job->getQueue().toCharArray());
    }

    locker.release();
}


void NavMeshManager::startJob(Reference<NavMeshJob*> job) {

    if (stopped || job == NULL) {
        return;
    }

    Reference<NavMeshRegion*> region = job->getRegion();

    if (region == NULL) {
    	return;
    }

    Reference<Zone*> zone = job->getZone();

    if (!zone) {
        Locker locker(&jobQueueMutex);
        jobs.put(region->getMeshName(), job);
        return;
    }

    Locker areaLocker(job->getMutex());
    //copy and clear this vector otherwise our scene data may not be correct if a zone was added during the build process
    Vector <AABB> dirtyZones = Vector<AABB>(job->getAreas());
    job->getAreas().removeAll();
    areaLocker.release();

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

    const AtomicBoolean* running = job->getJobStatus();
    builder = new RecastNavMeshBuilder(zone, filename, running);

	builder->setRecastConfig(job->getRecastConfig());

    float poleDist = job->getRecastConfig().distanceBetweenPoles;

    if(poleDist < 1.0f) {
        poleDist = zone->getPlanetManager()->getTerrainManager()->getProceduralTerrainAppearance()->getDistanceBetweenPoles();
    }

    builder->initialize(meshData, bBox, poleDist);
    meshData.removeAll();
    // This will take a very long time to complete
    Reference<RecastNavMesh*> navmesh = region->getNavMesh();
    bool initialBuild = (navmesh == NULL || !navmesh->isLoaded());
    if (initialBuild) {
#ifdef NAVMESH_DEBUG
        info("Rebuilding Base Mesh", true);
#endif
        builder->build();
    } else if (dirtyZones.size() > 0) {
#ifdef NAVMESH_DEBUG
        info("Rebuilding area", true);
#endif
        for (int i = dirtyZones.size() - 1; i >= 0; i--) {
            const AABB &area = dirtyZones.get(i);
            builder->rebuildArea(area, navmesh);
        }
    }

#ifdef NAVMESH_DEBUG
    info("Region->name: " + filename);
#endif

    if(running->get())
        builder->saveAll(filename);

    if(initialBuild) {
        if(navmesh == NULL)
            navmesh = new RecastNavMesh();

        navmesh->setFileName("navmeshes/" + filename);
        navmesh->setDetourNavMesh(builder->getNavMesh());
        navmesh->setDetourNavMeshHeader(builder->getNavMeshHeader());

        Core::getTaskManager()->executeTask([=]{
            Locker locker(region);
            region->setNavMesh(navmesh);
        }, "setNavMesh");
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
    }, "checkNavJobs", 1000, TileQueue.toCharArray());
}

void NavMeshManager::cancelJobs(NavMeshRegion* region) {
    Locker locker(&jobQueueMutex);

    if (runningJobs.size() > 0) {
        for (int i = runningJobs.size()-1; i >= 0; i--) {
            auto& job = runningJobs.get(i);
            if (job->getRegion() == region) {
                job->cancel();
                runningJobs.remove(i);
            }
        }
    }

    if (jobs.size() > 0) {
        for (int i = jobs.size()-1; i >= 0; i--) {
            auto& job = jobs.get(i);
            if (job->getRegion() == region) {
                jobs.remove(i);
            }
        }
    }
}

void NavMeshManager::cancelAllJobs() {
	Locker locker(&jobQueueMutex);

	if (runningJobs.size() > 0) {
		for (int i = runningJobs.size()-1; i >= 0; i--) {
			auto& job = runningJobs.get(i);
			job->cancel();
			runningJobs.remove(i);
		}
	}

	jobs.removeAll();
}

void NavMeshManager::stop() {
	stopped = true;
	cancelAllJobs();
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
