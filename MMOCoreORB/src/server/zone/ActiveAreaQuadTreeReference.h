#ifndef ACTIVEAREAQUADTREEREFERENCE_H_
#define ACTIVEAREAQUADTREEREFERENCE_H_

#include "engine/engine.h"

#include "server/zone/ActiveAreaQuadTree.h"

#ifdef WITH_STM
class ActiveAreaQuadTreeReference : public TransactionalReference<ActiveAreaQuadTree*> {
#else
class ActiveAreaQuadTreeReference : public Reference<server::zone::ActiveAreaQuadTree*> {
#endif
public:
	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

	server::zone::ActiveAreaQuadTree* operator=(server::zone::ActiveAreaQuadTree* obj);
};



#endif /* ACTIVEAREAQUADTREEREFERENCE_H_ */
