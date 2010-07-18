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


void SchematicList::getSchematicIDList(Vector<uint32>& schematics) {
	for (int i = 0; i < vector.size(); ++i) {
		DraftSchematic* schematic = vector.get(i);

		uint32 crc = schematic->getSchematicID();

		schematics.add(crc);
	}
}

bool SchematicList::toString(String& str) {
	Vector<uint32> names;
	getSchematicIDList(names);

	TypeInfo<uint32>::toString(&updateCounter, str);
	names.toString(str);

	return true;
}

bool SchematicList::toBinaryStream(ObjectOutputStream* stream) {
	Vector<uint32> names;
	getSchematicIDList(names);

	TypeInfo<uint32>::toBinaryStream(&updateCounter, stream);
	names.toBinaryStream(stream);

	return true;
}


bool SchematicList::parseFromString(const String& str, int version) {
	Vector<uint32> schematics;

	TypeInfo<uint32>::parseFromString(&updateCounter, str, version);
	schematics.parseFromString(str, version);

	loadFromSchematicIDs(schematics);

	return true;
}

bool SchematicList::parseFromBinaryStream(ObjectInputStream* stream) {
	Vector<uint32> schematics;

	TypeInfo<uint32>::parseFromBinaryStream(&updateCounter, stream);
	schematics.parseFromBinaryStream(stream);

	loadFromSchematicIDs(schematics);

	return true;
}

void SchematicList::loadFromSchematicIDs(Vector<uint32>& schematics) {
	ZoneServer* server = ServerCore::getZoneServer();
	CraftingManager* craftingManager = server->getCraftingManager();

	for (int i = 0; i < schematics.size(); ++i) {
		uint32 schematicID = schematics.get(i);

		DraftSchematic* schematic = craftingManager->getSchematic(schematicID);

		add(schematic);
	}
}

bool SchematicList::add(DraftSchematic* schematic, DeltaMessage* message, int updates) {

	bool val = vector.add(schematic);

	if (message != NULL) {
		if (updates != 0)
			message->startList(updates, updateCounter += updates);

		message->insertByte(1);
		message->insertShort(vector.size() - 1);

		message->insertInt(schematic->getSchematicID());
		message->insertInt(schematic->getClientObjectCRC()); /// Must be client CRC
	}

	return val;
}

Vector<ManagedReference<DraftSchematic* > > SchematicList::filterSchematicList(
		Vector<uint32>* enabledTabs, int complexityLevel) {

	Vector<ManagedReference<DraftSchematic* > > filteredschematics;

	for (int i = 0; i < size(); ++i) {
		ManagedReference<DraftSchematic*> schematic = get(i);

		for(int j = 0; j < enabledTabs->size(); ++j) {
			if(enabledTabs->get(j) == schematic->getToolTab() &&
					schematic->getComplexity() <= complexityLevel) {
				filteredschematics.add(schematic);
				break;
			}
		}
	}
	return filteredschematics;
}

void SchematicList::insertToMessage(BaseMessage* msg) {
	msg->insertInt(size());
	msg->insertInt(updateCounter);

	for (int i = 0; i < size(); ++i) {
		DraftSchematic* schematic = get(i);

		msg->insertInt(schematic->getSchematicID());
		msg->insertInt(schematic->getClientObjectCRC());  /// Must be client CRC
	}
}
