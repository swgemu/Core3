/*
 * OctreeReference.cpp
 *
 *  Created on: 03/09/2011
 *      Author: TheAnswer
 */

#include "OctreeReference.h"

using namespace server::zone;

bool OctreeReference::toBinaryStream(ObjectOutputStream* stream) {
	return true;
}

bool OctreeReference::parseFromBinaryStream(ObjectInputStream* stream) {
	return true;
}

Octree* OctreeReference::operator=(Octree* obj) {
#ifdef WITH_STM
	setObject(obj);
#else
	updateObject(obj);
#endif

	return obj;
}

