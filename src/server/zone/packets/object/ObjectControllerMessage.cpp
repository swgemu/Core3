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

#include "../../../ServerCore.h"

#include "../../Zone.h"
#include "../../ZoneServer.h"

#include "../../ZoneProcessServerImplementation.h"

#include "../../managers/player/PlayerManager.h"

#include "../../managers/item/ItemManager.h"
#include "../../managers/mission/MissionManager.h"
#include "../../managers/radial/RadialManager.h"
#include "../../managers/resource/ResourceManager.h"
#include "../../managers/loot/LootManager.h"
#include "../../managers/planet/PlanetManager.h"
#include "../../managers/slashcommands/SlashCommandManager.h"

#include "../../managers/skills/imagedesign/ImageDesignCustomization.h"

#include "../../objects.h"

#include "../../managers/combat/CommandQueueAction.h"

#include "ObjectControllerMessage.h"
#include "CommandQueueRemove.h"

#include "../../packets.h"

ObjectControllerMessage::ObjectControllerMessage(uint64 objid, uint32 header1,
		uint32 header2, bool comp) :
	BaseMessage() {
	insertShort(0x05);
	insertInt(0x80CE5E46); // CRC
	insertInt(header1);
	insertInt(header2);
	insertLong(objid);
	insertInt(0x00);

	setCompression(comp);
}

bool ObjectControllerMessage::parseDataTransform(Player* player, Message* pack) {
	//System::out << pack->toString() << "\n";
	pack->shiftOffset(8); // skip ObjectID and size

	uint32 movementStamp = pack->parseInt();
	uint32 movementCounter = pack->parseInt();

	float x;
	float z;
	float y;

	float dx = pack->parseFloat();
	float dy = pack->parseFloat();
	float dz = pack->parseFloat();
	float dw = pack->parseFloat();

	//System::out << "dir vector x:" << dx << " dz:" << dz << " dy:" << dy << " dw:" << dw << "\n";

	x = pack->parseFloat();
	z = pack->parseFloat();
	y = pack->parseFloat();

	if (x > 8192.0f || x < -8192.0f || y > 8192.0f || y < -8192.0f) {
		player->error("position out of bounds...");
		return false;
	}

	if (!player->isOnline())
		return false;

	uint32 lastStamp = player->getLastMovementUpdateStamp();

	if (lastStamp == 0 || lastStamp > movementStamp) {
		player->updateServerMovementStamp();

		player->setLastMovementUpdateStamp(movementStamp);

		player->setLastTestPositionX(x);
		player->setLastTestPositionY(y);
	} else {
		uint32 deltaStamp = (movementStamp - lastStamp);

		uint64 serverStamp = player->getLastServerMovementStamp();

		player->setLastMovementUpdateStamp(movementStamp);

		player->updateServerMovementStamp();

		if ((serverStamp > 50) && ((serverStamp + 250) < (uint64) deltaStamp)) {
			StringBuffer deltas;
			deltas << "speed hack detected " << "deltaStamp:[" << deltaStamp
					<< "] serversStamp:[" << serverStamp << "]";
			player->info(deltas.toString());

			player->bounceBack();
			return false;
		}

		int ignoreMovements = player->getIgnoreMovementTests();

		SceneObject* parent = player->getParent();

		if (ignoreMovements > 0) {
			player->setIgnoreMovementTests(--ignoreMovements);
		} else if (parent == NULL || !parent->isCell()) {
			float lastPosX = player->getLastTestPositionX();
			float lastPosY = player->getLastTestPositionY();

			float dist = sqrt(((x - lastPosX) * (x - lastPosX)) + ((y
					- lastPosY) * (y - lastPosY)));

			float speed = dist * 1000 / (float) deltaStamp;

			if (speed > player->getSpeed() * 1.5) {
				StringBuffer msg;
				msg << "SpeedHack detected on player: ["
						<< player->getFirstName() << "]\n";
				msg << "Player Speed:" << player->getSpeed()
						<< " caught speed:" << speed << "\n";
				player->info(msg.toString());

				player->setLastTestPositionX(x);
				player->setLastTestPositionY(y);

				player->bounceBack();
				return false;
			}
		}

		player->setLastTestPositionX(x);
		player->setLastTestPositionY(y);
	}

	//System::out << "Movement counter:" << movementCounter << "\n";

	player->setMovementCounter(movementCounter);

	player->setDirection(dx, dz, dy, dw);
	player->setPosition(x, z, y);

	/*System::out << "Player [" << player->getObjectID() << "] - Counter [" << player->getMovementCounter() << "]"
	 << " - Position (" << (int) x << "," << (int) z << "," << (int) y << ")\n";*/

	return true;
}

