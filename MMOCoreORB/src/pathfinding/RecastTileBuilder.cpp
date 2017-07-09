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

#include "RecastTileBuilder.h"
#include "pathfinding/recast/DetourNavMeshBuilder.h"
#include "templates/appearance/MeshData.h"
#include "ChunkyTriMesh.h"

inline unsigned int nextPow2(unsigned int v) {
	v--;
	v |= v>>1;
	v |= v>>2;
	v |= v>>4;
	v |= v>>8;
	v |= v>>16;
	v++;
	return v;
}

inline unsigned int ilog2(unsigned int v) {
	unsigned int r;
	unsigned int shift;
	r = (v > 0xffff)<<4;
	v >>= r;
	shift = (v > 0xff)<<3;
	v >>= shift;
	r |= shift;
	shift = (v > 0xf)<<2;
	v >>= shift;
	r |= shift;
	shift = (v > 0x3)<<1;
	v >>= shift;
	r |= shift;
	r |= (v>>1);
	return r;
}

RecastSettings::RecastSettings() {
	m_tileSize = 128.0f;
	m_cellSize = 0.15;            //buildSettings->cellSize;
	m_cellHeight = 0.15;        //buildSettings->cellHeight;
	m_agentHeight = 1.5f;        //buildSettings->agentHeight;
	m_agentRadius = 0.5f;        //buildSettings->agentRadius;
	m_agentMaxClimb = 0.75f;        //buildSettings->agentMaxClimb;
	m_agentMaxSlope = 85;        //buildSettings->agentMaxSlope;
	m_regionMinSize = 8;        //buildSettings->regionMinSize;
	m_regionMergeSize = 28;        //buildSettings->regionMergeSize;
	m_edgeMaxLen = 12;            //buildSettings->edgeMaxLen;
	m_edgeMaxError = 1.3;            //buildSettings->edgeMaxError;
	m_vertsPerPoly = 6;            //buildSettings->vertsPerPoly;
	m_detailSampleDist = 3;        //buildSettings->detailSampleDist;
	m_detailSampleMaxError = 1;    //buildSettings->detailSampleMaxError;
	m_partitionType = 0;        //buildSettings->partitionType;
	distanceBetweenPoles = 0;
}

RecastTileBuilder::RecastTileBuilder(float waterTableHeight, float x, float y, const AABB& bounds,
									 const rcChunkyTriMesh* mesh, const RecastSettings& settings) :
		m_keepInterResults(false),
		m_buildAll(true),
		m_totalBuildTimeMs(0),
		m_triareas(0),
		m_solid(0),
		m_chf(0),
		m_cset(0),
		m_pmesh(0),
		m_dmesh(0),
		m_maxTiles(0),
		m_maxPolysPerTile(0),
		bounds(Vector3(0, 0, 0), Vector3(0, 0, 0)),
		m_tileTriCount(0),
		waterTableHeight(waterTableHeight),
		lastTileBounds(bounds) {

	this->settings = settings;
	// Init build configuration from GUI
	memset(&m_cfg, 0, sizeof(m_cfg));
	m_cfg.cs = settings.m_cellSize;
	m_cfg.ch = settings.m_cellHeight;
	m_cfg.walkableSlopeAngle = settings.m_agentMaxSlope;
	m_cfg.walkableHeight = (int) ceilf(settings.m_agentHeight / m_cfg.ch);
	m_cfg.walkableClimb = (int) floorf(settings.m_agentMaxClimb / m_cfg.ch);
	m_cfg.walkableRadius = (int) ceilf(settings.m_agentRadius / m_cfg.cs);
	m_cfg.maxEdgeLen = (int) (settings.m_edgeMaxLen / settings.m_cellSize);
	m_cfg.maxSimplificationError = settings.m_edgeMaxError;
	m_cfg.minRegionArea = (int) rcSqr(settings.m_regionMinSize);        // Note: area = size*size
	m_cfg.mergeRegionArea = (int) rcSqr(settings.m_regionMergeSize);    // Note: area = size*size
	m_cfg.maxVertsPerPoly = (int) settings.m_vertsPerPoly;
	m_cfg.tileSize = (int) settings.m_tileSize;
	m_cfg.borderSize = m_cfg.walkableRadius + 3; // Reserve enough padding.
	m_cfg.width = m_cfg.tileSize + m_cfg.borderSize * 2;
	m_cfg.height = m_cfg.tileSize + m_cfg.borderSize * 2;
	m_cfg.detailSampleDist = settings.m_detailSampleDist < 0.9f ? 0 : settings.m_cellSize * settings.m_detailSampleDist;
	m_cfg.detailSampleMaxError = settings.m_cellHeight * settings.m_detailSampleMaxError;
	tileX = x;
	tileY = y;
	m_ctx = new rcContext();
	chunkyMesh = mesh;
}

