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

#include "../../managers/planet/PlanetManager.h"

#include "../../managers/item/ItemManager.h"
#include "../../managers/combat/CombatManager.h"
#include "../../managers/mission/MissionManager.h"
#include "../../managers/player/ProfessionManager.h"
#include "../../managers/radial/RadialManager.h"
#include "../../managers/group/GroupManager.h"
#include "../../managers/resource/ResourceManager.h"
#include "../../managers/loot/LootManager.h"
#include "../../managers/planet/PlanetManager.h"

#include "../../managers/skills/imagedesign/ImageDesignCustomization.h"

#include "../../managers/combat/CombatManager.h"
#include "../../../chat/ChatManager.h"

#include "../../objects.h"

#include "../../objects/player/sui/messagebox/SuiMessageBoxImplementation.h"

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
	uint64 target;
	UnicodeString name;

	//System::out << "acrc: " << actionCRC << "\n";

	if (actionCRC == 0) {
		player->clearQueueAction(actioncntr, 0.0f, 0, 0);
		return;
	}

	// DO NOT FORGET TO ADD EVERYTHING WHICH IS ALLOWED WHILE BEING INCAP/DEAD TO THIS SWITCH HERE AS WELL
	switch (actionCRC) {
	case (0x68851C4F): // groupchat
	case (0x0315D6D9): // g
	case (0x3CDFF0CC): // gsay
	case (0xEA69C1BD): // activateClone
	case (0x3F8F3496): // consent
	case (0xA2DF082A): // unconsent
	case (0xB93A3853): // haveconsent
	case (0x1E0B1E43): // guildremove
	case (0x03B65950): // Logout
	case (0x887B5461): // requestcharactersheetinfo
	case (0xCA604B86): // requestbadges
	case (0x7AFCA539): // requeststatmigrationdata
	case (0x1BAD8FFC): // requestbiography
	case (0xFBE911E4): // setbiography
	case (0x164550EF): // getattributesbatch
	case (0xDB555329): // setcurrentskilltitle
	case (0xA6F95839): // showpvprating
	case (0x9B9FE4A8): // toggleawayfromkeyboard
	case (0x3AD396A5): // lfg
	case (0x441F4A3E): // newbiehelper
	case (0x32871193): // roleplay
	case (0x665C7C03): // display faction rank
	case (0xD40D5142): // anon
	case (0x4982E17B): // requestwaypointatposition
	case (0x8A19D7E1): // requestcharactermatch
	case (0x640543FE): // waypoint (/way)
	case (0x398F891A): // setwaypointname
	case (0xC3EDA6B6): // setwaypointactivestatus
	case (0x88505D58): // invite
	case (0x2E26A47F): // uninvite
	case (0x43E1F84F): // decline
	case (0xA99E6807): // join
	case (0x5061D654): // leavegroup
	case (0x2F50053B): // dismissgroupmember
	case (0x46D22D3A): // disband
	case (0x939AD584): // makeleader
	case (0x79DEB176): // guild (chat)
	case (0x47948A6D): // guildsay
	case (0xC64D8CB0): // tip
	case (0x4178FD6A): // peace
	case (0xEF3CBEDB): // loot
	case (0x3CD5C98D): // lootall
	case (0x2A2357ED): // Add Friend
	case (0x929AD345): // Add Ignore
	case (0x3629157F): // Remove Ignore
	case (0x30BE6EE9): // Find Friend
	case (0x8E9091D7): // Remove Friend
	case (0x029D0CC5): // Harvest
	case (0xBD7DF918): // tellpet
		break;
	default:
		if (player->isIncapacitated() || player->isDead()) {
			player->clearQueueAction(actioncntr, 0.0f, 1, 19);
			return;
		}
	}

	player->setActionCounter(actioncntr);

	ChatManager* chatManager;
	CombatManager* combatManager = serv->getCombatManager();
	GuildManager* pGuild = serv->getGuildManager();

	UnicodeString option;
	bool canPowerboost;

	switch (actionCRC) {

	case (0x70177586): //Open Container
		handleContainerOpen(player, pack);
		break;
	case (0x1E0B1E43): //guildremove
		player->clearQueueAction(actioncntr);
		handleRemoveFromGuild(player, pack, serv);
		break;
	case (0x081D6710): //Equilibrium
		player->queueAction(player, target, actionCRC, actioncntr, "");
		break;
	case (0x124629F2): // Meditating
		if (parseMeditation(player))
			player->queueAction(player, target, actionCRC, actioncntr, "");
		break;
	case (0x8C2221CB): // Powerboost
		if (!player->hasSkill(actionCRC)) {
			player->clearQueueAction(actioncntr, 0, 2, 0);
			return;
		}

		if (!player->doPowerboost())
			break;

		player->queueAction(player, target, actionCRC, actioncntr, "");
		break;
	case (0x896713F2): //permissionlistmodify
		parsePermissionListModify(player, pack);
		break;
	case (0xB93A3853): //haveconsent
		parseHaveConsentRequest(player, pack);
		break;
	case (0xA2DF082A): //unconsent
		parseRevokeConsentRequest(player, pack);
		break;
	case (0x3F8F3496): //consent
		parseGiveConsentRequest(player, pack);
		break;
	case (0xEA69C1BD): //activateClone
		if (!player->isDead()) {
			player->sendSystemMessage("You must be dead to activate your clone.");
		} else {
			player->sendActivateCloneRequest();
		}
		break;
	case (0x03B65950): // Logout
		player->userLogout();
		break;
	case (0x7C8D63D4):
		chatManager = player->getZone()->getChatManager();
		chatManager->handleMessage(player, pack);
		break;
	case (0x32CF1BEE):
		chatManager = player->getZone()->getChatManager();
		chatManager->handleEmote(player, pack);
		break;
	case (0x7759F35E):
		chatManager = player->getZone()->getChatManager();
		chatManager->handleMood(player, pack);
		break;
	case (0xFC3D1CB2):
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		player->activateBurstRun();
		break;
	case (0x01B48B26):
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		player->changePosture(CreaturePosture::CROUCHED);
		break;
	case 0x335676c7: // equip, change weapon.
		parseTransferWeapon(player, pack);
		break;
	case 0x82f75977: // transferitemmisc
		parseTransferItemMisc(player, pack);
		break;
	case 0x18726ca1: // equip, change armor
		parseTransferArmor(player, pack);
		break;
	case (0xBD8D02AF):
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		player->changePosture(CreaturePosture::PRONE);
		break;
	case (0xB719FA26):
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		parseServerSit(player, pack);
		break;
		/*case (0x97640B97): // added temp here
		 player->activateForceRun1(7.0f, 0.922938f);
		 break;*/
	case (0xA8A25C79):
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		player->changePosture(CreaturePosture::UPRIGHT);
		return;
	case (0x468B3802):
		target = pack->parseLong();
		combatManager->requestDuel(player, target);
		break;
	case (0x34C0ADD2):
		target = pack->parseLong();
		combatManager->requestEndDuel(player, target);
		break;
		/*case (0x43E1F84F):
		 target = pack->parseLong();
		 combatManager->declineDuel(player, target);
		 break;*/
	case (0x006A99F1): // Surrender skill
		parseSurrenderSkillBox(player, pack);
		break;
	case (0x04CDAFCE): // npcconversationstart
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		parseNpcStartConversation(player, pack);
		break;
	case (0x97D734FE): // npcconversationstop
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		parseNpcStopConversation(player, pack);
		break;
	case (0x0F13C662): //delegatefactionpoints
		parseDelFactionPoints(player, pack);
		break;
	case (0x887B5461): //requestcharactersheetinfo
		parseCharacterSheetInfoRequest(player, pack);
		break;
	case (0xCA604B86): //requestbadges
		parseBadgesRequest(player, pack);
		break;
	case (0x7AFCA539): //requeststatmigrationdata
		parseStatMigrationDataRequest(player, pack);
		break;
	case (0xE7407732): //requestsetstatmigrationdata
		parseSetStatMigrationDataRequest(player, pack);
		break;
	case (0x1BAD8FFC): //requestbiography
		parseBiographyRequest(player, pack);
		break;
	case (0xFBE911E4): //setbiography
		parseSetBiography(player, pack);
		break;
	case (0xBFF5BE51): //purchaseticket
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		parsePurchaseTicket(player, pack);
		break;
	case (0x305EDE19): //npcconversationselect
		parseNpcConversationSelect(player, pack);
		break;
	case (0x164550EF): //getattributesbatch
		parseGetAttributes(player, pack);
		break;
	case (0xDB555329): //setcurrentskilltitle
		parseSetCurrentSkillTitle(player, pack);
		break;
	case (0xA6F95839): //showpvprating
		parseShowPvpRating(player, pack);
		break;
	case (0xDFC959BA): //imagedesign
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		parseImageDesign(player, pack);
		break;
	case (0xC8998CE9): //flourish
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		parseFlourish(player, pack, actioncntr);
		break;
	case (0xF4C60EC3): //bandflourish
		if (!player->hasSkill(actionCRC)) {
			player->clearQueueAction(actioncntr, 0, 2, 0);
			return;
		}
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		parseBandFlourish(player, pack, actionCRC, actioncntr);
		break;
	case (0xB5220E24): //changemusic
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		parseChangeMusic(player, pack);
		break;
	case (0x13EE2D35): //changedance
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		parseChangeDance(player, pack);
		break;

		/*
		 case (0x4A0D52DD): //stopmusic
		 if (player->isMounted()) {
		 player->clearQueueAction(actioncntr, 0, 1, 16);
		 return;
		 }
		 parseStopMusic(player, pack);
		 break;
		 case (0xECC171CC): //stopdance
		 if (player->isMounted()) {
		 player->clearQueueAction(actioncntr, 0, 1, 16);
		 return;
		 }
		 parseStopDance(player, pack);
		 break;*/
	case (0xEC93CA43): //watch
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		parseWatch(player, pack);
		break;
	case (0x5855BB1B): //listen
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		parseListen(player, pack);
		break;
	case (0xC2E4D4D0): //stoplistening
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		//player->stopListen();
		parseStopListen(player, pack);
		break;
	case (0x6651AD9A): //stopwatching
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		//player->stopWatch();
		parseStopWatch(player, pack);
		break;
	case (0x9B9FE4A8): // toggleawayfromkeyboard
		player->toggleCharacterBit(PlayerObjectImplementation::AFK);
		break;
	case (0x3AD396A5): // lfg
		player->toggleCharacterBit(PlayerObjectImplementation::LFG);
		break;
	case (0x441F4A3E): //newbiehelper
		player->toggleCharacterBit(PlayerObjectImplementation::NEWBIEHELPER);
		break;
	case (0x32871193): //roleplay
		player->toggleCharacterBit(PlayerObjectImplementation::ROLEPLAYER);
		break;
	case (0x665C7C03): // display faction rank
		player->toggleCharacterBit(PlayerObjectImplementation::FACTIONRANK);
		break;
	case (0xD40D5142): // anon
		player->toggleCharacterBit(PlayerObjectImplementation::ANONYMOUS);
		break;
	case (0x4982E17B): //requestwaypointatposition
		//parseWaypointCreate(player, pack);
		parseWaypointCommand(player, pack);
		break;
	case (0x8A19D7E1): //requestcharactermatch
		parseRequestCharacterMatch(player, pack);
		break;
	case (0x640543FE): //waypoint (/way)
		parseWaypointCommand(player, pack);
		break;
	case (0x398F891A): //1A 89 8F 39 //actioncrc: setwaypointname
		parseSetWaypointName(player, pack);
		break;
	case (0xE7AEC4FB):
		parseServerDestroyObject(player, pack);
		break;
	case (0xC3EDA6B6): // setwaypointactivestatus
		parseSetWaypointActiveStatus(player, pack);
		break;
	case (0x88505D58): // invite
		parseGroupInvite(player, pack, serv->getGroupManager());
		break;
	case (0x2E26A47F): // uninvite
		parseGroupUninvite(player, pack);
		break;
	case (0x43E1F84F): // decline
		parseGroupDecline(player, pack);
		break;
	case (0xA99E6807): // join
		parseGroupJoin(player, pack, serv->getGroupManager());
		break;
	case (0x5061D654): // leavegroup
		parseGroupLeave(player, pack, serv->getGroupManager());
		break;
	case (0x2F50053B): // dismissgroupmember
		parseGroupKick(player, pack, serv->getGroupManager());
		break;
	case (0x46D22D3A): // disband
		parseGroupDisband(player, pack, serv->getGroupManager());
		break;
	case (0x939AD584): // makeleader
		parseGroupMakeLeader(player, pack, serv->getGroupManager());
		break;
	case (0x68851C4F): // groupchat
	case (0x0315D6D9): // g
	case (0x3CDFF0CC): // gsay
		chatManager = player->getZone()->getChatManager();
		chatManager->handleGroupChat(player, pack);
		break;
	case (0x79DEB176): // guild (chat)
	case (0x47948A6D): //guildsay
		chatManager = player->getZone()->getChatManager();
		chatManager->handleGuildChat(player, pack);
		break;
	case (0xE007BF31): // mount
		parseMount(player, pack);
		break;
	case (0x6F978ED): // dismount
		parseDismount(player, pack);
		break;
	case (0xC64D8CB0): // tip
		parseTip(player, pack, serv->getZoneServer()->getPlayerManager());
		break;
	case (0x5997AC66): // centerofbeing
		if (!player->hasSkill(actionCRC)) {
			player->clearQueueAction(actioncntr, 0, 2, 0);
			return;
		} else
			player->doCenterOfBeing();
		break;
	case (0x4178FD6A):
		player->doPeace();
		break;
	case (0xE5F3B39B):
		handleDeathblow(player, pack, combatManager);
		break;
	case (0x7AF26B0B): // Place Structure
		parsePlaceStructure(player, pack);
		break;
	case (0xF9996AB6): // synchronizeduilisten
		parseSynchronizedUIListen(player, pack);
		break;
	case (0x7C158EFD): // synchronizeduistoplistening
		parseSynchronizedUIStopListening(player, pack);
		break;
	case (0xCE645C94): // harvesteractivate
		parseHarvesterActivate(player, pack);
		break;
	case (0x2C61CB03): // harvesterdeactivate
		parseHarvesterDeActivate(player, pack);
		break;
	case (0xC89B9E26): // harvesterdiscardhopper
		parseHarvesterDiscardHopper(player, pack);
		break;
	case (0xF096C059): // harvestergetresourcedata
		parseHarvesterGetResourceData(player, pack);
		break;
	case (0x9A35978E): // harvestermakecrate
		break;
	case (0xFF549D14): // harvesterselectresource
		parseHarvesterSelectResource(player, pack);
		break;
	case (0x7EE9D72B): // harvestertakesurvey
		break;
	case (0xF62E35BA): // extractobject
		parseExtractObject(player, pack);
		break;
	case (0x1F88CB58): // splitfactorycrate
		System::out << "generic split function called\n";
		break;
	case (0x19C9FAC1):
		parseSurveySlashRequest(player, pack);
		break;
	case (0xC00CFA18):
		parseSurveyRequest(player, pack);
		break;
	case (0x8D0C1504):
		parseSampleSlashRequest(player, pack);
		break;
	case (0x9223C634):
		parseSampleRequest(player, pack);
		break;
	case (0x74952854):
		parseResourceContainerSplit(player, pack);
		break;
	case (0xF7262A75):
		parseResourceContainerTransfer(player, pack);
		break;
	case (0x8b36dd88): // attach CA/AA to armor/clothing
		parseAttachmentDragDrop(player, pack);
		break;
	case (0xab559978): // attach Powerup to weapon
		parsePowerupDragDrop(player, pack);
		break;
	case (0x5FD21EB0): // Schematic Resources
		parseRequestDraftSlotsBatch(player, pack);
		break;
	case (0x9A8B385C): // Schematic Experimental Properties
		parseRequestResourceWeightsBatch(player, pack);
		break;
	case (0x094AC516): // Request Crafting Session
		parseRequestCraftingSession(player, pack);
		break;
	case (0x83250E2A): // Cancel Crafting Session
		parseCancelCraftingSession(player, pack);
		break;
	case (0x89242E02): // Select Draft Schematic
		parseSelectDraftSchematic(player, pack);
		break;
	case (0x6AD8ED4D): // Next crafting stage
		parseNextCraftingStage(player, pack);
		break;
	case (0xD61FF415): // Create Prototype
		parseCreatePrototype(player, pack);
		break;
	case (0xF4B66795): // Create Schematic
		parseCreateSchematic(player, pack);
		break;

	case (0xEF3CBEDB): //loot
		player->lootCorpse(false);
		break;
	case (0x3CD5C98D): // lootall
		player->lootCorpse();
		break;
	case (0x2A2357ED): // Add Friend
		parseAddFriend(player, pack);
		break;

	case (0x929AD345): // Add Ignore
		parseAddIgnore(player, pack);
		break;
	case (0x3629157F): // Remove Ignore
		parseRemoveIgnore(player, pack);
		break;
	case (0x30BE6EE9): // Find Friend
		parseFindFriend(player, pack, serv->getZoneServer()->getPlayerManager());
		break;
	case (0x8E9091D7): // Remove Friend
		parseRemoveFriend(player, pack);
		break;
	case (0x029D0CC5): // Harvest
		parseHarvestOrganics(player, pack);
		break;
	case (0xCF2D30F4): // newbieselectstartinglocation
		parseNewbieSelectStartingLocation(player, pack);
		break;
	case (0x5041F83A): // Teach
		parseTeach(player, pack);
		break;
	case (0xD6EE77C2): // System Group Message
		doInstantAction(player, pack, actionCRC, actioncntr);
		break;
	case (0x7EF26D6A): // Volley Fire
		doInstantAction(player, pack, actionCRC, actioncntr);
		break;
	case (0x4871BBF4): //Retreat
		doInstantAction(player, pack, actionCRC, actioncntr);
		break;
	case (0x549BE67): //throwtrap
		parseThrowTrap(player, pack, actionCRC, actioncntr);
	case (0xBBAF8943): //throwgrenade
		parseThrowGrenade(player, pack, actionCRC, actioncntr);
		break;
	case (0xA04EB6B8): //fireheavyweapon
		parseFireHeavyWeapon(player, pack, actionCRC, actioncntr);
		break;
	case (0xD2E938DB): //checkforcestatus
		player->checkForceStatus();
		break;
	case (0xBD7DF918):
		parseTellPet(player,pack);
		break;

	default:
		target = pack->parseLong();
		String actionModifier = "";

		// fancy if statement
		switch (actionCRC) { // modifier for entertainer-type commands /dazzle 2 vs /dazzle 1
		// they're dumb and all have the same action crc
		case (0x7B1DCBE0): //startdance
		case (0xDDD1E8F1): //startmusic
			//	target = player->getObjectID(); // Fake Queue Action on this - the parseLong is blank
		case (0xB008CBFA): //colorlights
		case (0x9C7713A5): //dazzle
		case (0xED4AA746): //spotlight
		case (0xD536B419): //smokebomb
		case (0x2434AC3A): //distract
		case (0x6CB6978F): //ventriloquism
		case (0x35ED32BE): //firejet
		case (0xC8998CE9): //flourish
		case (0xEEE029CF): //healenhance <poolaffected>
		case (0x0A9F00A0): //healdamage <targetname>
		case (0x2087CE04): //healwound <poolaffected>
		case (0x4A386BD5): //healstate <stateaffected>
		case (0xDF49EA58): //extinguishfire
		case (0xC9759876): //reviveplayer <targetname>
		case (0xDC7CF134): //diagnose
		case (0x273A06DA): //dragincapacitatedplayer <targetname>

			option = UnicodeString("");
			pack->parseUnicode(option);
			actionModifier = option.toString();

			//if (skillOptionID <=0 ) skillOptionID = 1; // default to level 1
			break;
		default:
			/* StringBuffer opc;
			 opc << "Opc: " << hex << actionCRC;
			 player->sendSystemMessage(opc.toString());*/
			break;
		}

		player->queueAction(player, target, actionCRC, actioncntr,
				actionModifier.toCharArray());
		return;
	}

	player->clearQueueAction(actioncntr);
}

