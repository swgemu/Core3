/*
 * PathNode.h
 *
 *  Created on: 02/12/2010
 *      Author: victor
 */

#ifndef PATHNODE_H_
#define PATHNODE_H_

#include "engine/engine.h"

class PathGraph;

class PathNode : public Object {
	Vector<PathNode*> children;

	uint32 id;
	int var2, globalGraphNodeID, var4;
	float x, z, y, var8;

	PathGraph* pathGraph;

public:
	PathNode(PathGraph* graph) {
		pathGraph = graph;
		id = 0;
		var2 = globalGraphNodeID = var4 = 0;
		x = z = y = var8 = 0;
	}

	inline void addChild(PathNode* node) {
		children.add(node);
	}

	void readObject(IffStream* iffStream) {
		id = iffStream->getInt();
		var2 = iffStream->getInt();
		globalGraphNodeID = iffStream->getInt();
		var4 = iffStream->getInt();

		x = iffStream->getFloat();
		z = iffStream->getFloat();
		y = iffStream->getFloat();
		var8 = iffStream->getFloat();
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

	/*inline uint32 getID() {
		return id;
	}*/

	uint32 getID();

	inline Vector3 getPosition() {
		return Vector3(x, y, z);
	}

	Vector<PathNode*>* getNeighbors() {
		return &children;
	}

	inline int getGlobalGraphNodeID() {
		return globalGraphNodeID;
	}

	inline PathGraph* getPathGraph() {
		return pathGraph;
	}

};


class PathEdge : public Object  {
	int from, to, var3, var4;

public:
	PathEdge() {

	}

	void readObject(IffStream* iffStream) {
		from = iffStream->getInt();
		to = iffStream->getInt();
		var3 = iffStream->getInt();
		var4 = iffStream->getInt();
	}

	inline int getFromConnection() {
		return from;
	}

	inline int getToConnection() {
		return to;
	}

};

#endif /* PATHNODE_H_ */
