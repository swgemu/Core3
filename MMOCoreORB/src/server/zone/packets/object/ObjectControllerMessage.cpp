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
	//cout << pack->toString() << "\n";
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

	//cout << "dir vector x:" << dx << " dz:" << dz << " dy:" << dy << " dw:" << dw << "\n";

	x = pack->parseFloat();
	z = pack->parseFloat();
	y = pack->parseFloat();

	if (x > 8192.0f || x < -8192.0f || y > 8192.0f || y < -8192.0f) {
		player->error("position out of bounds...");
		return false;
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

		if ((serverStamp > 50) && ((serverStamp + 250) < (uint64)deltaStamp)) {
			stringstream deltas;
			deltas << "speed hack detected " << "deltaStamp:[" << deltaStamp
					<< "] serversStamp:[" << serverStamp << "]";
			player->info(deltas.str());

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

			float speed = dist * 1000 / (float)deltaStamp;

			if (speed > player->getSpeed() * 1.5) {
				stringstream msg;
				msg << "SpeedHack detected on player: ["
						<< player->getFirstName() << "]\n";
				msg << "Player Speed:" << player->getSpeed()
						<< " caught speed:" << speed << "\n";
				player->info(msg.str());

				player->setLastTestPositionX(x);
				player->setLastTestPositionY(y);

				player->bounceBack();
				return false;
			}
		}

		player->setLastTestPositionX(x);
		player->setLastTestPositionY(y);
	}

	//cout << "Movement counter:" << movementCounter << "\n";

	player->setMovementCounter(movementCounter);

	player->setDirection(dx, dz, dy, dw);
	player->setPosition(x, z, y);


	/*cout << "Player [" << player->getObjectID() << "] - Counter [" << player->getMovementCounter() << "]"
	 << " - Position (" << (int) x << "," << (int) z << "," << (int) y << ")\n";*/

	return true;
}

uint64 ObjectControllerMessage::parseDataTransformWithParent(Player* player,
		Message* pack) {
	//cout << pack->toString() << "\n";
	pack->shiftOffset(8); // skip ObjectID and size

	uint32 movementStamp = pack->parseInt();

	player->setMovementCounter(pack->parseInt() + 1);

	uint64 parent = pack->parseLong();

	Zone* zone = player->getZone();
	if (zone == NULL)
		return 0;

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
		stringstream msg;
		msg << "position out of bounds cell:[" << parent << "]";
		player->error(msg.str());
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

		if ((serverStamp > 50) && ((serverStamp + 250) < (uint64)deltaStamp)) {
			stringstream deltas;
			deltas << "speed hack detected " << "deltaStamp:[" << deltaStamp
					<< "] serversStamp:[" << serverStamp << "]";
			player->info(deltas.str());

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

			float speed = dist * 1000 / (float)deltaStamp;

			if (speed > player->getSpeed() * 1.5) {
				stringstream msg;
				msg << "SpeedHack detected on player: ["
						<< player->getFirstName() << "]\n";
				msg << "Player Speed:" << player->getSpeed()
						<< " caught speed:" << speed << "\n";
				player->info(msg.str());

				player->setLastTestPositionX(x);
				player->setLastTestPositionY(y);

				player->bounceBack();
				return 0;
			}
		}

		player->setLastTestPositionX(x);
		player->setLastTestPositionY(y);
	}

	player->setDirection(dx, dz, dy, dw);
	player->setPosition(x, z, y);
	player->setLastMovementUpdateStamp(movementStamp);

	return parent;

	/*cout << "Player [" << player->getObjectID() << "] with Parent [" << parent << "] - Counter [" << player->getMovementCounter() << "]"
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
	pack->shiftOffset(12); // skip ObjectID and size

	uint32 actioncntr = pack->parseInt();
	uint32 actionCRC = pack->parseInt();
	uint64 target;
	unicode name;

	//TODO: This needs to be revisted, certain skills can be done while dead or incapacitated:
	// Like /activateClone, /consent, /unconsent, /haveconsent
	if ((player->isIncapacitated() || player->isDead()) && (actionCRC
			!= 0xEA69C1BD && actionCRC != 0x3F8F3496 && actionCRC != 0xA2DF082A
			&& actionCRC != 0xB93A3853)) {
		player->clearQueueAction(actioncntr, 0.0f, 1, 19);
		return;
	}

	if (actionCRC == 0) {
		player->clearQueueAction(actioncntr, 0.0f, 0, 0);
		return;
	}

	player->setActionCounter(actioncntr);

	/*stringstream msg;
	 msg << "parsing CommandQueueEnqueue actionCRC = (0x" << hex << actionCRC << dec <<  ")";
	 player->info(msg.str());*/

	ChatManager* chatManager;

	CombatManager* combatManager = serv->getCombatManager();

	// CommandQueueAction* action; - not used anymore?

	switch (actionCRC) {
	case (0x124629F2): // Meditating
		if (player->getMeditate()) {
			player->sendSystemMessage("jedi_spam", "already_in_meditative_state");
		} else {
			player->sendSystemMessage("teraskasi", "med_begin");
			player->queueAction(player, target, actionCRC, actioncntr, "");
		}
		break;
	case (0x8C2221CB): // Powerboost
		if (!player->hasSkill(actionCRC)) {
			player->clearQueueAction(actioncntr, 0, 2, 0);
			return;
		} else {
			player->doPowerboost();

			unicode option = unicode("");
			string actionModifier = "";

			//ToDo: Duration modifier for Master TK is not in this pack...hmmm
			pack->parseUnicode(option);
			actionModifier = option.c_str();

			player->queueAction(player, target, actionCRC, actioncntr, actionModifier.c_str());
		}
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
			player->activateClone();
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
		player->changePosture(CreatureObjectImplementation::CROUCHED_POSTURE);
		break;
	case 0x335676c7: // equip, change weapon.
		target = pack->parseLong();
		player->changeWeapon(target);
		break;
	case 0x82f75977: // transferitemmisc
		/*target = pack->parseLong();
		 player->changeCloth(target);*/
		parseTransferItemMisc(player, pack);
		break;
	case 0x18726ca1: // equip, change armor
		target = pack->parseLong();
		player->changeArmor(target, false);
		break;
	case (0xBD8D02AF):
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		player->changePosture(CreatureObjectImplementation::PRONE_POSTURE);
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
		player->changePosture(CreatureObjectImplementation::UPRIGHT_POSTURE);
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
		parseStopListen(player, pack);
		break;
	case (0x6651AD9A): //stopwatching
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
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
		chatManager = player->getZone()->getChatManager();
		chatManager->handleGroupChat(player, pack);
		break;
	case (0x0315D6D9): // g
		chatManager = player->getZone()->getChatManager();
		chatManager->handleGroupChat(player, pack);
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
	case (0x7AF26B0B):  // Place Structure
		parsePlaceStructure(player, pack);
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
	case (0x89242E02): // Select Draft Schematic
		parseSelectDraftSchematic(player, pack);
		break;
	case (0x83250E2A): // Cancel Crafting Session
		parseCancelCraftingSession(player, pack);
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
	case (0x30BE6EE9 ): // Find Friend
		parseFindFriend(player, pack, serv->getZoneServer()->getPlayerManager());
		break;
	case (0x8E9091D7): // Remove Friend
		parseRemoveFriend(player, pack);
		break;
	case (0x029D0CC5): // Harvest
		parseHarvestOrganics(player, pack);
		break;
	default:

		//Bobius, the changes you made in  584 were breaking the CommandQueue's default player->queueAction !

		target = pack->parseLong();
		string actionModifier = "";

		// fancy if statement
		switch (actionCRC) // modifier for entertainer-type commands /dazzle 2 vs /dazzle 1
		{ // they're dumb and all have the same action crc
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
		{
			unicode option = unicode("");
			pack->parseUnicode(option);
			actionModifier = option.c_str();
		}
			//if(skillOptionID <=0 ) skillOptionID = 1; // default to level 1
			break;

			default: {
				/*
				stringstream opc;
				opc << "Opc: " << hex << actionCRC;
				player->sendSystemMessage(opc.str());*/
			}
		}


		player->queueAction(player, target, actionCRC, actioncntr, actionModifier.c_str());
		return;
	}

	player->clearQueueAction(actioncntr);
}

void ObjectControllerMessage::parseAttachmentDragDrop(Player* player,
		Message* pack) {
	if (player->getTradeSize() != 0) {
		player->sendSystemMessage("You cant move objects while trading..");
		return;
	}

	uint64 attachmentID = pack->parseLong();
	unicode unicodeID;

	pack->parseUnicode(unicodeID);
	StringTokenizer tokenizer(unicodeID.c_str().c_str());

	if (tokenizer.hasMoreTokens()) {
		uint64 targetID = tokenizer.getLongToken();

		player->applyAttachment(attachmentID, targetID);
	}
}

