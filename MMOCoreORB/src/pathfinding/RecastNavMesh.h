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
	void loadAll(ObjectInputStream* stream);
	void saveAll(ObjectOutputStream* stream);

	dtNavMesh *navMesh;
	NavMeshSetHeader header;
	String name;

public:
	RecastNavMesh() : Logger("RecastNavMesh"), header() {
		navMesh = NULL;
	}

	~RecastNavMesh() {
		dtFreeNavMesh(navMesh);
	}

	bool toBinaryStream(ObjectOutputStream* stream);

	bool parseFromBinaryStream(ObjectInputStream* stream);

	bool isLoaded() const {
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

	void setName(const String& name) {
		this->name = name;
		Logger::setLoggingName("RecastNavMesh " + name);
	}

	void setupDetourNavMeshHeader();

	void copyMeshTo(dtNavMesh* mesh);

	void saveToFile();
};
#endif /* RECASTNAVMESH_H_ */
