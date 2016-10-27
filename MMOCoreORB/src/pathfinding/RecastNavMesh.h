/*
 * RecastNavMesh.h
 *
 *  Created on: April 29, 2016
 *      Author: gslomin
 */

#ifndef RECASTNAVMESH_H_
#define RECASTNAVMESH_H_

#include "engine/engine.h"
#include "pathfinding/RecastTileBuilder.h"

class dtNavMesh;

class RecastNavMesh : public Object, Logger {
	void loadAll(const String& filename);
	dtNavMesh *navMesh;
	//Vector3 position;
	NavMeshSetHeader header;
	String filename;
	ReadWriteLock rwLock;

public:
	RecastNavMesh(const String& filename, bool forceRebuild=false);
	RecastNavMesh() {
		navMesh = NULL;
	}

	~RecastNavMesh() {
		dtFreeNavMesh(navMesh);
	}

	void reloadNavmesh() {
		loadAll(filename);
	}

	void deleteFile();

	bool isLoaded() {
		return navMesh != NULL;
	}

	const NavMeshSetHeader& getMeshHeader() {
		return header;
	}

	dtNavMesh* getNavMesh() {
		return navMesh;
	}

    void setDetourNavMeshHeader(const NavMeshSetHeader& header) {
        this->header = header;
    }

	void setDetourNavMesh(dtNavMesh* navMesh) {
		this->navMesh = navMesh;
	}

	void setFileName(const String& name) {
		filename = name;
	}

	ReadWriteLock* getLock() { return &rwLock; }
};
#endif /* RECASTNAVMESH_H_ */
