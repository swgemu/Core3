/*
 * DataObjectComponentReference.cpp
 *
 *  Created on: 18/03/2012
 *      Author: victor
 */

#include "DataObjectComponent.h"
#include "DataObjectComponentReference.h"

bool DataObjectComponentReference::toBinaryStream(ObjectOutputStream* stream) {
	DataObjectComponent* object = Reference<DataObjectComponent*>::get();

	if (object != NULL)
		object->toBinaryStream(stream);
	else
		stream->writeShort(0);

	return true;
}

bool DataObjectComponentReference::parseFromBinaryStream(ObjectInputStream* stream) {
	DataObjectComponent* object = Reference<DataObjectComponent*>::get();

	if (object == NULL)
		stream->readShort();
	else
		object->parseFromBinaryStream(stream);

	return true;
}

DataObjectComponent* DataObjectComponentReference::operator= (DataObjectComponent* obj) {
	updateObject(obj);

	return obj;
}