uint64 ObjectControllerMessage::parseDataTransformWithParent(Player* player,
		Message* pack) {
	//System::out << pack->toString() << "\n";
	if (!player->isOnline())
		return 0;

	pack->shiftOffset(8); // skip ObjectID and size

	uint32 movementStamp = pack->parseInt();

	player->setMovementCounter(pack->parseInt() + 1);

	uint64 parent = pack->parseLong();
	uint64 oldParent = 0;

	Zone* zone = player->getZone();
	if (zone == NULL)
		return 0;

	if (player->getParent() != NULL)
		oldParent = player->getParent()->getObjectID();

	if (oldParent != parent) {
		ItemManager* itemManager = zone->getZoneServer()->getItemManager();
		if (itemManager != NULL) {
			itemManager->loadStructurePlayerItems(player, parent);
		}
	}

	if (zone->lookupObject(parent) == NULL)
		return 0;

	float dx = pack->parseFloat();
	float dy = pack->parseFloat();
	float dz = pack->parseFloat();
	float dw = pack->parseFloat();

	float x = pack->parseFloat();
	float z = pack->parseFloat();
	float y = pack->parseFloat();

	if (x > 1024.0f || x < -1024.0f || y > 1024.0f || y < -1024.0f) {
		StringBuffer msg;
		msg << "position out of bounds cell:[" << parent << "]";
		player->error(msg.toString());
		return 0;
	}

	uint32 lastStamp = player->getLastMovementUpdateStamp();

	if (lastStamp == 0 || lastStamp > movementStamp) {
		player->updateServerMovementStamp();

		player->setLastMovementUpdateStamp(movementStamp);

		player->setLastTestPositionX(x);
		player->setLastTestPositionY(y);
	} else {
		uint32 deltaStamp = (movementStamp - lastStamp);

		uint64 serverStamp = player->getLastServerMovementStamp();

		player->setLastMovementUpdateStamp(movementStamp);

		player->updateServerMovementStamp();

		if ((serverStamp > 50) && ((serverStamp + 250) < (uint64) deltaStamp)) {
			StringBuffer deltas;
			deltas << "speed hack detected " << "deltaStamp:[" << deltaStamp
					<< "] serversStamp:[" << serverStamp << "]";
			player->info(deltas.toString());

			player->bounceBack();
			return 0;
		}

		int ignoreMovements = player->getIgnoreMovementTests();

		if (ignoreMovements > 0) {
			player->setIgnoreMovementTests(--ignoreMovements);
		} else if (player->getParent() != NULL) {
			float lastPosX = player->getLastTestPositionX();
			float lastPosY = player->getLastTestPositionY();

			float dist = sqrt(((x - lastPosX) * (x - lastPosX)) + ((y
					- lastPosY) * (y - lastPosY)));

			float speed = dist * 1000 / (float) deltaStamp;

			if (speed > player->getSpeed() * 1.5) {
				StringBuffer msg;
				msg << "SpeedHack detected on player: ["
						<< player->getFirstName() << "]\n";
				msg << "Player Speed:" << player->getSpeed()
						<< " caught speed:" << speed << "\n";
				player->info(msg.toString());

				player->setLastTestPositionX(x);
				player->setLastTestPositionY(y);

				player->bounceBack();
				return 0;
			}
		}

		player->setLastTestPositionX(x);
		player->setLastTestPositionY(y);
	}

	/*
	 // if we changed cell
	 if (oldParent != parent)
	 {
	 // Just entered building
	 if (oldParent != 0)
	 {
	 // Remove from old parent cell?

	 }
	 else // from outside
	 {
	 // Remove from quadtree? before entering?
	 }

	 // Add to cell
	 UpdateContainmentMessage* link = new UpdateContainmentMessage(player->getObjectID(), parent, 0x04);
	 player->broadcastMessage(link);
	 }*/

	player->setDirection(dx, dz, dy, dw);
	player->setPosition(x, z, y);
	player->setLastMovementUpdateStamp(movementStamp);

	return parent;

	/*System::out << "Player [" << player->getObjectID() << "] with Parent [" << parent << "] - Counter [" << player->getMovementCounter() << "]"
	 << " - Position (" << (int) x << "," << (int) z << "," << (int) y << ")\n";*/
}

void ObjectControllerMessage::parseObjectTargetUpdate(Player* player,
		Message* pack) {
	pack->shiftOffset(12); // skip ObjectID and size

	uint64 target = pack->parseLong();
	player->updateTarget(target);
}

