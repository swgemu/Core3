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
#include "server/zone/objects/player/PlayerObject.h"

bool SchematicList::toBinaryStream(ObjectOutputStream* stream) {
	Vector<ManagedReference<DraftSchematic*> > schematics;
	getRewardedSchematicList(schematics);

	TypeInfo<DraftSchematic*>::toBinaryStream(&updateCounter, stream);
	schematics.toBinaryStream(stream);

	return true;
}

bool SchematicList::parseFromBinaryStream(ObjectInputStream* stream) {
	Vector<ManagedReference<DraftSchematic*> > schematics;

	TypeInfo<DraftSchematic*>::parseFromBinaryStream(&updateCounter, stream);
	schematics.parseFromBinaryStream(stream);

	populateRewardedSchematics(schematics);

	return true;
}

void SchematicList::getRewardedSchematicList(Vector<ManagedReference<DraftSchematic*> >& schematics) {
	for (int i = 0; i < rewardedSchematics.size(); ++i) {
		DraftSchematic* schematic = rewardedSchematics.get(i);
		schematics.add(schematic);
	}
}

void SchematicList::populateRewardedSchematics(Vector<ManagedReference<DraftSchematic*> >& schematics) {

	for (int i = 0; i < schematics.size(); ++i) {
		DraftSchematic*  schematic = schematics.get(i);
		rewardedSchematics.add(schematic);
	}
}

void SchematicList::addRewardedSchematics(SceneObject* player) {
	if(player->isPlayerObject()) {
		PlayerObject* ghost = cast<PlayerObject*>(player);
		if(ghost != NULL)
			ghost->addSchematics(rewardedSchematics, true);
	}

}

bool SchematicList::addRewardedSchematic(DraftSchematic* schematic) {
	if(schematic->isRewarded()){

		if(contains(schematic)) {
			// Increase Use Count
			for(int i = 0; i < rewardedSchematics.size(); ++i) {

				if(rewardedSchematics.get(i)->getServerObjectCRC() ==
						schematic->getServerObjectCRC()) {

					rewardedSchematics.get(i)->increaseUseCount(schematic->getUseCount());
					return true;
				}
			}

		} else {
			rewardedSchematics.add(schematic);
		}
	}

	return false;
}

void SchematicList::removeRewardedSchematic(DraftSchematic* schematic) {
	if(rewardedSchematics.contains(schematic))
		rewardedSchematics.removeElement(schematic);

}

bool SchematicList::add(DraftSchematic* schematic, DeltaMessage* message, int updates) {

	bool val = vector.add(schematic);

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