void ObjectControllerMessage::parsePowerupDragDrop(Player* player, Message* pack) {
	if (player->getTradeSize() != 0) {
		player->sendSystemMessage("You cant move objects while trading..");
		return;
	}

	uint64 powerupID = pack->parseLong();
	unicode unicodeID;

	pack->parseUnicode(unicodeID);
	StringTokenizer tokenizer(unicodeID.c_str());

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
		unicode skillBox;
		pack->parseUnicode(skillBox);

		player->surrenderSkillBox(skillBox.c_str().c_str());
	} catch (...) {
		cout << "unreported ObjectControllerMessage::parseSurrenderSkillBox(Player* player, Message* pack) exception\n";
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
				player->setConversatingCreature((CreatureObject*)object);
				object->sendConversationStartTo(player);
			}

			if (object != player)
				object->unlock();
		} catch (...) {
			player->error("unreported ObjectControllerMessage::parseNpcStartConversation(Player* player, Message* pack) exception");
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

		unicode opt;
		pack->parseUnicode(opt);

		int option = atoi(opt.c_str().c_str());
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

			StopNpcConversation* conv = new StopNpcConversation(player, npc->getObjectID());
			player->setConversatingCreature(NULL);

			player->sendMessage(conv);

			if (npc != player)
			npc->unlock();
		} catch (...) {
			cout << "unreported ObjectControllerMessage::parseNpcStopConversation(Player* player, Message* pack) exception\n";
			if (npc != player)
			npc->unlock();
		}
	}
}

void ObjectControllerMessage::parseStatMigrationDataRequest(Player* player, Message* pack) {
	uint64 objectid = pack->parseLong();

	StatMigrationTargetsMessage* smtm = new StatMigrationTargetsMessage(player);
	player->sendMessage(smtm);
}

void ObjectControllerMessage::parseSetStatMigrationDataRequest(Player* player, Message* pack) {
	uint64 objectid = pack->parseLong();

	unicode stats = unicode("");
	pack->parseUnicode(stats);

	//player->info(stats.c_str());

	StringTokenizer tokenizer(stats.c_str());
	tokenizer.setDelimeter(" ");

	uint32 targetHealth, targetStrength, targetConstitution;
	uint32 targetAction, targetQuickness, targetStamina;
	uint32 targetMind, targetFocus, targetWillpower;

	/*****************************************************
	 * TODO: Stat migration bug tracking.  Remove later. *
	 ****************************************************/
	ChatManager * chatManager = player->getZone()->getChatManager();
	const string  sender = "BUG TRACKER";
	unicode header = "STAT MIGRATION BUG REPORT";
	stringstream ss;
	ss << "The stat migration protection system has been triggered for user " << player->getCharacterName().c_str() << "." << endl;
	ss << "The following is the relevant debug information:" << endl << endl;
	ss << "Player Name: " << player->getCharacterName().c_str() << endl;
	ss << "Species: " << player->getSpeciesName() << endl;
	ss << "Sex: " << player->getGender() << endl;
	ss << "Target Stats: " << stats.c_str() << endl;
	ss << "Min/Max/Current Health: " << player->getMinHealth() << " | " << player->getMaxHealth() << " | " << player->getBaseHealth() << endl;
	ss << "Min/Max/Current Strength: " << player->getMinStrength() << " | " << player->getMaxStrength() << " | " << player->getBaseStrength() << endl;
	ss << "Min/Max/Current Constitution: " << player->getMinConstitution() << " | " << player->getMaxConstitution() << " | " << player->getBaseConstitution() << endl;
	ss << "Min/Max/Current Action: " << player->getMinAction() << " | " << player->getMaxAction() << " | " << player->getBaseAction() << endl;
	ss << "Min/Max/Current Quickness: " << player->getMinQuickness() << " | " << player->getMaxQuickness() << " | " << player->getBaseQuickness() << endl;
	ss << "Min/Max/Current Stamina: " << player->getMinStamina() << " | " << player->getMaxStamina() << " | " << player->getBaseStamina() << endl;
	ss << "Min/Max/Current Mind: " << player->getMinMind() << " | " << player->getMaxMind() << " | " << player->getBaseMind() << endl;
	ss << "Min/Max/Current Focus: " << player->getMinFocus() << " | " << player->getMaxFocus() << " | " << player->getBaseFocus() << endl;
	ss << "Min/Max/Current Willpower: " << player->getMinWillpower() << " | " << player->getMaxWillpower() << " | " << player->getBaseWillpower() << endl;
	ss << "Total Attrib Points: " << player->getTotalAttribPoints();
	unicode body = unicode(ss.str());
	const string reciever = "Bobius";
	/*******************************************************/

	for(int i = 0; tokenizer.hasMoreTokens(); i++) {
		uint32 value = tokenizer.getIntToken();
		switch(i) {
			case 0:
				if (value < player->getMinHealth() || value > player->getMaxHealth()) {
					chatManager->sendMail(sender, header, body, reciever); //TODO: remove bug tracking code later
					return;
				} else
					targetHealth = value;
				break;
			case 1:
				if (value < player->getMinStrength() || value > player->getMaxStrength()) {
					chatManager->sendMail(sender, header, body, reciever); //TODO: remove bug tracking code later
					return;
				} else
					targetStrength = value;
				break;
			case 2:
				if (value < player->getMinConstitution() || value > player->getMaxConstitution()) {
					chatManager->sendMail(sender, header, body, reciever); //TODO: remove bug tracking code later
					return;
				} else
					targetConstitution = value;
				break;
			case 3:
				if (value < player->getMinAction() || value > player->getMaxAction()) {
					chatManager->sendMail(sender, header, body, reciever); //TODO: remove bug tracking code later
					return;
				} else
					targetAction = value;
				break;
			case 4:
				if (value < player->getMinQuickness() || value > player->getMaxQuickness()) {
					chatManager->sendMail(sender, header, body, reciever); //TODO: remove bug tracking code later
					return;
				} else
					targetQuickness = value;
				break;
			case 5:
				if (value < player->getMinStamina() || value > player->getMaxStamina()) {
					chatManager->sendMail(sender, header, body, reciever); //TODO: remove bug tracking code later
					return;
				} else
					targetStamina = value;
				break;
			case 6:
				if (value < player->getMinMind() || value > player->getMaxMind()) {
					chatManager->sendMail(sender, header, body, reciever); //TODO: remove bug tracking code later
					return;
				} else
					targetMind = value;
				break;
			case 7:
				if (value < player->getMinFocus() || value > player->getMaxFocus()) {
					chatManager->sendMail(sender, header, body, reciever); //TODO: remove bug tracking code later
					return;
				} else
					targetFocus = value;
				break;
			case 8:
				if (value < player->getMinWillpower() || value > player->getMaxWillpower()) {
					chatManager->sendMail(sender, header, body, reciever); //TODO: remove bug tracking code later
					return;
				} else
					targetWillpower = value;
				break;
			default: // points available
				break;
		}
	}

	int targetPoints = targetHealth + targetStrength + targetConstitution
			+ targetAction + targetQuickness + targetStamina + targetMind
			+ targetFocus + targetWillpower;

	if (targetPoints == player->getTotalAttribPoints()) {
		player->setTargetHealth(targetHealth);
		player->setTargetStrength(targetStrength);
		player->setTargetConstitution(targetConstitution);
		player->setTargetAction(targetAction);
		player->setTargetQuickness(targetQuickness);
		player->setTargetStamina(targetStamina);
		player->setTargetMind(targetMind);
		player->setTargetFocus(targetFocus);
		player->setTargetWillpower(targetWillpower);
	} else {
		chatManager->sendMail(sender, header, body, reciever); //TODO: remove bug tracking code later
		return;
	}

	//chatManager->sendMail(sender, header, body, reciever); //TODO: remove bug tracking code later


	//if (tokenizer.hasMoreTokens()) {
	//	uint64 targetID = tokenizer.getLongToken();
	//
	//	player->applyAttachment(attachmentID, targetID);
	//}


	//StatMigrationTargetsMessage* smtm = new StatMigrationTargetsMessage(player);
	//player->sendMessage(smtm);
}


void ObjectControllerMessage::parseCharacterSheetInfoRequest(Player* player, Message* pack) {
	uint64 objectid = pack->parseLong();

	CharacterSheetResponseMessage* csrm = new CharacterSheetResponseMessage(objectid);
	player->sendMessage(csrm);
}

void ObjectControllerMessage::parseBiographyRequest(Player* player, Message *pack) {
	uint64 objectid = pack->parseLong();

	SceneObject* object = player->getZone()->lookupObject(objectid);

	if (object == NULL)
		return;

	try {
		if (object->isPlayer()) {
			Player* play = (Player*) object;

			if (play != player)
			play->wlock(player);

			Biography* bio = new Biography(player, play);
			player->sendMessage(bio);

			if (play != player)
			play->unlock();

		}
	} catch (...) {
		cout << "Unreported exception in ObjectControllerMessage::parseBiographyRequest(Player* player, Message *pack)";
	}
}

void ObjectControllerMessage::parseSetBiography(Player* player, Message *pack) {
	pack->shiftOffset(8);

	unicode bio;
	pack->parseUnicode(bio);

	player->setBiography(bio.c_str());
}

