/*
 * SchematicList.cpp
 *
 *  Created on: 6/3/2010
 *      Author: kyle
 */

#include "SchematicList.h"

#include "server/zone/objects/player/PlayerObject.h"

bool SchematicList::toBinaryStream(ObjectOutputStream* stream) {

	TypeInfo<VectorMap<ManagedReference<DraftSchematic* >, int > >::toBinaryStream(&rewardedSchematics, stream);
	//schematics.toBinaryStream(stream);

	return true;
}

bool SchematicList::parseFromBinaryStream(ObjectInputStream* stream) {

	TypeInfo<VectorMap<ManagedReference<DraftSchematic* >, int > >::parseFromBinaryStream(&rewardedSchematics, stream);
	//schematics.parseFromBinaryStream(stream);

	return true;
}

void SchematicList::addRewardedSchematics(SceneObject* player) {
	if (player->isPlayerObject()) {
		PlayerObject* ghost = cast<PlayerObject*>(player);

		if (ghost != NULL) {
			Vector<ManagedReference<DraftSchematic* > > schematics;

			for (int i = rewardedSchematics.size() - 1; i >= 0; --i) {
				DraftSchematic* schem = rewardedSchematics.elementAt(i).getKey();

				if (schem->getDraftSchematicTemplate() != NULL) {
					schematics.add(schem);
				} else {
					rewardedSchematics.drop(schem);
					schem->destroyObjectFromDatabase(true);
				}
			}

			ghost->addSchematics(schematics, true);
		}
	}
}

bool SchematicList::addRewardedSchematic(DraftSchematic* schematic, short type, int quantity) {
	if (type == MISSION) {
		for(int i = 0; i < rewardedSchematics.size(); ++i) {
			if(rewardedSchematics.elementAt(i).getKey() == schematic) {
				int newQuantity = rewardedSchematics.get(i) + quantity;
				rewardedSchematics.drop(schematic);
				rewardedSchematics.put(schematic, newQuantity);
				return false;
			}
		}
	}
	rewardedSchematics.put(schematic, quantity);
	return true;
}

void SchematicList::removeRewardedSchematic(DraftSchematic* schematic) {
	if(rewardedSchematics.contains(schematic))
		rewardedSchematics.drop(schematic);
}

bool SchematicList::decreaseSchematicUseCount(DraftSchematic* schematic) {
	if(rewardedSchematics.contains(schematic)) {

		for(int i = 0; i < rewardedSchematics.size(); ++i) {
			if(rewardedSchematics.elementAt(i).getKey() == schematic) {
				if(rewardedSchematics.get(i) > 1) {
					int newQuantity = rewardedSchematics.get(i) - 1;
					rewardedSchematics.drop(schematic);
					rewardedSchematics.put(schematic, newQuantity);
					return true;
				} else if(rewardedSchematics.get(i) == 1) {
					removeRewardedSchematic(schematic);
					return true;
				}
			}
		}
	}
	return false;
}

bool SchematicList::add(DraftSchematic* schematic, DeltaMessage* message, int updates) {

	bool val = vector.add(schematic);

	if (val && message != NULL) {
		if (updates != 0)
			message->startList(updates, updateCounter += updates);

		message->insertByte(1);
		message->insertShort(vector.size() - 1);

		message->insertInt(schematic->getClientObjectCRC());
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

		msg->insertInt(schematic->getClientObjectCRC());
		msg->insertInt(schematic->getClientObjectCRC());  /// Must be client CRC
	}
}
