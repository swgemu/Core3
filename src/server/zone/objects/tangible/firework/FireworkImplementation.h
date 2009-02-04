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

#ifndef FIREWORKIMPLEMENTATION_H_
#define FIREWORKIMPLEMENTATION_H_

#include "../../player/Player.h"
#include "../../draftschematic/DraftSchematic.h"
#include "../../static/firework/FireworkWorld.h"
#include "../../../packets/object/Animation.h"
#include "../../../packets/tangible/TangibleObjectDeltaMessage3.h"

#include "Firework.h"

class FireworkImplementation : public FireworkServant {
protected:
	Player* ply;
	int animationType;

public:
	FireworkImplementation(Player* player, uint32 tempCRC, const UnicodeString& n, const String& tempn, int anim)
			: FireworkServant(player->getNewItemID(), FIREWORK) {

		objectCRC = tempCRC;
		animationType = anim;

		customName = n;

		templateTypeName = "firework_n";
		templateName = tempn;

		ply = player;
	}

	FireworkImplementation(unsigned long oid, unsigned int tempCRC, const UnicodeString n, const String tempname, int tp = 0)
			: FireworkServant(oid, FIREWORK) {

		objectCRC = tempCRC;

		customName = n;

		templateTypeName = "firework_n";
		templateName = tempname;

		init();
	}

	void init() {
		switch (objectCRC) {
		case 0xF9E2CBB8: // 1
		case 0x15ADE9E5: // s01
			animationType = 1;
		case 0xCEBA4172: // s02
		case 0x1A8A9B32: // 2
			animationType = 2;
		case 0x87B726FF: // s03
		case 0x50E06D6C: // 3
			animationType = 3;
		case 0x1A0F19FE: // 4
		case 0x7C540DEB: // s04
			animationType = 4;
		case 0x35596A66: // s05
		case 0xE87446BF: // 5
			animationType = 5;
		case 0x47888310: // s10
			animationType = 6;
		case 0x0E85E49D: // s11
			animationType = 7;
		case 0x06618416: // s18
			animationType = 8;
		case 0xFB00F899: // Show
		case 0xA0E061DC: // test
			animationType = 0;
		}
	}

	void parseItemAttributes() {

		String temp;

		temp = "charges";
		objectCount = (int)itemAttributes->getFloatAttribute(temp);

		temp = "craftersname";
		craftersName = itemAttributes->getStringAttribute(temp);

		temp = "craftedserial";
		craftedSerial = itemAttributes->getStringAttribute(temp);


	}

	void generateAttributes(SceneObject* obj) {

		if (!obj->isPlayer())
			return;

		Player* player = (Player*) obj;

		AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);

		addAttributes(alm);

		player->sendMessage(alm);

	}

	void addAttributes(AttributeListMessage* alm) {

		alm->insertAttribute("volume", "1");

		alm->insertAttribute("charges", objectCount);

		if (craftersName != ""){

			alm->insertAttribute("crafter", craftersName);
		}
		if (craftedSerial != ""){

			alm->insertAttribute("serial_number", craftedSerial);
		}

	}

	void updateCraftingValues(DraftSchematic* draftSchematic){

		String name;

		Player* player = draftSchematic->getCrafter();

		DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();
		//craftingValues->toString();

		name = "charges";
		objectCount = (int)craftingValues->getCurrentValue("charges");
		itemAttributes->setFloatAttribute(name, objectCount);

		TangibleObjectDeltaMessage3 * dtano3 = new TangibleObjectDeltaMessage3(_this);
		dtano3->setQuantity(objectCount);
		dtano3->close();
		player->sendMessage(dtano3);
	}

	int getAnimation() {
		return animationType;
	}

	int useObject(Player* player) {

		//now we launch it.
		launchFirework(player);

		if(objectCount > 1) {

			setObjectCount(objectCount--);

			TangibleObjectDeltaMessage3 * dtano3 = new TangibleObjectDeltaMessage3(_this);
			dtano3->setQuantity(objectCount);
			dtano3->close();
			player->sendMessage(dtano3);

		} else {

			player->removeInventoryItem(objectID);

			_this->sendDestroyTo(player);

			_this->finalize();
		}

		return 0;
	}

	void launchFirework(Player* player) {
		//Create the firework in the world.
		FireworkWorld* firework = new FireworkWorld(player);

		switch (animationType) {
			case 1:
				firework->setFireworkObject(0xEF5A1CF7);
				break;
			case 2:
				firework->setFireworkObject(0x344DB460);
				break;
			case 3:
				firework->setFireworkObject(0x7D40D3ED);
				break;
			case 4:
				firework->setFireworkObject(0x86A3F8F9);
				break;
			case 5:
				firework->setFireworkObject(0xCFAE9F74);
				break;
			case 6:
				firework->setFireworkObject(0xF472118F);
				break;
			case 7:
				firework->setFireworkObject(0xFC967104);
				break;
			case 8:
				firework->setFireworkObject(0xBD7F7602);
				break;
			default:
				firework->setFireworkObject(0xEF5A1CF7);
				break;
		}

		//TODO: 19519 -> setZoneProcessServer() is no included by "insertToZone()". If its running stable on TC for a while,
		//i will remove the comment and the commented line.
		//firework->setZoneProcessServer(server);
		firework->setDirection(0, 0, -0.64, 0.76);
		firework->insertToZone(player->getZone());

		player->setPosture(CreaturePosture::CROUCHED);

		Animation* anim = new Animation(player, "manipulate_low");
		player->broadcastMessage(anim, 128, true, true);
	}

};

#endif /*FIREWORKIMPLEMENTATION_H_*/