void ObjectControllerMessage::doInstantAction(Player* player, Message* pack, uint32 actionCRC, uint32 actionCntr) {
	uint64 target = pack->parseLong();
	UnicodeString option = UnicodeString("");
	String actionModifier = "";

	pack->parseUnicode(option);
	actionModifier = option.toString();
	String amod = actionModifier.toCharArray();

	player->doInstantAction(target, actionCRC, actionCntr, amod);
}

void ObjectControllerMessage::parseAttachmentDragDrop(Player* player,
		Message* pack) {
	if (player->getTradeSize() != 0) {
		player->sendSystemMessage("You cant move objects while trading..");
		return;
	}

	uint64 attachmentID = pack->parseLong();
	UnicodeString unicodeStringID;

	pack->parseUnicode(unicodeStringID);
	StringTokenizer tokenizer(unicodeStringID.toString());

	if (tokenizer.hasMoreTokens()) {
		uint64 targetID = tokenizer.getLongToken();

		player->applyAttachment(attachmentID, targetID);
	}
}

void ObjectControllerMessage::parsePowerupDragDrop(Player* player,
		Message* pack) {
	if (player->getTradeSize() != 0) {
		player->sendSystemMessage("You cant move objects while trading..");
		return;
	}

	uint64 powerupID = pack->parseLong();
	UnicodeString UnicodeStringID;

	pack->parseUnicode(UnicodeStringID);
	StringTokenizer tokenizer(UnicodeStringID.toString());

	if (tokenizer.hasMoreTokens()) {
		uint64 targetID = tokenizer.getLongToken();

		player->applyPowerup(powerupID, targetID);
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

void ObjectControllerMessage::parseSurrenderSkillBox(Player* player,
		Message* pack) {
	try {
		pack->shiftOffset(8);

		UnicodeString skillBox;
		pack->parseUnicode(skillBox);

		player->surrenderSkillBox(skillBox.toString());
	} catch (Exception& e) {
		System::out
				<< "unreported ObjectControllerMessage::parseSurrenderSkillBox(Player* player, Message* pack) exception\n";
		e.printStackTrace();
	} catch (...) {
		System::out
				<< "unreported ObjectControllerMessage::parseSurrenderSkillBox(Player* player, Message* pack) exception\n";
	}
}

void ObjectControllerMessage::parseNpcStartConversation(Player* player,
		Message* pack) {
	uint64 target = pack->parseLong();

	SceneObject* object = player->getZone()->lookupObject(target);

	if (object != NULL && object->isNonPlayerCreature()) {
		try {
			if (object != player)
				object->wlock(player);

			if (player->isInRange(object, 5)) {
				player->setConversatingCreature((CreatureObject*) object);
				object->sendConversationStartTo(player);
			}

			if (object != player)
				object->unlock();
		} catch (...) {
			player->error(
					"unreported ObjectControllerMessage::parseNpcStartConversation(Player* player, Message* pack) exception");
			if (object != player)
				object->unlock();
		}
	}
}

void ObjectControllerMessage::parseNpcConversationSelect(Player* player,
		Message* pack) {
	pack->shiftOffset(8);

	SceneObject* object = player->getConversatingCreature();

	if (object != NULL) {
		if (!player->isInRange(object, 5))
			return;

		UnicodeString opt;
		pack->parseUnicode(opt);

		int option = Integer::valueOf(opt.toString());
		object->selectConversationOption(option, player);
	}
}

void ObjectControllerMessage::parseNpcStopConversation(Player* player,
		Message* pack) {
	uint64 target = pack->parseLong();

	CreatureObject* npc = player->getConversatingCreature();

	if (npc != NULL) {
		try {
			if (npc != player)
				npc->wlock(player);

				npc->sendConversationStopTo(player);

			if (npc != player)
				npc->unlock();
		} catch (...) {
			System::out
					<< "unreported ObjectControllerMessage::parseNpcStopConversation(Player* player, Message* pack) exception\n";
			if (npc != player)
				npc->unlock();
		}
	}
}


/**
 * This method is fired when a player has requested the stat migration data
 * For example: If they open the stat migration window in the character sheet.
 * \param player This is the player that has requested the data.
 * \param pack The packet.
 */
void ObjectControllerMessage::parseStatMigrationDataRequest(Player* player, Message* pack) {
	uint64 objectid = pack->parseLong(); //TargetID?

	StatMigrationTargetsMessage* smtm = new StatMigrationTargetsMessage(player);
	player->sendMessage(smtm);
}

/**
 * This method is fired when a player has requested that stat migration data be changed.
 * For example: They have changed the data in the stat migration window, and have pressed
 * okay rather than cancel.
 * \param player The player that has set that stat migration data request.
 * \param pack The packet.
 */
void ObjectControllerMessage::parseSetStatMigrationDataRequest(Player* player, Message* pack) {
	//This appears to be the ID of the target who's data is being set.
	uint64 targetID = pack->parseLong();

	UnicodeString stats = UnicodeString("");
	pack->parseUnicode(stats);

	StringTokenizer tokenizer(stats.toString());
	tokenizer.setDelimeter(" ");

	uint32 targetPointsTotal = 0;
	uint32 targetAttributes[9] = {0};

	for (int i = 0; tokenizer.hasMoreTokens(); i++) {
		uint32 value = tokenizer.getIntToken();

		if (value < player->getMinAttribute(i) && value > player->getMaxAttribute(i)) {
			player->info("Suspected stat migration hacking attempt.");
			return;
		}

		targetAttributes[i] = value;
		targetPointsTotal += value;
	}

	//Here we set the stat migration target attributes.
	//NOTE: We aren't actually migrating the stats at this point.
	if (targetPointsTotal == player->getTotalAttribPoints()) {
		player->setMigrationHealth(targetAttributes[0]);
		player->setMigrationStrength(targetAttributes[1]);
		player->setMigrationConstitution(targetAttributes[2]);
		player->setMigrationAction(targetAttributes[3]);
		player->setMigrationQuickness(targetAttributes[4]);
		player->setMigrationStamina(targetAttributes[5]);
		player->setMigrationMind(targetAttributes[6]);
		player->setMigrationFocus(targetAttributes[7]);
		player->setMigrationWillpower(targetAttributes[8]);
	} else {
		player->error("Trying to set migratory stats without assigning all available points.");
		return;
	}

	//Player is in the tutorial zone and is allowed to migrate stats.
	if (player->getZoneID() == 42)
		player->migrateStats();
}

void ObjectControllerMessage::parseCharacterSheetInfoRequest(Player* player, Message* pack) {
	uint64 objectid = pack->parseLong();

	CharacterSheetResponseMessage* csrm = new CharacterSheetResponseMessage(player);
	player->sendMessage(csrm);
}

void ObjectControllerMessage::parseBiographyRequest(Player* player, Message* pack) {
	uint64 objectid = pack->parseLong();

	SceneObject* object = player->getZone()->lookupObject(objectid);

	if (object == NULL)
		return;

	if (object->isPlayer()) {
		Player* play = (Player*) object;

		try {
			if (play != player)
				play->wlock(player);

			Biography* bio = new Biography(player, play);
			player->sendMessage(bio);

			if (play != player)
				play->unlock();
		} catch (...) {
			System::out
					<< "Unreported exception in ObjectControllerMessage::parseBiographyRequest(Player* player, Message *pack)";
			if (play != player)
				play->unlock();
		}
	}

}

void ObjectControllerMessage::parseSetBiography(Player* player, Message *pack) {
	pack->shiftOffset(8);

	UnicodeString bio;
	pack->parseUnicode(bio);

	player->setBiography(bio.toString());
}

void ObjectControllerMessage::parseBadgesRequest(Player* player, Message *pack) {
	uint64 objectid = pack->parseLong();

	SceneObject* object = player->getZone()->lookupObject(objectid);

	if (object == NULL)
		return;

	if (object->isPlayer()) {
		Player* play = (Player*) object;

		try {
			if (play != player)
				play->wlock(player);

			BadgesResponseMessage* brm = new BadgesResponseMessage(play);
			player->sendMessage(brm);

			if (play != player)
				play->unlock();
		} catch (...) {
			System::out
					<< "Unreported exception in ObjectControllerMessage::parseBiographyRequest(Player* player, Message *pack)";
			if (play != player)
				play->unlock();
		}
	}
}

void ObjectControllerMessage::parsePurchaseTicket(Player* player, Message *pack) {
	pack->shiftOffset(8); // skip ObjectID and size

	UnicodeString ticketmessage;
	pack->parseUnicode(ticketmessage);

	StringTokenizer tokenizer(ticketmessage.toString());

	String departurePlanet;
	if (tokenizer.hasMoreTokens())
		tokenizer.getStringToken(departurePlanet);
	else
		return;

	String departurePoint;
	if (tokenizer.hasMoreTokens())
		tokenizer.getStringToken(departurePoint);
	else
		return;

	String arrivalPlanet;
	if (tokenizer.hasMoreTokens())
		tokenizer.getStringToken(arrivalPlanet);
	else
		return;

	String arrivalPoint;
	if (tokenizer.hasMoreTokens())
		tokenizer.getStringToken(arrivalPoint);
	else
		return;

	bool roundTrip;
	if (tokenizer.hasMoreTokens())
		roundTrip = tokenizer.getIntToken();
	else
		return;

	PlanetManager* planetManager = player->getZone()->getPlanetManager();

	uint32 fare = planetManager->getTravelFare(departurePlanet, arrivalPlanet);

	if (fare == 0) {
		//Travel not allowed between these planets
		return;
	}

	//Replace Underscores with spaces
	departurePoint = departurePoint.replaceAll("_", " ");

	ShuttleCreature* shuttle = planetManager->getShuttle(departurePoint);

	if (shuttle == NULL) {
		SuiMessageBox* sui = new SuiMessageBox(player, SuiWindowType::TICKET_PURCHASE_MESSAGE);
		sui->setPromptTitle("@base_player:swg");
		sui->setPromptText("@travel:no_location_found");

		player->addSuiBox(sui);

		player->sendMessage(sui->generateMessage());
		return;
	}

	uint32 tax = shuttle->getTax();

	uint32 totalFee = fare + tax;

	if (roundTrip)
		totalFee *= 2;

	if (!player->verifyCashCredits(totalFee)) {
		SuiMessageBox* sui = new SuiMessageBox(player, SuiWindowType::TICKET_PURCHASE_MESSAGE);
		sui->setPromptTitle("@base_player:swg");
		sui->setPromptText("@travel:short_funds");

		player->addSuiBox(sui);

		player->sendMessage(sui->generateMessage());
		return;

	} else {
		player->subtractCashCredits(totalFee);
	}

	// create ticket item
	Ticket* ticket = new Ticket(player, 0xDAA0DE83, UnicodeString(
			"Travel Ticket"), "travel_ticket", departurePlanet, departurePoint,
			arrivalPlanet, arrivalPoint);

	player->addInventoryItem(ticket);
	ticket->sendTo(player, true);

	if (roundTrip) {
		Ticket* returnTicket = new Ticket(player, 0xDAA0DE83, UnicodeString(
				"Travel Ticket"), "travel_ticket", arrivalPlanet, arrivalPoint,
				departurePlanet, departurePoint);

		player->addInventoryItem(returnTicket);
		returnTicket->sendTo(player, true);
	}

	SuiMessageBox* sui = new SuiMessageBox(player, SuiWindowType::TICKET_PURCHASE_MESSAGE);
	sui->setPromptTitle("@base_player:swg");
	sui->setPromptText("@travel:ticket_purchase_complete");

	player->addSuiBox(sui);
	player->sendMessage(sui->generateMessage());
}

void ObjectControllerMessage::parseGetAttributes(Player* player, Message* pack) {
	pack->shiftOffset(8);

	UnicodeString objectid;
	pack->parseUnicode(objectid);

	StringTokenizer ids(objectid.toString());

	while (ids.hasMoreTokens()) {
		uint64 objid = 0;

		try {
			objid = ids.getLongToken();

		} catch (...) {
		}

		if (objid == 0)
			continue;

		Zone* zone = (Zone*) player->getZone();

		if (zone == NULL)
			return;

		SceneObject* object = zone->lookupObject(objid);

		if (object == NULL) {
			object = player->getPlayerItem(objid);

			if (object == NULL) {
				SceneObject* target = player->getTarget();

				if (target != NULL && target != player) {
					if (target->isPlayer()) {
						Player* targetPlayer = (Player*) target;

						try {
							targetPlayer->wlock(player);

							object = targetPlayer->getPlayerItem(objid);

							targetPlayer->unlock();
						} catch (...) {
							targetPlayer->unlock();
						}
					} else if (target->isNonPlayerCreature()) {
						Creature* creature = (Creature*) target;

						try {
							creature->wlock(player);

							object = creature->getLootItem(objid);

							creature->unlock();
						} catch (...) {
							creature->unlock();
						}
					}
				}
			}
		}

		if (object != NULL) {

			object->generateAttributes(player);

		} else {

			AttributeListMessage* msg = new AttributeListMessage(objid);
			player->sendMessage(msg);
		}
	}
}

void ObjectControllerMessage::parseRadialRequest(Player* player, Message* pack,
		RadialManager* radialManager) {
	radialManager->handleRadialRequest(player, pack);
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

void ObjectControllerMessage::parseSetCurrentSkillTitle(Player* player, Message* pack) {
	pack->shiftOffset(8); //shift past the blank id.
	UnicodeString title;
	pack->parseUnicode(title);
	String newTitle = title.toString();

	if (newTitle.length() > 0) {
		if (!player->hasSkillBox(newTitle))
				return;
	}

	PlayerObject* object = player->getPlayerObject();
	object->setCurrentTitle(newTitle, true);
}

void ObjectControllerMessage::parseShowPvpRating(Player* player, Message* pack) {
	StringBuffer msg;
	msg << "Your player vs. player combat rating is " << player->getPvpRating();

	player->sendSystemMessage(msg.toString());
}

void ObjectControllerMessage::parseWatch(Player* player, Message* pack) {
	uint64 watchID = pack->parseLong();

	player->startWatch(watchID);
}

void ObjectControllerMessage::parseListen(Player* player, Message* pack) {
	uint64 listenID = pack->parseLong();

	player->startListen(listenID);
}

void ObjectControllerMessage::parseImageDesign(Player* player, Message* pack) {

	String skillBox = "social_entertainer_novice";

	if (!player->getSkillBoxesSize() || !player->hasSkillBox(skillBox)) {
		// TODO: sendSystemMessage("cmd_err", "ability_prose", creature);
		player->sendSystemMessage(
				"You do not have sufficient abilities to image design.");
		return;
	}

	uint64 target = pack->parseLong(); // skip passed target get this later?

	SceneObject* object = player->getZone()->lookupObject(target);

	if (object == NULL)
		return;

	unsigned long tent = 0; // objectid of the salon building

	if (player->isInBuilding() && player->getBuildingType()
			== BuildingObjectImplementation::SALON) {
		CellObject* cell = (CellObject*) player->getParent();
		BuildingObject* building = (BuildingObject*) cell->getParent();

		tent = building->getObjectID();
	}

	try {
		if (object != player)
			object->wlock(player);

		if (object->isPlayer()) {
			Player* targetPlayer = (Player*) object;

			// If the target player isn't yourself, then that player must be in a group
			if (targetPlayer->getObjectID() != player->getObjectID()
					&& (!player->isInAGroup() || (player->isInAGroup()
							&& player->getGroupID()
									!= targetPlayer->getGroupID()))) {

				player->sendSystemMessage(
						"Target player must be in your group to Image Design.");

				if (object != player)
					object->unlock();

				return;
			}

			/*
			 Designer:
			 3A 02 00 00
			 72 B0 E9 91 22 00 00 00 // designer
			 00 00 00 00
			 72 B0 E9 91 22 00 00 00
			 DF D4 50 92 22 00 00 00
			 00 00 00 00 00 00 00 00 // tent
			 00 00


			 Designee:

			 3A 02 00 00
			 72 B0 E9 91 22 00 00 00
			 00 00 00 00
			 DF D4 50 92 22 00 00 00
			 72 B0 E9 91 22 00 00 00
			 00 00 00 00 00 00 00 00
			 00 00 */

			// Initiate Self
			ImageDesignStartMessage* msgPlayer = new ImageDesignStartMessage(
					player, player, targetPlayer, tent);
			player->sendMessage(msgPlayer);

			// Initiate Target (
			if (targetPlayer->getObjectID() != player->getObjectID()) {
				ImageDesignStartMessage* msgTarget =
						new ImageDesignStartMessage(targetPlayer, player,
								targetPlayer, tent);
				targetPlayer->sendMessage(msgTarget);
			}
		} else {
			player->sendSystemMessage("Invalid Image Design target.");
		}

		if (object != player)
			object->unlock();
	} catch (...) {
		System::out
				<< "Unreported exception in ObjectControllerMessage::parseImageDesign(Player* player, Message *pack)";
		if (object != player)
			object->unlock();
	}
}

void ObjectControllerMessage::parseFlourish(Player* player, Message* pack, uint32 actionCntr) {
	uint64 target = pack->parseLong(); // skip passed target

	UnicodeString option = UnicodeString("");
	pack->parseUnicode(option);
	String actionModifier = option.toString();

	player->queueFlourish(actionModifier, target, actionCntr);
	//player->queueFlourish()
	//player->doFlourish(actionModifier);
}

void ObjectControllerMessage::parseBandFlourish(Player* player, Message* pack, uint32 actionCRC, uint32 actionCntr) {
	uint64 target = pack->parseLong();

	UnicodeString option = UnicodeString("");
	pack->parseUnicode(option);
	String actionModifier = option.toString();

	player->queueAction(player, target, actionCRC, actionCntr, actionModifier);
}

void ObjectControllerMessage::parseChangeMusic(Player* player, Message* pack) {
	pack->parseLong(); // skip passed target

	UnicodeString option = UnicodeString("");
	pack->parseUnicode(option);
	String actionModifier = option.toString();

	player->startPlayingMusic(actionModifier, true);
}

void ObjectControllerMessage::parseChangeDance(Player* player, Message* pack) {
	pack->parseLong(); // skip passed target

	UnicodeString option = UnicodeString("");
	pack->parseUnicode(option);
	String actionModifier = option.toString();

	player->startDancing(actionModifier, true);
}

void ObjectControllerMessage::parseServerSit(Player* player, Message* pack) {
	pack->shiftOffset(8); //Shift past the blank long.

	UnicodeString waypoint;
	pack->parseUnicode(waypoint);

	if (waypoint.isEmpty()) {
		player->changePosture(CreaturePosture::SITTING);
	} else {
		Zone* zone = player->getZone();

		if (zone == NULL)
			return;

		ZoneServer* server = zone->getZoneServer();

		try {
			StringTokenizer tokenizer(waypoint.toString());
			tokenizer.setDelimeter(",");
			float x = tokenizer.getFloatToken();
			float y = tokenizer.getFloatToken();
			float z = tokenizer.getFloatToken();

			uint64 coID;
			if (tokenizer.hasMoreTokens())
				coID = tokenizer.getLongToken();

			if (x < -8192 || x > 8192)
				x = 0;
			if (y < -8192 || y > 8192)
				y = 0;
			if (z < -8192 || z > 8192)
				z = 0;

			player->setPosture(CreaturePosture::SITTING, false, true, x, y, z);
		} catch (...) {
			System::out
					<< "Unreported exception in ObjectControllerMessage::parseServerSit\n";
		}
	}
}

void ObjectControllerMessage::parseWaypointCreate(Player* player, Message* pack) {
	//outdated and throwing exceptions. We use now "parseWaypointCommand

	/*
	 pack->shiftOffset(8); //Shift past the blank long.

	 UnicodeString waypoint;
	 pack->parseUnicode(waypoint);

	 StringTokenizer tokenizer(waypoint.toCharArray());
	 try {
	 String planet;
	 tokenizer.getStringToken(planet);

	 float x = tokenizer.getFloatToken();
	 float z = tokenizer.getFloatToken();
	 float y = tokenizer.getFloatToken();

	 if (x < -8192 || x> 8192)
	 x = 0;
	 if (y < -8192 || y> 8192)
	 y = 0;
	 if (z < -8192 || z> 8192)
	 z = 0;

	 WaypointObject* waypoint = new WaypointObject(player, player->getNewItemID());
	 waypoint->setPlanetName(planet);
	 waypoint->setPosition(x, z, y);

	 player->addWaypoint(waypoint);

	 } catch (...) {
	 System::out << "Unreported exception in ObjectControllerMessage::parseWaypointCreate\n";
	 }
	 */
}

void ObjectControllerMessage::parseWaypointCommand(Player* player,
		Message* pack) {
	int counter = 0;
	String dummy;

	pack->shiftOffset(8);

	String usageError = "Usage: /waypoint X Y <name> or /waypoint <name>";

	UnicodeString rawWaypoint;
	pack->parseUnicode(rawWaypoint);
	String waypointData = rawWaypoint.toString();

	String waypointName = "New Waypoint";
	String planet = Planet::getPlanetName(player->getZoneID());
	float x = player->getPositionX();
	float y = player->getPositionY();
	float z = 0.0f;

	SceneObject* parentObject = player->getParent();

	if (parentObject != NULL) {
		if (parentObject->isCell()) {
			SceneObject* grandParentObject = parentObject->getParent();

			if (grandParentObject != NULL) {
				x = grandParentObject->getPositionX();
				y = grandParentObject->getPositionY();
			}
		}
	}

	StringTokenizer tokenizer(waypointData);
	tokenizer.setDelimeter(" ");

	if (tokenizer.hasMoreTokens()) {

		String arg1;
		tokenizer.getStringToken(arg1);

		if (tokenizer.hasMoreTokens()) {
			if (isalpha(arg1[0]) == 0) {
				//A waypoint in the form of /waypoint X Y <name>
				x = atof(arg1.toCharArray());

				if (tokenizer.hasMoreTokens()) {
					String temp;
					tokenizer.getStringToken(temp);
					if (isalpha(temp[0]) == 0) {
						y = atof(temp.toCharArray());
					} else {
						player->sendSystemMessage(usageError);
						return;
					}
				}

				StringBuffer newWaypointName;

				while (tokenizer.hasMoreTokens()) {
					String name;
					tokenizer.getStringToken(name);
					newWaypointName << name << " ";
				}

				/*if (!newWaypointName.isEmpty())
				 newWaypointName.deleteRange(0, 1);*/// ????

				waypointName = newWaypointName.toString();
			} else {
				//A waypoint in the form of /waypoint planet X Z Y - Planetary Map
				planet = arg1;

				if (Planet::getPlanetID(planet) < 0) { //Not a valid planet name - malformed command
					player->sendSystemMessage(usageError);
					return;
				}

				if (tokenizer.hasMoreTokens()) {
					String temp;
					tokenizer.getStringToken(temp);

					if (!Character::isLetterOrDigit(temp.charAt(0))) {
						x = Float::valueOf(temp);
					} else {
						player->sendSystemMessage(usageError);
						return;
					}
				}

				if (tokenizer.hasMoreTokens()) {
					String temp;
					tokenizer.getStringToken(temp);

					if (!Character::isLetterOrDigit(temp.charAt(0))) {
						z = Float::valueOf(temp);
					} else {
						player->sendSystemMessage(usageError);
						return;
					}
				}

				if (tokenizer.hasMoreTokens()) {
					String temp;
					tokenizer.getStringToken(temp);

					if (!Character::isLetterOrDigit(temp.charAt(0))) {
						y = Float::valueOf(temp);
					} else {
						player->sendSystemMessage(usageError);
						return;
					}
				}
			}
		} else {
			//A waypoint in the form of /waypoint <name>
			waypointName = arg1;
		}
	}

	x = (x < -8192) ? -8192 : x;
	x = (x > 8192) ? 8192 : x;

	y = (y < -8192) ? -8192 : y;
	y = (y > 8192) ? 8192 : y;

	//Create our waypoint
	WaypointObject* waypoint = new WaypointObject(player,
			player->getNewItemID());
	waypoint->setPlanetName(planet);
	waypoint->setPosition(x, z, y);
	waypoint->setName(waypointName);

	player->addWaypoint(waypoint);

}

void ObjectControllerMessage::parseSetWaypointName(Player* player,
		Message* pack) {
	uint64 wpId = pack->parseLong(); //get the waypoint id

	WaypointObject* waypoint = player->getWaypoint(wpId);

	if (waypoint == NULL)
		return;

	UnicodeString unicodeWaypointName; //new waypoint name
	pack->parseUnicode(unicodeWaypointName);

	String newWaypointName = unicodeWaypointName.toString();
	waypoint->setName(newWaypointName);
	waypoint->switchStatus();

	player->updateWaypoint(waypoint);
}

void ObjectControllerMessage::parseServerDestroyObject(Player* player, Message* pack) {
	uint64 objid = pack->parseLong(); //get the id

	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();

	if (player->getTradeSize() != 0) {
		player->sendSystemMessage("You cant destroy objects while trading..");
		return;
	}

	UnicodeString unkPramString;
	pack->parseUnicode(unkPramString); //?

	ManagedReference<WaypointObject> waypoint = player->getWaypoint(objid);
	ManagedReference<SceneObject> datapadData =  player->getDatapadItem(objid);
	ManagedReference<SceneObject> invObj = player->getInventoryItem(objid);
	ManagedReference<SceneObject> bankObj = player->getBankItem(objid);

	//Avoid redundant code:
	if (bankObj != NULL)
		invObj = bankObj;

	if (invObj != NULL && invObj->isTangible()) {
		TangibleObject* tano = (TangibleObject*) invObj.get();

		if (tano->isEquipped()) {
			player->unequipItem(tano);
		}

		if (tano->isContainer()) {
			Container* container = (Container*) tano;

			while (!container->isContainerEmpty()) {
				ManagedReference<SceneObject> sco = container->getObject(0);

				itemManager->deletePlayerItem(player, ((TangibleObject*) sco.get()), true);

				container->removeObject(0);
				sco->removeFromZone(true);
				sco->finalize();
			}
		}

		//System::out << "Server destroy happening\n";

		if(tano->isCraftingTool()) {

		CraftingTool* tool = (CraftingTool*) tano;

			if (!tool->isReady()) {
				player->sendSystemMessage("You cant delete an active crafting tool!");
				return;
			}
		}

		itemManager->deletePlayerItem(player, tano, true);

		//Move item to inventory top level for deletion
		Inventory* inventory = player->getInventory();
		if (inventory != NULL)
			inventory->moveObjectToTopLevel(player, tano);

		player->removeInventoryItem(objid);

		if (player->getWeapon() == tano)
			player->setWeapon(NULL);

		if (player->getSurveyTool() == tano)
			player->setSurveyTool(NULL);

		BaseMessage* msg = new SceneObjectDestroyMessage(tano);
		player->getClient()->sendMessage(msg);

		tano->finalize();

	} else if (waypoint != NULL) {
		if (player->removeWaypoint(waypoint))
			waypoint->finalize();

	} else if (datapadData != NULL) {
		if (datapadData->isIntangible()) {
			IntangibleObject* itno = (IntangibleObject*)datapadData.get();
			SceneObject* worldObject = itno->getWorldObject();

			if (worldObject->isNonPlayerCreature()) {
				CreatureObject* crea = (Creature*) worldObject;
				if (crea->isPet()) {
					try {
						((CreaturePet*)crea)->wlock();
						((CreaturePet*)crea)->store();
						((CreaturePet*)crea)->unlock();
					} catch (...) {
						System::out << "Unreported exception caught in RadialManager::handlePetCall\n";
						((CreaturePet*)crea)->unlock();
					}
				}
			}
		}
		player->removeDatapadItem(objid);

		itemManager->deleteDatapadItem(player, datapadData.get(), true);

		BaseMessage* msg = new SceneObjectDestroyMessage(datapadData);
		player->getClient()->sendMessage(msg);

		SceneObject* linkedItem = datapadData.get()->getObject(0);

		datapadData->finalize();

		if(linkedItem != NULL) {

			if(linkedItem->isNonPlayerCreature() && linkedItem == (CreatureObject*)player->getMount())
				player->setMount(NULL);

			linkedItem->finalize();
			msg = new SceneObjectDestroyMessage(linkedItem);
			player->getClient()->sendMessage(msg);
		}
	}
}

void ObjectControllerMessage::parseSetWaypointActiveStatus(Player* player,
		Message* pack) {
	uint64 wpId = pack->parseLong();

	WaypointObject* wp = player->getWaypoint(wpId);

	if (wp == NULL)
		return;

	wp->switchStatus();
}

void ObjectControllerMessage::parseRequestCharacterMatch(Player* player,
		Message* pack) {
	//pack->shiftOffset(8); //Shift past the blank long. Eventually parse stuff here. Not yet. lols.
	player->getPlayersNearYou();
}

void ObjectControllerMessage::parseResourceEmptyHopper(Player* player,
		Message* pack) {
	//cout << "parseResourceEmptyHopper: " <<  pack->toString() << endl;

	//System::out << "parseResourceEmptyHopper: " <<  pack->toString() << endl;

	//skip objId + old size
	pack->shiftOffset(12);

	//Grab the harvester object id
	pack->shiftOffset(8); // skip passed player
	uint64 hId = pack->parseLong();
	uint64 rId = pack->parseLong();
	uint32 quantity = pack->parseInt(); // need to verify the quantity exists in the hopper
	uint8 byte1 = pack->parseByte(); // Retrieve vs Discard
	uint8 byte2 = pack->parseByte(); // checksum?

	//System::out << "ObjectControllerMessage::parseResourceEmptyHopper(), hId: " << hex << hId << dec << " rId : " << rId << " id: " << rId << " quantity: " << quantity << endl;

	SceneObject* object = player->getZone()->lookupObject(hId);

	if (object == NULL) {
		//System::out << "ObjectControllerMessage::parseResourceEmptyHopper() bad object" << endl;
		return;
	}

	if (!object->isTangible()) {
		//System::out << "ObjectControllerMessage::parseResourceEmptyHopper() bad tano" << endl;
		return;
	}

	TangibleObject* tano = (TangibleObject*) object;

	if (tano->getObjectSubType() != TangibleObjectImplementation::HARVESTER) {
		//System::out << "ObjectControllerMessage::parseResourceEmptyHopper() bad harvester" << endl;
		return;
	}

	InstallationObject* inso = (InstallationObject*) tano;

	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	ResourceManager* resourceManager =
			zone->getZoneServer()->getResourceManager();
	if (resourceManager == NULL)
		return;

	bool makeNewResource = true;

	//before we mess with the resources, we want to make sure we have room.
	if (byte1 == 0 && player->getInventory()->getUnequippedItemCount() >= InventoryImplementation::MAXUNEQUIPPEDCOUNT) {
		player->sendSystemMessage("You don't have enough space in your inventory");
		return;
	}

	quantity = (uint32) inso->removeHopperItem(rId, quantity);
	if (quantity >= 1) {
		if (byte1 == 0) // Retreive vs Discard
		{
			ResourceContainer* newRcno = new ResourceContainer(
					player->getNewItemID());
			String resourceName = resourceManager->getResourceNameByID(rId);
			newRcno->setResourceName(resourceName);
			newRcno->setContents(quantity);
			resourceManager->setResourceData(newRcno, false);
			player->addInventoryResource(newRcno);
		}
	}

	// need to send to anyone looking
	InstallationObjectDeltaMessage7* dinso7 =
			new InstallationObjectDeltaMessage7(inso);
	dinso7->updateHopper();
	dinso7->updateHopperItem(rId);
	dinso7->updateHopperSize();
	dinso7->close();
	player->sendMessage(dinso7);

	GenericResponse* gr = new GenericResponse(player, 0xED, 1, byte2);
	//System::out << "GenericResponse: " <<  gr->toString() << endl;
	player->sendMessage(gr);

	/*
	 InstallationObjectDeltaMessage3* dinso3 = new InstallationObjectDeltaMessage3(inso);
	 dinso3->updateOperating(true);
	 dinso3->close();
	 player->sendMessage(dinso3);

	 InstallationObjectDeltaMessage7* dinso7 = new InstallationObjectDeltaMessage7(inso);
	 dinso7->updateOperating(true);
	 dinso7->close();
	 player->sendMessage(dinso7);
	 */

}

// Structures
void ObjectControllerMessage::parsePermissionListModify(Player* player, Message* pack) {
	//Skip target id
	pack->shiftOffset(8);

	//Grab the command string:
	UnicodeString commands;
	String commandStr;
	pack->parseUnicode(commands);
	commandStr = commands.toString();

	//Parse the vars from the command string
	String name;
	String temp;
	uint8 listType = 1;
	bool add = false;

	//Set the name of player being modified, list type & determine if player is being add/removed
	StringTokenizer cmdTok(commandStr);
	cmdTok.setDelimeter(" ");
	cmdTok.getStringToken(name);
	name = name.toLowerCase();

	cmdTok.getStringToken(temp);
	if(temp.compareTo("ENTRY") == 0) {
		listType = StructurePermissionList::ENTRYLIST;
	} else if(temp.compareTo("HOPPER") == 0) {
		listType = StructurePermissionList::HOPPERLIST;
	} else if(temp.compareTo("BAN") == 0) {
		listType = StructurePermissionList::BANLIST;
	} else if(temp.compareTo("VENDOR") == 0) {
		listType = StructurePermissionList::VENDORLIST;
	} else if(temp.compareTo("ADMIN") == 0) {
		listType = StructurePermissionList::ADMINLIST;
	} else {
		listType = StructurePermissionList::NONE;
	}

	//determine if the action is for adding/removing. remove = default.
	cmdTok.getStringToken(temp);
	if(temp.compareTo("add") == 0) {
		add = true;
	}

	//Send to buildingobject handler
	BuildingObject* blo = (BuildingObject*)player->getBuilding();
	if(blo == NULL)
		return;

	blo->handlePermissionListModify(player, listType, name, add);
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

void ObjectControllerMessage::parseGroupInvite(Player* player, Message* pack,
		GroupManager* groupManager) {
	uint64 objectID = pack->parseLong();
	SceneObject* object = player->getZone()->lookupObject(objectID);

	if (object == NULL || !object->isPlayer() || object == player)
		return;

	Player* invitePlayer = (Player*) object;
	groupManager->inviteToGroup(player, invitePlayer);
}

void ObjectControllerMessage::parseGroupJoin(Player* player, Message* pack,
		GroupManager* groupManager) {
	groupManager->joinGroup(player);
}

void ObjectControllerMessage::parseGroupUninvite(Player* player, Message* pack) {
	uint64 objectID = pack->parseLong();
	SceneObject* object = player->getZone()->lookupObject(objectID);

	if (object == NULL || !object->isPlayer() || object == player)
		return;

	Player* play = (Player*) object;

	try {
		play->wlock(player);

		if (play->getGroupInviterID() != player->getObjectID()) {
			player->sendSystemMessage("group", "must_be_leader");
			play->unlock();
			return;
		} else {
			play->updateGroupInviterId(0);
			play->sendSystemMessage("group", "uninvite_self");
			player->sendSystemMessage("group", "uninvite_target",
					play->getObjectID());
		}

		play->unlock();
	} catch (...) {
		play->unlock();
		System::out
				<< "Exception in parseGroupUninvite(Player* player, Message* pack)\n";
	}
}

void ObjectControllerMessage::parseGroupLeave(Player* player, Message* pack,
		GroupManager* groupManager) {
	ManagedReference<GroupObject> group = player->getGroupObject();

	if (group == NULL)
		return;

	groupManager->leaveGroup(group.get(), player);
}

void ObjectControllerMessage::parseGroupDisband(Player* player, Message* pack,
		GroupManager* groupManager) {
	ManagedReference<GroupObject> group = player->getGroupObject();
	if (group == NULL)
		return;

	//If player not is leader, he will leave the group instead.
	//Fix 13 feb 2009 - Bankler
	if (player != group->getLeader())
		groupManager->leaveGroup(group.get(), player);

	else
		groupManager->disbandGroup(group.get(), player);
}

void ObjectControllerMessage::parseGroupKick(Player* player, Message* pack,
		GroupManager* groupManager) {
	uint64 target = pack->parseLong();
	SceneObject* object = player->getZone()->lookupObject(target);

	if (object == NULL || !object->isPlayer() || object == player)
		return;

	Player* targetObject = (Player*) object;

	ManagedReference<GroupObject> group = player->getGroupObject();
	if (group == NULL)
		return;

	groupManager->kickFromGroup(group.get(), player, targetObject);
}

void ObjectControllerMessage::parseGroupMakeLeader(Player* player,
		Message* pack, GroupManager* groupManager) {
	uint64 target = pack->parseLong();
	SceneObject* object = player->getZone()->lookupObject(target);

	if (object == NULL || !object->isPlayer() || object == player)
		return;
	Player* targetObject = (Player*) object;

	GroupObject* group = player->getGroupObject();
	if (group == NULL)
		return;

	groupManager->makeLeader(group, player, targetObject);
}

void ObjectControllerMessage::parseGroupDecline(Player* player, Message* pack) {
	uint64 inviterID = player->getGroupInviterID();
	SceneObject* object = player->getZone()->lookupObject(inviterID);

	if (object == NULL || !object->isPlayer() || object == player)
		return;

	Player* inviter = (Player*) object;

	player->updateGroupInviterId(0);
	inviter->sendSystemMessage("group", "decline_leader", player->getObjectID());
	player->sendSystemMessage("group", "decline_self");
}

void ObjectControllerMessage::parseMount(Player* player, Message* pack) {
	uint64 target = pack->parseLong();
	SceneObject* object = player->getZone()->lookupObject(target);

	if (object == NULL || object->isPlayer() || object == player)
		return;
	CreatureObject* creo;
	if (object->isNonPlayerCreature())
		creo = (CreatureObject*) object;

	if (creo == NULL || !creo->isMount())
		return;
	else {
		if (player->isMounted())
			player->dismount();
		else
			player->mountCreature(creo);
	}
}

void ObjectControllerMessage::parseDismount(Player* player, Message* pack) {
	CreatureObject* mount = player->getMount();

	if (mount == NULL)
		return;
	else {
		player->dismount();
	}
}

void ObjectControllerMessage::parseTip(Player* player, Message* pack, PlayerManager* playerManager) {
	if (!player->canTip()) {
		player->sendSystemMessage("You can only tip once every 10 seconds.");
		return;
	}

	StfParameter* params = new StfParameter();

	player->updateNextTipTime();

	uint64 recipientID = pack->parseLong();

	UnicodeString tipParams;
	pack->parseUnicode(tipParams);

	StringTokenizer tokenizer(tipParams.toString());
	tokenizer.setDelimeter(" ");

	if (!tokenizer.hasMoreTokens()) {
		delete params;
		return;
	}

	uint32 tipAmount = 0;

	if (recipientID == 0) {
		//either player not in range. Or not online. So lets do a bank tip.

		String recipientName;
		tokenizer.getStringToken(recipientName);

		//Ok so now we have the name. Lets verify they exist first before doing anything else.
		if (!playerManager->validateName(recipientName)) {
			//Ok so the player exists. So lets parse the rest of the packet now.

			if (!tokenizer.hasMoreTokens()) {
				delete params;
				return;
			}

			String tips;
			tokenizer.getStringToken(tips);

			tipAmount = atol(tips.toCharArray());

			if (tipAmount == 0) {
				params->addTO(tips);
				player->sendSystemMessage("base_player", "prose_tip_invalid_param", params); //TIP: invalid amount ("%TO") parameter.
				delete params;
				return;
			}

			/*
			 if (tokenizer.hasMoreTokens()) {
			 //Theres more crap typed, we can just ignore it.
			 //Maybe change this in the future. To FORCE players to type bank.
			 player->sendSystemMessage("Invalid Tip Parameter (More Tokens)");
			 return;
			 }
			 */

			Player* recipient = playerManager->getPlayer(recipientName);

			if (recipient == NULL) {
				//The player exists but they are offline, so still do the tip.
				//Do stuff like altering the db here since they arent online.
				if (playerManager->modifyOfflineBank(player, recipientName, tipAmount))
					player->sendSystemMessage("Player not online. Credits should be transferred.");

				delete params;
				return;
			} else {
				//Player is online. Tip their stuff and send mail etc;
				//make sure they have the proper credits first.
				try {
					recipient->wlock(player);
					player->bankTipStart(recipient, tipAmount);
					recipient->unlock();
				} catch (...) {
					player->error("Unhandled exception in ObjectControllerMessage:parseTip");
					recipient->unlock();
				}
			}

		} else {
			//Invalid Player Name
			player->sendSystemMessage("ui_cmnty", "friend_location_failed_noname"); //No player with that name exists.
			delete params;
			return;
		}

	} else {
		//The player has SOMETHING targetted.
		//Lets first check if its a player, cause if it is we can skip some stuff.
		SceneObject* object = player->getZone()->lookupObject(recipientID);

		if (object == NULL) {
			player->sendSystemMessage("Usage: /tip <amount> with the player you want to tip as target. Use  '/tip <name> <amount> bank' to tip with the recipients name via bank.");
			delete params;
			return;
		}

		if (object == player) {
			player->sendSystemMessage("You cannot tip yourself.");
			delete params;
			return;
		}

		if (object->isPlayer()) {
			//Ok so we know its a player.
			//If its a player in range, the client will omit any text referencing the name.
			//So the next param SHOULD be the tip amount.
			if (!tokenizer.hasMoreTokens()) {
				delete params;
				return;
			}

			String tips;
			tokenizer.getStringToken(tips);
			tipAmount = atoi(tips.toCharArray());

			//Quick cast of the object to a Player.
			Player* recipient = (Player*) object;

			//They didnt type in a number, or typed in 0.
			if (tipAmount == 0) {
				params->addTO(tips);
				player->sendSystemMessage("base_player", "prose_tip_invalid_param", params); //TIP: invalid amount ("%TO") parameter.
				delete params;
				return;
			}

			//Now that we have the tip amount, we have to see if they want it to be a regular tip
			//or a bank tip. So we check if theres more tokens.
			if (tokenizer.hasMoreTokens()) {
				//Theres more crap typed, so we have to check that they typed ONLY bank.
				String bankParam;
				tokenizer.getStringToken(bankParam);

				if (bankParam == "bank") {
					//Bank tip. We don't need to parse anything else now that we have this info.
					try {
						recipient->wlock(player);
						player->bankTipStart(recipient, tipAmount);
						recipient->unlock();
					} catch (...) {
						player->error("Unhandled exception in ObjectControllerMessage:parseTip");
						recipient->unlock();
					}

				} else {
					//They typed something else other than bank.
					params->addTO(bankParam);
					player->sendSystemMessage("base_player", "prose_tip_invalid_param", params); //TIP: invalid amount ("%TO") parameter.
					delete params;
					return;
				}

			} else {
				//Theres nothing else typed, so they want to do a cash tip. Cake!
				try {
					recipient->wlock(player);
					player->cashTip(recipient, tipAmount);
					recipient->unlock();
				} catch (...) {
					player->error("Unhandled exception in ObjectControllerMessage:parseTip");
					recipient->unlock();
				}
			}

		} else {
			//The current target is not a player.
			//So we have to parse for a valid player name. (THIS IS ONLY FOR BANK TIPS)

			if (!tokenizer.hasMoreTokens()) {
				delete params;
				return;
			}

			String recipientName;
			tokenizer.getStringToken(recipientName);

			//Before we go any further we should validate the player name.
			if (!playerManager->validateName(recipientName)) {
				//They exist at least. Now lets grab the tip amount.
				if (!tokenizer.hasMoreTokens()) {
					delete params;
					return;
				}

				String tips;
				tokenizer.getStringToken(tips);
				tipAmount = atoi(tips.toCharArray());

				//They didnt type in a number, or typed in 0.
				if (tipAmount == 0) {
					params->addTO(tips);
					player->sendSystemMessage("base_player", "prose_tip_invalid_param", params); //TIP: invalid amount ("%TO") parameter.
					delete params;
					return;
				}

				//Ok so now we have the name, and we've verified the tip amount.
				//Now all thats left to do is the bank tip.
				//We have to make sure the player typed bank at the end.
				if (tokenizer.hasMoreTokens()) {
					//Theres more crap typed, so we have to check that they typed ONLY bank.
					String bankParam;
					tokenizer.getStringToken(bankParam);

					if (bankParam == "bank") {
						//Bank tip. We don't need to parse anything else now that we have this info.
						Player* recipient = playerManager->getPlayer(recipientName);
						if (recipient == NULL) {
							//The player exists but they are offline. So Still do the tip.
							//Do stuff like altering the db here since they arent online.
							playerManager->modifyOfflineBank(player, recipientName, tipAmount);
							player->sendSystemMessage("Player not online. Add Altering the DB in later.");
							delete params;
							return;
						} else {
							//Player is online. Tip their stuff and send mail etc;
							//make sure they have the proper credits first.
							try {
								recipient->wlock(player);
								player->bankTipStart(recipient, tipAmount);
								recipient->unlock();
							} catch (...) {
								player->error("Unhandled exception in ObjectControllerMessage:parseTip");
								recipient->unlock();
							}
						}
					} else {
						//They typed something else other than bank.
						params->addTO(bankParam);
						player->sendSystemMessage("base_player", "prose_tip_invalid_param", params); //TIP: invalid amount ("%TO") parameter.
						delete params;
						return;
					}
				}
			} else {
				//Invalid Player Name
				player->sendSystemMessage("ui_cmnty", "friend_location_failed_noname"); //No player with that name exists.
				delete params;
				return;
			}
		}
	}
}

void ObjectControllerMessage::handleDeathblow(Player* player, Message* packet,
		CombatManager* combatManager) {
	uint64 targetID = packet->parseLong();

	SceneObject* object = player->getZone()->lookupObject(targetID);

	if (object == NULL || !object->isPlayer() || object == player)
		return;

	Player* target = (Player*) object;


	try {
		target->wlock(player);

		if (combatManager->canAttack(player, target)
				&& target->isIncapacitated() && target->isInRange(player, 5)) {

			player->deathblow(target);
		}

		target->unlock();
	} catch (...) {
		System::out
				<< "Unreported exception caught in ObjectControllerMessage::handleDeathblow(Player* player, Message* packet)\n";
		target->unlock();
	}
}

void ObjectControllerMessage::parsePlaceStructure(Player* player,
		Message* packet) {
	player->sendSystemMessage("Placing Structure");
	packet->parseInt(); // Empty Data
	packet->parseInt(); // Empty Data

	UnicodeString data;
	packet->parseUnicode(data);

	StringTokenizer tokenizer(data.toString());

	String objectID;
	tokenizer.getStringToken(objectID);

	float x = tokenizer.getFloatToken();
	float y = tokenizer.getFloatToken();

	int orient = tokenizer.getIntToken();

	uint64 toID = (uint64)Long::valueOf(objectID);

	PlanetManager* planet = player->getZone()->getPlanetManager();

	planet->placePlayerStructure(player, toID, x, y, orient);
}

void ObjectControllerMessage::parseSynchronizedUIListen(Player *player,
		Message *pack) {
	uint64 objectid = pack->parseLong();  // Object ID
	int value = pack->parseInt();

	SceneObject* object = player->getZone()->lookupObject(objectid);

	if (object == NULL)
		return;

	object->synchronizedUIListen(player, value);
}

void ObjectControllerMessage::parseSynchronizedUIStopListening(Player *player,
		Message *pack) {
	uint64 objectid = pack->parseLong(); // Object ID
	int value = pack->parseInt();

	SceneObject* object = player->getZone()->lookupObject(objectid);

	if (object == NULL)
		return;

	object->synchronizedUIStopListen(player, value);

}

void ObjectControllerMessage::parseHarvesterActivate(Player *player,
		Message *pack) {
	uint64 objectid = pack->parseLong(); // Pop the Harvester ID - there might be some other int afterwards?

	SceneObject* object = player->getZone()->lookupObject(objectid);

	if (object == NULL)
		return;

	if (!object->isTangible())
		return;

	TangibleObject* tano = (TangibleObject*) object;

	if (tano->getObjectSubType() != TangibleObjectImplementation::HARVESTER)
		return;

	InstallationObject* inso = (InstallationObject*) tano;

	try {
		inso->wlock(player);

		InstallationObjectDeltaMessage3* dinso3 =
			new InstallationObjectDeltaMessage3(inso);
		dinso3->updateOperating(true);
		dinso3->close();
		player->sendMessage(dinso3);

		InstallationObjectDeltaMessage7* dinso7 =
			new InstallationObjectDeltaMessage7(inso);
		dinso7->updateOperating(true);
		dinso7->updateExtractionRate(inso->getActualRate());
		dinso7->close();
		player->sendMessage(dinso7);

		inso->unlock();
	} catch (...) {
		inso->unlock();
	}
}

void ObjectControllerMessage::parseHarvesterDeActivate(Player *player,
		Message *pack) {
	uint64 objectid = pack->parseLong(); // Pop the Harvester ID - there might be some other int afterwards?

	SceneObject* object = player->getZone()->lookupObject(objectid);

	if (object == NULL)
		return;

	if (!object->isTangible())
		return;

	TangibleObject* tano = (TangibleObject*) object;

	if (tano->getObjectSubType() != TangibleObjectImplementation::HARVESTER)
		return;

	InstallationObject* inso = (InstallationObject*) tano;

	try {
		inso->wlock(player);

		InstallationObjectDeltaMessage3* dinso3 =
			new InstallationObjectDeltaMessage3(inso);
		dinso3->updateOperating(false);
		dinso3->close();
		player->sendMessage(dinso3);

		InstallationObjectDeltaMessage7* dinso7 =
			new InstallationObjectDeltaMessage7(inso);
		dinso7->updateOperating(false);
		dinso7->close();
		player->sendMessage(dinso7);

		inso->unlock();
	} catch (...) {
		inso->unlock();
	}
}

void ObjectControllerMessage::parseHarvesterDiscardHopper(Player *player,
		Message *pack) {
	//skip objId + old size
	pack->shiftOffset(12);

	//if (pack->getSize())

	uint64 hId = pack->parseLong();
	SceneObject* object = player->getZone()->lookupObject(hId);

	if (object == NULL) {
		player->error(
				"ObjectControllerMessage::parseResourceEmptyHopper() bad object");
		return;
	}

	if (!object->isTangible()) {
		player->error(
				"ObjectControllerMessage::parseResourceEmptyHopper() bad tano");
		return;
	}

	TangibleObject* tano = (TangibleObject*) object;
	if (tano->getObjectSubType() != TangibleObjectImplementation::HARVESTER) {
		player->error(
				"ObjectControllerMessage::parseResourceEmptyHopper() bad harvester");
		return;
	}

	InstallationObject* inso = (InstallationObject*) tano;

	// Need to loop through and remove each item in hopper


	//Grab the harvester object id
	/*pack->shiftOffset(8); // skip passed player
	 uint64 hId = pack->parseLong();
	 uint64 rId = pack->parseLong();
	 uint32 quantity = pack->parseInt(); // need to verify the quantity exists in the hopper
	 uint8 byte1 = pack->parseByte(); // Retrieve vs Discard
	 uint8 byte2 = pack->parseByte(); // checksum?

	 System::out << "ObjectControllerMessage::parseResourceEmptyHopper(), hId: " << hex << hId << dec << " rId : " << rId << " id: " << rId << " quantity: " << quantity << endl;


	 InstallationObject* inso = (InstallationObject*) tano;

	 Zone* zone = player->getZone();
	 if (zone == NULL)
	 return;


	 ResourceManager* resourceManager = zone->getZoneServer()->getResourceManager();
	 if (resourceManager == NULL)
	 return;

	 bool makeNewResource = true;

	 quantity = inso->removeHopperItem(rId, quantity);
	 if (quantity >= 1)
	 {
	 if (byte1 == 0) // Retreive vs Discard
	 {
	 ResourceContainer* newRcno = new ResourceContainer(player->getNewItemID());
	 String resourceName = resourceManager->getResourceNameByID(rId);
	 newRcno->setResourceName(resourceName);
	 newRcno->setContents(quantity);
	 resourceManager->setResourceData(newRcno, false);
	 player->addInventoryResource(newRcno);
	 }
	 }
	 // need to send to anyone looking


	 InstallationObjectDeltaMessage7* dinso7 = new InstallationObjectDeltaMessage7(inso);
	 dinso7->updateHopper();
	 dinso7->updateHopperItem(rId);
	 dinso7->updateHopperSize();
	 dinso7->close();
	 player->sendMessage(dinso7);

	 GenericResponse* gr = new GenericResponse(player, 0xED, 1, byte2);
	 //System::out << "GenericResponse: " <<  gr->toString() << endl;
	 player->sendMessage(gr);

	 */

	/*
	 InstallationObjectDeltaMessage3* dinso3 = new InstallationObjectDeltaMessage3(inso);
	 dinso3->updateOperating(true);
	 dinso3->close();
	 player->sendMessage(dinso3);

	 InstallationObjectDeltaMessage7* dinso7 = new InstallationObjectDeltaMessage7(inso);
	 dinso7->updateOperating(true);
	 dinso7->close();
	 player->sendMessage(dinso7);
	 */

}

void ObjectControllerMessage::parseHarvesterGetResourceData(Player *player,
		Message *pack) {
	uint64 objectid = pack->parseLong(); // Pop the Harvester ID - there might be some other int afterwards?

	SceneObject* object = player->getZone()->lookupObject(objectid);

	if (object == NULL)
		return;

	if (!object->isTangible())
		return;

	TangibleObject* tano = (TangibleObject*) object;

	if (tano->getObjectSubType() != TangibleObjectImplementation::HARVESTER)
		return;

	HarvesterObject* hino = (HarvesterObject*) tano;

	HarvesterResourceDataMessage* hrdm = new HarvesterResourceDataMessage(
			player, hino);
	player->sendMessage(hrdm);
}

void ObjectControllerMessage::parseHarvesterSelectResource(Player *player,
		Message *pack) {
	uint64 objectid = pack->parseLong(); // Pop the Harvester ID - there might be some other int afterwards?
	SceneObject* object = player->getZone()->lookupObject(objectid);

	// Unicode - common!
	UnicodeString resourceIDUnicode("");
	pack->parseUnicode(resourceIDUnicode);

	String sResourceID = resourceIDUnicode.toString();

	//System::out << "harvesterSelectResource: " << sResourceID << endl;

	uint64 resourceID = (uint64)Long::valueOf(sResourceID);

	//return;
	if (object == NULL)
		return;

	if (!object->isTangible())
		return;

	TangibleObject* tano = (TangibleObject*) object;

	if (tano->getObjectSubType() != TangibleObjectImplementation::HARVESTER)
		return;

	InstallationObject* inso = (InstallationObject*) tano;

	try {
		inso->wlock(player);

		InstallationObjectDeltaMessage7* dinso7 =
			new InstallationObjectDeltaMessage7(inso);
		dinso7->updateActiveResource(resourceID);
		dinso7->updateExtractionRate(inso->getActualRate());
		dinso7->close();
		player->sendMessage(dinso7);

		inso->unlock();
	} catch (...) {
		inso->unlock();
	}
}

void ObjectControllerMessage::parseExtractObject(Player* player,
		Message* packet) {
	uint64 objectID = packet->parseLong();
	SceneObject* object = player->getInventoryItem(objectID);

	if (object == NULL)
		return;

	if (player->hasFullInventory()) {
		player->sendSystemMessage("You don't have enough space in your inventory to do that.");
		return;
	}
	TangibleObject* tano = (TangibleObject*) object;
	//if (!object->isFactoryCrate())
	//	return;

	FactoryCrate* crate = (FactoryCrate*) tano;

	try {
		crate->wlock(player);

		crate->useObject(player);

		crate->unlock();
	} catch (...) {
		crate->unlock();
	}
}

void ObjectControllerMessage::parseSurveySlashRequest(Player* player,
		Message* packet) {
	player->setSurveyErrorMessage();
}

void ObjectControllerMessage::parseSampleSlashRequest(Player* player,
		Message* packet) {
	player->setSampleErrorMessage();
}

void ObjectControllerMessage::parseSurveyRequest(Player* player,
		Message* packet) {
	uint64 targetID = packet->parseLong();

	UnicodeString resourceName;
	packet->parseUnicode(resourceName);

	String resName = resourceName.toString();

	String skillBox = "crafting_artisan_novice";

	if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox)) {
		if (player->getSurveyTool() == NULL) {
			player->sendSystemMessage("ui", "survey_notool"); //You must use a survey tool once from the Inventory before you can do this.
			return;
		}
		player->getSurveyTool()->surveyRequest(player, resName);
	} else {
		if (player->getSurveyErrorMessage())
			player->sendSystemMessage(
					"You do not have sufficient abilities to Survey Resources.");
	}
}

void ObjectControllerMessage::parseSampleRequest(Player* player,
		Message* packet) {
	uint64 targetID = packet->parseLong();

	UnicodeString resourceName;
	packet->parseUnicode(resourceName);

	String resName = resourceName.toString();

	String skillBox = "crafting_artisan_novice";

	if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox)) {
		if (player->getSurveyTool() == NULL) {
			player->sendSystemMessage(
					"You must use a survey tool once from the Inventory before you can do this.");
			return;
		}
		player->getSurveyTool()->sampleRequest(player, resName);
	} else {
		if (player->getSampleErrorMessage())
			player->sendSystemMessage(
					"You do not have sufficient abilities to Sample Resource.");
	}
}

