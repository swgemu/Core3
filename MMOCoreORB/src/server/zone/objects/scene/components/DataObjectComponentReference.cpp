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

	if (object != nullptr)
		object->toBinaryStream(stream);
	else
		stream->writeShort(0);

	return true;
}

bool DataObjectComponentReference::parseFromBinaryStream(ObjectInputStream* stream) {
	DataObjectComponent* object = Reference<DataObjectComponent*>::get();

	if (object == nullptr)
		stream->readShort();
	else
		object->parseFromBinaryStream(stream);

	return true;
}

DataObjectComponent* DataObjectComponentReference::operator= (DataObjectComponent* obj) {
	updateObject(obj);

	return obj;
}

void to_json(nlohmann::json& j, const DataObjectComponentReference& ref) {
	auto object = ref.get();

	if (object != nullptr)
		object->writeJSON(j);
	else
		j = {};

}
