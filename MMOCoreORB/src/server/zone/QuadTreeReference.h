/*
 * QuadTreeReference.h
 *
 *  Created on: 03/09/2011
 *      Author: TheAnswer
 */

#ifndef QUADTREEREFERENCE_H_
#define QUADTREEREFERENCE_H_

#include "engine/engine.h"
#include "server/zone/QuadTree.h"
#include "system/lang/ref/Reference.h"

namespace sys {
namespace io {
class ObjectInputStream;
class ObjectOutputStream;
}  // namespace io
}  // namespace sys

#ifdef WITH_STM
class QuadTreeReference : public TransactionalReference<QuadTree*> {
#else
class QuadTreeReference : public Reference<server::zone::QuadTree*> {
#endif
public:
	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

	server::zone::QuadTree* operator=(server::zone::QuadTree* obj);
};



#endif /* QUADTREEREFERENCE_H_ */