void ObjectControllerMessage::parseResourceContainerSplit(Player* player,
		Message* packet) {
	if (player->getTradeSize() != 0) {
		player->sendSystemMessage("You cant move objects while trading..");
		return;
	}

	if (player->hasFullInventory()) {
		player->sendSystemMessage(
				"Youd dont have enough space in your inventory");
		return;
	}

	uint64 objectID = packet->parseLong();

	UnicodeString resourceQuantity;
	packet->parseUnicode(resourceQuantity);

	StringTokenizer tokenizer(resourceQuantity.toString());

	String quantityString;

	if (tokenizer.hasMoreTokens())
		tokenizer.getStringToken(quantityString);
	else
		return;

	int newQuantity = atoi(quantityString.toCharArray());

	ManagedReference<SceneObject> invObj = player->getInventoryItem(objectID);

	if (invObj != NULL && invObj->isTangible()) {
		TangibleObject* tano = (TangibleObject*) invObj.get();

		if (tano->isResource()) {
			ResourceContainer* rco = (ResourceContainer*) tano;

			rco->splitContainer(player, newQuantity);
		}
	}
}

void ObjectControllerMessage::parseResourceContainerTransfer(Player* player,
		Message* packet) {
	if (player->getTradeSize() != 0) {
		player->sendSystemMessage("You cant move objects while trading..");
		return;
	}

	uint64 fromID = packet->parseLong();

	UnicodeString ustr;
	packet->parseUnicode(ustr);

	StringTokenizer tokenizer(ustr.toString());

	String quantityString, toIDString;

	if (tokenizer.hasMoreTokens())
		tokenizer.getStringToken(toIDString);

	if (tokenizer.hasMoreTokens())
		tokenizer.getStringToken(quantityString);

	uint64 toID = (uint64)Long::valueOf(toIDString);

	ManagedReference<SceneObject> object1 = player->getInventoryItem(fromID);
	ManagedReference<SceneObject> object2 = player->getInventoryItem(toID);

	if (object1 != NULL && object2 != NULL && object1->isTangible()
			&& object2->isTangible()) {
		TangibleObject* resCof = (TangibleObject*) object1.get();
		TangibleObject* resCot = (TangibleObject*) object2.get();
		if (resCof->isResource() && resCot->isResource()) {
			ResourceContainer* rcof = (ResourceContainer*) resCof;
			ResourceContainer* rcot = (ResourceContainer*) resCot;
			rcot->transferContents(player, rcof);
		}
	}
}


