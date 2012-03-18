/*
 * DataObjectReference.h
 *
 *  Created on: 18/03/2012
 *      Author: victor
 */

#ifndef DATAOBJECCOMPONENTTREFERENCE_H_
#define DATAOBJECCOMPONENTTREFERENCE_H_

#include "engine/engine.h"

#include "DataObjectComponent.h"

class DataObjectComponentReference : public Reference<DataObjectComponent*> {
public:
	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);
	DataObjectComponent* operator=(DataObjectComponent* obj);
};


#endif /* DATAOBJECTREFERENCE_H_ */