RecastTileBuilder::~RecastTileBuilder() {
	m_geom = NULL;
	cleanup();
	delete m_ctx;
}

void RecastTileBuilder::cleanup() {
	delete[] m_triareas;
	m_triareas = 0;
	rcFreeHeightField(m_solid);
	m_solid = 0;
	rcFreeCompactHeightfield(m_chf);
	m_chf = 0;
	rcFreeContourSet(m_cset);
	m_cset = 0;
	rcFreePolyMesh(m_pmesh);
	m_pmesh = 0;
	rcFreePolyMeshDetail(m_dmesh);
	m_dmesh = 0;
}

unsigned char* RecastTileBuilder::build(float x, float y, const AABB& lastTileBounds, int& dataSize) {

	int gw = 0, gh = 0;

	float bmin[3];
	float bmax[3];

	bmin[0] = bounds.getXMin();
	bmin[1] = bounds.getYMin();
	bmin[2] = bounds.getZMin();


	bmax[0] = bounds.getXMax();
	bmax[1] = bounds.getYMax();
	bmax[2] = bounds.getZMax();

	rcCalcGridSize(bmin, bmax, settings.m_cellSize, &gw, &gh);
	const int ts = (int) settings.m_tileSize;
	const int tw = (gw + ts - 1) / ts;
	const int th = (gh + ts - 1) / ts;

	// Max tiles and max polys affect how the tile IDs are caculated.
	// There are 22 bits available for identifying a tile and a polygon.
	int tileBits = rcMin((int) ilog2(nextPow2(tw * th)), 14);
	int polyBits = 22 - tileBits;
	m_maxTiles = 1<<tileBits;
	m_maxPolysPerTile = 1<<polyBits;

	dtNavMeshParams params;
	params.orig[0] = bounds.getXMin();
	params.orig[1] = bounds.getYMin();
	params.orig[2] = bounds.getZMin();

	//rcVcopy(params.orig, m_geom->getNavMeshBoundsMin());
	params.tileWidth = settings.m_tileSize * settings.m_cellSize;
	params.tileHeight = settings.m_tileSize * settings.m_cellSize;
	params.maxTiles = m_maxTiles;
	params.maxPolys = m_maxPolysPerTile;

	dtStatus status;
	this->lastTileBounds = lastTileBounds;
	return buildTileMesh(x, y, dataSize);
}

void RecastTileBuilder::getTilePos(const Vector3& pos, int& tx, int& ty) {
	if (!m_geom) return;

	const Vector3& bmin = *bounds.getMinBound();

	const float ts = settings.m_tileSize * settings.m_cellSize;
	tx = (int) ((pos.getX() - bmin.getX()) / ts);
	ty = (int) ((pos.getZ() - bmin.getZ()) / ts);
}

