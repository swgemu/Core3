/*
 * FloorMesh.cpp
 *
 *  Created on: 02/12/2010
 *      Author: victor
 */

#include "FloorMesh.h"
#include "templates/appearance/MeshData.h"

#define BARRIER_HEIGHT 3

void FloorMeshTriangleNode::readObject(IffStream* iffStream) {
	indicies[0] = iffStream->getInt(); // Corner Index[0]
	indicies[1] = iffStream->getInt(); // Corner Index[1]
	indicies[2] = iffStream->getInt(); // Corner Index[2]

	Vector3 tri[3];
	tri[0] = *mesh->getVertex(indicies[0]);
	tri[1] = *mesh->getVertex(indicies[1]);
	tri[2] = *mesh->getVertex(indicies[2]);
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
	case '0003':
		parseVersion0003(iffStream);
		break;
	default:
		error("unkown FloorMesh version " + String::hexvalueOf((int)nextFormType) + " in file " + iffStream->getFileName());
		break;
	}

	// Generating our own tree from triangles

	Vector<Triangle*> triangles(tris.size(), 1);

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
	//vertices.removeAll(1, 1);

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
		TriangleNode* node = tris.getUnsafe(i);

		Vector3 bary = node->getBarycenter();

		float sqrDistance = bary.squaredDistanceTo(point);

		if (sqrDistance < dist) {
			found = node;
			dist = sqrDistance;
		}
	}

	if (found == NULL) {
		StringBuffer msg;
		msg << "ERROR findNearestTriangle NULL tris.size() = " << tris.size() << "point: x:" << point.getX() << " y:"
				<< point.getY() << " z:" << point.getZ() << endl;

		error(msg);

		StackTrace::printStackTrace();
	}

	return found;
}

void FloorMesh::parseVersion0003(IffStream* iffStream) {
	try {
		iffStream->openForm('0003');

		Chunk* vertData = iffStream->openChunk('VERT');

		int vertSize = vertData->getChunkSize();

		while (vertSize > 0) {
			vertices.add(iffStream->getVector3());
			vertSize -= 12;
		}

		iffStream->closeChunk();

		Chunk* trisData = iffStream->openChunk('TRIS');

		int trisDataSize = trisData->getChunkSize();

		tris.removeAll(trisDataSize / 60);

		while (trisDataSize > 0) {
			FloorMeshTriangleNode* tri = new FloorMeshTriangleNode(this);

			tri->readObject(iffStream);

			tris.add(tri);

			trisDataSize -= 60;
		}

		iffStream->closeChunk();

		iffStream->closeForm('0003');
	} catch (Exception& e) {
		String err = "unable to parse file ";
		err += iffStream->getFileName();
		error(err);

		error(e.getMessage());
		e.printStackTrace();
	}
}

void FloorMesh::parseVersion0005(IffStream* iffStream) {
	try {
		iffStream->openForm('0005');

		Chunk* vertData = iffStream->openChunk('VERT');

		int vertSize = vertData->getChunkSize();

		vertices.removeAll(vertSize);

		while (vertSize > 0) {
			vertices.add(iffStream->getVector3());
			vertSize -= 12;
		}

		iffStream->closeChunk();

		Chunk* trisData = iffStream->openChunk('TRIS');

		int trisDataSize = trisData->getChunkSize();

		tris.removeAll(trisDataSize / 60);

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

		vertices.removeAll(verticesSize);

		for (int i = 0; i < verticesSize; ++i) {
			vertices.add(iffStream->getVector3());
		}

		iffStream->closeChunk();

		iffStream->openChunk('TRIS');

		int trisCount = iffStream->getInt();

		tris.removeAll(trisCount);

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

Vector <Reference<MeshData*>> FloorMesh::getTransformedMeshData(const Matrix4& parentTransform) const {
	Reference<MeshData*> data = new MeshData();

	Vector<Vector3> *vertices = data->getVerts();
	Vector<MeshTriangle> *triangles = data->getTriangles();

	for (const auto& edge : uncrossableEdges) {
		const auto& tri = tris.get(edge.getTriangleID());
		int startIndex = edge.getEdgeID() % 3;

		Vector3 start = tri->getVertex(startIndex);
		Vector3 end = tri->getVertex(startIndex < 2 ? startIndex + 1 : 0);

		//negate z + transform
		start.setZ(-start.getZ());
		start = start * parentTransform;

		end.setZ(-end.getZ());
		end = end * parentTransform;

		vertices->add(start);
		vertices->add(end);
		vertices->emplace(start.getX(), start.getY() + BARRIER_HEIGHT, start.getZ());
		vertices->emplace(end.getX(), end.getY() + BARRIER_HEIGHT, end.getZ());

		int ind = vertices->size() - 1;
		triangles->emplace(ind - 1, ind - 2, ind - 3);
		triangles->emplace(ind, ind - 2, ind - 1);
	}

	Vector<Reference<MeshData*>> meshData;
	meshData.emplace(std::move(data));

#ifdef RENDER_EXTERNAL_FLOOR_MESHES_ONLY
	Reference<MeshData*> floorData = new MeshData();

	Vector<Vector3>* floorVertices = floorData->getVerts();
	floorVertices->removeAll(this->vertices.size() + 1);

	Vector<MeshTriangle>* floorTriangles = floorData->getTriangles();
	floorTriangles->removeAll(tris.size() + 1);

	for (const auto& vert : this->vertices) {
		Vector3 transformedVert = vert;

		transformedVert.setZ(-transformedVert.getZ());
		transformedVert = transformedVert * parentTransform;

		floorVertices->add(transformedVert);
	}

	for (const auto& tri : tris) {
		floorTriangles->emplace(tri->getIndex(0), tri->getIndex(1), tri->getIndex(2));
	}

	meshData.emplace(std::move(floorData));
#endif

	return meshData;
}
