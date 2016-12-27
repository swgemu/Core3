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

#ifndef RECASTTILEBUILDER_H_
#define RECASTTILEBUILDER_H_

#include "engine/engine.h"
#include "pathfinding/recast/DetourNavMesh.h"
#include "pathfinding/recast/Recast.h"

#include "RecastPolygon.h"

class MeshData;

struct rcChunkyTriMesh;

static const int NAVMESHSET_MAGIC = 'M'<<24 | 'S'<<16 | 'E'<<8 | 'T'; //'MSET';
static const int NAVMESHSET_VERSION = 1;

struct NavMeshSetHeader {
	int magic;
	int version;
	int numTiles;
	dtNavMeshParams params;
};

struct NavMeshTileHeader {
	dtTileRef tileRef;
	int dataSize;
};


class RecastSettings {
public:
	float m_cellHeight;
	float m_agentHeight;
	float m_agentRadius;
	float m_agentMaxClimb;
	float m_agentMaxSlope;
	float m_regionMinSize;
	float m_regionMergeSize;
	float m_edgeMaxLen;
	float m_edgeMaxError;
	float m_vertsPerPoly;
	float m_detailSampleDist;
	float m_detailSampleMaxError;
	float m_tileSize;
	float m_cellSize;
	int m_partitionType;

	float distanceBetweenPoles;

	RecastSettings();
};

class RecastTileBuilder : public Logger {

protected:
	bool m_keepInterResults;
	bool m_buildAll;
	float m_totalBuildTimeMs;

	RecastSettings settings;
	rcContext* m_ctx;
	const rcChunkyTriMesh* chunkyMesh;

	unsigned char* m_triareas;
	rcHeightfield* m_solid;
	rcCompactHeightfield* m_chf;
	rcContourSet* m_cset;
	rcPolyMesh* m_pmesh;
	rcPolyMeshDetail* m_dmesh;
	rcConfig m_cfg;

	int m_maxTiles;
	int m_maxPolysPerTile;
	Reference<MeshData*> m_geom;
	AABB bounds;
	int m_tileTriCount;

	unsigned char* buildTileMesh(const int tx, const int ty, int& dataSize);

	void cleanup();

	Vector <Reference<RecastPolygon*>> water;

	//void buildTile(const Vector3& pos);
	void getTilePos(const Vector3& pos, int& tx, int& ty);

	float waterTableHeight;
	float tileX, tileY;
	AABB lastTileBounds;
public:
	void saveAll(const String& file);

	RecastTileBuilder(float waterTableHeight, float x, float y, const AABB& bounds, const rcChunkyTriMesh* mesh,
					  const RecastSettings& settings);

	virtual ~RecastTileBuilder();

	virtual void changeMesh(MeshData* geom);

	inline void setWater(const Vector<Reference<RecastPolygon*> >& waterBoundaries) {
		water = waterBoundaries;
	}

	virtual unsigned char* build(float x, float y, const AABB& tileBounds, int& dataSize);



	//
private:
	// Explicitly disabled copy constructor and copy assignment operator.
	RecastTileBuilder(const RecastTileBuilder&);

	RecastTileBuilder& operator=(const RecastTileBuilder&);
};


#endif // RECASTTILEBUILDER_H_
