/*
 * RecastNavMesh.cpp
 *
 *  Created on: April 29, 2016
 *      Author: gslomin
 */

#include "RecastNavMesh.h"

bool RecastNavMesh::toBinaryStream(ObjectOutputStream* stream) {
	saveAll(stream);
	return true;
}

bool RecastNavMesh::parseFromBinaryStream(ObjectInputStream* stream) {
	loadAll(stream);
	return true;
}

void RecastNavMesh::loadAll(ObjectInputStream* stream) {
	name.parseFromBinaryStream(stream);

	bool meshWritten = stream->readBoolean();

	if (!meshWritten) {
		info("Loading NavArea with null mesh: " + name, true);
		return;
	}

	// Read header.
	int size = sizeof(NavMeshSetHeader);
	stream->readStream((char*)&header, size);

	if (header.magic != NAVMESHSET_MAGIC) {
		error("Attempting to read invalid RecastNavMesh " + name);
		return;
	}

	if (header.version != NAVMESHSET_VERSION) {
		error("RecastNavMesh header version is out of date");
		return;
	}

	dtNavMesh* mesh = dtAllocNavMesh();
	if (!mesh) {
		error("Failed to allocate RecastNavMesh " + name);
		return;
	}

	dtStatus status = mesh->init(&header.params);
	if (dtStatusFailed(status)) {
		error("Invalid Detour status for RecastNavMesh " + name);
		dtFreeNavMesh(mesh);
		return;
	}

	// Read tiles.
	for (int i = 0; i < header.numTiles; ++i) {
		NavMeshTileHeader tileHeader;
		int headerSize = sizeof(tileHeader);

		stream->readStream((char*)&tileHeader, headerSize);

		if (!tileHeader.tileRef || !tileHeader.dataSize) {
			error("Invalid tileHeader tileRef or dataSize in " + name);
			dtFreeNavMesh(mesh);
			return;
		}

		byte* data = (byte*) dtAlloc(tileHeader.dataSize, DT_ALLOC_PERM);
		if (!data) {
			error("Failed to buffer for tile in RecastNavMesh " + name);
			dtFreeNavMesh(mesh);
			return;
		}

		memset(data, 0, tileHeader.dataSize);
		stream->readStream((char*)data, tileHeader.dataSize);

		mesh->addTile(data, tileHeader.dataSize, DT_TILE_FREE_DATA, tileHeader.tileRef, 0);
	}

	navMesh = mesh;
}

void RecastNavMesh::saveAll(ObjectOutputStream* stream) {
	name.toBinaryStream(stream);

	const dtNavMesh* mesh = navMesh;
	if (!mesh) {
		stream->writeBoolean(false); // not writing mesh
		return;
	}

	stream->writeBoolean(true); // writing mesh

	// Store header.
	stream->writeStream((char*)&header, sizeof(NavMeshSetHeader));

	// Store tiles.
	for (int i = 0; i < mesh->getMaxTiles(); ++i) {
		const dtMeshTile* tile = mesh->getTile(i);
		if (!tile || !tile->header || !tile->dataSize) continue;

		NavMeshTileHeader tileHeader;
		tileHeader.tileRef = mesh->getTileRef(tile);
		tileHeader.dataSize = tile->dataSize;
		stream->writeStream((char*)&tileHeader, sizeof(tileHeader));

		stream->writeStream((char*)tile->data, tile->dataSize);
	}
}

void RecastNavMesh::setupDetourNavMeshHeader() {
	const dtNavMesh* mesh = navMesh;
	if (!mesh) {
		error("dtNavMesh is null in RecastNavMesh::setupDetourNavMeshHeader for " + name);
		return;
	}

	header.magic = NAVMESHSET_MAGIC;
	header.version = NAVMESHSET_VERSION;
	header.numTiles = 0;
	for (int i = 0; i < mesh->getMaxTiles(); ++i) {
		const dtMeshTile* tile = mesh->getTile(i);
		if (!tile || !tile->header || !tile->dataSize) continue;
		header.numTiles++;
	}

	memcpy(&header.params, mesh->getParams(), sizeof(dtNavMeshParams));
}

void RecastNavMesh::copyMeshTo(dtNavMesh* mesh) {
	const dtNavMesh* origMesh = navMesh;
	if (!origMesh) {
		error("Original mesh is null in copyMeshTo for " + name);
		return;
	}

	dtStatus status = mesh->init(&header.params);
	if (dtStatusFailed(status)) {
		error("Invalid Detour status for dtNavMesh in copyMeshTo for " + name);
		dtFreeNavMesh(mesh);
		return;
	}

	// Copy tiles.
	for (int i = 0; i < origMesh->getMaxTiles(); ++i) {
		const dtMeshTile* tile = origMesh->getTile(i);
		if (!tile || !tile->header || !tile->dataSize) continue;

		NavMeshTileHeader tileHeader;
		tileHeader.tileRef = origMesh->getTileRef(tile);
		tileHeader.dataSize = tile->dataSize;

		byte* data = (byte*) dtAlloc(tileHeader.dataSize, DT_ALLOC_PERM);
		if (!data) {
			error("Failed to alloc data in copyMeshTo for " + name);
			dtFreeNavMesh(mesh);
			return;
		}

		memcpy(data, tile->data, tileHeader.dataSize);

		mesh->addTile(data, tileHeader.dataSize, DT_TILE_FREE_DATA, tileHeader.tileRef, 0);
	}
}

void RecastNavMesh::saveToFile() {
	const dtNavMesh* mesh = navMesh;
	if (!mesh) {
		error("trying to save to file a NULL nav mesh from RecastNavMesh " + name);
		return;
	}

	String newPath = "navmeshes/" + name;

	FILE* fp = fopen(newPath.toCharArray(), "wb");
	if (!fp) {
		error("could not open file to save navmesh: " + newPath);
		return;
	}

	// Store header.
	fwrite(&header, sizeof(NavMeshSetHeader), 1, fp);

	// Store tiles.
	for (int i = 0; i < mesh->getMaxTiles(); ++i) {
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