void ObjectControllerMessage::parseRequestCraftingSession(Player* player,
		Message* packet) {

	uint64 oid = packet->parseLong();
	ManagedReference<SceneObject> scno = player->getZone()->lookupObject(oid);

	if (scno == NULL)
		return;

	if (!scno->isTangible())
		return;

	if (((TangibleObject*) scno.get())->isCraftingTool()) {

		CraftingTool* craftingTool = (CraftingTool*) scno.get();

		if (craftingTool != NULL) {

			if (player->isMounted()) {
				craftingTool->sendToolStartFailure(player, "error_message",
						"survey_on_mount");
				return;
			}

			if (craftingTool->isReady())

				craftingTool->sendToolStart(player);

			else if (craftingTool->isFinished())

				craftingTool->sendToolStartFailure(player, "system_msg",
						"crafting_tool_full");

			else

				craftingTool->sendToolStartFailure(player, "system_msg",
						"crafting_tool_creating_prototype");

		}
	} else {

		if (!((TangibleObject*) scno.get())->isCraftingStation())
			return;

		CraftingStation* craftingStation = (CraftingStation*) scno.get();

		if (craftingStation == NULL)
			return;

		CraftingTool* craftingTool = player->getCraftingTool(
				craftingStation->getStationType(), false);

		if (craftingTool != NULL)
			craftingTool->sendToolStart(player);
		else
			player->sendSystemMessage("No tool available to start.");
	}
}

