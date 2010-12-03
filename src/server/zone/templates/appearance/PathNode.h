/*
 * PathNode.h
 *
 *  Created on: 02/12/2010
 *      Author: victor
 */

#ifndef PATHNODE_H_
#define PATHNODE_H_

#include "engine/engine.h"

class PathNode : public Object {
	Vector<PathNode*> children;

	int id, var2, var3, var4;
	float x, z, y, var8;

public:
	PathNode() {

	}

	inline void addChild(PathNode* node) {
		children.add(node);
	}

	void readObject(IffStream* iffStream) {
		id = iffStream->getInt();
		var2 = iffStream->getInt();
		var3 = iffStream->getInt();
		var4 = iffStream->getInt();

		x = iffStream->getFloat();
		z = iffStream->getFloat();
		y = iffStream->getFloat();
		var8 = iffStream->getFloat();
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