void ObjectControllerMessage::parseCommandQueueEnqueue(Player* player,
		Message* pack, ZoneProcessServerImplementation* serv) {

	/**
	 * Player is wlock() upon entry
	 */

	pack->shiftOffset(12); // skip ObjectID and size

	//uint64 objectid = pack->parseLong(); // grab object id
	//pack->shiftOffset(4); // skip size

	uint32 actioncntr = pack->parseInt();
	uint32 actionCRC = pack->parseInt();
	uint64 target; //?
	UnicodeString name; //?

	//System::out << "acrc: " << actionCRC << "\n";

	if (actionCRC == 0) {
		player->clearQueueAction(actioncntr, 0.0f, 0, 0);
		return;
	}

	player->setActionCounter(actioncntr);

	SkillManager* skillManager = serv->getSkillManager();
	if (skillManager == NULL)
		return;

	Skill* sk = skillManager->getSkill(actionCRC);
	if (sk != NULL) {
		target = pack->parseLong();

		UnicodeString option = UnicodeString("");
		pack->parseUnicode(option);
		String  actionModifier = option.toString();

		bool canPerform = sk->canPerform(player, pack);
		if (!canPerform)
			sendErrMsg(actioncntr, sk, player);
		else {
			//System::out << "Skill: " << sk->getSkillName() << " modifier: " << actionModifier << "\n";
			if (sk->isInstant())
				player->doInstantAction(target, actionCRC, actioncntr,
						actionModifier.toCharArray());
			else
				player->queueAction(player, target, actionCRC, actioncntr,
						actionModifier.toCharArray());
		}

		return;
	}

	SlashCommandManager* scManager = serv->getSlashCommandManager();
	if (scManager == NULL)
		return;

	SlashCommand* sc = scManager->getSlashCommand(actionCRC);
	if (sc != NULL) {
		bool completed = sc->doSlashCommand(player, pack);
		if (!completed)
			sc->onFail(actioncntr, player);
		else{
			sc->onComplete(actioncntr, player);
			if (sc->addToCombatQueue())
				player->clearQueueAction(actioncntr);
		}
		return;
	}

	player->clearQueueAction(actioncntr, 0, 2, 0);

}

/*
 * Unsuccessful skill completion alerts the player of the invalid state
 */
void ObjectControllerMessage::sendErrMsg(uint32 actioncntr, Skill* skill, Player* player) {

	uint64 states = skill->getStateMask() & player->getStateBitmask();

	if (!skill->checkStateMask(player)) {

		uint64 state = 1;
		int num = 0;

		while (num < 34) {
			if (states & state) {

				player->clearQueueAction(actioncntr, 0, 5, num);
				return;

			}

			state *= 2;
			++num;
		}
	}

	/*
	 * SOE is stupid so player postures do NOT match up with their respective client error message
	 * Because of this, we have to have this switch statement to match them up manually
	 * */
	if (!skill->checkInvalidPostures(player)){

		switch(player->getPosture()) {
		case(CreaturePosture::UPRIGHT):
			player->clearQueueAction(actioncntr, 0, 1, 0);
			break;
		case(CreaturePosture::CROUCHED):
			player->clearQueueAction(actioncntr, 0, 1, 4);
		break;
		case(CreaturePosture::PRONE):
			player->clearQueueAction(actioncntr, 0, 1, 7);
			break;
		case(CreaturePosture::SNEAKING):
			player->clearQueueAction(actioncntr, 0, 1, 5);
			break;
		case(CreaturePosture::BLOCKING):
			player->clearQueueAction(actioncntr, 0, 1, 21);
			break;
		case(CreaturePosture::CLIMBING):
			player->clearQueueAction(actioncntr, 0, 1, 10);
			break;
		case(CreaturePosture::FLYING):
			player->clearQueueAction(actioncntr, 0, 1, 12);
			break;
		case(CreaturePosture::LYINGDOWN):
			player->clearQueueAction(actioncntr, 0, 1, 13);
			break;
		case(CreaturePosture::SITTING):
			player->clearQueueAction(actioncntr, 0, 1, 14);
			break;
		case(CreaturePosture::SKILLANIMATING):
			player->clearQueueAction(actioncntr, 0, 1, 15);
			break;
		case(CreaturePosture::DRIVINGVEHICLE):
			player->clearQueueAction(actioncntr, 0, 1, 16);
			break;
		case(CreaturePosture::RIDINGCREATURE):
			player->clearQueueAction(actioncntr, 0, 1, 17);
			break;
		case(CreaturePosture::KNOCKEDDOWN):
			player->clearQueueAction(actioncntr, 0, 1, 18);
			break;
		case(CreaturePosture::INCAPACITATED):
			player->clearQueueAction(actioncntr, 0, 1, 19);
			break;
		case(CreaturePosture::DEAD):
			player->clearQueueAction(actioncntr, 0, 1, 20);
			break;
		default:
			player->clearQueueAction(actioncntr);
			break;
		}
	}
}

