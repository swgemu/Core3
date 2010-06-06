/*
 * SchematicList.cpp
 *
 *  Created on: 6/3/2010
 *      Author: kyle
 */

#include "SchematicList.h"

#include "server/zone/ZoneServer.h"
#include "server/ServerCore.h"
#include "server/zone/managers/crafting/CraftingManager.h"


void SchematicList::getCrcList(Vector<uint32>& schematics) {
	for (int i = 0; i < vector.size(); ++i) {
		DraftSchematic* schematic = vector.get(i);

		uint32 crc = schematic->getClientObjectCRC();

		schematics.add(crc);
	}
}

bool SchematicList::toString(String& str) {
	Vector<uint32> names;
	getCrcList(names);

	TypeInfo<uint32>::toString(&updateCounter, str);
	names.toString(str);

	return true;
}

bool SchematicList::toBinaryStream(ObjectOutputStream* stream) {
	Vector<uint32> names;
	getCrcList(names);

	TypeInfo<uint32>::toBinaryStream(&updateCounter, stream);
	names.toBinaryStream(stream);

	return true;
}


bool SchematicList::parseFromString(const String& str, int version) {
	Vector<uint32> schematics;

	TypeInfo<uint32>::parseFromString(&updateCounter, str, version);
	schematics.parseFromString(str, version);

	loadFromCrcs(schematics);

	return true;
}

bool SchematicList::parseFromBinaryStream(ObjectInputStream* stream) {
	Vector<uint32> schematics;

	TypeInfo<uint32>::parseFromBinaryStream(&updateCounter, stream);
	schematics.parseFromBinaryStream(stream);

	loadFromCrcs(schematics);

	return true;
}

void SchematicList::loadFromCrcs(Vector<uint32>& schematics) {
	ZoneServer* server = ServerCore::getZoneServer();
	CraftingManager* craftingManager = server->getCraftingManager();

	for (int i = 0; i < schematics.size(); ++i) {
		uint32 crc = schematics.get(i);

		DraftSchematic* schematic = craftingManager->getSchematic(crc);

		add(schematic);
	}
}

bool SchematicList::add(DraftSchematic* schematic, DeltaMessage* message, int updates) {

	bool val = vector.add(schematic);

	if (message != NULL) {
		if (updates != 0)
			message->startList(updates, updateCounter += updates);

		message->insertByte(1);
		message->insertShort(vector.size());

		message->insertInt(schematic->getClientObjectCRC());
		message->insertInt(schematic->getClientObjectCRC());
	}

	return val;
}

bool SchematicList::remove(DraftSchematic* schematic, DeltaMessage* message, int updates) {

	int index = -1;

	for(int i = 0; i < vector.size(); ++i) {
		if(schematic->getObjectNameStringIdName() == vector.get(i)->getObjectNameStringIdName()) {
			index = i;
			break;
		}
	}

	if(index == -1)
		return false;

	vector.removeElementAt(index);

	if (message != NULL) {
		if (updates != 0)
			message->startList(updates, updateCounter += updates);

		message->insertByte(0);
		message->insertShort(index + 1);
	}

	return true;
}

void SchematicList::insertToMessage(BaseMessage* msg) {
	msg->insertInt(size());
	msg->insertInt(updateCounter);

	for (int i = 0; i < size(); ++i) {
		DraftSchematic* schematic = get(i);

		msg->insertInt(schematic->getClientObjectCRC());
		msg->insertInt(schematic->getClientObjectCRC());
	}
}
