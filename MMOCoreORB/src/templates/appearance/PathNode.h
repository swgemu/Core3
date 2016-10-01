/*
 * PathNode.h
 *
 *  Created on: 02/12/2010
 *      Author: victor
 */

#ifndef PATHNODE_H_
#define PATHNODE_H_

#include "engine/engine.h"

#include "templates/appearance/PathEdge.h"

class PathGraph;

class PathNode : public Object {
protected:

	Vector<PathNode*> children;

	uint32 id;
	int var2, globalGraphNodeID;
	int type;
	float x, z, y, radius;

	PathGraph* pathGraph;

public:

	
	PathNode(PathGraph* graph) {
		pathGraph = graph;
		id = 0;
		var2 = globalGraphNodeID = 0;
		type = 0;
		x = z = y = radius = 0;
	}

	inline void addChild(PathNode* node) {
		children.add(node);
	}

	void readObject(IffStream* iffStream) {
		id = iffStream->getInt(); // index
		var2 = iffStream->getInt(); // ID
		globalGraphNodeID = iffStream->getInt(); // Key
		type = iffStream->getInt();

		x = iffStream->getFloat(); // position
		z = iffStream->getFloat();
		y = iffStream->getFloat();
		radius = iffStream->getFloat(); //radius
		if(radius == 0.0f)
			radius = 0.5f;
	}

	inline float getX() const {
		return x;
	}

	inline float getY() const {
		return y;
	}

	inline float getZ() const {
		return z;
	}

	/*inline uint32 getID() {
		return id;
	}*/

	uint32 getID();

	inline Vector3 getPosition() const {
		return Vector3(x, y, z);
	}

	inline float getRadius() const {
		return radius;
	}

	inline int getType() const {
		return type;
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

#endif /* PATHNODE_H_ */