void ObjectControllerMessage::parseCommandQueueClear(Player* player,
		Message* pack) {
	pack->shiftOffset(12); // skip ObjectID and size

	uint32 actioncntr = pack->parseInt();
	uint32 actionCRC = pack->parseInt();
	uint64 target;

	player->deleteQueueAction(actioncntr);
}

void ObjectControllerMessage::parseRadialRequest(Player* player, Message* pack,
		RadialManager* radialManager) {
	radialManager->handleRadialRequest(player, pack);
}

void ObjectControllerMessage::parseImageDesignCancel(Player* player,
		Message* pack) {
	// TODO combine these functions together
	try {
		// Read the Packet
		uint64 object = pack->parseLong();
		pack->shiftOffset(4); // size ?

		uint64 designer = pack->parseLong();
		uint64 target = pack->parseLong();
		uint64 tent = pack->parseLong();

		uint8 type = pack->parseByte();

		ImageDesignRejectMessage* msg_designer = new ImageDesignRejectMessage(
				designer, designer, target, tent, 0);
		ImageDesignRejectMessage* msg_target = new ImageDesignRejectMessage(
				target, designer, target, tent, 0);

		// Parse
		String hairObject;
		pack->parseAscii(hairObject);

		// Pack
		msg_designer->insertAscii(hairObject);
		msg_target->insertAscii(hairObject);

		// Parse
		String unknownString_1;
		pack->parseAscii(unknownString_1);

		// Pack
		msg_designer->insertAscii(unknownString_1);
		msg_target->insertAscii(unknownString_1);

		uint32 unknown_int_1 = pack->parseInt(); //  02 00 00 00  was set in stat migration button, zero for other?
		uint32 timestamp = pack->parseInt(); //   timestamp 1212950001 (2008-06-8 18:33:21Z)

		// Pack
		msg_designer->insertInt(unknown_int_1);
		msg_designer->insertInt(timestamp);
		msg_target->insertInt(unknown_int_1);
		msg_target->insertInt(timestamp);

		// Parse
		uint32 required_payment = pack->parseInt();
		uint32 offered_payment = pack->parseInt();

		// Pack
		msg_designer->insertInt(required_payment);
		msg_designer->insertInt(offered_payment);
		msg_target->insertInt(required_payment);
		msg_target->insertInt(offered_payment);

		uint8 designer_accepted = pack->parseByte();

		// Pack
		msg_designer->insertByte(designer_accepted);
		msg_target->insertByte(designer_accepted);

		// Parse
		uint32 target_accepted = pack->parseInt();

		//Pack
		msg_designer->insertInt(target_accepted);
		//msg_designer->insertInt(0x02);
		msg_target->insertInt(target_accepted);

		// Parse
		uint8 stat_migration = pack->parseByte();

		// Pack (I didn't find this byte in the live server->client)
		msg_designer->insertByte(stat_migration);
		msg_target->insertByte(stat_migration);

		// Parse
		uint32 unknown_int_4 = pack->parseInt();
		uint32 unknown_int_5 = pack->parseInt();
		uint32 unknown_int_6 = pack->parseInt();
		uint32 unknown_int_7 = pack->parseInt();

		// Pack
		msg_designer->insertInt(unknown_int_4);
		msg_designer->insertInt(unknown_int_5);
		msg_designer->insertInt(unknown_int_6);
		msg_designer->insertInt(unknown_int_7);

		msg_target->insertInt(unknown_int_4);
		msg_target->insertInt(unknown_int_5);
		msg_target->insertInt(unknown_int_6);
		msg_target->insertInt(unknown_int_7);

		// Parse
		uint32 size_float_attrs = pack->parseInt();

		// Pack
		msg_designer->insertInt(size_float_attrs);
		msg_target->insertInt(size_float_attrs);

		// Parse
		if (size_float_attrs > 0) {
			for (int i = 0; i < size_float_attrs; i++) {
				// do something later
				String attr;
				pack->parseAscii(attr);
				float val = pack->parseFloat();

				// Pack
				msg_designer->insertAscii(attr);
				msg_designer->insertFloat(val);
				msg_target->insertAscii(attr);
				msg_target->insertFloat(val);
			}
		}

		// Parse
		uint32 size_int_attrs = pack->parseInt();

		// Pack
		msg_designer->insertInt(size_int_attrs);
		msg_target->insertInt(size_int_attrs);

		// Parse
		if (size_int_attrs > 0) {
			for (int i = 0; i < size_int_attrs; i++) {
				// do something later
				String attr;
				pack->parseAscii(attr);
				uint32 val = pack->parseInt();

				// Pack
				msg_designer->insertAscii(attr.toCharArray());
				msg_designer->insertInt(val);
				msg_target->insertAscii(attr.toCharArray());
				msg_target->insertInt(val);
			}
		}

		// Parse
		String emote;
		pack->parseAscii(emote);

		// Pack
		msg_designer->insertAscii(emote);
		msg_target->insertAscii(emote);

		SceneObject* target_object = player->getZone()->lookupObject(target);
		SceneObject* designer_object =
				player->getZone()->lookupObject(designer);

		// If from designer send to target
		if (designer == target) {

			// do something else?
		} else if (player->getObjectID() == designer) {
			if (target_object != NULL)
				((Player *) target_object)->sendMessage(msg_target);

			// If from target send to designer
		} else if (player->getObjectID() == target) {

			if (designer_object != NULL) {
				//((Player *)designer_object)->sendSystemMessage("update from target!");
				//player->info(msg.toString());
				//player->info(msg_designer->toString());
				((Player *) designer_object)->sendMessage(msg_designer);
			}
		}

	} catch (...) {
		System::out
				<< "unreported ObjectControllerMessage::parseImageDesignReject(Player* player, Message* pack) exception\n";
	}
}

