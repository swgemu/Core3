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
		z = iffStream->getFloat();
		y = iffStream->getFloat();
	}


};

class Nods  : public Object {
	float x1, y1, z1, x2, y2, z2;
	int var1, var2, var3, var4;

public:
	Nods() {

	}

	void readObject(IffStream* iffStream) {
		x1 = iffStream->getFloat();
		y1 = iffStream->getFloat();
		z1 = iffStream->getFloat();

		x2 = iffStream->getFloat();
		y2 = iffStream->getFloat();
		z2 = iffStream->getFloat();

		var1 = iffStream->getInt();
		var2 = iffStream->getInt();
		var3 = iffStream->getInt();
		var4 = iffStream->getInt();
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
};

class FloorMesh : public IffTemplate, public Logger {
	Vector<Vert> vertices;
	//Vector<Tri> tris;
	//Vector<Nods> nodes;
	//Vector<Bedg> edges; these disabed cause of ram

	PathGraph* pathGraph;

public:
	FloorMesh() {
		setLoggingName("FloorMesh");
		pathGraph = NULL;
	}

	~FloorMesh() {
		if (pathGraph != NULL) {
			delete pathGraph;
			pathGraph = NULL;
		}
	}

	void readObject(IffStream* iffStream);
	void parseBTRE(IffStream* iffStream);
	void parseBEDG(IffStream* iffStream);
	void parsePGRF(IffStream* iffStream);
	void parseVersion0006(IffStream* iffStream);
	void parseVersion0005(IffStream* iffStream);


};


#endif /* FLOORMESH_H_ */
