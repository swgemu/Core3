#ifndef OCTTREEREFERENCE_H_
#define OCTTREEREFERENCE_H_

#include "engine/engine.h"

#include "server/zone/OctTree.h"

#ifdef WITH_STM
class OctTreeReference : public TransactionalReference<OctTree*> {
#else
class OctTreeReference : public Reference<server::zone::OctTree*> {
#endif
public:
	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

	server::zone::OctTree* operator=(server::zone::OctTree* obj);
};



#endif /* OCTTREEREFERENCE_H_ */