void ObjectControllerMessage::parseImageDesignChange(Player* player,
		Message* pack, ZoneProcessServerImplementation* serv) {
	int xpval = 0;

	try {
		/*player->sendSystemMessage("Image Designer Update");
		 player->info("Image Design Change - Original Packet");
		 player->info(pack->toString());*/

		// Read the Packet
		uint64 object = pack->parseLong();
		pack->shiftOffset(4); // size ?

		uint64 designer = pack->parseLong();
		uint64 target = pack->parseLong();
		uint64 tent = pack->parseLong();

		uint8 type = pack->parseByte();

		ImageDesignChangeMessage* msg_designer = new ImageDesignChangeMessage(
				designer, designer, target, tent, 0);
		ImageDesignChangeMessage* msg_target = new ImageDesignChangeMessage(
				target, designer, target, tent, 0);

		// Parse
		String hairObject;
		pack->parseAscii(hairObject);

		// Pack
		msg_designer->insertAscii(hairObject);
		msg_target->insertAscii(hairObject);

		// Parse
		String unknownString_1;
		pack->parseAscii(unknownString_1);

		// Pack
		msg_designer->insertAscii(unknownString_1);
		msg_target->insertAscii(unknownString_1);

		uint32 unknown_int_1 = pack->parseInt(); //  02 00 00 00  was set in stat migration button, zero for other?
		uint32 timestamp = pack->parseInt(); //   timestamp 1212950001 (2008-06-8 18:33:21Z)

		// Pack
		msg_designer->insertInt(unknown_int_1);
		msg_designer->insertInt(timestamp);
		msg_target->insertInt(unknown_int_1);
		msg_target->insertInt(timestamp);

		// Parse
		uint32 required_payment = pack->parseInt();
		uint32 offered_payment = pack->parseInt();

		// Pack
		msg_designer->insertInt(required_payment);
		msg_designer->insertInt(offered_payment);
		msg_target->insertInt(required_payment);
		msg_target->insertInt(offered_payment);

		uint8 designer_accepted = pack->parseByte();

		// Pack
		msg_designer->insertByte(designer_accepted);
		msg_target->insertByte(designer_accepted);

		// Parse
		uint32 target_accepted = pack->parseInt();

		//Pack
		msg_designer->insertInt(target_accepted);
		//msg_designer->insertInt(0x02);
		msg_target->insertInt(target_accepted);

		// Parse
		uint8 stat_migration = pack->parseByte();

		// Pack (I didn't find this byte in the live server->client)
		msg_designer->insertByte(stat_migration);
		msg_target->insertByte(stat_migration);

		// Parse
		uint32 unknown_int_4 = pack->parseInt();
		uint32 unknown_int_5 = pack->parseInt();
		uint32 unknown_int_6 = pack->parseInt();
		uint32 unknown_int_7 = pack->parseInt();

		// Pack
		msg_designer->insertInt(unknown_int_4);
		msg_designer->insertInt(unknown_int_5);
		msg_designer->insertInt(unknown_int_6);
		msg_designer->insertInt(unknown_int_7);

		msg_target->insertInt(unknown_int_4);
		msg_target->insertInt(unknown_int_5);
		msg_target->insertInt(unknown_int_6);
		msg_target->insertInt(unknown_int_7);

		// Parse
		uint32 size_float_attrs = pack->parseInt();

		// Pack
		msg_designer->insertInt(size_float_attrs);
		msg_target->insertInt(size_float_attrs);

		SceneObject* target_object = player->getZone()->lookupObject(target);
		SceneObject* designer_object =
				player->getZone()->lookupObject(designer);

		bool commitChanges = false;
		if (designer_accepted == 1 && target_object == designer_object
				&& target_object != NULL)
			commitChanges = true;

		if (target_accepted == 1 && designer_accepted == 1 && target_object
				!= designer_object && target_object != NULL)
			commitChanges = true;

		// This is a helper class for a bunch of the embedded logic
		ImageDesignCustomization* customization = NULL;

		try {

			if (target_object != NULL && player != target_object)
				target_object->wlock(player);

			if (commitChanges)
				customization = new ImageDesignCustomization(serv,
						((CreatureObject *) target_object));

			// Parse
			if (size_float_attrs > 0) {
				for (int i = 0; i < size_float_attrs; i++) {
					// do something later
					String attr;
					pack->parseAscii(attr);
					float val = pack->parseFloat();

					// Pack
					msg_designer->insertAscii(attr);
					msg_designer->insertFloat(val);
					msg_target->insertAscii(attr);
					msg_target->insertFloat(val);

					if (commitChanges)
						customization->updateCustomization(attr, val);
				}

				if (xpval < 300)
					xpval = 300;
			}

			// Parse
			uint32 attributesSize = pack->parseInt();

			// Pack
			msg_designer->insertInt(attributesSize);
			msg_target->insertInt(attributesSize);

			// Parse
			if (attributesSize > 0) {
				for (int i = 0; i < attributesSize; i++) {
					// do something later
					String attr;
					pack->parseAscii(attr);
					uint32 val = pack->parseInt();

					// Pack
					msg_designer->insertAscii(attr.toCharArray());
					msg_designer->insertInt(val);
					msg_target->insertAscii(attr.toCharArray());
					msg_target->insertInt(val);

					if (commitChanges)
						customization->updateCustomization(attr, val);
				}

				if (xpval < 100)
					xpval = 100;
			}

			if (target_object != NULL && player != target_object)
				target_object->unlock();
		} catch (...) {
			if (target_object != NULL && player != target_object)
				target_object->unlock();
		}

		// Parse
		String emote;
		pack->parseAscii(emote);

		// Pack
		msg_designer->insertAscii(emote);
		msg_target->insertAscii(emote);

		// If from designer send to target
		if (designer == target) {
			// do something else?
		} else if (player->getObjectID() == designer) {
			if (target_object != NULL)
				((Player *) target_object)->sendMessage(msg_target);

			// If from target send to designer
		} else if (player->getObjectID() == target) {
			if (designer_object != NULL) {
				//((Player *)designer_object)->sendSystemMessage("update from target!");
				//player->info(msg.toString());
				//player->info(msg_designer->toString());
				((Player *) designer_object)->sendMessage(msg_designer);
			}
		}

		if (commitChanges) {
			//Update Hair
			if (!hairObject.isEmpty()) {
				int idx = hairObject.indexOf("hair_");
				if (idx != -1) {
					hairObject = hairObject.replaceFirst("hair_",
							"shared_hair_");

					player->setHairObject(hairObject);
					player->updateHair();

					/*StringBuffer msg;
					 msg << "imagedesignerupdate, hairObject:" << hex << hairObject;
					 ((Player *)target_object)->sendSystemMessage(msg.toString());*/
				}

				if (xpval < 100)
					xpval = 100;
			}

			PlayerManager* playerManager = serv->getZoneServer()->getPlayerManager();

			// Stat Migration
			if (stat_migration > 0) {
				player->migrateStats();
				xpval = 2000;
			}

			// Add Experience
			String xptype("imagedesigner");
			if (designer == target) {
				if (!player->getImagedesignXpGiven()) {
					xpval /= 2;
					player->addXp(xptype, xpval, true);
					player->setImagedesignXpGiven(true);
				} else
					player->setImagedesignXpGiven(false);
			} else if (player->getObjectID() == target) {
				if (designer_object->isPlayer()) {
					Player* designer_player = (Player*) designer_object;
					designer_player->addXp(xptype, xpval, true);
				}
			}

			if (customization != NULL)
				delete customization;

			if (target_object != NULL)
				((CreatureObject *) target_object)->updateCharacterAppearance();

			if (playerManager != NULL)
				playerManager->updatePlayerAppearanceToDatabase(player);
		}
	} catch (...) {
		System::out << "unreported ObjectControllerMessage::parseImageDesignChange(Player* player, Message* pack) exception\n";
	}
}

