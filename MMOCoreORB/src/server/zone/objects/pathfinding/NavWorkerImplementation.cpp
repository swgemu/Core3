#include "server/zone/objects/pathfinding/NavWorker.h"
#include "server/zone/managers/collision/NavMeshManager.h"
#include "server/zone/managers/collision/NavMeshJob.h"
#include "pathfinding/RecastNavMesh.h"

void NavWorkerImplementation::buildMesh(NavMeshJob& job) {
	static Logger l;
    l.info("Buildmesh ", true);
    NavMeshManager::instance()->enqueueJob(job.getZone(), job.getRegion(), job.getAreas().get(0), job.getRecastConfig(), job.getQueue());
}


void NavWorkerImplementation::testBuild(Zone* zone, NavMeshRegion* region, Vector<AABB*>& areas) {
	RecastSettings settings;
	NavMeshManager::instance()->enqueueJob(zone, region, areas.get(0), settings, NavMeshManager::MeshQueue);
}