void ObjectControllerMessage::parseCancelCraftingSession(Player* player, Message* packet) {
	ManagedReference<CraftingTool> craftingTool = player->getActiveCraftingTool();

	if (craftingTool == NULL)
		return;

	// DPlay9
	PlayerObjectDeltaMessage9* dplay9 =
			new PlayerObjectDeltaMessage9(player->getPlayerObject());
	dplay9->setCraftingState(0);
	craftingTool->setCraftingState(0);
	dplay9->close();
	player->sendMessage(dplay9);

	// Clean up crafting here, delete, sceneremove unneeded objects
	craftingTool->cleanUp(player);

	// Object Controller ********************************************
	ObjectControllerMessage* objMsg =
			new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x01C2);
	objMsg->insertByte(0);

	player->sendMessage(objMsg);
	//End Object Controller ******************************************
}

void ObjectControllerMessage::parseSelectDraftSchematic(Player* player, Message* packet) {

	CraftingTool* craftingTool = player->getActiveCraftingTool();

	if(craftingTool == NULL)
		return;

	uint64 unknown = packet->parseLong();

	if(unknown != 0)
		System::out << "parseSelectDraftSchematic's unknown is " << unknown << endl;

	UnicodeString uniIndexOfSelectedSchematic;
	packet->parseUnicode(uniIndexOfSelectedSchematic);

	StringTokenizer tokenizer(uniIndexOfSelectedSchematic.toString());

	int indexOfSelectedSchematic;

	if (tokenizer.hasMoreTokens()) {
		indexOfSelectedSchematic = tokenizer.getIntToken();

		DraftSchematic* draftSchematic =
			craftingTool->getCurrentDraftSchematic(indexOfSelectedSchematic);

		if (draftSchematic == NULL) {

			parseCancelCraftingSession(player, packet);
			craftingTool->sendToolStart(player);
			draftSchematic = craftingTool->getCurrentDraftSchematic(indexOfSelectedSchematic);
		}

		if (draftSchematic != NULL) {

			CraftingManager* craftingManager =
				player->getZone()->getZoneServer()->getCraftingManager();

			craftingManager->prepareCraftingSession(player, craftingTool, draftSchematic);

		} else {
			// This else should never execute
			player->sendSystemMessage("Selected Draft Schematic was invalid.  Please inform Kyle of this error.");
		}
	}
}

