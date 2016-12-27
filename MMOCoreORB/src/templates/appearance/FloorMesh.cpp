/*
 * FloorMesh.cpp
 *
 *  Created on: 02/12/2010
 *      Author: victor
 */

#include "FloorMesh.h"

void FloorMeshTriangleNode::readObject(IffStream* iffStream) {
	indicies[0] = iffStream->getInt(); // Corner Index[0]
	indicies[1] = iffStream->getInt(); // Corner Index[1]
	indicies[2] = iffStream->getInt(); // Corner Index[2]

	Vector3 tri[3];
	tri[0] = mesh->getVertex(indicies[0])->getPosition();
	tri[1] = mesh->getVertex(indicies[1])->getPosition();
	tri[2] = mesh->getVertex(indicies[2])->getPosition();
	set(tri);

	triangleID = iffStream->getUnsignedInt(); // Triangle Index

	edges[0].neighbor = iffStream->getInt(); 
	edges[1].neighbor = iffStream->getInt(); 
	edges[2].neighbor = iffStream->getInt();

	normal.setX(iffStream->getFloat());
	normal.setY(iffStream->getFloat());
	normal.setZ(iffStream->getFloat());

	edges[0].flags = iffStream->getByte();
	edges[1].flags = iffStream->getByte();
	edges[2].flags = iffStream->getByte();

	nonSolid = (bool)iffStream->getByte();

	tag = iffStream->getInt();

	edges[0].portalID = iffStream->getInt(); 
	edges[1].portalID = iffStream->getInt(); 
	edges[2].portalID = iffStream->getInt();

	for(int i=0; i<3; i++) {
		EdgeID edgeID(triangleID, i);
		switch(edges[i].flags) {
			case 0:
				mesh->uncrossableEdges.put(edgeID);
				break;
			case 1:
				mesh->connectedEdges.put(edgeID);
				break;
			case 2:
				mesh->blockingEdges.put(edgeID);
				break;
		}
	}
}

FloorMesh::FloorMesh() {
	setLoggingName("FloorMesh");
	pathGraph = NULL;
	aabbTree = NULL;
	connectedEdges.setInsertPlan(SortedVector<EdgeID>::NO_DUPLICATE);
	uncrossableEdges.setInsertPlan(SortedVector<EdgeID>::NO_DUPLICATE);
	blockingEdges.setInsertPlan(SortedVector<EdgeID>::NO_DUPLICATE);

	cellID = -1;
}

FloorMesh::~FloorMesh() {
	if (pathGraph != NULL) {
		delete pathGraph;
		pathGraph = NULL;
	}

	delete aabbTree;
	aabbTree = NULL;

	for (int i = 0; i < tris.size(); ++i)
		delete tris.get(i);
}

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

	Vector<Triangle*> triangles;

	for (int i = 0; i < tris.size(); ++i) {
		FloorMeshTriangleNode* tri = tris.get(i);
		const FloorMeshTriangleNode::Edge* edges = tri->getEdges();

		for(int i=0; i<3; i++) {
			if (edges[i].neighbor != -1)
				tri->addNeighbor(tris.get(edges[i].neighbor));
		}

		triangles.add(tri);
	}

	/*if (tris.size() > 2) {
		Vector<TriangleNode*>* path = getPath(tris.get(0), tris.get(tris.size() - 1));

		delete path;
	}*/

	//tris.removeAll(1, 1);
	vertices.removeAll(1, 1);

	AABBTreeHeuristic heurData;
	heurData.maxdepth = 2; // maximum depth
	heurData.mintricnt = 5; // minimum triangle count
	heurData.tartricnt = 10; // target triangle count
	heurData.minerror = 0.5f; // minimum error required
	heurData.storePrimitives = true;

	aabbTree = new AABBTree(triangles, 0, heurData, false);

	iffStream->closeForm('FLOR');
}

Vector<TriangleNode*>* FloorMesh::getNeighbors(uint32 triangleID) {
	TriangleNode* triangle = tris.get(triangleID);

	return triangle->getNeighbors();
}

TriangleNode* FloorMesh::findNearestTriangle(const Vector3& point) {
	float dist = MAX_FLOAT;
	TriangleNode* found = NULL;

	for (int i = 0; i < tris.size(); ++i) {
		TriangleNode* node = tris.get(i);

		Vector3 bary = node->getBarycenter();

		float sqrDistance = bary.squaredDistanceTo(point);

		if (sqrDistance < dist) {
			found = node;
			dist = sqrDistance;
		}
	}

	if (found == NULL) {
		System::out << "ERROR findNearestTriangle NULL tris.size() = " << tris.size() << "point: x:" << point.getX() << " y:"
				<< point.getY() << " z:" << point.getZ() << endl;

		StackTrace::printStackTrace();
	}

	return found;
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
			FloorMeshTriangleNode* tri = new FloorMeshTriangleNode(this);

			tri->readObject(iffStream);

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
			FloorMeshTriangleNode* tri = new FloorMeshTriangleNode(this);

			tri->readObject(iffStream);

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
	Vector<Bedg> edges;

	iffStream->openChunk('BEDG');
	// TODO: Remove completely - obsolete
	iffStream->closeChunk('BEDG');
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

	if (nextForm != 'PGRF') {
		System::out << "EXPECTED PGRF PARSED " << hex << nextForm << endl;
		return;
	}

	pathGraph = new PathGraph(this);
	pathGraph->readObject(iffStream);
}

PathNode* FloorMesh::getGlobalNode(int globalID) {
	return pathGraph->findGlobalNode(globalID);
}

bool FloorMesh::testCollide(float x, float z, float y, float radius) {
	Vector3 point(x, z, y);

	Sphere sphere(point, radius);

	return aabbTree->testCollide(sphere);
}
