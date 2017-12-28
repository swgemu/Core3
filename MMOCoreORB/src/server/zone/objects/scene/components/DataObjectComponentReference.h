/*
 * DataObjectReference.h
 *
 *  Created on: 18/03/2012
 *      Author: victor
 */

#ifndef DATAOBJECCOMPONENTTREFERENCE_H_
#define DATAOBJECCOMPONENTTREFERENCE_H_

#include "DataObjectComponent.h"
#include "engine/engine.h"
#include "system/lang/ref/Reference.h"

namespace sys {
namespace io {
class ObjectInputStream;
class ObjectOutputStream;
}  // namespace io
}  // namespace sys

class DataObjectComponentReference : public Reference<DataObjectComponent*> {
public:
	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);
	DataObjectComponent* operator=(DataObjectComponent* obj);

};


#endif /* DATAOBJECTREFERENCE_H_ */
