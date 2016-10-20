/*
 * NAVMESHJOB.h
 *
 *  Created on: 10/01/2016
 *      Author: gslomin
 */

#ifndef NAVMESHJOB_H_
#define NAVMESHJOB_H_
#include <functional>
#include "engine/engine.h"
#include "engine/core/LambdaFunction.h"
#include "server/zone/objects/pathfinding/NavMeshRegion.h"
#include "pathfinding/RecastNavMesh.h"
#include "server/zone/Zone.h"
#include "engine/util/u3d/AABB.h"

class NavMeshJob : public Object {
protected:
	ManagedReference<NavMeshRegion*> region;
	ManagedWeakReference<Zone*> zone;
	Vector<AABB> areas;
	RecastSettings settings;
	const String& queue;
	//Vector<LambdaFunction<std::function<void(NavmeshRegion*, const Vector<AABB>*)> > > functions;
	Mutex mutex;
public:

	NavMeshJob();

	NavMeshJob(const NavMeshJob& rhs) : Object(rhs), queue(rhs.queue) {
		zone = rhs.zone;
		region = rhs.region;
		areas = rhs.areas;
		settings = rhs.settings;
	}

	Vector<AABB>& getAreas() {
		return areas;
	}

	ManagedReference<Zone*> getZone() {
		return zone.get();
	}

	NavMeshRegion* getRegion() {
		return region;
	}

	RecastSettings& getRecastConfig() {
		return settings;
	}
	NavMeshJob(NavMeshRegion *region, Zone* zone, const RecastSettings& config, const String& targetQueue) : queue(targetQueue)  {
		this->zone = zone;
		this->region = region;
		settings = config;
	}

	Mutex* getMutex() {
		return &mutex;
	}

	const String& getQueue() {
	    return queue;
	}

	void addArea(const AABB& area);

	bool toBinaryStream(ObjectOutputStream* stream);

	bool parseFromBinaryStream(ObjectInputStream* stream);

};
#endif