void ObjectControllerMessage::parseBadgesRequest(Player* player, Message *pack) {
	/*BadgesResponseMessage* brm = new BadgesResponseMessage(player);
	 player->sendMessage(brm);*/
}

void ObjectControllerMessage::parsePurchaseTicket(Player* player, Message *pack) {
	pack->shiftOffset(8); // skip ObjectID and size

	unicode ticketmessage;
	pack->parseUnicode(ticketmessage);

	StringTokenizer tokenizer(ticketmessage.c_str());

	string departurePlanet;
	if (tokenizer.hasMoreTokens())
		tokenizer.getStringToken(departurePlanet);
	else
		return;

	string departurePoint;
	if (tokenizer.hasMoreTokens())
		tokenizer.getStringToken(departurePoint);
	else
		return;

	string arrivalPlanet;
	if (tokenizer.hasMoreTokens())
		tokenizer.getStringToken(arrivalPlanet);
	else
		return;

	string arrivalPoint;
	if (tokenizer.hasMoreTokens())
		tokenizer.getStringToken(arrivalPoint);
	else
		return;

	bool roundTrip;
	if (tokenizer.hasMoreTokens())
		roundTrip = tokenizer.getIntToken();
	else
		return;

	PlanetManager * planetManager = player->getZone()->getPlanetManager();

	uint32 fare = planetManager->getTravelFare(departurePlanet, arrivalPlanet);

	if (fare == 0) {
		//Travel not allowed between these planets
		return;
	}

	//Replace Underscores with spaces
	int pos = 0;
	while ((pos = departurePoint.find("_", pos)) != string::npos) {
		departurePoint.replace(pos, 1, " ");
		pos++;
	}

	ShuttleCreature * shuttle = planetManager->getShuttle(departurePoint);

	if (shuttle == NULL) {
		SuiMessageBox* sui = new SuiMessageBox(player, 0xDAAD);
		sui->setPromptTitle("@base_player:swg");
		sui->setPromptText("@travel:no_location_found");
		player->addSuiBox(sui);
		player->sendMessage(sui->generateMessage());
		return;
	}

	uint32 tax = shuttle->getTax();

	uint32 totalFee = fare + tax;

	if(roundTrip)
		totalFee *= 2;

	if (!player->verifyCashCredits(totalFee)) {

		SuiMessageBox* sui = new SuiMessageBox(player, 0xDAAD);
		sui->setPromptTitle("@base_player:swg");
		sui->setPromptText("@travel:short_funds");
		player->addSuiBox(sui);
		player->sendMessage(sui->generateMessage());
		return;

	} else {
		player->subtractCashCredits(totalFee);
	}

	// create ticket item
	Ticket* ticket = new Ticket(player, 0xDAA0DE83, unicode("Travel Ticket"), "travel_ticket",
			departurePlanet, departurePoint, arrivalPlanet, arrivalPoint);

	player->addInventoryItem(ticket);
	ticket->sendTo(player, true);

	if (roundTrip) {
		Ticket* returnTicket = new Ticket(player, 0xDAA0DE83, unicode("Travel Ticket"), "travel_ticket",
				arrivalPlanet, arrivalPoint, departurePlanet, departurePoint);

		player->addInventoryItem(returnTicket);
		returnTicket->sendTo(player, true);
	}

	SuiMessageBox* sui = new SuiMessageBox(player, 0xDAAD);
	sui->setPromptTitle("@base_player:swg");
	sui->setPromptText("@travel:ticket_purchase_complete");

	player->addSuiBox(sui);
	player->sendMessage(sui->generateMessage());
}

void ObjectControllerMessage::parseGetAttributes(Player* player, Message* pack) {
	pack->shiftOffset(8);

	unicode objectid;
	pack->parseUnicode(objectid);

	StringTokenizer ids(objectid.c_str());

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

void ObjectControllerMessage::parseImageDesignChange(Player* player, Message* pack, ZoneProcessServerImplementation* serv) {
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

		ImageDesignChangeMessage* msg_designer = new ImageDesignChangeMessage(designer, designer, target, tent, 0);
		ImageDesignChangeMessage* msg_target = new ImageDesignChangeMessage(target, designer, target, tent, 0);


		// Parse
		string hairObject;
		pack->parseAscii(hairObject);

		// Pack
		msg_designer->insertAscii(hairObject);
		msg_target->insertAscii(hairObject);

		// Parse
		string unknownstring_1;
		pack->parseAscii(unknownstring_1);

		// Pack
		msg_designer->insertAscii(unknownstring_1);
		msg_target->insertAscii(unknownstring_1);

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
		SceneObject* designer_object = player->getZone()->lookupObject(designer);

		bool commitChanges = false;
		if (designer_accepted == 1 &&
			target_object == designer_object &&
			target_object != NULL )
			commitChanges = true;

		if (target_accepted == 1 &&
			designer_accepted == 1 &&
			target_object != designer_object &&
			target_object != NULL )
			commitChanges = true;

		// This is a helper class for a bunch of the embedded logic
		ImageDesignCustomization* customization = NULL;

		try {

			if (target_object != NULL && player != target_object)
				target_object->wlock(player);

			if (commitChanges)
				customization = new ImageDesignCustomization(serv, ((CreatureObject *)target_object));

			// Parse
			if(size_float_attrs > 0)
			{
				for(int i = 0; i < size_float_attrs; i++)
				{
					// do something later
					string attr;
					pack->parseAscii(attr);
					float val = pack->parseFloat();

					// Pack
					msg_designer->insertAscii(attr);
					msg_designer->insertFloat(val);
					msg_target->insertAscii(attr);
					msg_target->insertFloat(val);

					if(commitChanges)
						customization->updateCustomization(attr, val);
				}
			}

			// Parse
			uint32 size_int_attrs = pack->parseInt();

			// Pack
			msg_designer->insertInt(size_int_attrs);
			msg_target->insertInt(size_int_attrs);

			// Parse
			if(size_int_attrs > 0)
			{
				for(int i = 0; i < size_int_attrs; i++)
				{
					// do something later
					string attr;
					pack->parseAscii(attr);
					uint32 val = pack->parseInt();

					// Pack
					msg_designer->insertAscii(attr.c_str());
					msg_designer->insertInt(val);
					msg_target->insertAscii(attr.c_str());
					msg_target->insertInt(val);

					if(commitChanges)
						customization->updateCustomization(attr, val);
				}
			}

			if (target_object != NULL && player != target_object)
				target_object->unlock();
		} catch (...) {
			if (target_object != NULL && player != target_object)
				target_object->unlock();
		}

		// Parse
		string emote;
		pack->parseAscii(emote);

		// Pack
		msg_designer->insertAscii(emote);
		msg_target->insertAscii(emote);


		// If from designer send to target
		if(designer == target)
		{

			// do something else?
		} else if(player->getObjectID() == designer) {
			if(target_object != NULL)
				((Player *)target_object)->sendMessage(msg_target);

		// If from target send to designer
		} else if(player->getObjectID() == target) {

			if(designer_object != NULL) {
				//((Player *)designer_object)->sendSystemMessage("update from target!");
				//player->info(msg.str());
				//player->info(msg_designer->toString());
				((Player *)designer_object)->sendMessage(msg_designer);
			}
		}

		if(commitChanges) {

			//Update Hair
			if (!hairObject.empty()) {
				int idx = hairObject.find("hair_", 0);
				if (idx != -1) {
					hairObject.replace(idx, 5, "shared_hair_");
					player->setHairObject(hairObject);
					player->updateHair();
					/*stringstream msg;
					msg << "imagedesignerupdate, hairObject:" << hex << hairObject;
					((Player *)target_object)->sendSystemMessage(msg.str());*/

				}
			}

			PlayerManager* playerManager = serv->getZoneServer()->getPlayerManager();
			// Stat Migration
			if(stat_migration > 0)
			{
				if(player->getBaseHealth() != player->getTargetHealth())
					player->setBaseHealthBar(player->getTargetHealth());

				if(player->getBaseStrength() != player->getTargetStrength())
					player->setBaseStrengthBar(player->getTargetStrength());

				if(player->getBaseConstitution() != player->getTargetConstitution())
					player->setBaseConstitutionBar(player->getTargetConstitution());

				if(player->getBaseAction() != player->getTargetAction())
					player->setBaseActionBar(player->getTargetAction());

				if(player->getBaseQuickness() != player->getTargetQuickness())
					player->setBaseQuicknessBar(player->getTargetQuickness());

				if(player->getBaseStamina() != player->getTargetStamina())
					player->setBaseStaminaBar(player->getTargetStamina());

				if(player->getBaseMind() != player->getTargetMind())
					player->setBaseMindBar(player->getTargetMind());

				if(player->getBaseFocus() != player->getTargetFocus())
					player->setBaseFocusBar(player->getTargetFocus());

				if(player->getBaseWillpower() != player->getTargetWillpower())
					player->setBaseWillpowerBar(player->getTargetWillpower());

				if(playerManager != NULL)
					playerManager->updatePlayerBaseHAMToDatabase(player);
			}

			if(customization != NULL)
				delete customization;

			if(target_object != NULL)
				((CreatureObject *)target_object)->updateCharacterAppearance();


			if(playerManager != NULL)
				playerManager->updatePlayerAppearanceToDatabase(player);
		}

	} catch (...) {
		cout << "unreported ObjectControllerMessage::parseImageDesignChange(Player* player, Message* pack) exception\n";
	}

}

