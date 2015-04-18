/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLAYEROBJECTDELTAMESSAGE9_H_
#define PLAYEROBJECTDELTAMESSAGE9_H_

#include "../DeltaMessage.h"
#include "server/zone/objects/player/PlayerObject.h"

class PlayerObjectDeltaMessage9 : public DeltaMessage {
	PlayerObject* play;

public:
	PlayerObjectDeltaMessage9(PlayerObject* pl)
			: DeltaMessage(pl->getObjectID(), 0x504C4159, 9) {
		play = pl;
	}

	void updateStomachFilling() {
		addIntUpdate(0x0A, play->getFoodFilling());
		addIntUpdate(0x0B, play->getFoodFillingMax());
		addIntUpdate(0x0C, play->getDrinkFilling());
		addIntUpdate(0x0D, play->getDrinkFillingMax());
	}

	void updateFoodFilling(int newVal) {
		addIntUpdate(0x0A, newVal);
	}

	void updateDrinkFilling(int newVal) {
		addIntUpdate(0x0C, newVal);
	}

	void setLanguageID(uint8 lid) {
		startUpdate(9);
		insertInt((uint32)lid);
	}

	void setExperimentationEnabled(bool experimenting) {
		startUpdate(1);
		if (experimenting){
			insertInt(3);  // 3 // 4
		}
		else {
			insertInt(1);
		}
	}

	void setExperimentationPoints(int points){
		startUpdate(5);
		insertInt(points); // Number of experimentation points
	}

	void setCraftingState(int state) {
		startUpdate(2);
		insertInt(state);
	}

	void setClosestCraftingStation(uint64 oid) {
		startUpdate(3);
		insertLong(oid);
	}

	void setJediState(int state) {
		startUpdate(0x11);
		insertInt(state);
	}

	/*void startSkillListUpdate(int skillsToUpdate) {
		startUpdate(0);
		startList(skillsToUpdate, play->getPlayer()->getNewCreatureSkillsCount(skillsToUpdate));
	}

	void addSkill(const String& name, uint16 idx) {
		insertByte(1);
		insertShort(idx);
		insertAscii(name.toCharArray());
	}

	void removeSkill(uint16 idx) {
		insertByte(0);
		insertShort(idx);
	}

		// startUpdate(1), insertInt(2) closes the datapad (i think)
	void updateDraftSchematics() {
		Player* player = play->getPlayer();
		int schematicSize = player->getDraftSchematicListSize();
		startUpdate(4);

		startList(schematicSize + 1, player->getDraftSchematicUpdateCount(schematicSize + 1));

		// This deletes all the draft schematics on the client
		insertByte(3);
		insertShort(0);

		for (int i = 0; i < schematicSize; i++) {
			insertByte(1);
			insertShort(i+1);
			insertInt(player->getDraftSchematic(i)->getObjectCRC());
			insertInt(player->getDraftSchematic(i)->getSchematicID());
		}
	}

	void addDraftSchematic(DraftSchematic* draftSchematic) {
		Player* player = play->getPlayer();
		int schematicSize = player->getDraftSchematicListSize();
		startUpdate(4);

		// This deletes all the draft schematics on the client
		insertByte(0);

		insertShort(schematicSize + 1);
		insertInt(draftSchematic->getSchematicID());
		insertInt(draftSchematic->getObjectCRC());
	}

	void removeDraftSchematic(DraftSchematic* draftSchematic) {
		Player* player = play->getPlayer();
		int schematicSize = player->getDraftSchematicListSize();
		startUpdate(4);

		insertByte(1);

		DraftSchematic* tempSchematic;
		int index = -1;
		for (int i = 0; i < schematicSize; i++) {
			tempSchematic = player->getDraftSchematic(i);

			if (tempSchematic->getGroupName() == draftSchematic->getGroupName()
					&& tempSchematic->getObjectCRC()
							== draftSchematic->getObjectCRC()) {
				index = i;
				break;
			}
		}

		insertShort(index);
		insertInt(tempSchematic->getSchematicID());
		insertInt(tempSchematic->getObjectCRC());
	}

	void updateFriendsList(){
		FriendsList* friendsList = play->getFriendsList();

		startUpdate(7);
		insertInt(friendsList->getCount() + 1); // Size of friends list + 1


		insertInt(friendsList->getMagicNumber());
		insertByte(3); // Dunno - seems to be 3 always //ToDO: Figure...

		insertShort(friendsList->getCount());

		for (int i = 0; i < friendsList->getCount(); ++i){
			insertAscii(friendsList->getFriendsName(i));
		}
	}

	void updateIgnoreList(){
		IgnoreList* ignoreList = play->getIgnoreList();

		startUpdate(8);
		insertInt(ignoreList->getCount() + 1); // Size of ignore list + 1


		insertInt(ignoreList->getMagicNumber());
		insertByte(3); // Dunno - seems to be 3 always //ToDO: Figure...

		insertShort(ignoreList->getCount());

		for (int i = 0; i < ignoreList->getCount(); ++i){
			insertAscii(ignoreList->getIgnoreName(i));
		}
	}

	void updateSkilsAndCertifications() {
		Player* player = play->getPlayer();

		int certSize = player->getCertificationListSize();
		int skillsSize = player->getCreatureSkillsSize();

		startUpdate(0);
		startList(certSize + skillsSize + 1, player->getNewCreatureSkillsCount(certSize + skillsSize + 1));

		insertByte(3);

		insertShort(certSize + skillsSize);
		for (int i = 0; i < skillsSize; i++) {
			insertAscii(player->getSkill(i));
		}

		for (int i = 0; i < certSize; i++)
			insertAscii(player->getCertification(i));
	}

	void updateStomachFilling() {
		addIntUpdate(0x0A, play->getFoodFilling());
		addIntUpdate(0x0B, play->getFoodFillingMax());
		addIntUpdate(0x0C, play->getDrinkFilling());
		addIntUpdate(0x0D, play->getDrinkFillingMax());
	}*/

};

#endif /*PLAYEROBJECTDELTAMESSAGE9_H_*/