void ObjectControllerMessage::parseResourceEmptyHopper(Player* player, Message* pack) {

	pack->shiftOffset(20); //Shift past the playerid.

	uint64 harvesterid = pack->parseLong();
	uint64 resourceid = pack->parseLong();

	float quantity = (float) pack->parseInt(); // need to verify the quantity exists in the hopper

	bool discard = (bool) pack->parseByte(); // Are we retrieving or discarding.
	uint8 byte2 = pack->parseByte(); // unknown

	SceneObject* object = player->getZone()->lookupObject(harvesterid);

	if (object != NULL) {
		if (object->isTangible() && ((TangibleObject*)object)->isInstallation()) {
			InstallationObject* installation = (InstallationObject*) object;

			if (installation->isHarvester() || installation->isGenerator()) {
				HarvesterObject* harvester = (HarvesterObject*) installation;

				try {
					harvester->wlock(player);

					if (discard) {
						harvester->discardResource(player, resourceid, quantity);
					} else {
						harvester->retrieveResource(player, resourceid, quantity);
					}

					harvester->unlock();
				} catch (...) {
					player->error("Unhandled exception in ObjectControllerMessage::parseResourceEmptyHopper()");
					harvester->unlock();
				}

				GenericResponse* gr = new GenericResponse(player, 0xED, 1, byte2);
				player->sendMessage(gr);
			}
		}
	}

}

