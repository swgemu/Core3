/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef PLAYEROBJECTDELTAMESSAGE9_H_
#define PLAYEROBJECTDELTAMESSAGE9_H_

#include "../DeltaMessage.h"
#include "../../objects/player/PlayerObject.h"

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
