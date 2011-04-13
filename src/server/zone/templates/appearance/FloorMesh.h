/*
 * FloorMesh.h
 *
 *  Created on: 02/12/2010
 *      Author: victor
 */

#ifndef FLOORMESH_H_
#define FLOORMESH_H_

#include "engine/engine.h"
#include "../IffTemplate.h"
#include "PathNode.h"
#include "PathGraph.h"

class PortalLayout;

class Vert : public Object {
	float x, z, y;

public:
	Vert() {

	}

	Vert(const Vert& v) : Object() {
		x = v.x;
		z = v.z;
		y = v.y;
	}

	Vert(float px, float py, float pz) {
		x = px;
		y = py;
		z = pz;
	}

	void readObject(IffStream* iffStream) {
		x = iffStream->getFloat();
		y = iffStream->getFloat();
		z = iffStream->getFloat();
	}

	inline float getX() {
		return x;
	}

	inline float getY() {
		return y;
	}

	inline float getZ() {
		return z;
	}
};

class Nods  : public Object {
	float x0, y0, z0, x1, y1, z1;
	int id, var2, leftNode, rightNode;

public:
	Nods() {

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
};

class Bedg : public Object {
	int var1, var2;
	char var3;

public:
	Bedg() {

	}

	void readObject(IffStream* iffStream) {
		var1 = iffStream->getInt();
		var2 = iffStream->getInt();
		var3 = iffStream->getByte();
	}

	inline int getTriangleID() {
		return var1;
	}

};

class FloorMeshTriangleNode : public TriangleNode {
	//int vertex1, vertex2, vertex3,
	int northWestTriangle, northEastTriangle, southTriangle;
	uint32 id;
	Vector<TriangleNode*> neighbors;

	float var8, var9, var10;
	byte /*hasNorthWestTriangle, hasNorthEastTriangle, hasSouthTriangle,*/ var14;
	int var15, var16, var17, var18;
	FloorMesh* mesh;
	bool edge;

public:
	FloorMeshTriangleNode(FloorMesh* floorMesh) : neighbors(1, 1) {
		mesh = floorMesh;
		edge = false;
	}

	void readObject(IffStream* iffStream);

	inline void setEdge(bool val) {
		edge = val;
	}

	inline bool isEdge() {
		//return edge;
		return neighbors.size() < 3;
	}

	inline bool hasNorthWestTriangle() {
		return northWestTriangle != -1;
	}

	inline bool hasNorthEastTriangle() {
		return northEastTriangle != -1;
	}

	inline bool hasSouthTriangle() {
		return southTriangle != -1;
	}

	inline uint32 getID() {
		return id;
	}

	inline void addNeighbor(TriangleNode* node) {
		neighbors.add(node);
	}

	inline int getNorthWestTriangle() {
		return northWestTriangle;
	}

	inline int getNorthEastTriangle() {
		return northEastTriangle;
	}

	inline int getSouthTriangle() {
		return southTriangle;
	}

	inline Vector<TriangleNode*>* getNeighbors() {
		return &neighbors;
	}
};

class FloorMesh : public IffTemplate, public Logger {
	Vector<Vert> vertices;
	Vector<FloorMeshTriangleNode*> tris;
	//Vector<Nods> nodes;
	//Vector<Bedg> edges; these disabed cause of ram

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

	Vector<TriangleNode*>* getNeighbors(uint32 triangleID);

	TriangleNode* findNearestTriangle(const Vector3& point);

	bool testCollide(float x, float z, float y, float radius);

	PathNode* getGlobalNode(int globalID);

	inline PathGraph* getPathGraph() {
		return pathGraph;
	}

	inline AABBTree* getAABBTree() {
		return aabbTree;
	}

	inline Vert* getVertex(int vert) {
		return &vertices.get(vert);
	}

	inline int getCellID() {
		return cellID;
	}

	inline void setCellID(int id) {
		if (cellID != -1)
			System::out << "UIWBIUGFISUBGSFIUBGSODIFGN" << endl;

		cellID = id;
	}

	float calculateManhattanDistance(TriangleNode* node1, TriangleNode* node2) {
		Vector3 bary = node1->getBarycenter();
		Vector3 bary2 = node2->getBarycenter();

		return bary.squaredDistanceTo(bary2);

		/*return abs(bary.getX() - bary2.getX()) + abs(bary.getY() - bary2.getY())
				+ abs(bary.getZ() - bary2.getZ());*/
	}


};


#endif /* FLOORMESH_H_ */
