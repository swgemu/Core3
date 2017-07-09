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
#include "server/zone/managers/planet/PlanetManager.h"
#include "templates/appearance/MeshData.h"
#include "ChunkyTriMesh.h"
#include "terrain/layer/boundaries/BoundaryRectangle.h"
#include "terrain/layer/boundaries/BoundaryPolygon.h"
#include "conf/ConfigManager.h"

//#define NAVMESH_DEBUG

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

RecastNavMeshBuilder::RecastNavMeshBuilder(Zone* zone, const String& name, const AtomicBoolean* jobStatus) :
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
		m_tileTriCount(0),
		running(jobStatus),
		header() {
	ProceduralTerrainAppearance* pta = zone->getPlanetManager()->getTerrainManager()->getProceduralTerrainAppearance();
	if (pta->getUseGlobalWaterTable())
		waterTableHeight = pta->getGlobalWaterTableHeight();
	else {
#ifdef NAVMESH_DEBUG
		info("Disabling water table for " + zone->getZoneName(), true);
#endif
		waterTableHeight = -1000.0f;
	}
	this->name = name;
	this->zone = zone;
	m_navMesh = NULL;
	m_ctx = new rcContext();
	destroyMesh = true;
}

RecastNavMeshBuilder::~RecastNavMeshBuilder() {
	m_geom = NULL;
	cleanup();
	if (destroyMesh) {
		dtFreeNavMesh(m_navMesh);
		m_navMesh = 0;
	}
	delete m_ctx;
}

