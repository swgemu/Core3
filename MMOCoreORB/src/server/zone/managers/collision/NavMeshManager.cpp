#include "NavMeshManager.h"
#include "pathfinding/RecastNavMesh.h"
#include "pathfinding/RecastTileBuilder.h"

#include "pathfinding/RecastNavMeshBuilder.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "terrain/manager/TerrainManager.h"
#include "terrain/ProceduralTerrainAppearance.h"
#include "templates/building/SharedBuildingObjectTemplate.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/pathfinding/PersistentRecastNavMesh.h"

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


    ObjectDatabase* database = ObjectDatabaseManager::instance()->loadObjectDatabase("buildingmeshes", true);
    ObjectDatabaseIterator iterator(database);
    uint64 objectID = 0;
    try {

        while(iterator.getNextKey(objectID)) {
            ManagedReference<PersistentRecastNavMesh*> obj = Core::getObjectBroker()->lookUp(objectID).castTo<PersistentRecastNavMesh*>();
            if (obj != NULL) {
                RecastNavMesh *navMesh = obj->getNavMesh();
                buildingMeshes.put(navMesh->getName(), obj);
            }
        }
    } catch (Exception e) {
        e.printStackTrace();
    }
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
    Reference<NavMeshJob*> job = dynamic_cast<NavMeshJob*>(runningJobs.get(name).get());
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

    job = dynamic_cast<NavMeshJob*>(jobs.get(name).get());
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
    jobs.put(job->getMeshName(), job.get());

    Core::getTaskManager()->scheduleTask([=]{
        checkJobs();
    }, "checkJobs", 750, TileQueue.toCharArray());

}

void NavMeshManager::enqueueJob(Reference<RecastNavMesh*> mesh, SharedBuildingObjectTemplate* templ, const RecastSettings& recastConfig, const String& queue) {
    if (stopped)
        return;

    if (queue != TileQueue && queue != MeshQueue) {
        return;
    }

    Locker locker(&jobQueueMutex);

    const String& name = templ->getTemplateFileName();
    Reference<BuildingMeshJob*> job = dynamic_cast<BuildingMeshJob*>(runningJobs.get(name).get());
    if (job) {
        return;
    } else {
        job = new BuildingMeshJob(templ, recastConfig, queue, mesh);
    }

    jobs.put(job->getMeshName(), job.get());

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
        Reference<NavManagerJob*> job = jobs.get(0);

        if (!job->isValid()) {
            jobs.drop(jobs.elementAt(0).getKey());
            continue;
        }

        String name = job->getMeshName();
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

void NavMeshManager::startJob(Reference<NavManagerJob*> job) {
    if (stopped || job == NULL) {
        return;
    }

    bool failed = job->startJob();

    Locker locker(&jobQueueMutex);

    if (!failed && !job->isFinished()) {

        jobs.put(job->getMeshName(), job);
    } else {
        jobs.drop(job->getMeshName());
        runningJobs.drop(job->getMeshName());
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
            auto job = dynamic_cast<NavMeshJob*>(runningJobs.get(i).get());

            if (job->getNavArea() == area) {
                job->cancel();
                runningJobs.remove(i);
            }
        }
    }

    if (jobs.size() > 0) {
        for (int i = jobs.size()-1; i >= 0; i--) {
            auto job = dynamic_cast<NavMeshJob*>(runningJobs.get(i).get());
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

RecastNavMesh* NavMeshManager::getBuildingMesh(SharedBuildingObjectTemplate *templ) {
    const String& name = templ->getTemplateFileName();
    ManagedReference<PersistentRecastNavMesh*> mesh = buildingMeshes.get(name);

    if (mesh == NULL) {
        ManagedReference<ManagedObject*> obj = ObjectManager::instance()->createObject("PersistentRecastNavMesh", 1, "buildingmeshes");
        mesh = obj.castTo<PersistentRecastNavMesh*>();
    }

    if (!mesh->getNavMesh()->isLoaded()) {
        buildingMeshes.put(name, mesh);
        RecastSettings settings;
        settings.m_tileSize = 512.0f;
        settings.m_cellHeight = 0.1f;
        settings.m_cellSize = 0.1f;

        NavMeshManager::instance()->enqueueJob(mesh->getNavMesh(), templ, settings, NavMeshManager::TileQueue);
    }
    return mesh->getNavMesh();
}