// Missions
void ObjectControllerMessage::parseMissionListRequest(Player* player, Message* pack) {
	//skip objId + old size + unk byte + refresh byte
	pack->shiftOffset(14);

	//Grab the mission terminal id
	uint64 termId = pack->parseLong();

	//TODO: Take the error messages out after testing
	PlanetManager* plnMgr = player->getZone()->getPlanetManager();
	if (plnMgr == NULL) {
		System::out << "Error: Planet Manager NULL in parseMissionListRequest() \n";
		return;
	}

	MissionTerminal* mt = plnMgr->getMissionTerminal(termId);
	if (mt == NULL) {
		//Turn this message off after testing: (this msg will be frequent until we have a complete static object table)
		//System::out << "Error: Mission Terminal object NULL in parseMissionListRequest(). Mission Terminal does not exist! \n";
		return;
	}

	MissionManager* misoMgr = player->getZone()->getZoneServer()->getMissionManager();
	if (misoMgr == NULL) {
		System::out << "Error: Mission Manager NULL in parseMissionListRequest() \n";
		return;
	}

	misoMgr->sendTerminalData(player, mt->getTerminalMask(), true);
}

void ObjectControllerMessage::parseMissionAccept(Player* player, Message* pack) {
	//skip objId + old size
	pack->shiftOffset(12);

	//Grab the mission object id
	uint64 misoId = pack->parseLong();

	MissionManager* misoMgr =
			player->getZone()->getZoneServer()->getMissionManager();
	if (misoMgr == NULL) {
		System::out << "Error: Mission Manager NULL in parseMissionAccept() \n";
		return;
	}

	misoMgr->doMissionAccept(player, misoId, true);
}

void ObjectControllerMessage::parseMissionAbort(Player* player, Message* pack) {
	//skip objId + old size
	pack->shiftOffset(12);

	//Grab the mission object id
	uint64 misoId = pack->parseLong();

	MissionManager* misoMgr =
			player->getZone()->getZoneServer()->getMissionManager();
	if (misoMgr == NULL) {
		System::out << "Error: Mission Manager NULL in parseMissionAbort() \n";
		return;
	}

	misoMgr->doMissionAbort(player, misoId, true);
}

void ObjectControllerMessage::parseAddCraftingResource(Player* player, Message* packet) {

	CraftingTool* craftingTool = player->getActiveCraftingTool();

	if(craftingTool == NULL)
		return;

	packet->shiftOffset(12);

	uint64 resourceObjectID = packet->parseLong();

	int slot = packet->parseInt();

	packet->shiftOffset(4);

	int counter = packet->parseByte();

	ManagedReference<SceneObject> invObj = player->getInventoryItem(resourceObjectID);

	if (invObj != NULL && invObj->isTangible()) {
		TangibleObject* tano = (TangibleObject*) invObj.get();

		CraftingManager* craftingManager = player->getZone()->getZoneServer()->getCraftingManager();
		craftingManager->addIngredientToSlot(craftingTool, player, tano, slot, counter);

	} else {
		// This else should never execute
		player->sendSystemMessage("Add resource invalid, contact kyle");

	}
}

