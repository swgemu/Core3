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
    zoneServer = NULL;
}

void NavMeshManager::initialize(int numThreads, ZoneServer* server) {
    maxConcurrentJobs = numThreads;
    zoneServer = server;
    Core::getTaskManager()->initializeCustomQueue(TileQueue.toCharArray(), maxConcurrentJobs/2, false);
    Core::getTaskManager()->initializeCustomQueue(MeshQueue.toCharArray(), maxConcurrentJobs, false);
}

void NavMeshManager::enqueueJob(NavArea* area, AABB areaToBuild, const RecastSettings& recastConfig, const String& queue) {
	if (stopped)
		return;

	if (queue != TileQueue && queue != MeshQueue) {
		error("queue is not tile or mesh in NavMeshManager::enqueueJob. queue is " + queue + " for area " + area->getMeshName() + " in zone " + area->getZone()->getZoneName());
		return;
	}

    Locker locker(&jobQueueMutex);

    const String& name = area->getMeshName();
    Reference<NavMeshJob*> job = runningJobs.get(name);
    if (job) {
    	if (job->getNavArea() == area) {
    		job->addArea(areaToBuild);
#ifdef NAVMESH_DEBUG
        	info("Adding area to running job " + name);
#endif
    	} else {
    		error("Trying to add area to running job with same name and different NavArea");
    	}

    	return;
    }

    job = jobs.get(name);
    if (job == NULL) {
        job = new NavMeshJob(area, recastConfig, queue);
#ifdef NAVMESH_DEBUG
        info("Creating new job for " + name);
#endif
    } else {
    	if (job->getNavArea() != area) {
    		error("Trying to add area to queued job with same name and different NavArea");
    		return;
    	}
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
	if (stopped || zoneServer == NULL)
		return;

	while (zoneServer->isServerLoading())
		Thread::sleep(5000);

    Locker locker(&jobQueueMutex);

    while (jobs.size() > 0) {
#ifdef NAVMESH_DEBUG
        info("Popping job - CurrentSize: " + String::valueOf(jobs.size()), true);
#endif
        Reference<NavMeshJob*> job = jobs.get(0);
        Reference<NavArea*> area = job->getNavArea();

        if (area == NULL) {
        	jobs.drop(jobs.elementAt(0).getKey());
        	continue;
        }

        const String& name = area->getMeshName();
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
        }, "startNavMeshJob", job->getQueue().toCharArray());
    }

    locker.release();
}

void NavMeshManager::startJob(Reference<NavMeshJob*> job) {
    if (stopped || job == NULL) {
        return;
    }

    ManagedReference<NavArea*> area = job->getNavArea();

    if (area == NULL) {
    	return;
    }

    Reference<Zone*> zone = area->getZone();

    if (zone == NULL) {
        return;
    }

    Locker areaLocker(job->getMutex());
    //copy and clear this vector otherwise our scene data may not be correct if a zone was added during the build process
    Vector <AABB> dirtyZones = Vector<AABB>(job->getAreas());
    job->getAreas().removeAll();
    areaLocker.release();

    const AABB& bBox = area->getBoundingBox();

    float range = bBox.extents()[bBox.longestAxis()];
    const Vector3& center = bBox.center();

    String name = area->getMeshName();

	info("Starting building navmesh for area: " + name + " on planet: " + zone->getZoneName() + " at: " + area->getPosition().toString(), true);

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
            if (height > 10000 || height < -10000)
                continue;

            static const Matrix4 identity;

            meshData.addAll(sceno->getTransformedMeshData(&identity));
        }
    }

    Reference<RecastNavMeshBuilder*> builder = NULL;

    const AtomicBoolean* running = job->getJobStatus();
    builder = new RecastNavMeshBuilder(zone, name, running);

	builder->setRecastConfig(job->getRecastConfig());

    float poleDist = job->getRecastConfig().distanceBetweenPoles;

    if (poleDist < 1.0f) {
        poleDist = zone->getPlanetManager()->getTerrainManager()->getProceduralTerrainAppearance()->getDistanceBetweenPoles();
    }

    builder->initialize(meshData, bBox, poleDist);
    meshData.removeAll();

    // This will take a very long time to complete
    bool initialBuild = (!area->isNavMeshLoaded());
    if (initialBuild) {
#ifdef NAVMESH_DEBUG
        info("Rebuilding Base Mesh", true);
#endif
        builder->build();
    } else if (dirtyZones.size() > 0) {
#ifdef NAVMESH_DEBUG
        info("Rebuilding area", true);
#endif
        builder->rebuildAreas(dirtyZones, area);
    }

