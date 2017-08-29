/*
 * NAVMESHJOB.h
 *
 *  Created on: 10/01/2016
 *      Author: gslomin
 */

#ifndef NAVMESHJOB_H_
#define NAVMESHJOB_H_

#include <templates/building/SharedBuildingObjectTemplate.h>
#include "server/zone/objects/pathfinding/NavArea.h"
#include "engine/util/u3d/AABB.h"


class NavManagerJob : public Object {
	RecastSettings settings;
	String queue;
	AtomicBoolean running;
	Mutex mutex;
public:
	NavManagerJob(const RecastSettings& config, String targetQueue) : settings(config), queue(targetQueue), running(true) {
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
	virtual bool isFinished() = 0;

	virtual bool isValid() = 0;

	virtual bool startJob() = 0;

	virtual String getMeshName() = 0;

	const AtomicBoolean* getJobStatus() {
		return &running;
	}
};

class NavMeshJob : public NavManagerJob {
protected:
	WeakReference<NavArea*> area;
	Vector<AABB> areas;
public:

	bool isValid() {
		Reference<NavArea*> temp = area.get();
		if (temp == NULL)
			return false;

		if (temp->getZone() == NULL)
			return false;

		return true;
	}

	NavMeshJob(NavArea *area, const RecastSettings& config, const String& targetQueue) : NavManagerJob(config, targetQueue)  {
		this->area = area;
	}

	Vector<AABB>& getAreas() {
		return areas;
	}

	Reference<NavArea*> getNavArea() {
		return area.get();
	}

	String getMeshName() {
		Reference<NavArea*> temp = area.get();
		return temp->getMeshName();
	}

	bool isFinished() {
		if (areas.size() > 0)
			return false;

		return true;
	}

	bool startJob();

	void addArea(const AABB& area);

};

class BuildingMeshJob : public NavManagerJob {
protected:
	SharedBuildingObjectTemplate* templ;
	Reference<RecastNavMesh*> navmesh;
public:
	BuildingMeshJob(SharedBuildingObjectTemplate* buildingTemplate, const RecastSettings& settings, const String& queue, Reference<RecastNavMesh*> mesh) : NavManagerJob(settings, queue)  {
		templ = buildingTemplate;
		navmesh = mesh;
	}

	String getMeshName() {
		return templ->getTemplateFileName();
	}

	bool isFinished() {
		return true;
	}

	bool isValid() {
		return true;
	}

	bool startJob();


};
#endif