void ObjectControllerMessage::parseRequestDraftSlotsBatch(Player* player, Message* packet) {
	packet->shiftOffset(8);

	UnicodeString crcAndID;
	packet->parseUnicode(crcAndID);

	StringTokenizer tokenizer(crcAndID.toString());

	uint32 schematicID;
	uint32 schematicCRC;
	// CHANGE THIS WHEN .getIntToken WORKS RIGHT
	if (tokenizer.hasMoreTokens())
		schematicID = tokenizer.getLongToken();
	if (tokenizer.hasMoreTokens())
		schematicCRC = tokenizer.getLongToken();

	//Check to see if the correct obj id is in the players vector of draft schematics
	DraftSchematic* ds = player->getDraftSchematic(schematicID);
	if (ds != NULL) {
		ds->sendIngredientsToPlayer(player);
	}
}



void ObjectControllerMessage::parseRequestResourceWeightsBatch(Player* player, Message* packet) {

	packet->shiftOffset(8);

	UnicodeString id;
	packet->parseUnicode(id);

	StringTokenizer tokenizer(id.toString());

	uint32 schematicID;
	if (tokenizer.hasMoreTokens())
		schematicID = tokenizer.getIntToken();

	//Check to see if the correct obj id is in the players vector of draft schematics
	DraftSchematic* ds = player->getDraftSchematic(schematicID);
	if (ds != NULL) {
		ds->sendExperimentalPropertiesToPlayer(player);
	}
}