#ifdef NAVMESH_DEBUG
    info("NavArea->name: " + name);
#endif

    if (!running->get()) {
        return;
    }

    Core::getTaskManager()->executeTask([area, name, builder, initialBuild, this] {
    	if (stopped)
    		return;

    	Locker locker(area);
    	RecastNavMesh* navmesh = area->getNavMesh();

    	if (initialBuild) {
    		navmesh->setName(name);
    		navmesh->setDetourNavMeshHeader(builder->getNavMeshHeader());
    	} else {
    		dtNavMesh* oldMesh = navmesh->getNavMesh();

    		if (oldMesh)
    			dtFreeNavMesh(oldMesh);
    	}

    	navmesh->setDetourNavMesh(builder->getNavMesh());
    	navmesh->setupDetourNavMeshHeader();
    	area->_setUpdated(true);
    	info("Done building and setting navmesh for area: " + name + " on planet: " + area->getZone()->getZoneName() + " at: " + area->getPosition().toString(), true);
    }, "setNavMeshLambda");

    Locker locker(&jobQueueMutex);

    if (job->getAreas().size() > 0) {

        jobs.put(name, job);
    } else {
        jobs.drop(name);
        runningJobs.drop(name);
    }

    locker.release();

    //TODO: Fixme
    Core::getTaskManager()->scheduleTask([=]{
        checkJobs();
    }, "checkNavJobs", 1000, TileQueue.toCharArray());
}

void NavMeshManager::cancelJobs(NavArea* area) {
    Locker locker(&jobQueueMutex);

    if (runningJobs.size() > 0) {
        for (int i = runningJobs.size()-1; i >= 0; i--) {
            auto& job = runningJobs.get(i);
            if (job->getNavArea() == area) {
                job->cancel();
                runningJobs.remove(i);
            }
        }
    }

    if (jobs.size() > 0) {
        for (int i = jobs.size()-1; i >= 0; i--) {
            auto& job = jobs.get(i);
            if (job->getNavArea() == area) {
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

void NavMeshManager::dumpMeshesToFiles() {
	ObjectDatabaseManager* dbManager = ObjectDatabaseManager::instance();
	dbManager->loadDatabases(false);
	ObjectDatabase* navAreasDatabase = dbManager->loadObjectDatabase("navareas", false, 0xFFFF, false);

	if (navAreasDatabase != NULL) {
		int i = 0;

		try {
			ObjectDatabaseIterator iterator(navAreasDatabase);

			uint64 objectID;
			ObjectInputStream* objectData = new ObjectInputStream(2000);

			while (iterator.getNextKeyAndValue(objectID, objectData)) {
				RecastNavMesh mesh;

				if (!Serializable::getVariable<RecastNavMesh>(STRING_HASHCODE("NavArea.recastNavMesh"), &mesh, objectData)) {
					objectData->clear();
					continue;
				}

				++i;
				mesh.saveToFile();

				objectData->clear();
			}

			delete objectData;
		} catch (DatabaseException& e) {
			error("Database exception in NavMeshManager::dumpMeshesToFiles(): " + e.getMessage());
		}

		info(String::valueOf(i) + " nav meshes saved to file.", true);
	} else {
		error("Could not load the navareas database.");
	}
}
