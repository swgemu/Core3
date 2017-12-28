/*
 * NAVMESHJOB.h
 *
 *  Created on: 10/01/2016
 *      Author: gslomin
 */

#ifndef NAVMESHJOB_H_
#define NAVMESHJOB_H_

#include <algorithm>

#include "engine/util/u3d/AABB.h"
#include "pathfinding/RecastTileBuilder.h"
#include "server/zone/objects/pathfinding/NavArea.h"
#include "system/lang/Object.h"
#include "system/lang/String.h"
#include "system/lang/ref/Reference.h"
#include "system/lang/ref/WeakReference.h"
#include "system/thread/Mutex.h"
#include "system/thread/atomic/AtomicBoolean.h"
#include "system/util/Vector.h"

class NavMeshJob : public Object {
protected:
	WeakReference<NavArea*> area;
	Vector<AABB> areas;
	RecastSettings settings;
	String queue;
	AtomicBoolean running;
	Mutex mutex;

public:
	NavMeshJob(NavArea *area, const RecastSettings& config, const String& targetQueue) : queue(targetQueue), running(true)  {
		this->area = area;
		settings = config;
	}

	Vector<AABB>& getAreas() {
		return areas;
	}

	Reference<NavArea*> getNavArea() {
		return area.get();
	}

	RecastSettings& getRecastConfig() {
		return settings;
	}

	Mutex* getMutex() {
		return &mutex;
	}

	const String& getQueue() {
	    return queue;
	}

	void cancel() {
		running.set(false);
	}

	const AtomicBoolean* getJobStatus() {
		return &running;
	}

	void addArea(const AABB& area);

};
#endif
