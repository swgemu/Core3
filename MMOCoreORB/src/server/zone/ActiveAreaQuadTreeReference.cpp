#include "ActiveAreaQuadTreeReference.h"

using namespace server::zone;

bool ActiveAreaQuadTreeReference::toBinaryStream(ObjectOutputStream* stream) {
	return true;
}

bool ActiveAreaQuadTreeReference::parseFromBinaryStream(ObjectInputStream* stream) {
	return true;
}

ActiveAreaQuadTree* ActiveAreaQuadTreeReference::operator=(ActiveAreaQuadTree* obj) {
#ifdef WITH_STM
	setObject(obj);
#else
	updateObject(obj);
#endif

	return obj;
}