void RecastNavMeshBuilder::cleanup() {
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

void RecastNavMeshBuilder::rebuildAreas(const Vector<AABB>& buildAreas, NavArea* navArea) {
	ReadLocker rLocker(navArea);

	RecastNavMesh* existingMesh = navArea->getNavMesh();
	dtNavMesh* oldMesh = existingMesh->getNavMesh();

	if (!oldMesh) {
		error("old mesh is null in RecastNavMeshBuilder::rebuildAreas for " + navArea->getMeshName());
		return;
	}

	m_navMesh = dtAllocNavMesh();
	if (!m_navMesh) {
		error("Failed to allocate m_navMesh in RecastNavMeshBuilder::rebuildAreas for " + navArea->getMeshName());
		return;
	}

	existingMesh->copyMeshTo(m_navMesh);
	rLocker.release();

    for (int i = buildAreas.size() - 1; i >= 0; i--) {
        const AABB &aabb = buildAreas.get(i);
        rebuildArea(aabb);
    }
}

void RecastNavMeshBuilder::rebuildArea(const AABB& buildArea) {
	float longest = buildArea.extents()[buildArea.longestAxis()];
	longest = Math::max(settings.m_tileSize * settings.m_cellSize * 2.25f, longest);

	Vector3 center = buildArea.midPoint();
	//un-fucking (or re-fucking) our coordinate system
	AABB area = AABB(Vector3(center.getX() - longest, -100000, -center.getY() - longest),
				Vector3(center.getX() + longest, 100000, -center.getY() + longest));

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

	if (!m_geom) return;
	if (!m_navMesh) return;

	buildAllTiles(area);
}

bool RecastNavMeshBuilder::build() {
	if (m_navMesh) {
		dtFreeNavMesh(m_navMesh);
	}

	m_navMesh = dtAllocNavMesh();
	destroyMesh = true;
	if (!m_navMesh) {
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

	status = m_navMesh->init(&params);
	if (dtStatusFailed(status)) {
		error("buildTiledNavigation: Could not init navmesh.");
		return false;
	}

	if (m_buildAll)
		buildAllTiles();

	return true;
}

void RecastNavMeshBuilder::buildAllTiles(const AABB& area) {
	if (!m_geom) return;
	if (!m_navMesh) return;

	const Vector <Vector3>* vertArray = m_geom->getVerts();
	const Vector <MeshTriangle>* triArray = m_geom->getTriangles();

	const int nverts = vertArray->size();
	float* verts = new float[nverts * 3];//m_geom->getMesh()->getVerts();

	int* tris = new int[triArray->size() * 3];
	for (int i = 0; i < nverts; i++) {
		const Vector3& vert = vertArray->get(i);
		verts[i * 3 + 0] = vert.getX();
		verts[i * 3 + 1] = vert.getY();
		verts[i * 3 + 2] = vert.getZ();
	}

	for (int i = 0; i < triArray->size(); i++) {
		memcpy(tris + (i * 3), triArray->get(i).getVerts(), sizeof(int) * 3);
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
	const int ts = (int) settings.m_tileSize;
	int tw = (gw + ts - 1) / ts;
	int th = (gh + ts - 1) / ts;
	const float tcs = settings.m_tileSize * settings.m_cellSize;

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
	builder.setWater(water);

	//info("Bounds: " + bounds.getMinBound()->toString() + " | " + bounds.getMaxBound()->toString() + "\n", true);

	float zStart = (fabs(bounds.getZMin() - area.getZMin()) / tcs) - 1.0f;
	float xStart = (fabs(bounds.getXMin() - area.getXMin()) / tcs) - 1.0f;

	th = ceil((fabs(bounds.getZMin() - area.getZMax()) / tcs) + 1.0f);
	tw = ceil((fabs(bounds.getXMin() - area.getXMax()) / tcs) + 1.0f);

	if (zStart < 0 || xStart < 0)
		return;

	for (int y = floor(zStart); y < th; ++y) {
		float zTileStart = bmin[2] + ((y + 1) * tcs);
		//info("zStart: " + String::valueOf(zTileStart), true);
		if (zTileStart < area.getZMin() || zTileStart > area.getZMax())
			continue;

		if (!running->get())
			return;

		for (int x = floor(xStart); x < tw; ++x) {

			float xTileStart = bmin[0] + ((x + 1) * tcs);
			//info("xStart: " + String::valueOf(xTileStart), true);
			if (xTileStart < area.getXMin() || xTileStart > area.getXMax())
				continue;


			float minx = bmin[0] + x * tcs;
			float miny = bmin[1];
			float minz = bmin[2] + y * tcs;

			float maxx = bmin[0] + (x + 1) * tcs;
			float maxy = bmax[1];
			float maxz = bmin[2] + (y + 1) * tcs;
			lastTileBounds = AABB(Vector3(minx, miny, minz), Vector3(maxx, maxy, maxz));

#ifdef NAVMESH_DEBUG
			info("BuiltTile : " + lastTileBounds.getMinBound()->toString() + " | " + lastTileBounds.getMaxBound()->toString() + "\n", false);
#endif
			int dataSize = 0;

			unsigned char* data = builder.build(x, y, lastTileBounds, dataSize);

			if (data) {
				// Remove any previous data (navmesh owns and deletes the data).
				m_navMesh->removeTile(m_navMesh->getTileRefAt(x, y, 0), 0, 0);
				// Let the navmesh own the data.
				dtStatus status = m_navMesh->addTile(data, dataSize, DT_TILE_FREE_DATA, 0, 0);

				if (dtStatusFailed(status)) {
					info("dtStatusFailed", true);
					dtFree(data);
				}
			}
		}
		progress.add(tw);
#ifdef NAVMESH_DEBUG
		info("Generating tiles: " + String::valueOf(progress.get() * 100 / (th * tw)) + "% complete", true);
#endif

	}
}


void RecastNavMeshBuilder::buildAllTiles() {
	if (!m_geom) return;
	if (!m_navMesh) return;

	const Vector <Vector3>* vertArray = m_geom->getVerts();
	const Vector <MeshTriangle>* triArray = m_geom->getTriangles();

	const int nverts = vertArray->size();
	float* verts = new float[nverts * 3];//m_geom->getMesh()->getVerts();

	int* tris = new int[triArray->size() * 3];
	for (int i = 0; i < nverts; i++) {
		const Vector3& vert = vertArray->get(i);
		verts[i * 3 + 0] = vert.getX();
		verts[i * 3 + 1] = vert.getY();
		verts[i * 3 + 2] = vert.getZ();
	}

	for (int i = 0; i < triArray->size(); i++) {
		memcpy(tris + (i * 3), triArray->get(i).getVerts(), sizeof(int) * 3);
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
	const int ts = (int) settings.m_tileSize;
	const int tw = (gw + ts - 1) / ts;
	const int th = (gh + ts - 1) / ts;
	const float tcs = settings.m_tileSize * settings.m_cellSize;

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
	builder.setWater(water);

	for (int y = 0; y < th; ++y) {

		if (!running->get())
			return;

		for (int x = 0; x < tw; ++x) {

			float minx = bmin[0] + x * tcs;
			float miny = bmin[1];
			float minz = bmin[2] + y * tcs;

			float maxx = bmin[0] + (x + 1) * tcs;
			float maxy = bmax[1];
			float maxz = bmin[2] + (y + 1) * tcs;
			lastTileBounds = AABB(Vector3(minx, miny, minz), Vector3(maxx, maxy, maxz));

			int dataSize = 0;
			unsigned char* data = builder.build(x, y, lastTileBounds, dataSize);
			if (data) {
				// Remove any previous data (navmesh owns and deletes the data).
				m_navMesh->removeTile(m_navMesh->getTileRefAt(x, y, 0), 0, 0);
				// Let the navmesh own the data.
				dtStatus status = m_navMesh->addTile(data, dataSize, DT_TILE_FREE_DATA, 0, 0);

				if (dtStatusFailed(status)) {
					info("dtStatusFailed", true);
					dtFree(data);
				}
			} else {
				info("No data", true);
			}
		}
		progress.add(tw);
#ifdef NAVMESH_DEBUG
		info("Generating tiles: " + String::valueOf(progress.get() * 100 / (th * tw)) + "% complete", true);
#endif
	}
}

void
RecastNavMeshBuilder::initialize(Vector<Reference<MeshData*> >& meshData, const AABB& bounds, float distanceBetweenHeights) {
	TerrainManager* terrainManager = zone->getPlanetManager()->getTerrainManager();

#ifdef NAVMESH_DEBUG
	info("Building region terrain for: " + name, true);
#endif

	float boundsRadius = bounds.extents()[bounds.longestAxis()] * 2.0f;
	assert(boundsRadius != 0.f);

	Vector3 center = bounds.center();
#ifdef NAVMESH_DEBUG
	info(center.toString() + " Radius: " + String::valueOf(boundsRadius), true);
#endif
	meshData.add(getTerrainMesh(center, boundsRadius, terrainManager, 32,
								distanceBetweenHeights));

	Reference < MeshData * > flattened = flattenMeshData(meshData);

	Vector <Reference<MeshData*>> test;
	test.add(flattened);
	meshData.removeAll();

	if (ConfigManager::instance()->getDumpObjFiles()) {
		String objName = name + ".obj";
		dumpOBJ(objName, test);
	}

	changeMesh(flattened);

#ifdef NAVMESH_DEBUG
	info("Building region navmesh for: " + name, true);
#endif
	Vector<const Boundary*> water;
	terrainManager->getProceduralTerrainAppearance()->getWaterBoundariesInAABB(bounds, &water);
	// Render water as polygons
	for (const Boundary* boundary : water) {
		const BoundaryPolygon* bPoly = dynamic_cast<const BoundaryPolygon*>(boundary);
		const BoundaryRectangle* bRect = dynamic_cast<const BoundaryRectangle*>(boundary);
		if (bPoly != NULL) {
			const Vector<Point2D*>& points = bPoly->getVertices();

			Reference < RecastPolygon * > poly = new RecastPolygon(points.size());
			poly->type = SAMPLE_POLYAREA_WATER;

			for (int i = points.size() - 1; i >= 0; i--) {
				const Point2D& point = *points.get(i);
				const float& x = point.getX();
				const float& z = point.getY();

				poly->verts[i * 3 + 0] = x;
				poly->verts[i * 3 + 1] = bPoly->getLocalWaterTableHeight();
				poly->verts[i * 3 + 2] = -z;
			}

			poly->hmin = -FLT_MAX;
			poly->hmax = bPoly->getLocalWaterTableHeight();

			addWater(poly);
			continue;

		} else if (bRect != NULL) {
			Reference < RecastPolygon * > poly = new RecastPolygon(4);
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

Reference<MeshData*> RecastNavMeshBuilder::flattenMeshData(Vector <Reference<MeshData*>>& data) {
	MeshData* mesh = new MeshData();
	Vector <Vector3>& newV = *mesh->getVerts();
	Vector <MeshTriangle>& newT = *mesh->getTriangles();

	for (int x = 0; x < data.size(); x++) {
		MeshData* mesh = data.get(x);
		Vector <Vector3>* verts = mesh->getVerts();
		Vector <MeshTriangle>* tris = mesh->getTriangles();

		for (int i = 0; i < verts->size(); i++) {
			Vector3& vert = verts->get(i);
			float xPos = vert.getX();
			float yPos = vert.getY();
			float zPos = vert.getZ();
			newV.add(Vector3(xPos, yPos, zPos));
		}
	}

	int lastIndex = 0;
	for (int x = 0; x < data.size(); x++) {

		MeshData* mesh = data.get(x);
		Vector <Vector3>* verts = mesh->getVerts();
		Vector <MeshTriangle>* tris = mesh->getTriangles();

		for (int i = 0; i < tris->size(); i++) {
			MeshTriangle& tri = tris->get(i);
			newT.add(MeshTriangle(lastIndex + tri.getVerts()[2], lastIndex + tri.getVerts()[1],
								  lastIndex + tri.getVerts()[0]));
		}

		lastIndex += verts->size();
	}

	return mesh;
}

void RecastNavMeshBuilder::dumpOBJ(const String& filename, Vector <Reference<MeshData*>>& data) {

	String outputFileName = "navmeshes/" + filename;
	File file(outputFileName);
	FileOutputStream outputStream(&file);

	for (int x = 0; x < data.size(); x++) {
		MeshData* mesh = data.get(x);
		Vector <Vector3>* verts = mesh->getVerts();
		Vector <MeshTriangle>* tris = mesh->getTriangles();

		for (int i = 0; i < verts->size(); i++) {
			Vector3& vert = verts->get(i);
			float xPos = vert.getX();
			float yPos = vert.getY();
			float zPos = vert.getZ();
			outputStream.write(
					"v " + String::valueOf(xPos) + " " + String::valueOf(yPos) + " " + String::valueOf(zPos) + "\n");
		}
	}

	int lastIndex = 1;
	for (int x = 0; x < data.size(); x++) {
		MeshData* mesh = data.get(x);
		Vector <Vector3>* verts = mesh->getVerts();
		Vector <MeshTriangle>* tris = mesh->getTriangles();

		for (int i = 0; i < tris->size(); i++) {
			MeshTriangle& tri = tris->get(i);
			outputStream.write("f " + String::valueOf(lastIndex + tri.getVerts()[0]) + " " + String::valueOf(
					lastIndex + tri.getVerts()[1]) + " " + String::valueOf(lastIndex + tri.getVerts()[2]) + "\n");
		}
		lastIndex += verts->size();

	}
	outputStream.flush();
	file.close();
}

Reference<MeshData*>
RecastNavMeshBuilder::getTerrainMesh(Vector3& position, float terrainSize, TerrainManager* terrainManager,
									 float chunkSize, float distanceBetweenHeights) {


	float centerX = position.getX();
	float centerY = position.getZ();

	float originX = centerX + (-terrainSize / 2);
	float originY = centerY + (-terrainSize / 2);

	unsigned int numRows = static_cast<unsigned int>( terrainSize / chunkSize );
	unsigned int numColumns = numRows;

	float oneChunkRows = chunkSize / distanceBetweenHeights + 1;
	float oneChunkColumns = chunkSize / distanceBetweenHeights + 1;

	int chunkNumRows = terrainSize / chunkSize;
	int chunkNumColumns = chunkNumRows;

	Reference < MeshData * > mesh = new MeshData();

	Vector <Vector3>* verts = mesh->getVerts();
	Vector <MeshTriangle>* tris = mesh->getTriangles();
	int numCells = terrainSize / distanceBetweenHeights;
	for (int x = 0; x < numCells; x++) {
		for (int y = 0; y < numCells; y++) {
			float xPos = originX + x * distanceBetweenHeights;
			float yPos = originY + y * distanceBetweenHeights;
			verts->add(Vector3(xPos, terrainManager->getProceduralTerrainAppearance()->getHeight(xPos, yPos), -yPos));
		}
		//info("Building terrain verts Row #" + String::valueOf(x*numCells));
	}


	for (int x = 0; x < numCells - 1; x++) {
		for (int y = 0; y < numCells - 1; y++) {
			MeshTriangle tri;
			tri.set(0, x + y * (numCells));
			tri.set(1, x + 1 + y * (numCells));
			tri.set(2, x + 1 + (y + 1) * (numCells)); // top right tri

			tris->add(tri);

			tri.set(0, x + 1 + (y + 1) * (numCells)); // bottom left tri
			tri.set(1, x + (y + 1) * (numCells));
			tri.set(2, x + y * (numCells));
			tris->add(tri);
		}
		//info("Building terrain Tris Row #" + String::valueOf(x*numCells));
	}

	return mesh;
}

void RecastNavMeshBuilder::changeMesh(MeshData* geom) {
	cleanup();

	dtFreeNavMesh(m_navMesh);
	m_navMesh = 0;

	m_geom = geom;
	bounds = geom->buildAABB();
}