void ObjectControllerMessage::parseRemoveCraftingResource(Player* player, Message* packet) {

	CraftingTool* craftingTool = player->getActiveCraftingTool();

	if(craftingTool == NULL)
		return;

	packet->shiftOffset(12);

	int slot = packet->parseInt();

	uint64 resID = packet->parseLong();

	int counter = packet->parseByte();

	CraftingManager* craftingManager = player->getZone()->getZoneServer()->getCraftingManager();
	craftingManager->removeIngredientFromSlot(craftingTool, player, slot, counter);

}

void ObjectControllerMessage::parseCraftCustomization(Player* player, Message* packet) {

	CraftingTool* craftingTool = player->getActiveCraftingTool();

	if(craftingTool == NULL)
		return;

	packet->shiftOffset(12);

	UnicodeString n;
	packet->parseUnicode(n);

	String name = n.toString();

	packet->shiftOffset(1);

	int manufacturingSchematicCount = packet->parseInt();

	int customizationcount = packet->parseByte();

	int value, count;

	StringBuffer ss;

	for (int i = 0; i < customizationcount; ++i) {

		count = packet->parseInt();

		value = packet->parseInt();

		ss << count << " " << value;

		if (i < customizationcount - 1)
			ss << " ";
	}

	String customizationString = ss.toString();

	CraftingManager* craftingManager = player->getZone()->getZoneServer()->getCraftingManager();
	craftingManager->craftingCustomization(craftingTool, player, name, manufacturingSchematicCount, customizationString);
}

void ObjectControllerMessage::parseExperimentation(Player* player, Message* pack) {

	CraftingTool* craftingTool = player->getActiveCraftingTool();

	if(craftingTool == NULL)
		return;

	pack->shiftOffset(12);

	int counter = pack->parseByte();

	if (player->canExperiment()) {

		player->setLastExperimentationAttempt();

		int numRowsAttempted = pack->parseInt();

		int rowEffected, pointsAttempted;
		StringBuffer ss;

		for (int i = 0; i < numRowsAttempted; ++i) {

			rowEffected = pack->parseInt();
			pointsAttempted = pack->parseInt();

			ss << rowEffected << " " << pointsAttempted << " ";
		}

		String expString = ss.toString();

		CraftingManager* craftingManager = player->getZone()->getZoneServer()->getCraftingManager();
		craftingManager->handleExperimenting(craftingTool, player, counter, numRowsAttempted, expString);

	} else {
		player->sendSystemMessage("healing_response", "healing_must_wait");

		ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x0113);
		objMsg->insertInt(0x105);

		objMsg->insertInt(8); // Experimentation Result
		// 0 = Amazing
		// 1 = Great
		// 2 = Good
		// 3 = Moderate
		// 4 = A success
		// 5 = Marginally Successful
		// 6 = "ok"
		// 7 = Barely Succeeded
		// 8 = Critical Failure
		objMsg->insertByte(counter);

		player->sendMessage(objMsg);
	}
}

void ObjectControllerMessage::parsePickup(Player* player, Message* pack) {
	//System::out << pack->toString() << "\n";
}

void ObjectControllerMessage::parseItemDropTrade(Player* player, Message* pack) {
	uint64 targetPlayerId = pack->parseLong();

	pack->shiftOffset(16);

	uint64 tradeItemId = pack->parseLong();

	ManagedReference<SceneObject> obj = player->getZone()->lookupObject(targetPlayerId);
	ManagedReference<SceneObject> item = player->getZone()->lookupObject(tradeItemId);

	if (obj == NULL || item == NULL)
		return;

	if (!obj->isPlayer() || !item->isPlayer())
		return;

	Player* sender = (Player*) obj.get();
	Player* receiver = (Player*) item.get();

	if (sender != NULL && receiver != NULL) {

		sender->setTradeRequestedPlayer(receiver->getObjectID());

		StfParameter* params = new StfParameter();
		params->addTU(player->getCharacterName().toString());

		receiver->sendSystemMessage("ui_trade", "requested_prose", params);

		delete params;
	}
}

void ObjectControllerMessage::parseRotateItem(Player* player, Message* pack) {
	uint64 target = pack->parseLong();

	SceneObject* object = player->getZone()->getZoneServer()->getObject(target,
			true);

	try {
		object->wlock(player);

		object->setDirection(object->getDirectionX(), (object->getDirectionZ()
				+ sqrt(.5)), object->getDirectionY(), (object->getDirectionW()
				+ sqrt(.5)));

		object->unlock();
	} catch (...) {
		object->unlock();
		System::out
				<< "unreported exception caught in ObjectControllerMessage::parseRotateItem\n";
	}
}