void ObjectControllerMessage::parseImageDesignCancel(Player* player, Message* pack) {
	// TODO combine these functions together
	try {
		// Read the Packet
		uint64 object = pack->parseLong();
		pack->shiftOffset(4); // size ?

		uint64 designer = pack->parseLong();
		uint64 target = pack->parseLong();
		uint64 tent = pack->parseLong();

		uint8 type = pack->parseByte();

		ImageDesignRejectMessage* msg_designer = new ImageDesignRejectMessage(designer, designer, target, tent, 0);
		ImageDesignRejectMessage* msg_target = new ImageDesignRejectMessage(target, designer, target, tent, 0);


		// Parse
		string hairObject;
		pack->parseAscii(hairObject);

		// Pack
		msg_designer->insertAscii(hairObject);
		msg_target->insertAscii(hairObject);

		// Parse
		string unknownstring_1;
		pack->parseAscii(unknownstring_1);

		// Pack
		msg_designer->insertAscii(unknownstring_1);
		msg_target->insertAscii(unknownstring_1);

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
		if(size_float_attrs > 0)
		{
			for(int i = 0; i < size_float_attrs; i++)
			{
				// do something later
				string attr;
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
		if(size_int_attrs > 0)
		{
			for(int i = 0; i < size_int_attrs; i++)
			{
				// do something later
				string attr;
				pack->parseAscii(attr);
				uint32 val = pack->parseInt();

				// Pack
				msg_designer->insertAscii(attr.c_str());
				msg_designer->insertInt(val);
				msg_target->insertAscii(attr.c_str());
				msg_target->insertInt(val);
			}
		}

		// Parse
		string emote;
		pack->parseAscii(emote);

		// Pack
		msg_designer->insertAscii(emote);
		msg_target->insertAscii(emote);

		SceneObject* target_object = player->getZone()->lookupObject(target);
		SceneObject* designer_object = player->getZone()->lookupObject(designer);

		// If from designer send to target
		if(designer == target)
		{

			// do something else?
		} else if(player->getObjectID() == designer) {
			if(target_object != NULL)
				((Player *)target_object)->sendMessage(msg_target);

		// If from target send to designer
		} else if(player->getObjectID() == target) {

			if(designer_object != NULL) {
				//((Player *)designer_object)->sendSystemMessage("update from target!");
				//player->info(msg.str());
				//player->info(msg_designer->toString());
				((Player *)designer_object)->sendMessage(msg_designer);
			}
		}


	} catch (...) {
		cout << "unreported ObjectControllerMessage::parseImageDesignReject(Player* player, Message* pack) exception\n";
	}
}

void ObjectControllerMessage::parseSetCurrentSkillTitle(Player* player,
		Message* pack) {
	pack->shiftOffset(8); //shift past the blank id.
	unicode title;
	pack->parseUnicode(title);
	string newTitle = title.c_str();

	if (!player->hasSkillBox(newTitle))
		return;

	PlayerObject* object = player->getPlayerObject();
	object->setCurrentTitle(newTitle, true);
}

void ObjectControllerMessage::parseShowPvpRating(Player* player, Message* pack) {
	stringstream msg;
	msg << "Your player vs. player combat rating is " << player->getPvpRating();

	player->sendSystemMessage(msg.str());
}

void ObjectControllerMessage::parseWatch(Player* player, Message* pack) {
	uint64 watchID = pack->parseLong();

	player->startWatch(watchID);
}

void ObjectControllerMessage::parseListen(Player* player, Message* pack) {
	uint64 listenID = pack->parseLong();

	player->startListen(listenID);
}

void ObjectControllerMessage::parseStopWatch(Player* player, Message* pack) {
	Zone* zone = player->getZone();

	uint64 watchID = pack->parseLong();
	player->stopWatch(watchID);
}

void ObjectControllerMessage::parseStopListen(Player* player, Message* pack) {
	uint64 listenID = pack->parseLong();

	player->stopListen(listenID);
}

void ObjectControllerMessage::parseImageDesign(Player* player, Message* pack) {


	string skillBox = "social_entertainer_novice";

	if (!player->getSkillBoxesSize() || !player->hasSkillBox(skillBox)) {
		// TODO: sendSystemMessage("cmd_err", "ability_prose", creature);
		player->sendSystemMessage("You do not have sufficient abilities to image design.");
		return;
	}

	uint64 target = pack->parseLong(); // skip passed target get this later?

	SceneObject* object = player->getZone()->lookupObject(target);

	if (object == NULL)
		return;

	unsigned long tent = 0; // objectid of the salon building

	if (player->isInBuilding() && player->getBuildingType()
			== BuildingObjectImplementation::SALON) {
		CellObject* cell = (CellObject*)player->getParent();
		BuildingObject* building = (BuildingObject*)cell->getParent();

		tent = building->getObjectID();
	}

	try {
		if (object != player)
		object->wlock(player);

		if (object->isPlayer()) {
			Player* targetPlayer = (Player*) object;

			// If the target player isn't yourself, then that player must be in a group
			if (targetPlayer->getObjectID() != player->getObjectID()
					&& (!player->isInAGroup() || (player->isInAGroup() && player->getGroupID() != targetPlayer->getGroupID()))) {

				player->sendSystemMessage("Target player must be in your group to Image Design.");

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
			ImageDesignStartMessage* msgPlayer = new ImageDesignStartMessage(player, player, targetPlayer, tent);
			player->sendMessage(msgPlayer);

			// Initiate Target (
			if (targetPlayer->getObjectID() != player->getObjectID()) {
				ImageDesignStartMessage* msgTarget = new ImageDesignStartMessage(targetPlayer, player, targetPlayer, tent);
				targetPlayer->sendMessage(msgTarget);
			}
		} else {
			player->sendSystemMessage("Invalid Image Design target.");
		}

		if (object != player)
		object->unlock();
	} catch (...) {
		cout << "Unreported exception in ObjectControllerMessage::parseImageDesign(Player* player, Message *pack)";
		if (object != player)
		object->unlock();
	}
}

void ObjectControllerMessage::parseFlourish(Player* player, Message* pack,
		uint32 actionCntr) {
	uint64 target = pack->parseLong(); // skip passed target

	unicode option = unicode("");
	pack->parseUnicode(option);
	string actionModifier = option.c_str();

	player->queueFlourish(actionModifier, target, actionCntr);
	//player->queueFlourish()
	//player->doFlourish(actionModifier);
}

void ObjectControllerMessage::parseChangeMusic(Player* player, Message* pack) {
	pack->parseLong(); // skip passed target

	unicode option = unicode("");
	pack->parseUnicode(option);
	string actionModifier = option.c_str();

	player->startPlayingMusic(actionModifier, true);
}

void ObjectControllerMessage::parseChangeDance(Player* player, Message* pack) {
	pack->parseLong(); // skip passed target

	unicode option = unicode("");
	pack->parseUnicode(option);
	string actionModifier = option.c_str();

	player->startDancing(actionModifier, true);
}

void ObjectControllerMessage::parseServerSit(Player* player, Message* pack) {
	pack->shiftOffset(8); //Shift past the blank long.

	unicode waypoint;
	pack->parseUnicode(waypoint);

	if (waypoint.size() == 0) {
		player->changePosture(CreatureObjectImplementation::SITTING_POSTURE);
	} else {
		Zone* zone = player->getZone();

		if (zone == NULL)
			return;

		ZoneServer* server = zone->getZoneServer();

		try {
			StringTokenizer tokenizer(waypoint.c_str());
			tokenizer.setDelimeter(",");
			float x = tokenizer.getFloatToken();
			float y = tokenizer.getFloatToken();
			float z = tokenizer.getFloatToken();

			uint64 coID;
			if (tokenizer.hasMoreTokens())
				coID = tokenizer.getLongToken();

			if (x < -8192 || x> 8192)
			x = 0;
			if (y < -8192 || y> 8192)
			y = 0;
			if (z < -8192 || z> 8192)
			z = 0;

			player->setPosture(CreatureObjectImplementation::SITTING_POSTURE, false, true, x, y, z);
		} catch (...) {
			cout << "Unreported exception in ObjectControllerMessage::parseServerSit\n";
		}
	}
}

void ObjectControllerMessage::parseWaypointCreate(Player* player, Message* pack) {
	//outdated and throwing exceptions. We use now "parseWaypointCommand

	/*
	pack->shiftOffset(8); //Shift past the blank long.

	unicode waypoint;
	pack->parseUnicode(waypoint);

	StringTokenizer tokenizer(waypoint.c_str());
	try {
		string planet;
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
		cout << "Unreported exception in ObjectControllerMessage::parseWaypointCreate\n";
	}
	*/
}


void ObjectControllerMessage::parseWaypointCommand(Player* player, Message* pack) {
	int counter = 0;
	string dummy;

	pack->shiftOffset(8);

	string usageError = "Usage: /waypoint X Y <name> or /waypoint <name>";

	unicode rawWaypoint;
	pack->parseUnicode(rawWaypoint);
	string waypointData = rawWaypoint.c_str();

	string waypointName = "New Waypoint";
	string planet = Planet::getPlanetName(player->getZoneID());
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

	if (!tokenizer.hasMoreTokens())
		return;

	string arg1;
	tokenizer.getStringToken(arg1);

	if (tokenizer.hasMoreTokens()) {
		if (isalpha(arg1[0]) == 0) {
			//A waypoint in the form of /waypoint X Y <name>
			x = atof(arg1.c_str());

			if (tokenizer.hasMoreTokens()) {
				string temp;
				tokenizer.getStringToken(temp);
				if (isalpha(temp[0]) == 0) {
					y = atof(temp.c_str());
				} else {
					player->sendSystemMessage(usageError);
					return;
				}
			}

			stringstream newWaypointName;

			while (tokenizer.hasMoreTokens()) {
				newWaypointName << " ";
				tokenizer.getStringToken(newWaypointName);
			}

			string tempName = newWaypointName.str();

			if (!tempName.empty()) {
				tempName.erase(0,1);
				waypointName = tempName;
			}

		} else {
			//A waypoint in the form of /waypoint planet X Z Y - Planetary Map
			planet = arg1;

			if (Planet::getPlanetID(planet) < 0) { //Not a valid planet name - malformed command
				player->sendSystemMessage(usageError);
				return;
			}

			if (tokenizer.hasMoreTokens()) {
				string temp;
				tokenizer.getStringToken(temp);
				if (isalpha(temp[0]) == 0) {
					x = atof(temp.c_str());
				} else {
					player->sendSystemMessage(usageError);
					return;
				}
			}

			if (tokenizer.hasMoreTokens()) {
				string temp;
				tokenizer.getStringToken(temp);
				if (isalpha(temp[0]) == 0) {
					z = atof(temp.c_str());
				} else {
					player->sendSystemMessage(usageError);
					return;
				}
			}

			if (tokenizer.hasMoreTokens()) {
				string temp;
				tokenizer.getStringToken(temp);
				if (isalpha(temp[0]) == 0) {
					y = atof(temp.c_str());
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

	x = (x < -8192) ? -8192 : x;
	x = (x > 8192) ? 8192 : x;

	y = (y < -8192) ? -8192 : y;
	y = (y > 8192) ? 8192 : y;


	//Create our waypoint
	WaypointObject* waypoint = new WaypointObject(player, player->getNewItemID());
	waypoint->setPlanetName(planet);
	waypoint->setPosition(x, z, y);
	waypoint->setName(waypointName);

	player->addWaypoint(waypoint);


}

void ObjectControllerMessage::parseSetWaypointName(Player* player, Message* pack) {
	uint64 wpId = pack->parseLong(); //get the waypoint id

	WaypointObject* wp = player->getWaypoint(wpId);

	if (wp == NULL)
		return;

	unicode newWpName_u; //new waypoint name
	pack->parseUnicode(newWpName_u);

	string newWpName = newWpName_u.c_str().c_str();
	wp->setName(newWpName);
	wp->switchStatus();

	player->updateWaypoint(wp);
}

void ObjectControllerMessage::parseServerDestroyObject(Player* player,
		Message* pack) {
	//NOTE: this is probably used for more than deleteing waypoints.
	uint64 objid = pack->parseLong(); //get the id

	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();

	if (player->getTradeSize() != 0) {
		player->sendSystemMessage("You cant destroy objects while trading..");
		return;
	}

	unicode unkPramString;
	pack->parseUnicode(unkPramString); //?

	WaypointObject* waypoint = player->getWaypoint(objid);
	IntangibleObject* datapadData = (IntangibleObject*) player->getDatapadItem(objid);

	SceneObject* invObj = player->getInventoryItem(objid);

	if (invObj != NULL && invObj->isTangible()) {
		TangibleObject* item = (TangibleObject*) invObj;

		if (item->isEquipped()) {
			//player->changeCloth(objid);
			player->sendSystemMessage("You must unequip the item before destroying it.");
			return;
		}

		//cout << "Server destroy happening\n";

		if (player->getCurrentCraftingTool() == item) {
			CraftingTool* tool = (CraftingTool*) item;

			if (!tool->isReady()) {
				player->sendSystemMessage("You cant delete a working crafting tool!");
				return;
			} else
				player->clearCurrentCraftingTool();
		}

		itemManager->deletePlayerItem(player, item, true);

		player->removeInventoryItem(objid);

		if (player->getWeapon() == item)
			player->setWeapon(NULL);

		if (player->getSurveyTool() == item)
			player->setSurveyTool(NULL);

		BaseMessage* msg = new SceneObjectDestroyMessage(item);
		player->getClient()->sendMessage(msg);

		item->finalize();
	} else if (waypoint != NULL) {
		if (player->removeWaypoint(waypoint))
			waypoint->finalize();
	} else if (datapadData != NULL){
		player->removeDatapadItem(objid);

		BaseMessage* msg = new SceneObjectDestroyMessage(datapadData);
		player->getClient()->sendMessage(msg);
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

void ObjectControllerMessage::parseMissionListRequest(Player* player, Message* pack) {
	//skip objId + old size + unk byte + refresh byte
	pack->shiftOffset(14);
	
	//Grab the mission terminal id
	uint64 termId = pack->parseLong();
	
	//TODO: Take the error messages out after testing
	PlanetManager* plnMgr = player->getZone()->getPlanetManager();
	if (plnMgr == NULL) {
		cout << "Error: Planet Manager NULL in parseMissionListRequest() \n";
		return;
	}

	MissionTerminal* mt = plnMgr->getMissionTerminal(termId);
	if (mt == NULL) {
		//Turn this message off after testing: (this msg will be frequent until we have a complete static object table)
		cout << "Error: Mission Terminal object NULL in parseMissionListRequest(). Mission Terminal does not exist! \n";
		return;
	}
	
	MissionManager* misoMgr = player->getZone()->getZoneServer()->getMissionManager();
	if (misoMgr == NULL) {
		cout << "Error: Mission Manager NULL in parseMissionListRequest() \n";
		return;
	}

	misoMgr->sendTerminalData(player, mt->getTerminalMask(), true);
}

void ObjectControllerMessage::parseMissionAccept(Player* player, Message* pack){
	//skip objId + old size
	pack->shiftOffset(12);
	
	//Grab the mission object id
	uint64 misoId = pack->parseLong();
	
	MissionManager* misoMgr = player->getZone()->getZoneServer()->getMissionManager();
	if (misoMgr == NULL) {
		cout << "Error: Mission Manager NULL in parseMissionAccept() \n";
		return;
	}
	
	misoMgr->doMissionAccept(player, misoId, true);
}

void ObjectControllerMessage::parseMissionAbort(Player* player, Message* pack) {
	//skip objId + old size
	pack->shiftOffset(12);
	
	//Grab the mission object id
	uint64 misoId = pack->parseLong();
	
	MissionManager* misoMgr = player->getZone()->getZoneServer()->getMissionManager();
	if (misoMgr == NULL) {
		cout << "Error: Mission Manager NULL in parseMissionAbort() \n";
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

	Player* invitePlayer = (Player*)object;
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
			player->sendSystemMessage("group", "uninvite_target", play->getObjectID());
		}

		play->unlock();
	} catch (...) {
		play->unlock();
		cout << "Exception in parseGroupUninvite(Player* player, Message* pack)\n";
	}
}

void ObjectControllerMessage::parseGroupLeave(Player* player, Message* pack,
		GroupManager* groupManager) {
	GroupObject* group = player->getGroupObject();

	if (group == NULL)
		return;

	groupManager->leaveGroup(group, player);
}

void ObjectControllerMessage::parseGroupDisband(Player* player, Message* pack,
		GroupManager* groupManager) {
	GroupObject* group = player->getGroupObject();
	if (group == NULL)
		return;

	groupManager->disbandGroup(group, player);
}

void ObjectControllerMessage::parseGroupKick(Player* player, Message* pack,
		GroupManager* groupManager) {
	uint64 target = pack->parseLong();
	SceneObject* object = player->getZone()->lookupObject(target);

	if (object == NULL || !object->isPlayer() || object == player)
		return;

	Player* targetObject = (Player*) object;

	GroupObject* group = player->getGroupObject();
	if (group == NULL)
		return;

	groupManager->kickFromGroup(group, player, targetObject);
}

void ObjectControllerMessage::parseGroupMakeLeader(Player* player,
		Message* pack, GroupManager* groupManager) {
	uint64 target = pack->parseLong();
	SceneObject* object = player->getZone()->lookupObject(target);

	if (object == NULL || !object->isPlayer() || object == player)
		return;
	Player* targetObject = (Player*)object;

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

	Player* inviter = (Player*)object;

	player->updateGroupInviterId(0);
	inviter->sendSystemMessage("group", "decline_leader", player->getObjectID());
	player->sendSystemMessage("group", "decline_self");
}

void ObjectControllerMessage::parseMount(Player* player, Message* pack) {
	uint64 target = pack->parseLong();
	SceneObject* object = player->getZone()->lookupObject(target);

	if (object == NULL || object->isPlayer() || object == player)
		return;

	MountCreature* mount = player->getMount();

	if (object != (SceneObject*)mount)
		return;
	else {
		if (player->isMounted())
			player->dismount();
		else
			player->mountCreature(mount);
	}
}

void ObjectControllerMessage::parseDismount(Player* player, Message* pack) {
	MountCreature* mount = player->getMount();

	if (mount == NULL)
		return;
	else {
		player->dismount();
	}
}

void ObjectControllerMessage::parseTip(Player* player, Message* pack,
		PlayerManager* playerManager) {
	uint64 tipToId = pack->parseLong();

	unicode tipParams;
	pack->parseUnicode(tipParams);

	StringTokenizer tokenizer(tipParams.c_str());
	tokenizer.setDelimeter(" ");

	if (!tokenizer.hasMoreTokens())
		return;

	uint32 tipAmount;

	if (tipToId == 0) {
		//either player not in range. Or not online. So lets do a bank tip.

		string tipToName;
		tokenizer.getStringToken(tipToName);

		//Ok so now we have the name. Lets verify they exist first before doing anything else.
		if (!playerManager->validateName(tipToName)) {
			//Ok so the player exists. So lets parse the rest of the packet now.

			if (!tokenizer.hasMoreTokens())
				return;

			string tips;
			tokenizer.getStringToken(tips);

			tipAmount = atol(tips.c_str());

			if (tipAmount == 0) {
				//Invalid Tip Amount/Parameter.
				player->sendSystemMessage("Invalid Tip parameter. (Tip Amount not a number)");
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

			Player* tiptoPlayer = playerManager->getPlayer(tipToName);
			if (tiptoPlayer == NULL) {
				//The player exists but they are offline. So Still do the tip.
				//Do stuff like altering the db here since they arent online.
				if (playerManager->modifyOfflineBank(player, tipToName,
						tipAmount))
					player->sendSystemMessage("Player not online. Credits should be transferred.");
				return;
			} else {
				//Player is online. Tip their stuff and send mail etc;
				//make sure they have the proper credits first.
				playerManager->doBankTip(player, tiptoPlayer, tipAmount, true);
			}

		} else {
			//Invalid Player Name
			player->sendSystemMessage(tipToName
					+ " is not a valid player name.");
			return;
		}

	} else {
		//The player has SOMETHING targetted.
		//Lets first check if its a player, cause if it is we can skip some stuff.
		SceneObject* object = player->getZone()->lookupObject(tipToId);

		if (object == NULL) {
			player->sendSystemMessage("SceneObject is NULL for some reason.");
			return;
		}

		if (object == player) {
			player->sendSystemMessage("You can't tip yourself.");
			return;
		}

		if (object->isPlayer()) {
			//Ok so we know its a player.
			//If its a player in range, the client will omit any text referencing the name.
			//So the next param SHOULD be the tip amount.
			if (!tokenizer.hasMoreTokens())
				return;

			string tips;
			tokenizer.getStringToken(tips);
			tipAmount = atoi(tips.c_str());

			//Quick cast of the object to a Player.
			Player* tipTo = (Player*) object;

			//They didnt type in a number, or typed in 0.
			if (tipAmount == 0) {
				//Invalid Tip Amount/Parameter.
				player->sendSystemMessage("Invalid Tip parameter. (Tip Amount not a number)");
				return;
			}

			//Now that we have the tip amount, we have to see if they want it to be a regular tip
			//or a bank tip. So we check if theres more tokens.
			if (tokenizer.hasMoreTokens()) {
				//Theres more crap typed, so we have to check that they typed ONLY bank.
				string bankParam;
				tokenizer.getStringToken(bankParam);

				if (bankParam == "bank") {
					//Bank tip. We don't need to parse anything else now that we have this info.
					playerManager->doBankTip(player, tipTo, tipAmount, true);

				} else {
					//They typed something else other than bank.
					player->sendSystemMessage("Invalid Tip parameter. (Bank Parameter)");
					return;
				}

			} else {
				//Theres nothing else typed, so they want to do a cash tip. Cake!
				playerManager->doCashTip(player, tipTo, tipAmount, true);
			}

		} else {
			//The current target is not a player.
			//So we have to parse for a valid player name. (THIS IS ONLY FOR BANK TIPS)

			if (!tokenizer.hasMoreTokens())
				return;

			string tipToName;
			tokenizer.getStringToken(tipToName);

			//Before we go any further we should validate the player name.
			if (!playerManager->validateName(tipToName)) {
				//They exist at least. Now lets grab the tip amount.
				if (!tokenizer.hasMoreTokens())
					return;

				string tips;
				tokenizer.getStringToken(tips);
				tipAmount = atoi(tips.c_str());

				//They didnt type in a number, or typed in 0.
				if (tipAmount == 0) {
					//Invalid Tip Amount/Parameter.
					player->sendSystemMessage("Invalid Tip parameter. (Tip Amount not a number)");
					return;
				}

				//Ok so now we have the name, and we've verified the tip amount.
				//Now all thats left to do is the bank tip.
				//We have to make sure the player typed bank at the end.
				if (tokenizer.hasMoreTokens()) {
					//Theres more crap typed, so we have to check that they typed ONLY bank.
					string bankParam;
					tokenizer.getStringToken(bankParam);

					if (bankParam == "bank") {
						//Bank tip. We don't need to parse anything else now that we have this info.
						Player* tiptoPlayer =
								playerManager->getPlayer(tipToName);
						if (tiptoPlayer == NULL) {
							//The player exists but they are offline. So Still do the tip.
							//Do stuff like altering the db here since they arent online.
							playerManager->modifyOfflineBank(player, tipToName,
									tipAmount);
							player->sendSystemMessage("Player not online. Add Altering the DB in later.");
							return;
						} else {
							//Player is online. Tip their stuff and send mail etc;
							//make sure they have the proper credits first.
							playerManager->doBankTip(player, tiptoPlayer,
									tipAmount, true);
						}
					} else {
						//They typed something else other than bank.
						player->sendSystemMessage("Invalid Tip parameter. (Bank Parameter)");
						return;
					}
				}
			} else {
				//Invalid Player Name
				player->sendSystemMessage(tipToName
						+ " is not a valid player name.");
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

		if (combatManager->canAttack(player, target) && target->isIncapacitated()
				&& target->isInRange(player, 5)) {

			player->unlock();

			target->deathblow(player);

			player->wlock(target);

			float currentRating = (float)player->getPvpRating();
			float opponentRating = (float)target->getPvpRating();

			//Using the formula: N = P1 + ( (1/9) * (P2 - P1 + 100) ), where P2 - P1 - 100 >= 0
			int pointsGained = (int)round((1.0f/9.0f) * (opponentRating - currentRating + 100.0f));

			pointsGained = (pointsGained >= 0) ? pointsGained : 0;
			//TODO: Is there a max pvp rating?

			player->increasePvpRating(pointsGained);

			int newRating = player->getPvpRating();

			stringstream victoryMsg;

			string victimName = "";
			unicode uniName = unicode("");
			uniName = target->getCharacterName();
			victimName = uniName.c_str();

			if (pointsGained > 0) {
				switch (System::random(2)) {
				case 0:
					victoryMsg << "You have fought valiantly against " << victimName.c_str() << ".  For your part in their death your player combat rating has been adjusted to " << newRating << ".";
					break;
				case 1:
					victoryMsg << "You have killed " << victimName.c_str() << ". For your part in their death your player combat rating has been adjusted to " << newRating << ".";
					break;
				case 2:
				default:
					victoryMsg << "You have fearlessly slain your foe " << victimName.c_str() << ".  For your part in their death your player combat rating has been adjusted to " << newRating << ".";
					break;
				}
			} else {
				victoryMsg << "Although you have valiantly defeated " << victimName.c_str() << " in combat, you can reap no more combat rating points from %PT death at this time.  Your player combat rating remains at " << newRating << ".";
			}

			player->sendSystemMessage("base_player", "prose_target_dead", target->getObjectID());
			player->sendSystemMessage(victoryMsg.str());
		}

		target->unlock();
	} catch (...) {
		cout << "Unreported exception caught in ObjectControllerMessage::handleDeathblow(Player* player, Message* packet)\n";
		target->unlock();
	}
}

void ObjectControllerMessage::parsePlaceStructure(Player* player, Message* packet){

	player->sendSystemMessage("Placing Structure");
	packet->parseInt();  // Empty Data
	packet->parseInt();  // Empty Data

	unicode data;
	packet->parseUnicode(data);

	StringTokenizer tokenizer(data.c_str());

	string objectID;
	tokenizer.getStringToken(objectID);
	float x = tokenizer.getFloatToken();
	float y = tokenizer.getFloatToken();
	int orient = tokenizer.getIntToken();

	uint64 toID = String::toUnsignedLong(objectID.c_str());

	PlanetManager * planet = player->getZone()->getPlanetManager();
	planet->placePlayerStructure(player, toID, x, y, orient);

}

void ObjectControllerMessage::parseSurveySlashRequest(Player* player,
		Message* packet) {
	player->setSurveyErrorMessage();
}

void ObjectControllerMessage::parseSampleSlashRequest(Player* player,
		Message* packet) {
	player->setSampleErrorMessage();
}

void ObjectControllerMessage::parseSurveyRequest(Player* player, Message* packet) {
	uint64 targetID = packet->parseLong();

	unicode resourceName;
	packet->parseUnicode(resourceName);
	string resName = resourceName.c_str().c_str();

	string skillBox = "crafting_artisan_novice";

	if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox)) {
		if (player->getSurveyTool() == NULL) {
			player->sendSystemMessage("You must use a survey tool once from the Inventory before you can do this.");
			return;
		}
		player->getSurveyTool()->surveyRequest(player, resName);
	} else {
		if (player->getSurveyErrorMessage())
			player->sendSystemMessage("You do not have sufficient abilities to Survey Resources.");
	}
}

void ObjectControllerMessage::parseSampleRequest(Player* player, Message* packet) {
	uint64 targetID = packet->parseLong();

	unicode resourceName;
	packet->parseUnicode(resourceName);
	string resName = resourceName.c_str().c_str();

	string skillBox = "crafting_artisan_novice";

	if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox)) {
		if (player->getSurveyTool() == NULL) {
			player->sendSystemMessage("You must use a survey tool once from the Inventory before you can do this.");
			return;
		}
		player->getSurveyTool()->sampleRequest(player, resName);
	} else {
		if (player->getSampleErrorMessage())
			player->sendSystemMessage("You do not have sufficient abilities to Sample Resource.");
	}
}

void ObjectControllerMessage::parseResourceContainerSplit(Player* player,
		Message* packet) {
	if (player->getTradeSize() != 0) {
		player->sendSystemMessage("You cant move objects while trading..");
		return;
	}

	if (player->hasFullInventory()) {
		player->sendSystemMessage("Youd dont have enough space in your inventory");
		return;
	}

	uint64 objectID = packet->parseLong();

	unicode resourceQuantity;
	packet->parseUnicode(resourceQuantity);

	StringTokenizer tokenizer(resourceQuantity.c_str());

	string quantityString;

	if (tokenizer.hasMoreTokens())
		tokenizer.getStringToken(quantityString);
	else
		return;

	int newQuantity = atoi(quantityString.c_str());

	SceneObject* invObj = player->getInventoryItem(objectID);

	if (invObj != NULL && invObj->isTangible()) {
		TangibleObject* tano = (TangibleObject*) invObj;

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

	unicode ustr;
	packet->parseUnicode(ustr);

	StringTokenizer tokenizer(ustr.c_str());

	string quantityString, toIDString;

	if (tokenizer.hasMoreTokens())
		tokenizer.getStringToken(toIDString);

	if (tokenizer.hasMoreTokens())
		tokenizer.getStringToken(quantityString);

	uint64 toID = String::toUnsignedLong(toIDString.c_str());

	SceneObject* object1 = player->getInventoryItem(fromID);
	SceneObject* object2 = player->getInventoryItem(toID);

	if (object1 != NULL && object2 != NULL && object1->isTangible()
			&& object2->isTangible()) {
		TangibleObject* resCof = (TangibleObject*) object1;
		TangibleObject* resCot = (TangibleObject*) object2;
		if (resCof->isResource() && resCot->isResource()) {
			ResourceContainer* rcof = (ResourceContainer*)resCof;
			ResourceContainer* rcot = (ResourceContainer*) resCot;
			rcot->transferContents(player, rcof);
		}
	}
}

void ObjectControllerMessage::parseRequestDraftSlotsBatch(Player* player,
		Message* packet) {
	packet->shiftOffset(8);

	unicode crcAndID;
	packet->parseUnicode(crcAndID);

	StringTokenizer tokenizer(crcAndID.c_str());

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

void ObjectControllerMessage::parseRequestResourceWeightsBatch(Player* player,
		Message* packet) {
	packet->shiftOffset(8);

	unicode id;
	packet->parseUnicode(id);

	StringTokenizer tokenizer(id.c_str());

	uint32 schematicID;
	if (tokenizer.hasMoreTokens())
		schematicID = tokenizer.getIntToken();

	//Check to see if the correct obj id is in the players vector of draft schematics
	DraftSchematic* ds = player->getDraftSchematic(schematicID);
	if (ds != NULL) {
		ds->sendExperimentalPropertiesToPlayer(player);
	}
}

void ObjectControllerMessage::parseRequestCraftingSession(Player* player,
		Message* packet) {
	uint64 ctSceneObjID = packet->parseLong();

	//Check to see if the correct obj id is in the player's datapad
	SceneObject* invObj = player->getInventoryItem(ctSceneObjID);

	CraftingTool* craftingTool = NULL;

	if (invObj != NULL && invObj->isTangible() && ((TangibleObject*)invObj)->isCraftingTool()) {
		craftingTool = (CraftingTool*) invObj;

		if (craftingTool->isReady()) {

			craftingTool->sendToolStart(player);

		} else if (craftingTool->isFinished()) {

			player->sendSystemMessage("Cannot start crafting session with item in hopper");

		} else {

			// Start Object Controller **************************************
			ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x010C);
			objMsg->insertInt(0x10F);
			objMsg->insertInt(0);
			objMsg->insertByte(0);

			player->sendMessage(objMsg);

		}
	} else {
		// This case is reached if double clicking on a crafting station

		CraftingStation* craftingStation = (CraftingStation*)player->getZone()->lookupObject(ctSceneObjID);

		if(craftingStation != NULL){

			craftingTool = player->getCraftingTool(craftingStation->getStationType(), false);

			if(craftingTool != NULL){

				craftingTool->sendToolStart(player);

			} else {

				player->sendSystemMessage("No tool available to start.");

			}

		} else {

			player->sendSystemMessage("Something happened that shouldn't have.  Not a tool or a station, contact Kyle");

		}

	}
}

void ObjectControllerMessage::parseCancelCraftingSession(Player* player,
		Message* packet) {

	//TODO: Try to find a Cancel Crafting Session server->client packet in live for researching

	// This is just a guess as to what the client wants when it sends a Cancel Crafting Session packet
	CraftingTool * ct = player->getCurrentCraftingTool();

	if (ct != NULL) {
		// DPlay9
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player->getPlayerObject());
		dplay9->setCraftingState(0);
		ct->setCraftingState(0);
		dplay9->close();
		player->sendMessage(dplay9);

		// Clean up crafting here, delete, sceneremove unneeded objects
		ct->cleanUp(player);
	}

}

void ObjectControllerMessage::parseSelectDraftSchematic(Player* player,
		Message* packet) {

	packet->shiftOffset(8);

	unicode uniIndexOfSelectedSchematic;
	packet->parseUnicode(uniIndexOfSelectedSchematic);

	StringTokenizer tokenizer(uniIndexOfSelectedSchematic.c_str());

	int indexOfSelectedSchematic;

	if (tokenizer.hasMoreTokens())
		indexOfSelectedSchematic = tokenizer.getIntToken();

	// Find the selected schematic

	CraftingTool * craftingTool = player->getCurrentCraftingTool();

	if (craftingTool != NULL) {

		DraftSchematic
				* draftSchematic =
						craftingTool->getCurrentDraftSchematic(indexOfSelectedSchematic);

		if (draftSchematic != NULL) {

			try {

				craftingTool->wlock();

				player->prepareCraftingSession(craftingTool, draftSchematic);

				craftingTool->unlock();

			}
			catch(...) {

				craftingTool->unlock();

			}

		}
	} else {
		// This eles should never execute
		player->sendSystemMessage("Selected Draft Schematic was invalid.  Please inform Link of this error.");
	}

}
void ObjectControllerMessage::parseAddCraftingResource(Player* player,
		Message* packet) {

	packet->shiftOffset(12);

	uint64 resourceObjectID = packet->parseLong();

	int slot = packet->parseInt();

	packet->shiftOffset(4);

	int counter = packet->parseByte();

	SceneObject* invObj = player->getInventoryItem(resourceObjectID);

	if (invObj != NULL && invObj->isTangible()) {
		player->addIngredientToSlot((TangibleObject*)invObj, slot, counter);

	} else {
		// This eles should never execute
		player->sendSystemMessage("Add resource invalid, contact kyle");

	}
}
void ObjectControllerMessage::parseRemoveCraftingResource(Player* player,
		Message* packet) {

	packet->shiftOffset(12);

	int slot = packet->parseInt();

	uint64 resID = packet->parseLong();

	int counter = packet->parseByte();

	player->removeResourceFromCraft(resID, slot, counter);

}
void ObjectControllerMessage::parseNextCraftingStage(Player* player,
		Message* packet) {

	packet->shiftOffset(8);

	unicode d;
	packet->parseUnicode(d);

	string data = d.c_str();

	player->nextCraftingStage(data);

}
void ObjectControllerMessage::parseCraftCustomization(Player* player,
		Message* packet) {

	packet->shiftOffset(12);

	unicode n;
	packet->parseUnicode(n);

	string name = n.c_str();

	packet->shiftOffset(1);

	int condition = packet->parseInt();

	player->craftingCustomization(name, condition);
}
void ObjectControllerMessage::parseCreatePrototype(Player* player,
		Message* packet) {

	packet->shiftOffset(8);

	unicode d;
	packet->parseUnicode(d);

	string count = d.c_str();

	player->createPrototype(count);
}

void ObjectControllerMessage::parseCreateSchematic(Player* player,
		Message* packet) {

	packet->shiftOffset(8);

	unicode d;
	packet->parseUnicode(d);

	string count = d.c_str().c_str();

	player->createSchematic(count);
}

void ObjectControllerMessage::parseExperimentation(Player * player,
		Message* pack) {
	ZoneClientSessionImplementation* client =
			(ZoneClientSessionImplementation*) pack->getClient();

	if (player == NULL)
		return;

	pack->shiftOffset(12);

	int counter = pack->parseByte();

	int numRowsAttempted = pack->parseInt();

	int rowEffected, pointsAttempted;
	stringstream ss;

	for (int i = 0; i < numRowsAttempted; ++i) {

		rowEffected = pack->parseInt();
		pointsAttempted = pack->parseInt();

		ss << rowEffected << " " << pointsAttempted << " ";

	}

	string expstring = ss.str();

	player->handleExperimenting(counter, numRowsAttempted, expstring);

}

void ObjectControllerMessage::parsePickup(Player* player, Message* pack) {
	//cout << pack->toString() << "\n";
}

void ObjectControllerMessage::parseTransferItemMisc(Player* player,
		Message* pack) {
	uint64 target = pack->parseLong();

	SceneObject* object = player->getPlayerItem(target);

	if (object != NULL) {
		player->changeCloth(target);
		return;
	}

	SceneObject* targetObject = player->getTarget();

	if (targetObject != NULL && targetObject != player
			&& targetObject->isNonPlayerCreature()) {
		Creature* creature = (Creature*) targetObject;

		try {
			creature->wlock(player);

			object = creature->getLootItem(target);

			creature->unlock();
		} catch (...) {
			creature->unlock();
		}

		if (object != NULL)
			player->lootObject(creature, object);
	}
}
void ObjectControllerMessage::parseAddFriend(Player* player, Message* pack) {
	//ToDO: Split the token based on dots for game (SWG), server (eg. sunrunner) and name (SWG.sunrunner.john)
	pack->shiftOffset(8);

	unicode d;
	pack->parseUnicode(d);

	string name = d.c_str();

	if(name != ""){
		player->getPlayerObject()->addFriend(name, player->getZone()->getZoneServer()->getServerName());
	}
}

void ObjectControllerMessage::parseRemoveFriend(Player* player, Message* pack) {
	pack->shiftOffset(8);

	unicode d;
	pack->parseUnicode(d);

	string name = d.c_str();

	if(name != ""){
		player->getPlayerObject()->removeFriend(name);
	}
}

void ObjectControllerMessage::parseFindFriend(Player* player, Message* pack, PlayerManager* playerManager) {
	pack->shiftOffset(8);

	unicode d;
	pack->parseUnicode(d);

	string name = d.c_str();

	if(name != ""){
		player->getPlayerObject()->findFriend(name, playerManager);
	}
}

void ObjectControllerMessage::parseRotateItem(Player* player, Message* pack) {
	uint64 target = pack->parseLong();

	SceneObject* object = player->getZone()->getZoneServer()->getObject(target, true);

	try {
		object->wlock(player);

		object->setDirection(object->getDirectionX(), (object->getDirectionZ()
				+ sqrt(.5)), object->getDirectionY(), (object->getDirectionW()
						+ sqrt(.5)));

		object->unlock();
	} catch (...) {
		object->unlock();
		cout << "unreported exception caught in ObjectControllerMessage::parseRotateItem\n";
	}
}

void ObjectControllerMessage::parseAddIgnore(Player* player, Message* pack) {
	//ToDO: Split the token based on dots for game (SWG), server (eg. sunrunner) and name (SWG.sunrunner.john)
	pack->shiftOffset(8);

	unicode d;
	pack->parseUnicode(d);

	string name = d.c_str();

	if(name != ""){
		player->getPlayerObject()->addIgnore(name, player->getZone()->getZoneServer()->getServerName());
	}
}

void ObjectControllerMessage::parseRemoveIgnore(Player* player, Message* pack) {

	pack->shiftOffset(8);

	unicode d;
	pack->parseUnicode(d);

	string name = d.c_str();

	if(name != ""){
		player->getPlayerObject()->removeIgnore(name);
	}
}

void ObjectControllerMessage::parseGiveConsentRequest(Player* player, Message* pack) {
	if (player->getConsentSize() >= 15) { //Max consent list size = 15
		player->sendSystemMessage("Your consent list is full. You must /unconsent someone before consenting another player.");
		return;
	}

	pack->shiftOffset(8);
	unicode unicodeName;
	pack->parseUnicode(unicodeName);
	string name = unicodeName.c_str();
	string consentName = "";

	if (name.empty()) {
		player->sendSystemMessage("Usage: /consent <name>");
		return;
	}

	StringTokenizer tokenizer(name);
	tokenizer.setDelimeter(" ");
	tokenizer.getStringToken(consentName);

	PlayerManager* playerManager = player->getZone()->getZoneServer()->getPlayerManager();
	Player* playerTarget = playerManager->getPlayer(consentName);

	if (playerTarget != NULL) {
		if (playerTarget == player) {
			player->sendSystemMessage("You ask yourself for consent, but you get no reply.");
			return;
		}

		if (player->giveConsent(playerTarget->getFirstName())) {
			player->sendSystemMessage("base_player", "prose_consent", playerTarget->getObjectID()); //You give your consent to %TO.
			playerTarget->sendSystemMessage("base_player", "prose_got_consent", player->getObjectID()); //%TO consents you.
		} else {
			player->sendSystemMessage("You have already given them your consent.");
		}

		return;
	} else {
		player->sendSystemMessage("Your target for consent is either offline or does not exist.");
	}
}

void ObjectControllerMessage::parseRevokeConsentRequest(Player* player, Message* pack) {
	if (player->getConsentSize() <= 0) {
		player->sendSystemMessage("You have no one on your consent list to remove.");
		return;
	}

	pack->shiftOffset(8);
	unicode unicodeName;
	pack->parseUnicode(unicodeName);
	string name = unicodeName.c_str();
	string consentName = "";

	if (name.empty()) {
		player->sendSystemMessage("Usage: /unconsent <name>");
		return;
	}

	StringTokenizer tokenizer(name);
	tokenizer.setDelimeter(" ");
	tokenizer.getStringToken(consentName);

	PlayerManager* playerManager = player->getZone()->getZoneServer()->getPlayerManager();
	Player* playerTarget = playerManager->getPlayer(consentName);

	if (player->revokeConsent(consentName)) {
		player->sendSystemMessage("You revoke your consent from " + consentName + ".");

		if (playerTarget != NULL) {
			playerTarget->sendSystemMessage(player->getFirstNameProper() + " revokes your consent.");
		}
	} else {
		player->sendSystemMessage("Your target for unconsent is offline or does note exist.");
	}
}

void ObjectControllerMessage::parseHaveConsentRequest(Player* player, Message* pack) {
	pack->shiftOffset(8);
	unicode unicodeName;
	pack->parseUnicode(unicodeName);
	string name = unicodeName.c_str();
	string consentName = "";

	if (name.empty()) {
		player->sendConsentBox();
		return;
	}

	/*
	StringTokenizer tokenizer(name);
	tokenizer.setDelimeter(" ");
	tokenizer.getStringToken(consentName);
	*/
}

void ObjectControllerMessage::parseHarvestOrganics(Player* player, Message* pack){

	Zone* zone = player->getZone();
	if(zone == NULL)
		return;

	ResourceManager* resourceManager = zone->getZoneServer()->getResourceManager();
	if(resourceManager == NULL)
		return;

	CreatureManager* creatureManager = zone->getCreatureManager();
	if(creatureManager == NULL)
		return;

	uint64 creatureID = pack->parseLong();
	Creature* creature = creatureManager->getCreature(creatureID);
	if(creature == NULL)
		return;

	int type = 0;

	unicode restype;
	pack->parseUnicode(restype);

	string resourceType = restype.c_str().c_str();

	if(resourceType == "meat")
		type = 1;

	if(resourceType == "hide")
		type = 2;

	if(resourceType == "bone")
		type = 3;

	resourceManager->harvestOrganics(player, creature, type);

}






