#ifndef OCTREEREFERENCE_H_
#define OCTREEREFERENCE_H_

#include "engine/engine.h"

#include "server/zone/Octree.h"

#ifdef WITH_STM
class OctreeReference : public TransactionalReference<Octree*> {
#else
class OctreeReference : public Reference<server::zone::Octree*> {
#endif
public:
	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

	server::zone::Octree* operator=(server::zone::Octree* obj);
};



#endif /* OCTREEREFERENCE_H_ */
