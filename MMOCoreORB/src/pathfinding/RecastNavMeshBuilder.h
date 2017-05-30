//
// Copyright (c) 2009-2010 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#ifndef RECASTSAMPLETILEMESH_H
#define RECASTSAMPLETILEMESH_H

#include "engine/engine.h"
#include "pathfinding/recast/DetourNavMesh.h"
#include "pathfinding/recast/Recast.h"
#include "RecastPolygon.h"
#include "server/zone/Zone.h"
#include "terrain/manager/TerrainManager.h"
#include "pathfinding/RecastTileBuilder.h"

class RecastNavMesh;

class MeshData;

class RecastNavMeshBuilder : public Object, Logger {
protected:
	bool m_keepInterResults;
	bool m_buildAll;
	float m_totalBuildTimeMs;

	rcContext* m_ctx;
	RecastSettings settings;
	unsigned char* m_triareas;
	rcHeightfield* m_solid;
	rcCompactHeightfield* m_chf;
	rcContourSet* m_cset;
	rcPolyMesh* m_pmesh;
	rcPolyMeshDetail* m_dmesh;
	dtNavMesh* m_navMesh;

	int m_maxTiles;
	int m_maxPolysPerTile;
	Zone* zone;
	Reference<MeshData*> m_geom;
	AABB bounds;
	AABB lastTileBounds;
	int m_tileTriCount;
	String name;
	const AtomicBoolean* running;

	unsigned char* buildTileMesh(const int tx, const int ty, int& dataSize);

	virtual void rebuildArea(const AABB& buildArea);

	void cleanup();

	Vector <Reference<RecastPolygon*>> water;

	float waterTableHeight;
	bool destroyMesh;
	NavMeshSetHeader header;
public:
	void initialize(Vector <Reference<MeshData*>>& meshData, const AABB& bounds, float distanceBetweenHeights = 2);

	static Reference<MeshData*> flattenMeshData(Vector <Reference<MeshData*>>& data);

	static void dumpOBJ(const String& filename, Vector <Reference<MeshData*>>& data);

	static Reference<MeshData*>
	getTerrainMesh(Vector3& position, float terrainSize, TerrainManager* terrainManager, float chunkSize,
				   float distanceBetweenHeights);

	RecastNavMeshBuilder(Zone* zone, const String& name, const AtomicBoolean* jobStatus);

	virtual ~RecastNavMeshBuilder();

	virtual void changeMesh(MeshData* geom);

	inline void addWater(const Reference<RecastPolygon*>& waterBoundary) {
		water.add(waterBoundary);
	}

	virtual bool build();

	virtual void rebuildAreas(const Vector<AABB>& buildAreas, NavArea* navArea);

	void buildAllTiles();

	void buildAllTiles(const AABB& areaToRebuild);

	RecastSettings& getRecastConfig() {
		return settings;
	}

	const RecastSettings& getRecastConfig() const {
		return settings;
	}

	void setRecastConfig(const RecastSettings& config) {
		settings = config;
	}

	const NavMeshSetHeader& getNavMeshHeader() {
		return header;
	}

	dtNavMesh* getNavMesh() {
		destroyMesh = false;
		return m_navMesh;
	}


private:
	// Explicitly disabled copy constructor and copy assignment operator.
	RecastNavMeshBuilder(const RecastNavMeshBuilder&);

	RecastNavMeshBuilder& operator=(const RecastNavMeshBuilder&);
};


#endif // RECASTSAMPLETILEMESH_H
