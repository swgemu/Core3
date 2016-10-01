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

#include "RecastNavMeshBuilder.h"
#include "pathfinding/recast/Recast.h"
#include "pathfinding/recast/DetourNavMesh.h"
#include "pathfinding/recast/DetourNavMeshBuilder.h"
#include "pathfinding/recast/DetourNavMeshQuery.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "templates/appearance/MeshData.h"
#include "ChunkyTriMesh.h"
#include "terrain/layer/boundaries/BoundaryRectangle.h"
#include "terrain/layer/boundaries/BoundaryPolygon.h"

inline unsigned int nextPow2(unsigned int v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

inline unsigned int ilog2(unsigned int v)
{
	unsigned int r;
	unsigned int shift;
	r = (v > 0xffff) << 4; v >>= r;
	shift = (v > 0xff) << 3; v >>= shift; r |= shift;
	shift = (v > 0xf) << 2; v >>= shift; r |= shift;
	shift = (v > 0x3) << 1; v >>= shift; r |= shift;
	r |= (v >> 1);
	return r;
}

RecastNavMeshBuilder::RecastNavMeshBuilder(Zone* zone, String name) :
Logger(name),
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
lastTileBounds(Vector3(0, 0, 0), Vector3(0, 0, 0)),
m_tileTriCount(0)
{
	
	waterTableHeight = zone->getPlanetManager()->getTerrainManager()->getProceduralTerrainAppearance()->getGlobalWaterTableHeight();
	settings.m_tileSize = 128.0f;
	settings.m_cellSize = 0.15;			//buildSettings->cellSize;
	settings.m_cellHeight = 0.15;		//buildSettings->cellHeight;
	settings.m_agentHeight = 1.5f;		//buildSettings->agentHeight;
	settings.m_agentRadius = 0.5f;		//buildSettings->agentRadius;
	settings.m_agentMaxClimb = 0.75f;		//buildSettings->agentMaxClimb;
	settings.m_agentMaxSlope = 85;		//buildSettings->agentMaxSlope;
	settings.m_regionMinSize = 8;		//buildSettings->regionMinSize;
	settings.m_regionMergeSize = 28;		//buildSettings->regionMergeSize;
	settings.m_edgeMaxLen = 12;			//buildSettings->edgeMaxLen;
	settings.m_edgeMaxError = 1.3;			//buildSettings->edgeMaxError;
	settings.m_vertsPerPoly = 6;			//buildSettings->vertsPerPoly;
	settings.m_detailSampleDist = 3;		//buildSettings->detailSampleDist;
	settings.m_detailSampleMaxError = 1;	//buildSettings->detailSampleMaxError;
	settings.m_partitionType = 0;		//buildSettings->partitionType;
	this->name = name;
	this->zone = zone;
	m_navMesh = NULL;
	m_ctx = new rcContext();
	destroyMesh = true;
}

RecastNavMeshBuilder::~RecastNavMeshBuilder()
{
	m_geom = NULL;
	cleanup();
	if(destroyMesh) {
		dtFreeNavMesh(m_navMesh);
		m_navMesh = 0;
	}
	delete m_ctx;
}

void RecastNavMeshBuilder::cleanup()
{
	delete [] m_triareas;
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


void RecastNavMeshBuilder::saveAll(const String& path)
{
	const dtNavMesh* mesh = m_navMesh;
	if (!mesh) return;
	
	FILE* fp = fopen(path.toCharArray(), "wb");
	if (!fp)
		return;
	
	// Store header.
	NavMeshSetHeader header;
	header.magic = NAVMESHSET_MAGIC;
	header.version = NAVMESHSET_VERSION;
	header.numTiles = 0;
	for (int i = 0; i < mesh->getMaxTiles(); ++i)
	{
		const dtMeshTile* tile = mesh->getTile(i);
		if (!tile || !tile->header || !tile->dataSize) continue;
		header.numTiles++;
	}
	memcpy(&header.params, mesh->getParams(), sizeof(dtNavMeshParams));
	fwrite(&header, sizeof(NavMeshSetHeader), 1, fp);
	
	// Store tiles.
	for (int i = 0; i < mesh->getMaxTiles(); ++i)
	{
		const dtMeshTile* tile = mesh->getTile(i);
		if (!tile || !tile->header || !tile->dataSize) continue;
		
		NavMeshTileHeader tileHeader;
		tileHeader.tileRef = mesh->getTileRef(tile);
		tileHeader.dataSize = tile->dataSize;
		fwrite(&tileHeader, sizeof(tileHeader), 1, fp);
		
		fwrite(tile->data, tile->dataSize, 1, fp);
	}
	
	fclose(fp);
}

//void Sample_TileMesh::handleSettings()
//{
//	Sample::handleCommonSettings();
//	
//	if (imguiCheck("Keep Itermediate Results", m_keepInterResults))
//		m_keepInterResults = !m_keepInterResults;
//	
//	if (imguiCheck("Build All Tiles", m_buildAll))
//		m_buildAll = !m_buildAll;
//	
//	imguiLabel("Tiling");
//	imguiSlider("TileSize", &m_tileSize, 16.0f, 1024.0f, 16.0f);
//	
//	if (m_geom)
//	{
//		char text[64];
//		int gw = 0, gh = 0;
//		const float* bmin = m_geom->getNavMeshBoundsMin();
//		const float* bmax = m_geom->getNavMeshBoundsMax();
//		rcCalcGridSize(bmin, bmax, m_cellSize, &gw, &gh);
//		const int ts = (int)m_tileSize;
//		const int tw = (gw + ts-1) / ts;
//		const int th = (gh + ts-1) / ts;
//		snprintf(text, 64, "Tiles  %d x %d", tw, th);
//		imguiValue(text);
//		
//		// Max tiles and max polys affect how the tile IDs are caculated.
//		// There are 22 bits available for identifying a tile and a polygon.
//		int tileBits = rcMin((int)ilog2(nextPow2(tw*th)), 14);
//		if (tileBits > 14) tileBits = 14;
//		int polyBits = 22 - tileBits;
//		m_maxTiles = 1 << tileBits;
//		m_maxPolysPerTile = 1 << polyBits;
//		snprintf(text, 64, "Max Tiles  %d", m_maxTiles);
//		imguiValue(text);
//		snprintf(text, 64, "Max Polys  %d", m_maxPolysPerTile);
//		imguiValue(text);
//	}
//	else
//	{
//		m_maxTiles = 0;
//		m_maxPolysPerTile = 0;
//	}
//	
//	imguiSeparator();
//	
//	imguiIndent();
//	imguiIndent();
//	
//	if (imguiButton("Save"))
//	{
//		saveAll("all_tiles_navmesh.bin", m_navMesh);
//	}
//	
//	if (imguiButton("Load"))
//	{
//		dtFreeNavMesh(m_navMesh);
//		m_navMesh = loadAll("all_tiles_navmesh.bin");
//		m_navQuery->init(m_navMesh, 2048);
//	}
//	
//	imguiUnindent();
//	imguiUnindent();
//	
//	char msg[64];
//	snprintf(msg, 64, "Build Time: %.1fms", m_totalBuildTimeMs);
//	imguiLabel(msg);
//	
//	imguiSeparator();
//	
//	imguiSeparator();
//	
//}

bool RecastNavMeshBuilder::rebuildArea(AABB area, RecastNavMesh* existingMesh) {
	
	
	destroyMesh = false;
	float longest = area.extents()[area.longestAxis()];
	longest = MAX(settings.m_tileSize*settings.m_cellSize*2.25, longest);
	
	
	Vector3 center = area.midPoint();
	//un-fucking (or re-fucking) our coordinate system
	area = AABB(Vector3(center.getX()-longest, -100000, -center.getY()-longest), Vector3(center.getX()+longest, 100000, -center.getY()+longest));
	
	m_navMesh = existingMesh->getNavMesh();
	if (!m_navMesh)
		return false;
	
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
	const int ts = (int)settings.m_tileSize;
	const int tw = (gw + ts-1) / ts;
	const int th = (gh + ts-1) / ts;
	
	// Max tiles and max polys affect how the tile IDs are caculated.
	// There are 22 bits available for identifying a tile and a polygon.
	int tileBits = rcMin((int)ilog2(nextPow2(tw*th)), 14);
	if (tileBits > 14) tileBits = 14;
	int polyBits = 22 - tileBits;
	m_maxTiles = 1 << tileBits;
	m_maxPolysPerTile = 1 << polyBits;
	
	if (!m_geom) return false;
	if (!m_navMesh) return false;
	
	buildAllTiles(area);
	return true;
}

bool RecastNavMeshBuilder::build()
{
	
	dtFreeNavMesh(m_navMesh);
	
	if (m_navMesh) {
		dtFreeNavMesh(m_navMesh);
	}
	
	m_navMesh = dtAllocNavMesh();
	destroyMesh = true;
	if (!m_navMesh)
	{
		error("buildTiledNavigation: Could not allocate navmesh.");
		return false;
	}
	
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
	const int ts = (int)settings.m_tileSize;
	const int tw = (gw + ts-1) / ts;
	const int th = (gh + ts-1) / ts;
	
	// Max tiles and max polys affect how the tile IDs are caculated.
	// There are 22 bits available for identifying a tile and a polygon.
	int tileBits = rcMin((int)ilog2(nextPow2(tw*th)), 14);
	if (tileBits > 14) tileBits = 14;
	int polyBits = 22 - tileBits;
	m_maxTiles = 1 << tileBits;
	m_maxPolysPerTile = 1 << polyBits;
	
	dtNavMeshParams params;
	params.orig[0] = bounds.getXMin();
	params.orig[1] = bounds.getYMin();
	params.orig[2] = bounds.getZMin();
	
	//rcVcopy(params.orig, m_geom->getNavMeshBoundsMin());
	params.tileWidth = settings.m_tileSize*settings.m_cellSize;
	params.tileHeight = settings.m_tileSize*settings.m_cellSize;
	params.maxTiles = m_maxTiles;
	params.maxPolys = m_maxPolysPerTile;
	
	dtStatus status;
	
	status = m_navMesh->init(&params);
	if (dtStatusFailed(status))
	{
		error("buildTiledNavigation: Could not init navmesh.");
		return false;
	}
	
	if (m_buildAll)
		buildAllTiles();
	
	return true;
}



void RecastNavMeshBuilder::buildTile(const Vector3& pos)
{
	if (!m_geom) return;
	if (!m_navMesh) return;
	
	const Vector3& bmin = *bounds.getMinBound();
	const Vector3& bmax = *bounds.getMaxBound();
	
	const float ts = settings.m_tileSize*settings.m_cellSize;
	const int tx = (int)((pos.getX() - bmin.getX()) / ts);
	const int ty = (int)((pos.getZ() - bmin.getZ()) / ts);
	
	float minx = bmin[0] + tx*ts;
	float miny = bmin[1];
	float minz = bmin[2] + ty*ts;
	
	float maxx = bmin[0] + (tx+1)*ts;
	float maxy = bmax[1];
	float maxz = bmin[2] + (ty+1)*ts;
	
	lastTileBounds = AABB(Vector3(minx, miny, minz), Vector3(maxx, maxy, maxz));
	
	m_ctx->resetLog();
	
	int dataSize = 0;
	unsigned char* data = buildTileMesh(tx, ty, dataSize);
	
	// Remove any previous data (navmesh owns and deletes the data).
	m_navMesh->removeTile(m_navMesh->getTileRefAt(tx,ty,0),0,0);
	
	// Add tile, or leave the location empty.
	if (data)
	{
		// Let the navmesh own the data.
		dtStatus status = m_navMesh->addTile(data,dataSize,DT_TILE_FREE_DATA,0,0);
		if (dtStatusFailed(status))
			dtFree(data);
	}
	
	//m_ctx->dumpLog("Build Tile (%d,%d):", tx,ty);
}

void RecastNavMeshBuilder::getTilePos(const Vector3& pos, int& tx, int& ty)
{
	if (!m_geom) return;
	
	const Vector3& bmin = *bounds.getMinBound();
	
	const float ts = settings.m_tileSize*settings.m_cellSize;
	tx = (int)((pos.getX() - bmin.getX()) / ts);
	ty = (int)((pos.getZ() - bmin.getZ()) / ts);
}

void RecastNavMeshBuilder::buildAllTiles(AABB area)
{
	if (!m_geom) return;
	if (!m_navMesh) return;
	
	const Vector<Vector3>* vertArray = m_geom->getVerts();
	const Vector<MeshTriangle>* triArray = m_geom->getTriangles();
	
	const int nverts = vertArray->size();
	float* verts = new float[nverts*3];//m_geom->getMesh()->getVerts();
	
	int* tris = new int[triArray->size()*3];
	for(int i=0; i<nverts; i++) {
		const Vector3& vert = vertArray->get(i);
		verts[i*3+0] = vert.getX();
		verts[i*3+1] = vert.getY();
		verts[i*3+2] = vert.getZ();
	}
	
	for(int i=0; i<triArray->size(); i++) {
		memcpy(tris+(i*3), triArray->get(i).getVerts(), sizeof(int)*3);
	}
	
	float bmin[3];
	float bmax[3];
	
	bmin[0] = bounds.getXMin();
	bmin[1] = bounds.getYMin();
	bmin[2] = bounds.getZMin();
	
	
	bmax[0] = bounds.getXMax();
	bmax[1] = bounds.getYMax();
	bmax[2] = bounds.getZMax();
	int gw = 0, gh = 0;
	rcCalcGridSize(bmin, bmax, settings.m_cellSize, &gw, &gh);
	const int ts = (int)settings.m_tileSize;
	int tw = (gw + ts-1) / ts;
	int th = (gh + ts-1) / ts;
	const float tcs = settings.m_tileSize*settings.m_cellSize;
	
	rcChunkyTriMesh mesh;
	rcCreateChunkyTriMesh(verts, tris, triArray->size(), 256, &mesh);
	const rcChunkyTriMesh* chunkyMesh = &mesh;
	// Start the build process.
	
	AtomicInteger jobStatus;
	AtomicInteger progress;
	
	delete[] tris;
	delete[] verts;
	
	RecastTileBuilder builder(waterTableHeight, 0, 0, lastTileBounds, chunkyMesh, settings);
	builder.changeMesh(m_geom);
	for(auto& a : water)
		builder.addWater(a);
	
	info("Bounds: " + bounds.getMinBound()->toString() + " | " + bounds.getMaxBound()->toString() + "\n", true);
	
	float zStart = (fabs(bounds.getZMin() - area.getZMin()) / tcs) - 1.0f;
	float xStart = (fabs(bounds.getXMin() - area.getXMin()) / tcs) - 1.0f;

	th = ceil((fabs(bounds.getZMin() - area.getZMax()) / tcs) + 1.0f);
	tw = ceil((fabs(bounds.getXMin() - area.getXMax()) / tcs) + 1.0f);


	if ( zStart < 0 || xStart < 0)
		return;
	
	for (int y = floor(zStart); y < th; ++y)
	{
		float zTileStart = bmin[2] + ((y+1) * tcs);
		//info("zStart: " + String::valueOf(zTileStart), true);
		if(zTileStart < area.getZMin() || zTileStart > area.getZMax())
			continue;
		
		for (int x = floor(xStart); x < tw; ++x)
		{
			
			

			float xTileStart = bmin[0] + ((x+1) * tcs);
			//info("xStart: " + String::valueOf(xTileStart), true);
			if(xTileStart < area.getXMin() || xTileStart > area.getXMax())
				continue;
			
			
			
			float minx = bmin[0] + x*tcs;
			float miny = bmin[1];
			float minz = bmin[2] + y*tcs;
			
			float maxx = bmin[0] + (x+1)*tcs;
			float maxy = bmax[1];
			float maxz = bmin[2] + (y+1)*tcs;
			lastTileBounds = AABB(Vector3(minx, miny, minz), Vector3(maxx, maxy, maxz));
			
			info("BuiltTile : " + lastTileBounds.getMinBound()->toString() + " | " + lastTileBounds.getMaxBound()->toString() + "\n", false);
			int dataSize = 0;
			unsigned char* data = builder.build(x, y, lastTileBounds, dataSize);//buildTileMesh(x, y, dataSize);
			if (data)
			{
				// Remove any previous data (navmesh owns and deletes the data).
				m_navMesh->removeTile(m_navMesh->getTileRefAt(x,y,0),0,0);
				// Let the navmesh own the data.
				dtStatus status = m_navMesh->addTile(data,dataSize,DT_TILE_FREE_DATA,0,0);
				if (dtStatusFailed(status)) {
					info("dtStatusFailed", true);
					dtFree(data);
				}
			} else {
				info("No data", true);
			}
			
			
		}
		progress.add(tw);
		info("Generating tiles: " + String::valueOf(progress.get()*100 / (th*tw)) +"% complete", true);
		
	}
}



void RecastNavMeshBuilder::buildAllTiles()
{
	if (!m_geom) return;
	if (!m_navMesh) return;
	
	const Vector<Vector3>* vertArray = m_geom->getVerts();
	const Vector<MeshTriangle>* triArray = m_geom->getTriangles();
	
	const int nverts = vertArray->size();
	float* verts = new float[nverts*3];//m_geom->getMesh()->getVerts();
	
	int* tris = new int[triArray->size()*3];
	for(int i=0; i<nverts; i++) {
		const Vector3& vert = vertArray->get(i);
		verts[i*3+0] = vert.getX();
		verts[i*3+1] = vert.getY();
		verts[i*3+2] = vert.getZ();
	}
	
	for(int i=0; i<triArray->size(); i++) {
		memcpy(tris+(i*3), triArray->get(i).getVerts(), sizeof(int)*3);
	}
	
	float bmin[3];
	float bmax[3];
	
	bmin[0] = bounds.getXMin();
	bmin[1] = bounds.getYMin();
	bmin[2] = bounds.getZMin();
	
	
	bmax[0] = bounds.getXMax();
	bmax[1] = bounds.getYMax();
	bmax[2] = bounds.getZMax();
	int gw = 0, gh = 0;
	rcCalcGridSize(bmin, bmax, settings.m_cellSize, &gw, &gh);
	const int ts = (int)settings.m_tileSize;
	const int tw = (gw + ts-1) / ts;
	const int th = (gh + ts-1) / ts;
	const float tcs = settings.m_tileSize*settings.m_cellSize;
	
	rcChunkyTriMesh mesh;
	rcCreateChunkyTriMesh(verts, tris, triArray->size(), 256, &mesh);
	const rcChunkyTriMesh* chunkyMesh = &mesh;
	// Start the build process.
	
	AtomicInteger jobStatus;
	AtomicInteger progress;
	
	delete[] tris;
	delete[] verts;
	
	RecastTileBuilder builder(waterTableHeight, 0, 0, lastTileBounds, chunkyMesh, settings);
	builder.changeMesh(m_geom);
	for(auto& a : water)
		builder.addWater(a);
	
	for (int y = 0; y < th; ++y)
	{
		for (int x = 0; x < tw; ++x)
		{
			
			float minx = bmin[0] + x*tcs;
			float miny = bmin[1];
			float minz = bmin[2] + y*tcs;
			
			float maxx = bmin[0] + (x+1)*tcs;
			float maxy = bmax[1];
			float maxz = bmin[2] + (y+1)*tcs;
			lastTileBounds = AABB(Vector3(minx, miny, minz), Vector3(maxx, maxy, maxz));
			
			
			int dataSize = 0;
			unsigned char* data = builder.build(x, y, lastTileBounds, dataSize);//buildTileMesh(x, y, dataSize);
			if (data)
			{
				// Remove any previous data (navmesh owns and deletes the data).
				m_navMesh->removeTile(m_navMesh->getTileRefAt(x,y,0),0,0);
				// Let the navmesh own the data.
				dtStatus status = m_navMesh->addTile(data,dataSize,DT_TILE_FREE_DATA,0,0);
				if (dtStatusFailed(status)) {
					info("dtStatusFailed", true);
					dtFree(data);
				}
			} else {
				info("No data", true);
			}
			
			
		}
		progress.add(tw);
		info("Generating tiles: " + String::valueOf(progress.get()*100 / (th*tw)) +"% complete", true);
		
	}
}


void RecastNavMeshBuilder::removeAllTiles()
{
	if (!m_geom || !m_navMesh)
		return;
	
	float bmin[3];
	float bmax[3];
	
	bmin[0] = bounds.getXMin();
	bmin[1] = bounds.getYMin();
	bmin[2] = bounds.getZMin();
	
	
	bmax[0] = bounds.getXMax();
	bmax[1] = bounds.getYMax();
	bmax[2] = bounds.getZMax();
	
	int gw = 0, gh = 0;
	rcCalcGridSize(bmin, bmax, settings.m_cellSize, &gw, &gh);
	const int ts = (int)settings.m_tileSize;
	const int tw = (gw + ts-1) / ts;
	const int th = (gh + ts-1) / ts;
	
	for (int y = 0; y < th; ++y)
		for (int x = 0; x < tw; ++x)
			m_navMesh->removeTile(m_navMesh->getTileRefAt(x,y,0),0,0);
}


unsigned char* RecastNavMeshBuilder::buildTileMesh(const int tx, const int ty, int& dataSize)
{
	const Vector3& bmin = *lastTileBounds.getMinBound();
	const Vector3& bmax = *lastTileBounds.getMaxBound();
	
	cleanup();
	
	const Vector<Vector3>* vertArray = m_geom->getVerts();
	const Vector<MeshTriangle>* triArray = m_geom->getTriangles();
	
	const int nverts = vertArray->size();
	float* verts = new float[nverts*3];//m_geom->getMesh()->getVerts();
	
	for(int i=0; i<nverts; i++) {
		const Vector3& vert = vertArray->get(i);
		verts[i*3+0] = vert.getX();
		verts[i*3+1] = vert.getY();
		verts[i*3+2] = vert.getZ();
	}
	
	
	const int ntris = triArray->size();
	//const rcChunkyTriMesh* chunkyMesh = m_geom->getChunkyMesh();
	
	// Init build configuration from GUI
	memset(&m_cfg, 0, sizeof(m_cfg));
	m_cfg.cs = settings.m_cellSize;
	m_cfg.ch = settings.m_cellHeight;
	m_cfg.walkableSlopeAngle = settings.m_agentMaxSlope;
	m_cfg.walkableHeight = (int)ceilf(settings.m_agentHeight / m_cfg.ch);
	m_cfg.walkableClimb = (int)floorf(settings.m_agentMaxClimb / m_cfg.ch);
	m_cfg.walkableRadius = (int)ceilf(settings.m_agentRadius / m_cfg.cs);
	m_cfg.maxEdgeLen = (int)(settings.m_edgeMaxLen / settings.m_cellSize);
	m_cfg.maxSimplificationError = settings.m_edgeMaxError;
	m_cfg.minRegionArea = (int)rcSqr(settings.m_regionMinSize);		// Note: area = size*size
	m_cfg.mergeRegionArea = (int)rcSqr(settings.m_regionMergeSize);	// Note: area = size*size
	m_cfg.maxVertsPerPoly = (int)settings.m_vertsPerPoly;
	m_cfg.tileSize = (int)settings.m_tileSize;
	m_cfg.borderSize = m_cfg.walkableRadius + 3; // Reserve enough padding.
	m_cfg.width = m_cfg.tileSize + m_cfg.borderSize*2;
	m_cfg.height = m_cfg.tileSize + m_cfg.borderSize*2;
	m_cfg.detailSampleDist = settings.m_detailSampleDist < 0.9f ? 0 : settings.m_cellSize * settings.m_detailSampleDist;
	m_cfg.detailSampleMaxError = settings.m_cellHeight * settings.m_detailSampleMaxError;
	
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
	m_cfg.bmin[0] -= m_cfg.borderSize*m_cfg.cs;
	m_cfg.bmin[2] -= m_cfg.borderSize*m_cfg.cs;
	m_cfg.bmax[0] += m_cfg.borderSize*m_cfg.cs;
	m_cfg.bmax[2] += m_cfg.borderSize*m_cfg.cs;
	
	// Allocate voxel heightfield where we rasterize our input data to.
	m_solid = rcAllocHeightfield();
	if (!m_solid)
	{
		error("buildNavigation: Out of memory 'solid'.");
		return 0;
	}
	if (!rcCreateHeightfield(m_ctx, *m_solid, m_cfg.width, m_cfg.height, m_cfg.bmin, m_cfg.bmax, m_cfg.cs, m_cfg.ch))
	{
		error("buildNavigation: Could not create solid heightfield.");
		return 0;
	}
	

	
	float tbmin[2], tbmax[2];
	tbmin[0] = m_cfg.bmin[0];
	tbmin[1] = m_cfg.bmin[2];
	tbmax[0] = m_cfg.bmax[0];
	tbmax[1] = m_cfg.bmax[2];
	AABB aabb(Vector3(tbmin[0], -100000, tbmin[1]), Vector3(tbmax[0], 100000, tbmax[1]));
	Vector<MeshTriangle>* triangles = m_geom->getMeshWithinBounds(aabb);
	
	// Allocate array that can hold triangle flags.
	// If you have multiple meshes you need to process, allocate
	// and array which can hold the max number of triangles you need to process.
	m_triareas = new unsigned char[triangles->size()];
	memset(m_triareas, 0, triangles->size());
	
	if (!m_triareas)
	{
		error("buildNavigation: Out of memory 'm_triareas'");
		return 0;
	}
	
	int* tris = new int[triangles->size()*3];
	for(int i=0; i<triangles->size(); i++) {
		const MeshTriangle& triangle = triangles->get(i);
		const int* indicies = triangle.getVerts();
		
		tris[i*3+0] = indicies[0];
		tris[i*3+1] = indicies[1];
		tris[i*3+2] = indicies[2];
	}
	rcMarkWalkableTriangles(m_ctx, m_cfg.walkableSlopeAngle, verts, nverts, tris, triangles->size(), m_triareas);
	if (!rcRasterizeTriangles(m_ctx, verts, nverts, tris, m_triareas, triangles->size(), *m_solid, m_cfg.walkableClimb)) {
		delete[] verts;
		delete[] m_triareas;
		return 0;
	}
	delete[] verts;
	delete triangles;
	delete[] m_triareas;
	m_triareas = 0;
	
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
	if (!m_chf)
	{
		error("buildNavigation: Out of memory 'chf'.");
		return 0;
	}
	if (!rcBuildCompactHeightfield(m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid, *m_chf))
	{
		error("buildNavigation: Could not build compact data.");
		return 0;
	}
	
	rcFreeHeightField(m_solid);
	m_solid = 0;

	
	// Erode the walkable area by agent radius.
	if (!rcErodeWalkableArea(m_ctx, m_cfg.walkableRadius, *m_chf))
	{
		error("buildNavigation: Could not erode.");
		return 0;
	}
	
	
	
	// (Optional) Mark areas.
	for (int i  = 0; i < water.size(); ++i) {
		Reference<RecastPolygon*> poly = water.get(i);
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
	
	if (settings.m_partitionType == 0)
	{
		// Prepare for region partitioning, by calculating distance field along the walkable surface.
		if (!rcBuildDistanceField(m_ctx, *m_chf))
		{
			error("buildNavigation: Could not build distance field.");
			return 0;
		}
		
		// Partition the walkable surface into simple regions without holes.
		if (!rcBuildRegions(m_ctx, *m_chf, m_cfg.borderSize, m_cfg.minRegionArea, m_cfg.mergeRegionArea))
		{
			error("buildNavigation: Could not build watershed regions.");
			return 0;
		}
	}
	else if (settings.m_partitionType == 1)
	{
		// Partition the walkable surface into simple regions without holes.
		// Monotone partitioning does not need distancefield.
		if (!rcBuildRegionsMonotone(m_ctx, *m_chf, m_cfg.borderSize, m_cfg.minRegionArea, m_cfg.mergeRegionArea))
		{
			error("buildNavigation: Could not build monotone regions.");
			return 0;
		}
	}
	else // SAMPLE_PARTITION_LAYERS
	{
		// Partition the walkable surface into simple regions without holes.
		if (!rcBuildLayerRegions(m_ctx, *m_chf, m_cfg.borderSize, m_cfg.minRegionArea))
		{
			error("buildNavigation: Could not build layer regions.");
			return 0;
		}
	}
	
	// Create contours.
	m_cset = rcAllocContourSet();
	if (!m_cset)
	{
		error("buildNavigation: Out of memory 'cset'.");
		return 0;
	}
	if (!rcBuildContours(m_ctx, *m_chf, m_cfg.maxSimplificationError, m_cfg.maxEdgeLen, *m_cset))
	{
		error("buildNavigation: Could not create contours.");
		return 0;
	}
	
	if (m_cset->nconts == 0)
	{
		return 0;
	}
	
	// Build polygon navmesh from the contours.
	m_pmesh = rcAllocPolyMesh();
	if (!m_pmesh)
	{
		error("buildNavigation: Out of memory 'pmesh'.");
		return 0;
	}
	if (!rcBuildPolyMesh(m_ctx, *m_cset, m_cfg.maxVertsPerPoly, *m_pmesh))
	{
		error("buildNavigation: Could not triangulate contours.");
		return 0;
	}
	
	// Build detail mesh.
	m_dmesh = rcAllocPolyMeshDetail();
	if (!m_dmesh)
	{
		error("buildNavigation: Out of memory 'dmesh'.");
		return 0;
	}
	
	if (!rcBuildPolyMeshDetail(m_ctx, *m_pmesh, *m_chf,
							   m_cfg.detailSampleDist, m_cfg.detailSampleMaxError,
							   *m_dmesh))
	{
		error("buildNavigation: Could build polymesh detail.");
		return 0;
	}

	rcFreeCompactHeightfield(m_chf);
	m_chf = 0;
	rcFreeContourSet(m_cset);
	m_cset = 0;

	
	unsigned char* navData = 0;
	int navDataSize = 0;
	if (m_cfg.maxVertsPerPoly <= DT_VERTS_PER_POLYGON)
	{
		if (m_pmesh->nverts >= 0xffff)
		{
			// The vertex indices are ushorts, and cannot point to more than 0xffff vertices.
			error("Too many vertices per tile");
			return 0;
		}
		
		// Update poly flags from areas.
		for (int i = 0; i < m_pmesh->npolys; ++i)
		{
			if (m_pmesh->areas[i] == RC_WALKABLE_AREA)
				m_pmesh->areas[i] = SAMPLE_POLYAREA_GROUND;
			
			if (m_pmesh->areas[i] == SAMPLE_POLYAREA_GROUND ||
				m_pmesh->areas[i] == SAMPLE_POLYAREA_GRASS ||
				m_pmesh->areas[i] == SAMPLE_POLYAREA_ROAD)
			{
				m_pmesh->flags[i] = SAMPLE_POLYFLAGS_WALK;
			}
			else if (m_pmesh->areas[i] == SAMPLE_POLYAREA_WATER)
			{
				m_pmesh->flags[i] = SAMPLE_POLYFLAGS_SWIM;
			}
			else if (m_pmesh->areas[i] == SAMPLE_POLYAREA_DOOR)
			{
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
		
		if (!dtCreateNavMeshData(&params, &navData, &navDataSize))
		{
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

void RecastNavMeshBuilder::initialize(Vector<Reference<MeshData*> > meshData, AABB bounds, float distanceBetweenHeights) {
	TerrainManager *terrainManager = zone->getPlanetManager()->getTerrainManager();
	
	info("Building region terrain for: " + name, true);
	Vector3 center = bounds.center();
	meshData.add(getTerrainMesh(center, bounds.extents()[bounds.longestAxis()]*2, terrainManager, 32, distanceBetweenHeights));
	
	Reference<MeshData*> flattened = flattenMeshData(meshData);
	
	Vector<Reference<MeshData*> > test;
	test.add(flattened);
	meshData.removeAll();
	dumpOBJ(name+".obj", test);
	
	changeMesh(flattened);
	
	
	
	info("Building region navmesh for: " + name, true);
	Vector<const Boundary*> water;
	terrainManager->getProceduralTerrainAppearance()->getWaterBoundariesInAABB(bounds, &water);
	// Render water as polygons
	for(const Boundary* boundary : water) {
		const BoundaryPolygon *bPoly = dynamic_cast<const BoundaryPolygon*>(boundary);
		const BoundaryRectangle *bRect = dynamic_cast<const BoundaryRectangle*>(boundary);
		if(bPoly != NULL) {
			const Vector<Point2D*>& points = bPoly->getVertices();
			
			Reference<RecastPolygon*> poly = new RecastPolygon(points.size());
			poly->type = SAMPLE_POLYAREA_WATER;
			
			for (int i=points.size()-1; i>=0; i--) {
				const Point2D& point = *points.get(i);
				const float &x = point.getX();
				const float &z = point.getY();
				
				poly->verts[i*3+0] = x;
				poly->verts[i*3+1] = bPoly->getLocalWaterTableHeight();
				poly->verts[i*3+2] = -z;
			}
			
			poly->hmin = -FLT_MAX;
			poly->hmax = bPoly->getLocalWaterTableHeight();
			
			addWater(poly);
			continue;
			
		} else if(bRect != NULL) {
			Reference<RecastPolygon*> poly = new RecastPolygon(4);
			poly->type = SAMPLE_POLYAREA_WATER;
			float tableHeight = bRect->getLocalWaterTableHeight();
			poly->verts[0] = bRect->getMinX();
			poly->verts[1] = tableHeight;
			poly->verts[2] = -bRect->getMinY();
			
			poly->verts[3] = bRect->getMaxX();
			poly->verts[4] = tableHeight;
			poly->verts[5] = -bRect->getMinY();
			
			poly->verts[6] = bRect->getMaxX();
			poly->verts[7] = tableHeight;
			poly->verts[8] = -bRect->getMaxY();
			
			poly->verts[9] = bRect->getMinX();
			poly->verts[10] = tableHeight;
			poly->verts[11] = -bRect->getMaxY();
			
			poly->hmin = -FLT_MAX;
			poly->hmax = tableHeight;
			
			addWater(poly);
			continue;
		} else {
			info("BoundaryPolyCast Fail", true);
		}
	}
}

Reference<MeshData*> RecastNavMeshBuilder::flattenMeshData(Vector<Reference<MeshData*> >& data) {
	MeshData *mesh = new MeshData();
	Vector<Vector3>& newV = *mesh->getVerts();
	Vector<MeshTriangle>& newT = *mesh->getTriangles();
	
	for(int x=0; x<data.size(); x++) {
		MeshData *mesh = data.get(x);
		Vector<Vector3> *verts = mesh->getVerts();
		Vector<MeshTriangle> *tris = mesh->getTriangles();
		
		for (int i=0; i<verts->size(); i++) {
			Vector3& vert = verts->get(i);
			float xPos = vert.getX();
			float yPos = vert.getY();
			float zPos = vert.getZ();
			newV.add(Vector3(xPos, yPos, zPos));
		}
	}
	
	int lastIndex = 0;
	for(int x=0; x<data.size(); x++) {
		
		MeshData *mesh = data.get(x);
		Vector<Vector3> *verts = mesh->getVerts();
		Vector<MeshTriangle> *tris = mesh->getTriangles();
		
		for (int i=0; i<tris->size(); i++) {
			MeshTriangle& tri = tris->get(i);
			newT.add(MeshTriangle(lastIndex+tri.getVerts()[2], lastIndex+tri.getVerts()[1], lastIndex+tri.getVerts()[0]));
		}
		
		lastIndex += verts->size();
	}
	
	return mesh;
}

void RecastNavMeshBuilder::dumpOBJ(String filename, Vector<Reference<MeshData*> > data) {
	
	File file(filename);
	FileOutputStream outputStream(&file);
	
	for(int x=0; x<data.size(); x++) {
		MeshData *mesh = data.get(x);
		Vector<Vector3> *verts = mesh->getVerts();
		Vector<MeshTriangle> *tris = mesh->getTriangles();
		
		for (int i=0; i<verts->size(); i++) {
			Vector3& vert = verts->get(i);
			float xPos = vert.getX();
			float yPos = vert.getY();
			float zPos = vert.getZ();
			outputStream.write("v " + String::valueOf(xPos) +  " " + String::valueOf(yPos)+ " " + String::valueOf(zPos) +"\n");
		}
	}
	
	int lastIndex = 1;
	for(int x=0; x<data.size(); x++) {
		MeshData *mesh = data.get(x);
		Vector<Vector3> *verts = mesh->getVerts();
		Vector<MeshTriangle> *tris = mesh->getTriangles();
		
		for (int i=0; i<tris->size(); i++) {
			MeshTriangle& tri = tris->get(i);
			outputStream.write("f " + String::valueOf(lastIndex+tri.getVerts()[0]) + " " + String::valueOf(lastIndex+tri.getVerts()[1]) + " " + String::valueOf(lastIndex+tri.getVerts()[2])+"\n");
		}
		lastIndex += verts->size();
		
	}
	outputStream.flush();
	file.close();
}

Reference<MeshData*> RecastNavMeshBuilder::getTerrainMesh(Vector3& position, float terrainSize, TerrainManager* terrainManager, float chunkSize, float distanceBetweenHeights) {
	
	
	
	float centerX = position.getX();
	float centerY = position.getZ();
	
	float originX = centerX + (-terrainSize / 2);
	float originY = centerY + (-terrainSize / 2);
	
	unsigned int numRows = static_cast<unsigned int>( terrainSize / chunkSize );
	unsigned int numColumns = numRows;
	
	float oneChunkRows = chunkSize / distanceBetweenHeights + 1 ;
	float oneChunkColumns = chunkSize / distanceBetweenHeights + 1;
	
	int chunkNumRows = terrainSize / chunkSize;
	int chunkNumColumns = chunkNumRows;
	
	Reference<MeshData*> mesh = new MeshData();
	
	Vector<Vector3>* verts = mesh->getVerts();
	Vector<MeshTriangle>* tris = mesh->getTriangles();
	int numCells = terrainSize/distanceBetweenHeights;
	for (int x=0; x<numCells; x++) {
		for (int y=0; y<numCells; y++) {
			float xPos = originX + x*distanceBetweenHeights;
			float yPos = originY + y*distanceBetweenHeights;
			verts->add(Vector3(xPos, terrainManager->getProceduralTerrainAppearance()->getHeight(xPos, yPos), -yPos));
		}
		//info("Building terrain verts Row #" + String::valueOf(x*numCells));
	}
	
	
	for (int x=0; x<numCells-1; x++) {
		for (int y=0; y<numCells-1; y++) {
			MeshTriangle tri;
			tri.set(0, x+y*(numCells));
			tri.set(1, x+1 + y*(numCells));
			tri.set(2, x+1 + (y+1) * (numCells)); // top right tri
			
			tris->add(tri);
			
			tri.set(0, x+1 + (y+1) * (numCells)); // bottom left tri
			tri.set(1, x + (y+1) * (numCells));
			tri.set(2, x + y * (numCells));
			tris->add(tri);
		}
		//info("Building terrain Tris Row #" + String::valueOf(x*numCells));
	}
	
	return mesh;
}

void RecastNavMeshBuilder::changeMesh(MeshData* geom)
{	
	cleanup();
	
	dtFreeNavMesh(m_navMesh);
	m_navMesh = 0;
	
	m_geom = geom;
	bounds = geom->buildAABB();
}
