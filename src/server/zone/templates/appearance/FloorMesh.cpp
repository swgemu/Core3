/*
 * FloorMesh.cpp
 *
 *  Created on: 02/12/2010
 *      Author: victor
 */

#include "FloorMesh.h"

#include "MeshAppearanceTemplate.h"

void FloorMesh::readObject(IffStream* iffStream) {
	iffStream->openForm('FLOR');

	uint32 nextFormType = iffStream->getNextFormType();

	switch (nextFormType) {
	case '0006':
		parseVersion0006(iffStream);
		break;
	case '0005':
		parseVersion0005(iffStream);
		break;
	default:
		error("unkown FloorMesh version " + String::hexvalueOf((int)nextFormType));
		break;
	}

	// Generating our own tree from triangles

	Vector<Triangle> triangles;

	for (int i = 0; i < tris.size(); ++i) {
		Tri* tri = &tris.get(i);

		int pointA = tri->getVertex1();
		int pointB = tri->getVertex2();
		int pointC = tri->getVertex3();

		Vert* vert1 = &vertices.get(pointA);
		Vert* vert2 = &vertices.get(pointB);
		Vert* vert3 = &vertices.get(pointC);

		Vector3 trian[3];
		trian[0] = Vector3(vert1->getX(), vert1->getY(), vert1->getZ());
		trian[1] = Vector3(vert2->getX(), vert2->getY(), vert2->getZ());
		trian[2] = Vector3(vert3->getX(), vert3->getY(), vert3->getZ());

		triangles.add(Triangle(trian));
	}

	tris.removeAll(1, 1);
	vertices.removeAll(1, 1);

	AABBTreeHeuristic heurData;
	heurData.maxdepth = 2; // maximum depth
	heurData.mintricnt = 5; // minimum triangle count
	heurData.tartricnt = 10; // target triangle count
	heurData.minerror = 0.5f; // minimum error required
	heurData.storePrimitives = true;

	aabbTree = new AABBTree(triangles, 0, heurData);

	iffStream->closeForm('FLOR');
}

void FloorMesh::parseVersion0005(IffStream* iffStream) {
	try {
		iffStream->openForm('0005');

		Chunk* vertData = iffStream->openChunk('VERT');

		int vertSize = vertData->getChunkSize();

		while (vertSize > 0) {
			Vert vert;
			vert.readObject(iffStream);

			vertices.add(vert);

			vertSize -= 12;
		}

		iffStream->closeChunk();

		Chunk* trisData = iffStream->openChunk('TRIS');

		int trisDataSize = trisData->getChunkSize();

		while (trisDataSize > 0) {
			Tri tri;

			tri.readObject(iffStream);

			tris.add(tri);

			trisDataSize -= 60;
		}

		iffStream->closeChunk();

		parseBTRE(iffStream);

		parseBEDG(iffStream);

		parsePGRF(iffStream);

		iffStream->closeForm('0005');
	} catch (Exception& e) {
		String err = "unable to parse file ";
		err += iffStream->getFileName();
		error(err);

		error(e.getMessage());
		e.printStackTrace();
	}
}

void FloorMesh::parseVersion0006(IffStream* iffStream) {
	try {
		iffStream->openForm('0006');

		Chunk* data = iffStream->openChunk('VERT');

		int verticesSize = data->readInt();

		for (int i = 0; i < verticesSize; ++i) {
			Vert vert;
			vert.readObject(iffStream);

			vertices.add(vert);
		}

		iffStream->closeChunk();

		iffStream->openChunk('TRIS');

		int trisCount = iffStream->getInt();

		for (int i = 0; i < trisCount; ++i) {
			Tri tri;

			tri.readObject(iffStream);

			tris.add(tri);
		}

		iffStream->closeChunk();

		parseBTRE(iffStream);

		parseBEDG(iffStream);

		parsePGRF(iffStream);

		iffStream->closeForm('0006');
	} catch (Exception& e) {
		String err = "unable to parse file ";
		err += iffStream->getFileName();
		error(err);

		error(e.getMessage());
		e.printStackTrace();
	}
}

void FloorMesh::parseBTRE(IffStream* iffStream) {
	uint32 nextForm = 0;

	try {
		nextForm = iffStream->getNextFormType();
	} catch (Exception& e) {
		return;
	}

	if (nextForm != 'BTRE')
		return;

	iffStream->openForm('BTRE');

	iffStream->openForm('0000');

	iffStream->openChunk('NODS');

	int nodeSize = iffStream->getInt();

	/*for (int i = 0; i < nodeSize; ++i) {
		Nods nods;
		nods.readObject(iffStream);

		nodes.add(nods);
	}*/

	iffStream->closeChunk();

	iffStream->closeForm('0000');

	iffStream->closeForm('BTRE');
}

void FloorMesh::parseBEDG(IffStream* iffStream) {
	/*Vector<Bedg> edges;

	iffStream->openChunk('BEDG');

	int edgeSize = iffStream->getInt();

	for (int i = 0; i < edgeSize; ++i) {
		Bedg bedg;

		bedg.readObject(iffStream);

		edges.add(bedg);
	}

	iffStream->closeChunk('BEDG');*/
}

void FloorMesh::parsePGRF(IffStream* iffStream) {
	if (iffStream->getRemainingSubChunksNumber() == 0) {
		return;
	}

	uint32 nextForm = 0;

	try {
		nextForm = iffStream->getNextFormType();
	} catch (Exception& e) {
		return;
	}

	if (nextForm != 'PGRF')
		return;

	pathGraph = new PathGraph();
	pathGraph->readObject(iffStream);
}

bool FloorMesh::testCollide(float x, float z, float y, float radius) {
	Vector3 point(x, z, y);

	Sphere sphere(point, radius);

	return aabbTree->testCollide(sphere);
}
