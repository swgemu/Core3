/*
 * WaypointObject.cpp
 *
 *  Created on: 28/12/2009
 *      Author: victor
 */

#include "WaypointObject.h"

WaypointObject::WaypointObject() {
	objectID = 0;
	cellID = 0; //?

	positionX = 0.f;
	positionZ = 0.f;
	positionY = 0.f;
	unknown = 0;
	planetCRC = 0;

	color = 0;
	active = 0;

	addSerializableVariables();
}

WaypointObject::WaypointObject(const WaypointObject& obj) : Object(), Serializable() {
	copy(obj);

	addSerializableVariables();
}

void WaypointObject::copy(const WaypointObject& obj) {
	objectID = obj.objectID;
	cellID = obj.cellID;

	positionX = obj.positionX;
	positionZ = obj.positionZ;
	positionY = obj.positionY;
	unknown = obj.unknown;
	planetCRC = obj.planetCRC;
	color = obj.color;
	active = obj.active;
}

void WaypointObject::addSerializableVariables() {
	addSerializableVariable("objectID", &objectID);
	addSerializableVariable("cellID", &cellID);
	addSerializableVariable("positionX", &positionX);
	addSerializableVariable("positionZ", &positionZ);
	addSerializableVariable("positionY", &positionY);
	addSerializableVariable("unknown", &unknown);
	addSerializableVariable("planetCRC", &planetCRC);
	addSerializableVariable("customName", &customName);
	addSerializableVariable("color", &color);
	addSerializableVariable("active", &active);
}

bool WaypointObject::toBinaryStream(ObjectOutputStream* stream) {
	stream->writeInt(cellID); // cellID
	stream->writeFloat(positionX);
	stream->writeFloat(positionZ); //Z
	stream->writeFloat(positionY);
	stream->writeLong(unknown); //?
	stream->writeInt(planetCRC);
	customName.toBinaryStream(stream);
	stream->writeLong(objectID);
	stream->writeByte(color);
	stream->writeByte(active);

	return true;
}

bool WaypointObject::parseFromBinaryStream(ObjectInputStream* stream) {
	cellID = stream->readInt();
	positionX = stream->readFloat();
	positionZ = stream->readFloat();
	positionY = stream->readFloat();
	unknown = stream->readLong();
	planetCRC = stream->readInt();
	customName.parseFromBinaryStream(stream);
	objectID = stream->readLong();
	color = stream->readByte();
	active = stream->readByte();

	return true;
}
