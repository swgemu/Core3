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

/*bool SchematicList::toString(String& str) {
	Vector<ManagedReference<DraftSchematic*> > schematics;
	getLimitedUseSchematicList(schematics);

	TypeInfo<DraftSchematic*>::toString(&updateCounter, str);
	schematics.toString(str);

	return true;
}*/

bool SchematicList::toBinaryStream(ObjectOutputStream* stream) {
	Vector<ManagedReference<DraftSchematic*> > schematics;
	getLimitedUseSchematicList(schematics);

	TypeInfo<DraftSchematic*>::toBinaryStream(&updateCounter, stream);
	schematics.toBinaryStream(stream);

	return true;
}


/*bool SchematicList::parseFromString(const String& str, int version) {
	Vector<ManagedReference<DraftSchematic*> > schematics;

	TypeInfo<DraftSchematic*>::parseFromString(&updateCounter, str, version);
	schematics.parseFromString(str, version);

	loadLimitedUseSchematics(schematics);

	return true;
}*/

bool SchematicList::parseFromBinaryStream(ObjectInputStream* stream) {
	Vector<ManagedReference<DraftSchematic*> > schematics;

	TypeInfo<DraftSchematic*>::parseFromBinaryStream(&updateCounter, stream);
	schematics.parseFromBinaryStream(stream);

	loadLimitedUseSchematics(schematics);

	return true;
}

void SchematicList::getLimitedUseSchematicList(Vector<ManagedReference<DraftSchematic*> >& schematics) {
	for (int i = 0; i < vector.size(); ++i) {
		DraftSchematic* schematic = vector.get(i);

		if(schematic->getGroupName().isEmpty()) {
			schematics.add(schematic);
		}
	}
}

void SchematicList::loadLimitedUseSchematics(Vector<ManagedReference<DraftSchematic*> >& schematics) {

	for (int i = 0; i < schematics.size(); ++i) {
		ManagedReference<DraftSchematic*>  schematic = schematics.get(i);
		limitedUseSchematics.add(schematic);
	}
	awardLimitedUseSchematics();
}

void SchematicList::awardLimitedUseSchematics() {

	for (int i = 0; i < limitedUseSchematics.size(); ++i) {
		ManagedReference<DraftSchematic*>  schematic = limitedUseSchematics.get(i);
		add(schematic);
	}
}

bool SchematicList::add(DraftSchematic* schematic, DeltaMessage* message, int updates) {

	bool val = vector.add(schematic);

	if(schematic->getGroupName().isEmpty())
		limitedUseSchematics.add(schematic);

	if (val && message != NULL) {
		if (updates != 0)
			message->startList(updates, updateCounter += updates);

		message->insertByte(1);
		message->insertShort(vector.size() - 1);

		message->insertInt(schematic->getSchematicID());
		message->insertInt(schematic->getClientObjectCRC()); /// Must be client CRC
	}

	return val;
}

bool SchematicList::contains(DraftSchematic* schematic) {

	for(int i = 0; i < size(); ++i) {

		DraftSchematic* existingSchematic = get(i);

		if(existingSchematic == NULL)
			continue;

		if((existingSchematic->getClientObjectCRC() == schematic->getClientObjectCRC()) &&
				(existingSchematic->getCustomName() == schematic->getCustomName()))

			return true;
	}

	return false;
}

bool SchematicList::updateUseCount(DraftSchematic* schematic) {

	for(int i = 0; i < size(); ++i) {

		DraftSchematic* existingSchematic = get(i);

		if(existingSchematic == NULL)
			continue;

		if((existingSchematic->getClientObjectCRC() == schematic->getClientObjectCRC()) &&
				(existingSchematic->getCustomName() == schematic->getCustomName())) {

			if(existingSchematic->getUseCount() > 0)
				existingSchematic->increaseUseCount(schematic->getUseCount());

			return true;
		}
	}

	return false;
}

bool SchematicList::contains(Vector<ManagedReference<DraftSchematic* > > filteredschematics, DraftSchematic* schematic) {

	for(int i = 0; i < filteredschematics.size(); ++i) {

		DraftSchematic* existingSchematic = filteredschematics.get(i);

		if(existingSchematic == NULL)
			continue;

		if((existingSchematic->getClientObjectCRC() == schematic->getClientObjectCRC()) &&
				(existingSchematic->getCustomName() == schematic->getCustomName()))

			return true;
	}

	return false;
}

/**
 *  Complexity Requirements
 	 1 - 15 General Crafting Tool
	16 - 20 Specialized Crafting Tool
	21 - 25 Specialized Crafting Tool + Public Crafting Station
	26 - Specialized Crafting Tool + Private Crafting Station

	http://swg.stratics.com/content/gameplay/guides/guides.php?Cat=664&uid=902
 */

Vector<ManagedReference<DraftSchematic* > > SchematicList::filterSchematicList(
		CreatureObject* player, Vector<uint32>* enabledTabs, int complexityLevel) {

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