void ObjectControllerMessage::parseAddCraftingResource(Player* player,
		Message* packet) {

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
void ObjectControllerMessage::parseRemoveCraftingResource(Player* player,
		Message* packet) {

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
void ObjectControllerMessage::parseNextCraftingStage(Player* player, Message* packet) {

	CraftingTool* craftingTool = player->getActiveCraftingTool();

	if(craftingTool == NULL)
		return;

	packet->shiftOffset(8);

	UnicodeString d;
	packet->parseUnicode(d);

	String data = d.toString();

	CraftingManager* craftingManager = player->getZone()->getZoneServer()->getCraftingManager();
	craftingManager->nextCraftingStage(craftingTool, player, data);
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
void ObjectControllerMessage::parseCreatePrototype(Player* player, Message* packet) {

	CraftingTool* craftingTool = player->getActiveCraftingTool();

	if(craftingTool == NULL)
		return;

	packet->shiftOffset(8);

	UnicodeString d;
	packet->parseUnicode(d);

	int counter, practice;

	StringTokenizer tokenizer(d.toString());

	if(tokenizer.hasMoreTokens())
		counter = tokenizer.getIntToken();
	else
		return;

	if(tokenizer.hasMoreTokens())
		practice = tokenizer.getIntToken();
	else
		practice = 1;

	CraftingManager* craftingManager = player->getZone()->getZoneServer()->getCraftingManager();
	craftingManager->createPrototype(craftingTool, player, counter, practice);
}

void ObjectControllerMessage::parseCreateSchematic(Player* player, Message* packet) {

	CraftingTool* craftingTool = player->getActiveCraftingTool();

	if(craftingTool == NULL)
		return;

	packet->shiftOffset(8);

	UnicodeString str;
	packet->parseUnicode(str);

	int counter;

	StringTokenizer tokenizer(str.toString());

	if(tokenizer.hasMoreTokens())
		counter = tokenizer.getIntToken();
	else
		return;

	CraftingManager* craftingManager = player->getZone()->getZoneServer()->getCraftingManager();
	craftingManager->createSchematic(craftingTool, player, counter);
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

void ObjectControllerMessage::parseTransferArmor(Player* player, Message* pack) {
	uint64 target = pack->parseLong();

	TangibleObject* targetTanoObject;
	targetTanoObject = (TangibleObject*) player->getInventoryItem(target);

	if (targetTanoObject != NULL) {
		Inventory* inventory = player->getInventory();

		if (inventory != NULL)
			inventory->moveObjectToTopLevel(player, targetTanoObject);

		player->changeArmor(target, false);
	}
}

void ObjectControllerMessage::parseItemDropTrade(Player* player, Message* pack) {
	uint64 targetPlayerId = pack->parseLong();

	pack->shiftOffset(16);

	uint64 tradeItemId = pack->parseLong();

	ManagedReference<SceneObject> obj = player->getZone()->lookupObject(targetPlayerId);
	ManagedReference<SceneObject> item = player->getZone()->lookupObject(tradeItemId);

	if(obj.get() == NULL || item.get() == NULL)
		return;

	if (!obj->isPlayer())
		return;

	if (!item->isPlayer())
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

void ObjectControllerMessage::parseTransferWeapon(Player* player, Message* pack) {
	uint64 target = pack->parseLong();

	TangibleObject* targetTanoObject;
	targetTanoObject = (TangibleObject*) player->getInventoryItem(target);

	if (targetTanoObject != NULL) {
		Inventory* inventory = player->getInventory();

		if (inventory != NULL)
			inventory->moveObjectToTopLevel(player, targetTanoObject);

		player->changeWeapon(target, true);
	}
}

void ObjectControllerMessage::parseTransferItemMisc(Player* player, Message* pack) {
	//Equip weapon + equip armor never gets here, they have their own CRC, while unequipping of all items WILL go here
	uint64 target = pack->parseLong();
	UnicodeString data;
	pack->parseUnicode(data);

	StringTokenizer tokenizer(data.toString());
	tokenizer.setDelimeter(" ");

	uint64 destinationID = tokenizer.getLongToken();

	//TODO: Pretty sure that this should be called transferType rather than unknown?
	int unknown = tokenizer.getIntToken(); // I've seen -1 usually.. 4 when equipping most clothes (I think -1 is remove)

	float x = tokenizer.getFloatToken();
	float z = tokenizer.getFloatToken();
	float y = tokenizer.getFloatToken();

	TangibleObject* targetTanoObject;

	if (destinationID == player->getObjectID()) { //equipping misc. item to player
		targetTanoObject = (TangibleObject*) player->getInventoryItem(target);

		if (targetTanoObject != NULL) {
			Inventory* inventory = player->getInventory();

			if (inventory != NULL)
				inventory->moveObjectToTopLevel(player, targetTanoObject);

			if(targetTanoObject->isInstrument()) {
				player->changeWeapon(target, true);

			} else if(targetTanoObject->isClothing()) {
				player->changeArmor(target, true);

			} else if(targetTanoObject->isWearableContainer()) {
				player->changeArmor(target, true);
			}

		}

	} else if (destinationID == player->getObjectID() + 1) { //item is going to inventory
		targetTanoObject = (TangibleObject*) player->getInventoryItem(target);

		if (targetTanoObject == NULL){ //the item can't be found in the inventory - maybe a world object?
			Zone* zone = player->getZone();

			//Here we check to see if the player is staff, and if not, we check to see if they have permission to pickup the item in the structure they are in.
			if (player->getAdminLevel() == PlayerImplementation::NORMAL && player->isInBuilding()) {
				BuildingObject* building = (BuildingObject*) player->getBuilding();

				if (building != NULL) {
					try {
						building->lock();

						if (building->hasCell(destinationID) && !building->isOnAdminList(player)) {
							player->sendSystemMessage("container_error_message", "container08"); //You do not have permission to access that container.
							building->unlock();
							return;
						}

						building->unlock();
					} catch (Exception& e) {
						player->error("Error in ObjectControllerMessage locking building on item pickup");
						building->unlock();
					}
				}
			}

			if (zone != NULL) {
				targetTanoObject = (TangibleObject*) zone->lookupObject(target);
			}
		}

 		if (targetTanoObject != NULL) {
 			if(player->isTanoObjEquipped(targetTanoObject)) {

 				if(targetTanoObject->isWeapon()) {
 					player->changeWeapon(target, true);

 				} else if(targetTanoObject->isInstrument()) {
 					player->changeWeapon(target, true);

 				} else if(targetTanoObject->isArmor()) {
 					player->changeArmor(target, true);

 				} else if(targetTanoObject->isClothing()) {
 					player->changeArmor(target, true);

 				} else if(targetTanoObject->isWearableContainer()) {
 					player->changeArmor(target, true);
 				}
 			}

 		} else {
			//what else object could this be?
 			return;
		}

		SceneObject* targetObject = player->getTarget();

		//Player's target is a dead creature, looting to players inventory
		if (targetObject != NULL && targetObject->isNonPlayerCreature()) {
			Creature* creature = (Creature*) targetObject;

			SceneObject* object;

			try {
				creature->wlock(player);

				//if this is null, player isn't looting but moving stuff around in inventory
				object = creature->getLootItem(target);

				creature->unlock();

			} catch (...) {
				creature->unlock();
			}

			if (object != NULL) {
				player->lootObject(creature, object);
			} else {
				//Current target is a dead creature but player is moving stuff in inventory (because creature->getLootItem returned NULL)
				ManagedReference<TangibleObject> item = validateDropAction(player, target);

				if (item != NULL)
					transferItemToContainer(player, item, destinationID);

				return;
			}

		} else {
			//Player has no dead creature as target and dropping an item from a cell or container to the inventory
			ManagedReference<TangibleObject> item = validateDropAction(player, target);

			if (item != NULL)
				transferItemToContainer(player, item, destinationID);

			return;
		}

		//Dropping FROM the players inventory TO a cell or container (which could also be a nested inventory container)
	} else {
		ManagedReference<TangibleObject> item = validateDropAction(player, target);

		//Here we check to see if the player is staff, and if not, we check to see if they have permission to drop the item in the structure they are in.
		if (player->getAdminLevel() == PlayerImplementation::NORMAL && player->isInBuilding()) {
			BuildingObject* building = (BuildingObject*) player->getBuilding();

			if (building != NULL) {
				try {
					building->lock();

					if (building->hasCell(destinationID) && !building->isOnAdminList(player)) {
						player->sendSystemMessage("container_error_message", "container08"); //You do not have permission to access that container.
						building->unlock();
						return;
					}

					building->unlock();
				} catch (Exception& e) {
					player->error("Unhandled exception in ObjectControllerMessage when trying to lock building and dropping an item.");
					building->unlock();
				}
			}
		}

		if (item != NULL)
			transferItemToContainer(player, item, destinationID);

		return;
	}
}

void ObjectControllerMessage::parseAddFriend(Player* player, Message* pack) {
	//ToDO: Split the token based on dots for game (SWG), server (eg. sunrunner) and name (SWG.sunrunner.john)
	pack->shiftOffset(8);

	UnicodeString d;
	pack->parseUnicode(d);

	String name = d.toString();

	if (name != "") {
		player->getPlayerObject()->addFriend(name,
				player->getZone()->getZoneServer()->getServerName());
	}
}

void ObjectControllerMessage::parseRemoveFriend(Player* player, Message* pack) {
	pack->shiftOffset(8);

	UnicodeString d;
	pack->parseUnicode(d);

	String name = d.toString();

	if (name != "") {
		player->getPlayerObject()->removeFriend(name);
	}
}

void ObjectControllerMessage::parseFindFriend(Player* player, Message* pack,
		PlayerManager* playerManager) {
	pack->shiftOffset(8);

	UnicodeString d;
	pack->parseUnicode(d);

	String name = d.toString();

	if (name != "") {
		player->getPlayerObject()->findFriend(name, playerManager);
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

void ObjectControllerMessage::parseAddIgnore(Player* player, Message* pack) {
	//ToDO: Split the token based on dots for game (SWG), server (eg. sunrunner) and name (SWG.sunrunner.john)
	pack->shiftOffset(8);

	UnicodeString d;
	pack->parseUnicode(d);

	String name = d.toString();

	if (name != "") {
		player->getPlayerObject()->addIgnore(name,
				player->getZone()->getZoneServer()->getServerName());
	}
}

void ObjectControllerMessage::parseRemoveIgnore(Player* player, Message* pack) {

	pack->shiftOffset(8);

	UnicodeString d;
	pack->parseUnicode(d);

	String name = d.toString();

	if (name != "") {
		player->getPlayerObject()->removeIgnore(name);
	}
}

void ObjectControllerMessage::parseGiveConsentRequest(Player* player, Message* pack) {
	if (player->getConsentListSize() >= 15) { //Max consent list size = 15
		player->sendSystemMessage("player_structure", "too_many_entries"); //You have too many entries on that list. You must remove some before adding more.
		return;
	}

	pack->shiftOffset(8);
	UnicodeString UnicodeStringName;
	pack->parseUnicode(UnicodeStringName);
	String name = UnicodeStringName.toString();
	String consentName = "";

	if (name.isEmpty()) {
		player->sendSystemMessage("Syntax: /consent <name>");
		return;
	}

	StringTokenizer tokenizer(name);
	tokenizer.setDelimeter(" ");
	tokenizer.getStringToken(consentName);

	PlayerManager* playerManager = player->getZone()->getZoneServer()->getPlayerManager();
	consentName = consentName.toLowerCase();
	Player* playerTarget = playerManager->getPlayer(consentName);

	if (playerTarget != NULL)
		player->consent(playerTarget);
}

void ObjectControllerMessage::parseRevokeConsentRequest(Player* player, Message* pack) {
	if (player->getConsentListSize() <= 0) {
		player->sendSystemMessage("error_message", "consent_to_empty"); //You have not granted consent to anyone.
		return;
	}

	pack->shiftOffset(8);

	UnicodeString unicodeNames;
	pack->parseUnicode(unicodeNames);
	String nameList = unicodeNames.toString();

	if (nameList.isEmpty()) {
		player->sendConsentList();
		return;
	}

	StringTokenizer tokenizer(nameList);
	tokenizer.setDelimeter(",");

	PlayerManager* playerManager = player->getZone()->getZoneServer()->getPlayerManager();

	while (tokenizer.hasMoreTokens()) {
		String name = "";
		tokenizer.getStringToken(name);
		name = name.toLowerCase();

		player->unconsent(name);
	}

	//TODO: Check for invalid input, and relay the syntax command.
	//player->sendSystemMessage("error_message", "syntax_unconsent"); //syntax: /unconsent  {optionally, use commas to seperate several player names}
}

void ObjectControllerMessage::parseHaveConsentRequest(Player* player,
		Message* pack) {
	pack->shiftOffset(8);
	UnicodeString UnicodeStringName;
	pack->parseUnicode(UnicodeStringName);
	String name = UnicodeStringName.toString();
	String consentName = "";

	if (name.isEmpty()) {
		player->sendConsentList();
		return;
	}

	/*
	 StringTokenizer tokenizer(name);
	 tokenizer.setDelimeter(" ");
	 tokenizer.getStringToken(consentName);
	 */
}

void ObjectControllerMessage::parseHarvestOrganics(Player* player,
		Message* pack) {
	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	ResourceManager* resourceManager =
			zone->getZoneServer()->getResourceManager();
	if (resourceManager == NULL)
		return;

	CreatureManager* creatureManager = zone->getCreatureManager();
	if (creatureManager == NULL)
		return;

	uint64 creatureID = pack->parseLong();

	Creature* creature = creatureManager->getCreature(creatureID);
	if (creature == NULL)
		return;

	//System::out << "Name:" << creature->getObjectID() << "\n";


	try {

		creature->wlock(player);

		int type = 0;

		UnicodeString restype;
		pack->parseUnicode(restype);

		String resourceType = restype.toString();

		if (resourceType == "meat")
			type = 1;

		if (resourceType == "hide")
			type = 2;

		if (resourceType == "bone")
			type = 3;

		resourceManager->harvestOrganics(player, creature, type);

		creature->unlock();
	} catch (...) {
		creature->unlock();
	}
}

void ObjectControllerMessage::parseTeach(Player* player, Message* pack) {
	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	uint64 targetid = pack->parseLong();

	SceneObject* object = zone->lookupObject(targetid);
	if (object == NULL) {
		player->sendSystemMessage("teaching", "no_target");
		return;
	}

	Player* target = NULL;
	if (object->isPlayer())
		target = (Player*) object;
	else {
		player->sendSystemMessage("teaching", "no_target");
		return;
	}

	StfParameter *params = new StfParameter();
	params->addTT(target->getFirstNameProper());

	if (player == target) {
		player->sendSystemMessage("teaching", "no_teach_self");
		delete params;
		return;
	} else if (target->isDead() || target->isIncapacitated()) {
		player->sendSystemMessage("teaching", "student_dead", params);
		delete params;
		return;
	} else if (!player->isInRange(target, 128)) {
		player->sendSystemMessage("teaching", "student_too_far_target", params);
		delete params;
		return;
	} else if (!player->isInAGroup() || !target->isInAGroup()
			|| (player->getGroupObject() != target->getGroupObject())) {
		player->sendSystemMessage("teaching", "not_in_same_group");
		delete params;
		return;
	} else if (target->getTeacher() != NULL) {
		player->sendSystemMessage("teaching", "student_has_offer_to_learn",
				params);
		delete params;
		return;
	}

	delete params;

	UnicodeString opts;
	pack->parseUnicode(opts);

	String skillname = opts.toString();

	if (skillname.length() <= 0) {
		player->teachPlayer(target);
	}
}

void ObjectControllerMessage::handleRemoveFromGuild(Player* player,
		Message* pack, ZoneProcessServerImplementation* serv) {
	//player is prelocked
	uint64 objectid = pack->parseLong();

	SceneObject* object = player->getZone()->lookupObject(objectid);

	if (object == NULL)
		return;

	Player* removePlayer = NULL;

	if (object->isPlayer())
		removePlayer = (Player*) object;
	else
		return;

	GuildManager* pGuild = serv->getGuildManager();

	player->unlock();
	pGuild->removeOnlineFromGuild(player, removePlayer);
	player->wlock();
}

bool ObjectControllerMessage::parseMeditation(Player* player) {

	if (player->isMounted() || player->isDizzied() || player->isInCombat()
			|| player->isKnockedDown()) {

		player->sendSystemMessage("teraskasi", "med_fail");
		return false;
	}

	if (player->isMeditating()) {
		player->sendSystemMessage("jedi_spam", "already_in_meditative_state");
		return false;
	} else {
		player->sendSystemMessage("teraskasi", "med_begin");
		return true;
	}
}

void ObjectControllerMessage::parseDelFactionPoints(Player* player,
		Message* pack) {
	uint64 tipToId = pack->parseLong();

	UnicodeString tipParams;
	pack->parseUnicode(tipParams);

	StringTokenizer tokenizer(tipParams.toString());
	tokenizer.setDelimeter(" ");

	if (!tokenizer.hasMoreTokens())
		return;

	uint32 tipAmount;

	if (tipToId == 0)
		return;

	//The player has SOMETHING targetted.
	//Lets first check if its a player, cause if it is we can skip some stuff.
	SceneObject* object = player->getZone()->lookupObject(tipToId);

	if (object == NULL || !object->isPlayer() || object == player)
		return;

	//Ok so we know its a player.
	//If its a player in range, the client will omit any text referencing the name.
	//So the next param SHOULD be the tip amount.
	if (!tokenizer.hasMoreTokens())
		return;

	tipAmount = tokenizer.getIntToken();

	//Quick cast of the object to a Player.
	Player* tipTo = (Player*) object;

	//They didnt type in a number, or typed in 0.
	if (tipAmount == 0)
		return;

	if (tokenizer.hasMoreTokens())
		return;

	player->delFactionPoints(tipTo, tipAmount);
}

void ObjectControllerMessage::handleContainerOpen(Player* player, Message* pack) {
	//TODO:Cell permission must take place here
	uint64 target = pack->parseLong();

	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	SceneObject* obj = zone->lookupObject(target);
	if (obj == NULL)
		return;

	if (!obj->isTangible())
		return;

	TangibleObject* tano = (TangibleObject*) obj;

	if (!tano->isContainer())
		return;

	Container* conti = (Container*) obj;

	SceneObject* parent = conti->getParent();
	if (parent == NULL)
		return;

	if (parent == player->getInventory() || parent->isCell() || ((player->getBankContainer() != NULL) && (parent =  player->getBankContainer()))) {
		conti->sendTo(player);
		conti->openTo(player);
	}
}

TangibleObject* ObjectControllerMessage::validateDropAction(Player* player,
		uint64 target) {
	SceneObject* obj;

	//TODO:Cell permission must take place here
	Zone* zone = player->getZone();
	if (zone == NULL)
		return NULL;

	ZoneServer* zoneServer = zone->getZoneServer();
	if (zoneServer == NULL)
		return NULL;

	obj = zone->lookupObject(target);

	if (obj == NULL) {
		obj = player->getInventoryItem(target);
		if (obj == NULL)
			return NULL;

	}

	if (!obj->isTangible())
		return NULL;

	return (TangibleObject*) obj;
}

void ObjectControllerMessage::transferItemToContainer(Player* player,
		TangibleObject* item, uint64 destinationID) {
	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	ZoneServer* zoneServer = zone->getZoneServer();
	if (zoneServer == NULL)
		return;

	ItemManager* im = zoneServer->getItemManager();
	if (im == NULL)
		return;

	im->transferContainerItem(player, item, destinationID);
}

void ObjectControllerMessage::parseNewbieSelectStartingLocation(Player* player,
		Message* pack) {

	pack->shiftOffset(8);
	UnicodeString startingcity;
	pack->parseUnicode(startingcity);
	String city = startingcity.toString();
	//"0=Corellia, 1=Dantooine, 2=Dathomir, 3=Endor, 4=Lok,\n"
	//"5=Naboo, 6=Rori, 7=Talus, 8=Tatooine, 9=Yavin 4, 10=Bad player prison (Space)");
	/*
	 (1,'bestine',8,-1290.000000,0.000000,-3590.000000,'Bestine, Tatooine',3,180),
	 (2,'mos_espa',8,-2902.000000,0.000000,2130.000000,'Mos Espa, Tatooine',3,180),
	 (3,'mos_eisley',8,3528.000000,0.000000,-4804.000000,'Mos Eisley, Tatooine',3,180),
	 (4,'mos_entha',8,1291.000000,0.000000,3138.000000,'Mos Entha, Tatooine',3,180),
	 (5,'coronet',0,-137.000000,0.000000,-4723.000000,'Coronet, Corellia',3,180),
	 (6,'tyrena',0,-5045.000000,0.000000,-2294.000000,'Tyrena, Corellia',3,180),
	 (7,'kor_vella',0,-3138.000000,0.000000,2808.000000,'Kor Vella, Corellia',3,180),
	 (8,'doaba_guerfel',0,3336.000000,0.000000,5525.000000,'Doaba Guerfel, Corellia',3,180),
	 (9,'dearic',7,335.000000,0.000000,-2931.000000,'Dearic, Talus',3,180),
	 (10,'nashal',7,4371.000000,0.000000,5165.000000,'Nashal, Talus',3,180),
	 (11,'narmle',6,-5310.000000,0.000000,-2221.000000,'Narmle, Rori',3,180),
	 (12,'restuss',6,5362.000000,0.000000,5663.000000,'Restuss, Rori',3,180),
	 (13,'theed',6,-4856.000000,0.000000,4162.000000,'Theed, Naboo',3,180),
	 (14,'moenia',5,4800.000000,0.000000,-4700.000000,'Moenia, Naboo',3,180),
	 (15,'keren',5,1441.000000,0.000000,2771.000000,'Keren, Naboo',3,180),
	 (16,'kaadara',5,5209.000000,0.000000,6677.000000,'Kaadara, Naboo',3,180),
	 (17,'tutorial',41,0.000000,0.000000,0.000000,'Tutorial',3,180);
	 */
	if (city == "mos_eisley") {
		player->setPosition(3528.0f, 0, -4804.0f);
		player->switchMap(8);

	} else if (city == "bestine") {
		player->setPosition(-1290.0f, 0, -3590.0f);
		player->switchMap(8);

	} else if (city == "theed") {
		player->setPosition(-4908.0f, 6, 4101.0f);
		player->switchMap(5);

	} else if (city == "moenia") {
		player->setPosition(4800.0f, 0, -4700.0f);
		player->switchMap(5);

	} else if (city == "coronet") {
		player->setPosition(-137.00f, 0, -4723.0f);
		player->switchMap(0);

	} else if (city == "tyrena") {
		player->setPosition(-5045.0f, 0, -2294.0f);
		player->switchMap(0);

	}

}

void ObjectControllerMessage::parseThrowTrap(Player* player, Message* pack, uint32 actionCRC, uint32 actionCntr) {
	uint64 target = pack->parseLong();
	UnicodeString option = UnicodeString("");
	String actionModifier = "";

	pack->parseUnicode(option);
	actionModifier = option.toString();

	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	ZoneServer* zoneServer = zone->getZoneServer();
	if (zoneServer == NULL)
		return;
	uint64 objectId = 0;
	if (!actionModifier.isEmpty())
		try {
			objectId = Long::valueOf(actionModifier);
		} catch (...) {
			System::out << "cant convert long:[" << actionModifier << "]\n";
			//player->throwTrap(target);
		}
	else {
		player->throwTrap(target);
	}


	SceneObject* obj = player->getInventoryItem(objectId);

	if (obj == NULL)
		return;

	if (obj->isTangible() && ((TangibleObject*)obj)->isThrowable()) {
		((ThrowableWeapon*)obj)->activateSkill(player);
	}

}

void ObjectControllerMessage::parseThrowGrenade(Player* player, Message* pack, uint32 actionCRC, uint32 actionCntr) {
	uint64 target = pack->parseLong();
	UnicodeString option = UnicodeString("");
	String actionModifier = "";

	pack->parseUnicode(option);
	actionModifier = option.toString();

	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	ZoneServer* zoneServer = zone->getZoneServer();
	if (zoneServer == NULL)
		return;
	uint64 objectId = 0;
	if (!actionModifier.isEmpty())
		objectId = Long::valueOf(actionModifier);
	else {
		player->throwGrenade(target);
	}


	SceneObject* obj = player->getInventoryItem(objectId);

	if (obj == NULL)
		return;

	if (obj->isTangible() && ((TangibleObject*)obj)->isThrowable()) {
		player->queueAction(player, target, ((ThrowableWeapon*)obj)->getSkillCRC(), actionCntr,
						actionModifier.toCharArray());

		//((ThrowableWeapon*)obj)->activateSkill(player);
	}
}

void ObjectControllerMessage::parseFireHeavyWeapon(Player* player, Message* pack, uint32 actionCRC, uint32 actionCntr) {
	uint64 target = pack->parseLong();
	UnicodeString option = UnicodeString("");
	String actionModifier = "";

	pack->parseUnicode(option);
	actionModifier = option.toString();

	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	ZoneServer* zoneServer = zone->getZoneServer();
	if (zoneServer == NULL)
		return;
	uint64 objectId = 0;
	if (!actionModifier.isEmpty())
		objectId = Long::valueOf(actionModifier);
	else {
		//TODO : find hw
	}


	SceneObject* obj = player->getInventoryItem(objectId);

	if (obj == NULL)
		return;

	if (obj->isTangible() && ((TangibleObject*)obj)->isWeapon() && ((Weapon*)obj)->isHeavyWeapon()) {
		player->queueAction(player, target, ((HeavyRangedWeapon*)obj)->getSkillCRC(), actionCntr,
				actionModifier.toCharArray());

		//((HeavyRangedWeapon*)obj)->activateSkill(player);
	}

}

void ObjectControllerMessage::parseStopWatch(Player* player, Message* pack) {
	uint64 watchID = pack->parseLong();

	player->stopWatch(watchID);
}

void ObjectControllerMessage::parseStopListen(Player* player, Message* pack) {
	uint64 listenID = pack->parseLong();

	player->stopListen(listenID);
}

void ObjectControllerMessage::parseTellPet(Player* player, Message* pack) {
	pack->parseLong(); // skip passed target

	UnicodeString msg = UnicodeString("");
	pack->parseUnicode(msg);

	player->sendMessageToPets(msg);
}
