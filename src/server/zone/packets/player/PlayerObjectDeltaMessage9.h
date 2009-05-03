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
#include "../../objects/player/Player.h"

#include "../../objects/draftschematic/DraftSchematic.h"

#include "../../objects/player/FriendsList.h"
#include "../../objects/player/IgnoreList.h"

class PlayerObjectDeltaMessage9 : public DeltaMessage {
	PlayerObject* play;

public:
	PlayerObjectDeltaMessage9(PlayerObject* pl)
			: DeltaMessage(pl->getObjectID(), 0x504C4159, 9) {
		play = pl;
	}

	void startSkillListUpdate(int skillsToUpdate) {
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

	void setExperimentationEnabled(bool experimenting) {
		startUpdate(1);
		if (experimenting){
			insertInt(3);  // 3 // 4
		}
		else {
			insertInt(1);
		}
	}

	void setCraftingState(int state) {
		startUpdate(2);
		insertInt(state);
	}

	void setClosestCraftingStation(uint64 oid) {
		startUpdate(3);
		insertLong(oid);
	}

	void startUpdateDraftSchematics(int count) {

		Player* player = play->getPlayer();

		startUpdate(4);
		startList(count, player->getDraftSchematicUpdateCount(count));
	}

	void removeDraftSchematic(uint16 index) {

		insertByte(0);
		insertShort(index);
	}

	void addDraftSchematic(DraftSchematic* draftSchematic) {

		Player* player = play->getPlayer();
		int index = player->getDraftSchematicMapSize();

		insertByte(1);

		insertShort(index);

		//insertLong(draftSchematic->getObjectID());

		insertInt(draftSchematic->getSchematicID());
		insertInt(draftSchematic->getObjectCRC());
	}


	void changeDraftSchematic(uint16 index, DraftSchematic* draftSchematic) {

		insertByte(2);
		insertShort(index);

		//insertLong(draftSchematic->getObjectID());
		insertInt(draftSchematic->getSchematicID());
		insertInt(draftSchematic->getObjectCRC());
	}

	void clearDraftSchematics() {

		DraftSchematic* draftSchematic;
		Player* player = play->getPlayer();

		insertByte(4);
	}

	void resetDraftSchematics() {

		DraftSchematic* draftSchematic;
		Player* player = play->getPlayer();

		insertByte(3);

		for(int i = 0; i < player->getDraftSchematicMapSize(); ++i) {

			draftSchematic = player->getDraftSchematicByIndex(i);

			//insertLong(draftSchematic->getObjectID());
			insertInt(draftSchematic->getSchematicID());
			insertInt(draftSchematic->getObjectCRC());
		}
	}

	void setExperimentationPoints(int points){
		startUpdate(5);
		insertInt(points); // Number of experimentation points
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
	}

};

#endif /*PLAYEROBJECTDELTAMESSAGE9_H_*/