unsigned char* RecastTileBuilder::buildTileMesh(const int tx, const int ty, int& dataSize) {
	const Vector3& bmin = *lastTileBounds.getMinBound();
	const Vector3& bmax = *lastTileBounds.getMaxBound();

	cleanup();

	// Expand the heighfield bounding box by border size to find the extents of geometry we need to build this tile.
	//
	// This is done in order to make sure that the navmesh tiles connect correctly at the borders,
	// and the obstacles close to the border work correctly with the dilation process.
	// No polygons (or contours) will be created on the border area.
	//
	// IMPORTANT!
	//
	//   :''''''''':
	//   : +-----+ :
	//   : |     | :
	//   : |     |<--- tile to build
	//   : |     | :
	//   : +-----+ :<-- geometry needed
	//   :.........:
	//
	// You should use this bounding box to query your input geometry.
	//
	// For example if you build a navmesh for terrain, and want the navmesh tiles to match the terrain tile size
	// you will need to pass in data from neighbour terrain tiles too! In a simple case, just pass in all the 8 neighbours,
	// or use the bounding box below to only pass in a sliver of each of the 8 neighbours.

	m_cfg.bmin[0] = lastTileBounds.getXMin();
	m_cfg.bmin[1] = lastTileBounds.getYMin();
	m_cfg.bmin[2] = lastTileBounds.getZMin();


	m_cfg.bmax[0] = lastTileBounds.getXMax();
	m_cfg.bmax[1] = lastTileBounds.getYMax();
	m_cfg.bmax[2] = lastTileBounds.getZMax();

	//rcVcopy(m_cfg.bmin, bmin);
	//rcVcopy(m_cfg.bmax, bmax);
	m_cfg.bmin[0] -= m_cfg.borderSize * m_cfg.cs;
	m_cfg.bmin[2] -= m_cfg.borderSize * m_cfg.cs;
	m_cfg.bmax[0] += m_cfg.borderSize * m_cfg.cs;
	m_cfg.bmax[2] += m_cfg.borderSize * m_cfg.cs;

	// Allocate voxel heightfield where we rasterize our input data to.
	m_solid = rcAllocHeightfield();
	if (!m_solid) {
		error("buildNavigation: Out of memory 'solid'.");
		return 0;
	}

	if (!rcCreateHeightfield(m_ctx, *m_solid, m_cfg.width, m_cfg.height, m_cfg.bmin, m_cfg.bmax, m_cfg.cs, m_cfg.ch)) {
		error("buildNavigation: Could not create solid heightfield.");
		return 0;
	}

	// Allocate array that can hold triangle flags.
	// If you have multiple meshes you need to process, allocate
	// and array which can hold the max number of triangles you need to process.
	m_triareas = new unsigned char[chunkyMesh->maxTrisPerChunk];
	if (!m_triareas) {
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'm_triareas' (%d).", chunkyMesh->maxTrisPerChunk);
		return 0;
	}

	float tbmin[2], tbmax[2];
	tbmin[0] = m_cfg.bmin[0];
	tbmin[1] = m_cfg.bmin[2];
	tbmax[0] = m_cfg.bmax[0];
	tbmax[1] = m_cfg.bmax[2];
	int cid[512];// TODO: Make grow when returning too many items.
	const int ncid = rcGetChunksOverlappingRect(chunkyMesh, tbmin, tbmax, cid, 512);

	if (!ncid) {
		return 0;
	}

	const Vector <Vector3>* vertArray = m_geom->getVerts();

	const int nverts = vertArray->size();
	float* verts = new float[nverts * 3];//m_geom->getMesh()->getVerts();

	for (int i = 0; i < nverts; i++) {
		const Vector3& vert = vertArray->getUnsafe(i);
		verts[i * 3 + 0] = vert.getX();
		verts[i * 3 + 1] = vert.getY();
		verts[i * 3 + 2] = vert.getZ();
	}

	m_tileTriCount = 0;

	for (int i = 0; i < ncid; ++i) {
		const rcChunkyTriMeshNode& node = chunkyMesh->nodes[cid[i]];
		const int* ctris = &chunkyMesh->tris[node.i * 3];
		const int nctris = node.n;

		m_tileTriCount += nctris;

		memset(m_triareas, 0, nctris * sizeof(unsigned char));
		rcMarkWalkableTriangles(m_ctx, m_cfg.walkableSlopeAngle,
								verts, nverts, ctris, nctris, m_triareas);

		if (!rcRasterizeTriangles(m_ctx, verts, nverts, ctris, m_triareas, nctris, *m_solid, m_cfg.walkableClimb)) {
			delete[] verts;
			return 0;
		}
	}

	delete[] verts;

	if (!m_keepInterResults) {
		delete[] m_triareas;
		m_triareas = 0;
	}

	// Once all geometry is rasterized, we do initial pass of filtering to
	// remove unwanted overhangs caused by the conservative rasterization
	// as well as filter spans where the character cannot possibly stand.
	rcFilterLowHangingWalkableObstacles(m_ctx, m_cfg.walkableClimb, *m_solid);
	rcFilterLedgeSpans(m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid);
	rcFilterWalkableLowHeightSpans(m_ctx, m_cfg.walkableHeight, *m_solid);

	// Compact the heightfield so that it is faster to handle from now on.
	// This will result more cache coherent data as well as the neighbours
	// between walkable cells will be calculated.
	m_chf = rcAllocCompactHeightfield();
	if (!m_chf) {
		error("buildNavigation: Out of memory 'chf'.");
		return 0;
	}

	if (!rcBuildCompactHeightfield(m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid, *m_chf)) {
		error("buildNavigation: Could not build compact data.");
		return 0;
	}

	rcFreeHeightField(m_solid);
	m_solid = 0;


	// Erode the walkable area by agent radius.
	if (!rcErodeWalkableArea(m_ctx, m_cfg.walkableRadius, *m_chf)) {
		error("buildNavigation: Could not erode.");
		return 0;
	}

	// (Optional) Mark areas.
	for (int i = 0; i < water.size(); ++i) {
		Reference < RecastPolygon * > poly = water.get(i);
		rcMarkConvexPolyArea(m_ctx, poly->verts, poly->numVerts, poly->hmin, poly->hmax, poly->type, *m_chf);
	}

	float min[3], max[3];
	min[0] = bmin.getX();
	min[1] = bmin.getY();
	min[2] = bmin.getZ();

	max[0] = bmax.getX();
	max[1] = waterTableHeight;
	max[2] = bmax.getZ();

	rcMarkBoxArea(m_ctx, min, max, SAMPLE_POLYAREA_WATER, *m_chf);


	rcMedianFilterWalkableArea(m_ctx, *m_chf);

	// Partition the heightfield so that we can use simple algorithm later to triangulate the walkable areas.
	// There are 3 martitioning methods, each with some pros and cons:
	// 1) Watershed partitioning
	//   - the classic Recast partitioning
	//   - creates the nicest tessellation
	//   - usually slowest
	//   - partitions the heightfield into nice regions without holes or overlaps
	//   - the are some corner cases where this method creates produces holes and overlaps
	//      - holes may appear when a small obstacles is close to large open area (triangulation can handle this)
	//      - overlaps may occur if you have narrow spiral corridors (i.e stairs), this make triangulation to fail
	//   * generally the best choice if you precompute the nacmesh, use this if you have large open areas
	// 2) Monotone partioning
	//   - fastest
	//   - partitions the heightfield into regions without holes and overlaps (guaranteed)
	//   - creates long thin polygons, which sometimes causes paths with detours
	//   * use this if you want fast navmesh generation
	// 3) Layer partitoining
	//   - quite fast
	//   - partitions the heighfield into non-overlapping regions
	//   - relies on the triangulation code to cope with holes (thus slower than monotone partitioning)
	//   - produces better triangles than monotone partitioning
	//   - does not have the corner cases of watershed partitioning
	//   - can be slow and create a bit ugly tessellation (still better than monotone)
	//     if you have large open areas with small obstacles (not a problem if you use tiles)
	//   * good choice to use for tiled navmesh with medium and small sized tiles

	if (settings.m_partitionType == 0) {
		// Prepare for region partitioning, by calculating distance field along the walkable surface.
		if (!rcBuildDistanceField(m_ctx, *m_chf)) {
			error("buildNavigation: Could not build distance field.");
			return 0;
		}

		// Partition the walkable surface into simple regions without holes.
		if (!rcBuildRegions(m_ctx, *m_chf, m_cfg.borderSize, m_cfg.minRegionArea, m_cfg.mergeRegionArea)) {
			error("buildNavigation: Could not build watershed regions.");
			return 0;
		}
	} else if (settings.m_partitionType == 1) {
		// Partition the walkable surface into simple regions without holes.
		// Monotone partitioning does not need distancefield.
		if (!rcBuildRegionsMonotone(m_ctx, *m_chf, m_cfg.borderSize, m_cfg.minRegionArea, m_cfg.mergeRegionArea)) {
			error("buildNavigation: Could not build monotone regions.");
			return 0;
		}
	} else // SAMPLE_PARTITION_LAYERS
	{
		// Partition the walkable surface into simple regions without holes.
		if (!rcBuildLayerRegions(m_ctx, *m_chf, m_cfg.borderSize, m_cfg.minRegionArea)) {
			error("buildNavigation: Could not build layer regions.");
			return 0;
		}
	}

	// Create contours.
	m_cset = rcAllocContourSet();
	if (!m_cset) {
		error("buildNavigation: Out of memory 'cset'.");
		return 0;
	}

	if (!rcBuildContours(m_ctx, *m_chf, m_cfg.maxSimplificationError, m_cfg.maxEdgeLen, *m_cset)) {
		error("buildNavigation: Could not create contours.");
		return 0;
	}

	if (m_cset->nconts == 0) {
		return 0;
	}

	// Build polygon navmesh from the contours.
	m_pmesh = rcAllocPolyMesh();
	if (!m_pmesh) {
		error("buildNavigation: Out of memory 'pmesh'.");
		return 0;
	}

	if (!rcBuildPolyMesh(m_ctx, *m_cset, m_cfg.maxVertsPerPoly, *m_pmesh)) {
		error("buildNavigation: Could not triangulate contours.");
		return 0;
	}

	// Build detail mesh.
	m_dmesh = rcAllocPolyMeshDetail();
	if (!m_dmesh) {
		error("buildNavigation: Out of memory 'dmesh'.");
		return 0;
	}

	if (!rcBuildPolyMeshDetail(m_ctx, *m_pmesh, *m_chf,
							   m_cfg.detailSampleDist, m_cfg.detailSampleMaxError,
							   *m_dmesh)) {
		error("buildNavigation: Could build polymesh detail.");
		return 0;
	}

	rcFreeCompactHeightfield(m_chf);
	m_chf = 0;
	rcFreeContourSet(m_cset);
	m_cset = 0;


	unsigned char* navData = 0;
	int navDataSize = 0;
	if (m_cfg.maxVertsPerPoly <= DT_VERTS_PER_POLYGON) {
		if (m_pmesh->nverts >= 0xffff) {
			// The vertex indices are ushorts, and cannot point to more than 0xffff vertices.
			error("Too many vertices per tile");
			return 0;
		}

		// Update poly flags from areas.
		for (int i = 0; i < m_pmesh->npolys; ++i) {
			if (m_pmesh->areas[i] == RC_WALKABLE_AREA)
				m_pmesh->areas[i] = SAMPLE_POLYAREA_GROUND;

			if (m_pmesh->areas[i] == SAMPLE_POLYAREA_GROUND ||
				m_pmesh->areas[i] == SAMPLE_POLYAREA_GRASS ||
				m_pmesh->areas[i] == SAMPLE_POLYAREA_ROAD) {
				m_pmesh->flags[i] = SAMPLE_POLYFLAGS_WALK;
			} else if (m_pmesh->areas[i] == SAMPLE_POLYAREA_WATER) {
				m_pmesh->flags[i] = SAMPLE_POLYFLAGS_SWIM;
			} else if (m_pmesh->areas[i] == SAMPLE_POLYAREA_DOOR) {
				m_pmesh->flags[i] = SAMPLE_POLYFLAGS_WALK | SAMPLE_POLYFLAGS_DOOR;
			}
		}

		dtNavMeshCreateParams params;
		memset(&params, 0, sizeof(params));
		params.verts = m_pmesh->verts;
		params.vertCount = m_pmesh->nverts;
		params.polys = m_pmesh->polys;
		params.polyAreas = m_pmesh->areas;
		params.polyFlags = m_pmesh->flags;
		params.polyCount = m_pmesh->npolys;
		params.nvp = m_pmesh->nvp;
		params.detailMeshes = m_dmesh->meshes;
		params.detailVerts = m_dmesh->verts;
		params.detailVertsCount = m_dmesh->nverts;
		params.detailTris = m_dmesh->tris;
		params.detailTriCount = m_dmesh->ntris;
		params.offMeshConVerts = NULL;//m_geom->getOffMeshConnectionVerts();
		params.offMeshConRad = NULL;//m_geom->getOffMeshConnectionRads();
		params.offMeshConDir = NULL;//m_geom->getOffMeshConnectionDirs();
		params.offMeshConAreas = NULL;//m_geom->getOffMeshConnectionAreas();
		params.offMeshConFlags = NULL;//m_geom->getOffMeshConnectionFlags();
		params.offMeshConUserID = NULL;//m_geom->getOffMeshConnectionId();
		params.offMeshConCount = 0;//m_geom->getOffMeshConnectionCount();
		params.walkableHeight = settings.m_agentHeight;
		params.walkableRadius = settings.m_agentRadius;
		params.walkableClimb = settings.m_agentMaxClimb;
		params.tileX = tx;
		params.tileY = ty;
		params.tileLayer = 0;
		rcVcopy(params.bmin, m_pmesh->bmin);
		rcVcopy(params.bmax, m_pmesh->bmax);
		params.cs = m_cfg.cs;
		params.ch = m_cfg.ch;
		params.buildBvTree = true;


		if (!dtCreateNavMeshData(&params, &navData, &navDataSize)) {
			error("Could not build Detour navmesh.");
			return 0;
		}
	}
	//m_tileMemUsage = navDataSize/1024.0f;

	m_ctx->stopTimer(RC_TIMER_TOTAL);

	// Show performance stats.
	//duLogBuildTimes(*m_ctx, m_ctx->getAccumulatedTime(RC_TIMER_TOTAL));
	//m_ctx->log(RC_LOG_PROGRESS, ">> Polymesh: %d vertices  %d polygons", m_pmesh->nverts, m_pmesh->npolys);

	//m_tileBuildTime = m_ctx->getAccumulatedTime(RC_TIMER_TOTAL)/1000.0f;

	dataSize = navDataSize;
	return navData;
}

void RecastTileBuilder::changeMesh(MeshData* geom) {
	cleanup();

	m_geom = geom;
	bounds = geom->buildAABB();
}
