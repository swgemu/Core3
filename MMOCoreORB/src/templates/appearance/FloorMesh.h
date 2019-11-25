/*
 * FloorMesh.h
 *
 *  Created on: 02/12/2010
 *      Author: victor
 */

#ifndef FLOORMESH_H_
#define FLOORMESH_H_

#include "engine/engine.h"
#include "templates/IffTemplate.h"
#include "templates/appearance/PathNode.h"
#include "templates/appearance/PathGraph.h"

//#define RENDER_EXTERNAL_FLOOR_MESHES_ONLY

class MeshData;

class EdgeID {
	int triangleID;
	int edgeID;
public:
	EdgeID(int triangleID, int edgeID) {
		this->triangleID = triangleID;
		this->edgeID = edgeID;
	}

	EdgeID() {
		triangleID = -1;
		edgeID = -1;
	}

	EdgeID(const EdgeID& edge) {
		triangleID = edge.triangleID;
		edgeID = edge.edgeID;
	}

	inline int getEdgeID() const { return edgeID; }
	inline int getTriangleID() const { return triangleID; }

	int compareTo(const EdgeID& rhs) const {
		if(triangleID == rhs.triangleID) {
			if (edgeID == rhs.edgeID)
				return 0;
			else if(edgeID < rhs.edgeID)
				return 1;
			else
				return -1;
		} else if (triangleID < rhs.triangleID) {
			return 1;
		} else {
			return -1;
		}
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		return false;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		return false;
	}

};

class Nods {
	float x0, y0, z0, x1, y1, z1;
	int id, var2, leftNode, rightNode;

public:
	Nods() {
		x0 = y0 = z0 = x1 = y1 = z1 = 0;
		id = var2 = leftNode = rightNode = 0;
	}

	void readObject(IffStream* iffStream) {
		x1 = iffStream->getFloat();
		z1 = iffStream->getFloat();
		y1 = iffStream->getFloat();

		x0 = iffStream->getFloat();
		z0 = iffStream->getFloat();
		y0 = iffStream->getFloat();

		id = iffStream->getInt();
		var2 = iffStream->getInt();
		leftNode = iffStream->getInt();
		rightNode = iffStream->getInt();
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		return false;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		return false;
	}

};

class Bedg {
	int triangleID;
	int edgeID;
	char var3;
public:
	Bedg() {
		triangleID = edgeID = 0;
		var3 = 0;
	}

	void readObject(IffStream* iffStream) {
		triangleID = iffStream->getInt();
		edgeID = iffStream->getInt();
		var3 = iffStream->getByte();
	}

	inline int getTriangleID() const {
		return triangleID;
	}

	inline int getEdgeID() const {
		return edgeID;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		return false;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		return false;
	}
};

class FloorMeshTriangleNode : public TriangleNode {
public:
	class Edge : public Object {
	protected:
		int32 neighbor;
		uint8 flags;
		int32 portalID;
	public:
		Edge() {
			neighbor = -1;
			flags = -1;
			portalID = -1;
		}

		int32 getNeighbor() const { return neighbor; }

		uint8 getFlags() const { return flags; }

		int32 getPortalID() const { return portalID; }
		friend class FloorMeshTriangleNode;
		friend class FloorMesh;
	};

protected:

	int32 indicies[3];
	uint32 triangleID;
	Vector3 normal;
	Edge edges[3];
	bool nonSolid;
	int32 tag;
	FloorMesh *mesh;
	Vector<TriangleNode*> neighbors;

public:
	FloorMeshTriangleNode(FloorMesh* floorMesh) : neighbors(1, 1) {
		mesh = floorMesh;
		indicies[0] = 0;
		indicies[1] = 0;
		indicies[2] = 0;
		triangleID = 0;
		tag = 0;
		nonSolid = false;
	}

	void readObject(IffStream* iffStream);

	inline int getIndex(int val) {
		assert(val < 3);

		return indicies[val];
	}

	inline bool isEdge() const {
		//return edge;
		return neighbors.size() < 3;
	}

	inline uint32 getID() const final {
		return triangleID;
	}

	const Edge* getEdges() const {
		return edges;
	}

	inline void addNeighbor(TriangleNode* node) {
		neighbors.add(node);
	}

	inline const Vector<TriangleNode*>* getNeighbors() const final {
		return &neighbors;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		return false;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		return false;
	}

	friend class FloorMesh;
};

class FloorMesh : public IffTemplate, public Logger {
	Vector<Vector3> vertices;
	Vector<FloorMeshTriangleNode*> tris;
	SortedVector<EdgeID> connectedEdges;
	SortedVector<EdgeID> uncrossableEdges;
	SortedVector<EdgeID> blockingEdges;

	PathGraph* pathGraph;
	AABBTree* aabbTree;

	int cellID;

public:
	FloorMesh();
	~FloorMesh();

	void readObject(IffStream* iffStream);
	void parseBTRE(IffStream* iffStream);
	void parseBEDG(IffStream* iffStream);
	void parsePGRF(IffStream* iffStream);
	void parseVersion0006(IffStream* iffStream);
	void parseVersion0005(IffStream* iffStream);
	void parseVersion0003(IffStream* iffStream);

	Vector <Reference<MeshData*>> getTransformedMeshData(const Matrix4& parentTransform) const;

	const Vector<TriangleNode*>* getNeighbors(uint32 triangleID) const;

	const TriangleNode* findNearestTriangle(const Vector3& point) const;

	bool testCollide(float x, float z, float y, float radius) const;

	const PathNode* getGlobalNode(int globalID) const;

	inline const PathGraph* getPathGraph() const {
		return pathGraph;
	}

	inline PathGraph* getPathGraph() {
		return pathGraph;
	}

	inline const FloorMeshTriangleNode* getTriangle(int tri) const {
		return tris.get(tri);
	}

	inline int getTriangleCount() const {
		return tris.size();
	}

	inline const AABBTree* getAABBTree() const {
		return aabbTree;
	}

	inline const Vector3* getVertex(int vert) const {
		return &vertices.get(vert);
	}

	inline int getCellID() const {
		return cellID;
	}

	inline void setCellID(int id) {
		cellID = id;
	}

	float calculateManhattanDistance(const TriangleNode* node1, const TriangleNode* node2) const {
		Vector3 bary = node1->getBarycenter();
		Vector3 bary2 = node2->getBarycenter();

		return bary.squaredDistanceTo(bary2);
	}

	friend class FloorMeshTriangleNode;
};

#endif /* FLOORMESH_H_ */
