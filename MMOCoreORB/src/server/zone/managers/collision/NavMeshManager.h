/*
 * NavMeshManager.h
 *
 *  Created on: 10/01/2016
 *      Author: gslomin
 */

#ifndef NAVMESHMANAGER_H_
#define NAVMESHMANAGER_H_

#include "server/zone/objects/pathfinding/NavArea.h"
#include "engine/util/u3d/AABB.h"
#include "server/zone/managers/collision/NavMeshJob.h"

class NavMeshManager : public Singleton<NavMeshManager>, public Logger, public Object{

protected:
	int maxConcurrentJobs;
	VectorMap<String, Reference<NavMeshJob*> > jobs;
	VectorMap<String, Reference<NavMeshJob*> > runningJobs;
	Mutex jobQueueMutex;
	bool stopped;
	ZoneServer* zoneServer;


	void startJob(Reference<NavMeshJob*> job);
    void checkJobs();

public:
	NavMeshManager();
	~NavMeshManager() { }
	void initialize(int numThreads, ZoneServer* server);

	void enqueueJob(NavArea* area, AABB areaToBuild, const RecastSettings& recastConfig, const String& queue);

	void cancelJobs(NavArea* area);
	void cancelAllJobs();
	void stop();

	bool isStopped() {
		return stopped;
	}

	void dumpMeshesToFiles();

    static bool AABBEncompasessAABB(const AABB& lhs, const AABB& rhs);

    // Lower thread count, used during runtime
    static const String TileQueue; //"NavMeshWorker";

    // Higher thread count, used for building large static cities during initialization
    static const String MeshQueue; //"NavMeshBuilder";

};
#endif
