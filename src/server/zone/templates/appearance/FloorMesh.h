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

class Vert : public Object {
	float x, z, y;

public:
	Vert() {

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

	inline int getFrom() {
		return var1;
	}

	inline int getTo() {
		return var2;
	}

};

class Tri : public Object  {
	int var1, var2, var3, var4, var5, var6, var7;
	float var8, var9, var10;
	byte var11, var12, var13, var14;
	int var15, var16, var17, var18;

public:
	Tri() {

	}

	void readObject(IffStream* iffStream) {
		var1 = iffStream->getInt();
		var2 = iffStream->getInt();
		var3 = iffStream->getInt();
		var4 = iffStream->getInt();
		var5 = iffStream->getInt();
		var6 = iffStream->getInt();
		var7 = iffStream->getInt();
		var8 = iffStream->getFloat();
		var9 = iffStream->getFloat();
		var10 = iffStream->getFloat();

		var11 = iffStream->getByte();
		var12 = iffStream->getByte();
		var13 = iffStream->getByte();
		var14 = iffStream->getByte();

		var15 = iffStream->getInt();
		var16 = iffStream->getInt();
		var17 = iffStream->getInt();
		var18 = iffStream->getInt();
	}

	inline int getVertex1() {
		return var1;
	}

	inline int getVertex2() {
		return var2;
	}

	inline int getVertex3() {
		return var3;
	}
};

class FloorMesh : public IffTemplate, public Logger {
	Vector<Vert> vertices;
	Vector<Tri> tris;
	//Vector<Nods> nodes;
	//Vector<Bedg> edges; these disabed cause of ram

	PathGraph* pathGraph;

	AABBTree* aabbTree;

public:
	FloorMesh() {
		setLoggingName("FloorMesh");
		pathGraph = NULL;
		aabbTree = NULL;
	}

	~FloorMesh() {
		if (pathGraph != NULL) {
			delete pathGraph;
			pathGraph = NULL;
		}

		delete aabbTree;
		aabbTree = NULL;
	}

	void readObject(IffStream* iffStream);
	void parseBTRE(IffStream* iffStream);
	void parseBEDG(IffStream* iffStream);
	void parsePGRF(IffStream* iffStream);
	void parseVersion0006(IffStream* iffStream);
	void parseVersion0005(IffStream* iffStream);


	bool testCollide(float x, float z, float y, float radius);


};


#endif /* FLOORMESH_H_ */
