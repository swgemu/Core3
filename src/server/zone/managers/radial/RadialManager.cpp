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

#include "RadialManager.h"
#include "../../Zone.h"
#include "../../objects/SceneObject.h"
#include "../../objects/intangible/player/PlayerObject.h"
#include "../../packets/object/ObjectMenuResponse.h"

RadialManager::RadialManager() {
}

/**
 * This method is fired when the server receives a packet requesting radial options for an object.
 * In response, an ObjectMenuResponse packet is sent to the client, containing the radial options.
 * \param player The player that has requested the radial options.
 * \param pack The packet that was sent from the client to the server.
 */
void RadialManager::handleRadialRequest(PlayerObject* player, Packet* pack) {
	pack->shiftOffset(12); // skip ObjectID and size

	uint64 objectid = pack->parseLong();
	uint64 playerid = pack->parseLong();

	ObjectMenuResponse* omr;
	omr = parseDefaults(player, objectid, pack);

	Zone* zone = player->getZone();

	if (zone == NULL) {
		delete omr;
		return;
	}

	//ManagedReference<SceneObject> object = zone->lookupObject(objectid);

	//System::out << "Radial Request ObjectID: " << dec << objectid << "\n";
	/*if (object == NULL)
		object = player->getPlayerItem(objectid);

	if (object == NULL) {
		sendDefaultRadialResponse(player, omr);
	} else {
		try {
			if (object != player)
				object->wlock(player);

			object->sendRadialResponseTo(player, omr);

			if (object != player)
				object->unlock();
		} catch (...) {
			if (object != player)
				object->unlock();
			System::out << "unreported exception caught in RadialManager::handleRadialRequest\n";
		}
	}*/
}

void RadialManager::handleRadialSelect(PlayerObject* player, Packet* pack) {
	/*
	try {
		player->wlock();

		uint64 objectID = pack->parseLong();
		uint8 radialID = pack->parseByte();

		Zone* zone = player->getZone();

		if (zone == NULL) {
			player->unlock();
			return;
		}

		//System::out << "Radial ID = " << dec << radialID << endl;
		ManagedReference<SceneObject> obj = zone->lookupObject(objectID);

		if (obj == NULL) {
			obj = player->getInventoryItem(objectID);

			if (obj == NULL)
				obj = player->getDatapadItem(objectID);

			if (obj == NULL) {
				player->unlock();
				return;
			}
		}

		try {
			handleSelection(radialID, player, obj);
		} catch (Exception& e) {
			System::out << "exceptcion while handling radial selection \n" << e.getMessage();
			e.printStackTrace();
		} catch (...) {
			System::out << "unreported exception caught while handling radial selection\n";
		}

	} catch (...) {
		System::out << "unreported exception in void RadialManager::handleRadialSelect(Player* player, Packet* pack)\n";
		player->unlock();
	}*/
}

void RadialManager::handleSelection(int radialID, PlayerObject* player, SceneObject* obj) {
	// Pre: player is wlocked, obj is unlocked
	// Post: player and obj unlocked


	//System::out << "Radial ID = " << dec << radialID << endl;

	//TODO: Revisit locking before and after this method since we are handing on the object
	//rather than in the manager.
	//Should objects which need casting still be handled? Should everything be handled, then
	//point to it's objects onRadialHandler?
	try {
		switch (radialID) {
		case 0: //UNKNOWN
		case 1: //COMBAT_TARGET
		case 2: //COMBAT_UNTARGET
		case 3: //COMBAT_ATTACK
		case 4: //COMBAT_PEACE
		case 5: //COMBAT_DUEL
		case 6: //COMBAT_DEATH_BLOW
			break;
		case 7: //EXAMINE
			break;
		case 8: //TRADE_START
			//handleTrade(player, obj);
			//obj->tradeStart(player);
			break;
		case 9: //TRADE_ACCEPT
			//obj->tradeAccept(player);
			break;
		case 10: //ITEM_PICKUP
			//obj->pickup(player);
		case 11: //ITEM_EQUIP
			//obj->equip(player);
			break;
		case 12: //ITEM_UNEQUIP
			//obj->unequip(player);
			break;
		case 13: //ITEM_DROP
			//obj->drop(player);
			break;
		case 14: //ITEM_DESTROY
			//obj->destroy(player);
			break;
		case 15: //ITEM_TOKEN
			break;
		case 16: //ITEM_OPEN
			//obj->open(player);
			break;
		case 17: //ITEM_OPEN_NEW_WINDOW
			break;
		case 18: //ITEM_ACTIVATE
			//obj->activate(player);
			break;
		case 19: //ITEM_DEACTIVATE
			//obj->deactivate(player);
			break;
		case 20: //ITEM_USE
			//obj->use(player);
			break;
		case 21: //ITEM_USE_SELF
		case 22: //ITEM_USE_OTHER
		case 23: //ITEM_SIT
		case 24: //ITEM_MAIL
		case 25: //CONVERSE_START
			//obj->converseStart(player);
			break;
		case 26: //CONVERSE_RESPOND
			//obj->converseRespond(player);
			break;
		case 27: //CONVERSE_RESPONSE
			//obj->converseResponse(player);
			break;
		case 28: //CONVERSE_STOP
			//obj->converseStop(player);
			break;
		case 29: //CRAFT_OPTIONS
			break;
		case 30: //CRAFT_START
			break;
		case 31: //CRAFT_HOPPER_INPUT
			break;
		case 32: //CRAFT_HOPPER_OUTPUT
			//handleOpenCraftingToolHopper(player, obj);
			break;
		case 33: //MISSION_TERMINAL_LIST
			break;
		case 34: //MISSION_DETAILS
			break;
		case 35: //LOOT
			//obj->loot(player, false);
			break;
		case 36: //LOOT_ALL
			//obj->loot(player);
			break;
		case 37: //GROUP_INVITE
			//player->sendGroupInviteTo((Player*) obj);
			break;
		case 38: //GROUP_JOIN
			//player->acceptGroupInvite(player);
			break;
		case 39: //GROUP_LEAVE
			//obj->leaveGroup();
			break;
		case 40: //GROUP_KICK
			//player->kickFromGroup((Player*) obj);
			break;
		case 41: //GROUP_DISBAND
			//obj->groupDisband();
			break;
		case 42: //GROUP_DECLINE
			//player->declineGroupInvite(player);
			break;
		case 43: //EXTRACT_OBJECT
			break;
		case 44: //PET_CALL
			//obj->call(player);
			break;
		case 45: //TERMINAL_AUCTION_USE
			//sendRadialResponseForBazaar(obj->getObjectID(), player);
			break;
		case 46: //CREATURE_FOLLOW
			//player->follow(obj);
			break;
		case 47: //CREATURE_STOP_FOLLOW
			//player->stopFollow(obj);
			break;
		case 48: //SPLIT
			//obj->splitContents(player);
			break;
		case 49: //IMAGEDESIGN
			//player->imageDesign(obj);
			break;
		case 50: //SET_NAME
			//obj->sendCustomNamePromptTo(player);
			break;
		case 51: //ITEM_ROTATE - MENU ROOT
			break;
		case 52: //ITEM_ROTATE_RIGHT
			//obj->rotate(player, "right");
			break;
		case 53: //ITEM_ROTATE_LEFT
			//obj->rotate(player, "left");
			break;
		case 54: //ITEM_MOVE - MENU ROOT
			break;
		case 55: //ITEM_MOVE_FORWARD
			//obj->move(player, "forward");
			break;
		case 56: //ITEM_MOVE_BACK
			//obj->move(player, "back");
			break;
		case 57: //ITEM_MOVE_UP
			//obj->move(player, "up");
			break;
		case 58: //ITEM_MOVE_DOWN
			//obj->move(player, "down");
			break;
		case 59: //PET_STORE
			//obj->store(player);
			break;
		case 60: //VEHICLE_GENERATE
			//obj->generateVehicle(player);
			break;
		case 61: //VEHICLE_STORE
			//obj->store(player);
			break;
		case 62: //MISSION_ABORT
			//obj->missionAbort(player);
			break;
		case 63: //MISSION_END_DUTY
			//obj->missionEndDuty(player);
			break;
		case 64: //SHIP_MANAGE_COMPONENTS
		case 65: //WAYPOINT_AUTOPILOT
		case 66: //PROGRAM_DROID
		case 67: //SERVER_DIVIDER
			break;
		case 68: //SERVER_MENU1
			//obj->onRadialMenu1(player);
			break;
		case 69: //SERVER_MENU2
			//obj->onRadialMenu2(player);
			break;
		case 70: //SERVER_MENU3
			//obj->onRadialMenu3(player);
			break;
		case 71: //SERVER_MENU4
			//obj->onRadialMenu4(player);
			break;
		case 72: //SERVER_MENU5
			//obj->onRadialMenu5(player);
			break;
		case 73: //SERVER_MENU6
			//obj->onRadialMenu6(player);
			break;
		case 74: //SERVER_MENU7
			//obj->onRadialMenu7(player);
			break;
		case 75: //SERVER_MENU8
			//obj->onRadialMenu8(player);
			break;
		case 76: //SERVER_MENU9
			//obj->onRadialMenu9(player);
			break;
		case 77: //SERVER_MENU10
			//obj->onRadialMenu10(player);
			break;
		case 78: //SERVER_HARVESTER_MANAGE
			//obj->manageHarvester(player);
			break;
		case 79: //SERVER_HOUSE_MANAGE
		case 80: //SERVER_FACTION_HALL_MANAGE
		case 81: //SERVER_HUE
		case 82: //SERVER_OBSERVE
		case 83: //SERVER_STOP_OBSERVING
		case 84: //SERVER_TRAVEL_OPTIONS
		case 85: //SERVER_BAZAAR_OPTIONS
		case 86: //SERVER_SHIPPING_OPTIONS
		case 87: //SERVER_HEAL_WOUND
			break;
		case 88: //SERVER_HEAL_WOUND_HEALTH
			//player->healWound(obj, CreatureAttribute::HEALTH);
			break;
		case 89: //SERVER_HEAL_WOUND_ACTION
			//player->healWound(obj, CreatureAttribute::ACTION);
			break;
		case 90: //SERVER_HEAL_WOUND_STRENGTH
			//player->healWound(obj, CreatureAttribute::STRENGTH);
			break;
		case 91: //SERVER_HEAL_WOUND_CONSTITUTION
			//player->healWound(obj, CreatureAttribute::CONSTITUTION);
			break;
		case 92: //SERVER_HEAL_WOUND_QUICKNESS
			//player->healWound(obj, CreatureAttribute::QUICKNESS);
			break;
		case 93: //SERVER_HEAL_WOUND_STAMINA
			//player->healWound(obj, CreatureAttribute::STAMINA);
			break;
		case 94: //SERVER_HEAL_DAMAGE
			//player->healDamage(obj);
			break;
		case 95: //SERVER_HEAL_STATE
			break;
		case 96: //SERVER_HEAL_STATE_STUNNED
			//player->healState(obj, CreatureState::STUNNED);
			break;
		case 97: //SERVER_HEAL_STATE_BLINDED
			//player->healState(obj, CreatureState::BLINDED);
			break;
		case 98: //SERVER_HEAL_STATE_DIZZY
			//player->healState(obj, CreatureState::DIZZY);
			break;
		case 99: //SERVER_HEAL_STATE_INTIMIDATED
			//player->healState(obj, CreatureState::INTIMIDATED);
			break;
		case 100: //SERVER_HEAL_ENHANCE
			break;
		case 101: //SERVER_HEAL_ENHANCE_HEALTH
			//player->healEnhance(obj, CreatureAttribute::HEALTH);
			break;
		case 102: //SERVER_HEAL_ENHANCE_ACTION
			//player->healEnhance(obj, CreatureAttribute::ACTION);
			break;
		case 103: //SERVER_HEAL_ENHANCE_STRENGTH
			//player->healEnhance(obj, CreatureAttribute::STRENGTH);
			break;
		case 104: //SERVER_HEAL_ENHANCE_CONSTITUTION
			//player->healEnhance(obj, CreatureAttribute::CONSTITUTION);
			break;
		case 105: //SERVER_HEAL_ENHANCE_QUICKNESS
			//player->healEnhance(obj, CreatureAttribute::QUICKNESS);
			break;
		case 106: //SERVER_HEAL_ENHANCE_STAMINA
			//player->healEnhance(obj, CreatureAttribute::STAMINA);
			break;
		case 107: //SERVER_HEAL_FIRSTAID
			//player->applyFirstAid(obj);
			break;
		case 108: //SERVER_HEAL_CURE_POISON
			//player->curePoison(obj);
			break;
		case 109: //SERVER_HEAL_CURE_DISEASE
			//player->cureDisease(obj);
			break;
		case 110: //SERVER_HEAL_APPLY_POISON
			//player->applyPoison(player);
			break;
		case 111: //SERVER_HEAL_APPLY_DISEASE
			//player->applyDisease(player);
			break;
		case 112: //SERVER_HARVEST_CORPSE
			//player->harvestCorpse(obj);
			break;
		case 113: //SERVER_PERFORMANCE_LISTEN
			//obj->performanceListen(player);
			break;
		case 114: //SERVER_PERFORMANCE_WATCH
			//obj->performanceWatch(player);
			break;
		case 115: //SERVER_PERFORMANCE_LISTEN_STOP
			//obj->performanceListenStop(player);
			break;
		case 116: //SERVER_PERFORMANCE_WATCH_STOP
			//obj->performanceWatchStop(player);
			break;
		case 117: //SERVER_TERMINAL_PERMISSIONS
		case 118: //SERVER_TERMINAL_MANAGEMENT
			break;
		case 119: //SERVER_TERMINAL_PERMISSIONS_ENTER
			//obj->sendPermissionListTo(player, "ENTRY");
			break;
		case 120: //SERVER_TERMINAL_PERMISSIONS_BANNED
			//obj->sendPermissionListTo(player, "BAN");
			break;
		case 121: //SERVER_TERMINAL_PERMISSIONS_ADMIN
			//obj->sendPermissionListTo(player, "ADMIN");
			break;
		case 122: //SERVER_TERMINAL_PERMISSIONS_VENDOR
			//obj->sendPermissionListTo(player, "VENDOR");
			break;
		case 123: //SERVER_TERMINAL_PERMISSIONS_HOPPER
			//obj->sendPermissionListTo(player, "HOPPER");
			break;
		case 124: //SERVER_TERMINAL_MANAGEMENT_STATUS
			//obj->sendStructureStatusTo(player);
			break;
		case 125: //SERVER_TERMINAL_MANAGEMENT_PRIVACY
			//obj->sendStructurePrivacyTo(player);
			break;
		case 126: //SERVER_TERMINAL_MANAGEMENT_TRANSFER
			//obj->sendStructureTransferTo(player);
			break;
		case 127: //SERVER_TERMINAL_MANAGEMENT_RESIDENCE
			//obj->declareResidence(player);
			break;
		case 128: //SERVER_TERMINAL_MANAGEMENT_DESTROY
			//obj->sendDestroyStructureTo(player);
			break;
		case 129: //SERVER_TERMINAL_MANAGEMENT_PAY
			//obj->sendPayMaintenanceTo(player);
			break;
		case 130: //SERVER_TERMINAL_CREATE_VENDOR
			//obj->sendCreateVendorTo(player);
			break;
		case 131: //SERVER_GIVE_VENDOR_MAINTENANCE
			//obj->payMaintenance(player);
			break;
		case 132: //SERVER_ITEM_OPTIONS
			break;
		case 133: //SERVER_SURVEY_TOOL_RANGE
			//sendRadialResponseForSurveyToolRange(player, obj);
			break;
		case 134: //SERVER_SURVEY_TOOL_RESOLUTION
		case 135: //SERVER_SURVEY_TOOL_CLASS
			break;
		case 136: //SERVER_PROBE_DROID_TRACK_TARGET
		case 137: //SERVER_PROBE_DROID_FIND_TARGET
		case 138: //SERVER_PROBE_DROID_ACTIVATE
		case 139: //SERVER_PROBE_DROID_BUY
			break;
		case 140: // SERVER_TEACH
			//player->sendTeachTo(obj);
			break;
		case 141: //PET_COMMAND
			break;
		case 142: //PET_FOLLOW
			//obj->commandFollow(player);
			break;
		case 143: //PET_STAY
			//obj->commandStay(player);
			break;
		case 144: //PET_GUARD
			//obj->commandGuard(player);
			break;
		case 145: //PET_FRIEND
			//obj->commandFriend(player);
			break;
		case 146: //PET_ATTACK
			//obj->commandAttack(player);
			break;
		case 147: //PET_PATROL
			//obj->commandPatrol(player);
			break;
		case 148: //PET_GET_PATROL_POINT
			//obj->commandGetPatrolPoints(player);
			break;
		case 149: //PET_CLEAR_PATROL_POINTS
			//obj->commandClearPatrolPoints(player);
			break;
		case 150: //PET_ASSUME_FORMATION_1
			//obj->commandAssumeFormation(player, 1);
			break;
		case 151: //PET_ASSUME_FORMATION_2
			//obj->commandAssumeFormation(player, 2);
			break;
		case 152: //PET_TRANSFER
			//obj->commandTransfer(player);
			break;
		case 153: //PET_RELEASE
			//obj->commandRelease(player);
			break;
		case 154: //PET_TRICK_1
			//obj->commandTrick(player, 1);
			break;
		case 155: //PET_TRICK_2
			//obj->commandTrick(player, 2);
			break;
		case 156: //PET_TRICK_3
			//obj->commandTrick(player, 3);
			break;
		case 157: //PET_TRICK_4
			//obj->commandTrick(player, 4);
			break;
		case 158: //PET_GROUP
			//obj->commandGroup(player);
			break;
		case 159: //PET_TAME
			//obj->commandTame(player);
			break;
		case 160: //PET_FEED
			//obj->commandFeed(player);
			break;
		case 161: //PET_SPECIAL_ATTACK_ONE
			//obj->commandSpecialAttack(player, 1);
			break;
		case 162: //PET_SPECIAL_ATTACK_TWO
			//obj->commandSpecialAttack(player, 2);
			break;
		case 163: //PET_RANGED_ATTACK
			//obj->commandRangedAttack(player);
			break;
		case 164: // ROLL_DICE (Configure)
			break;
		case 165: // DICE_TWO_FACE
			//obj->configure(player, 2);
			break;
		case 166: // DICE_THREE_FACE
			//obj->configure(player, 3);
			break;
		case 167: // DICE_FOUR_FACE
			//obj->configure(player, 4);
			break;
		case 168: // DICE_FIVE_FACE
			//obj->configure(player, 5);
			break;
		case 169: // DICE_SIX_FACE
			//obj->configure(player, 6);
			break;
		case 170: // DICE_SEVEN_FACE
			//obj->configure(player, 7);
			break;
		case 171: // DICE_EIGHT_FACE
			//obj->configure(player, 8);
			break;
		case 172: // DICE_COUNT_ONE
			//obj->setDiceCount(1);
			break;
		case 173: // DICE_COUNT_TWO
			//obj->setDiceCount(2);
			break;
		case 174: // DICE_COUNT_THREE
			//obj->setDiceCount(3);
			break;
		case 175: // DICE_COUNT_FOUR
			//obj->setDiceCount(4);
			break;
		case 176: //CREATE_BALLOT
		case 177: //VOTE
		case 178: //BOMBING_RUN
		case 179: //SELF_DESTRUCT
		case 180: //THIRTY_SEC
		case 181: //FIFTEEN_SEC
			break;
		case 182: //SERVER_CAMP_DISBAND
			//obj->disband(player);
			break;
		case 183: //SERVER_CAMP_ASSUME_OWNERSHIP
			//obj->transferOwnership(player);
			break;
		case 184: //SERVER_PROBE_DROID_PROGRAM
			break;
		case 185: //SERVER_GUILD_CREATE
			//obj->create(player);
			break;
		case 186: //SERVER_GUILD_INFO
			//obj->sendInfoTo(player);
			break;
		case 187: // SERVER_GUILD_MEMBERS
			//obj->sendMembersTo(player);
			break;
		case 188: //SERVER_GUILD_SPONSORED
			//obj->sendSponsoredListTo(player);
			break;
		case 189: //SERVER_GUILD_ENEMIES
			//obj->sendEnemiesListTo(player);
			break;
		case 190: //SERVER_GUILD_SPONSOR
			//obj->sendSponsorTo(player);
			break;
		case 191: //SERVER_GUILD_DISBAND
			//obj->disband(player);
			break;
		case 192: //SERVER_GUILD_NAMECHANGE
			//obj->sendCustomNamePromptTo(player);
			break;
		case 193: //SERVER_GUILD_GUILD_MANAGEMENT
			break;
		case 194: //SERVER_GUILD_MEMBER_MANAGEMENT
			//obj->sendMemberManagementTo(player);
			break;
		case 195: //SERVER_MANF_HOPPER_INPUT
			//obj->onRadialManufactureInputHopper(player);
			break;
		case 196: //SERVER_MANF_HOPPER_OUTPUT
			//obj->onRadialManufactureOutputHopper(player);
			break;
		case 197: //SERVER_MANF_STATION_SCHEMATIC
			//obj->onRadialManufactureSchematic(player);
			break;
		case 198: //ELEVATOR_UP
			//obj->up(player);
			break;
		case 199: //ELEVATOR_DOWN
			//obj->down(player);
			break;
		case 200: //SERVER_PET_OPEN
			//Must be for droids?
			//obj->petOpen(player);
			break;
		case 201: //SERVER_PET_DPAD
			//Must be for droids?
			//obj->petDpad(player);
			break;
		case 202: //SERVER_MED_TOOL_DIAGNOSE
			//player->diagnose(obj);
			break;
		case 203: //SERVER_MED_TOOL_TENDWOUND
			//player->tendWound(obj);
			break;
		case 204: //SERVER_MED_TOOL_TENDDAMAGE
			//player->tendDamage(obj);
			break;
		case 205: //SERVER_PET_MOUNT
			//obj->mount(player);
			break;
		case 206: //SERVER_PET_DISMOUNT
			//obj->dismount(player);
			break;
		case 207: //SERVER_PET_TRAIN_MOUNT
			//obj->trainMount(player);
			break;
		case 208: //SERVER_VEHICLE_ENTER
			//obj->enterVehicle(player);
			break;
		case 209: //SERVER_VEHICLE_EXIT
			//obj->exitVehicle(player);
			break;
		case 210: //OPEN_NAVICOMP_DPAD
		case 211: //INIT_NAVICOMP_DPAD
		case 212: //CITY_STATUS
		case 213: //CITY_CITIZENS
		case 214: //CITY_STRUCTURES
		case 215: //CITY_TREASURY
		case 216: //CITY_MANAGEMENT
		case 217: //CITY_NAME
		case 218: //CITY_MILITIA
		case 219: //CITY_TAXES
		case 220: //CITY_TREASURY_DEPOSIT
		case 221: //CITY_TREASURY_WITHDRAW
		case 222: //CITY_REGISTER
		case 223: //CITY_RANK
		case 224: //CITY_ADMIN_1
		case 225: //CITY_ADMIN_2
		case 226: //CITY_ADMIN_3
		case 227: //CITY_ADMIN_4
		case 228: //CITY_ADMIN_5
		case 229: //CITY_ADMIN_6
		case 230: //MEMORY_CHIP_PROGRAM
		case 231: //MEMORY_CHIP_TRANSFER
		case 232: //MEMORY_CHIP_ANALYZE
		case 233: //EQUIP_DROID_ON_SHIP
			break;
		default:
			//System::out << "Unknown radial selection received:" << radialID << "\n";
			break;
		}
	} catch (Exception& e) {
		System::out << e.getMessage();
		e.printStackTrace();
	} catch (...) {
		System::out << "unreported exception caught in void RadialManager::handleSelection\n";
		StackTrace::printStackTrace();
	}

	player->unlock();
}

ObjectMenuResponse* RadialManager::parseDefaults(PlayerObject* player, uint64 objectid, Packet* pack) {
	int size = pack->parseInt();
	ObjectMenuResponse* omr = new ObjectMenuResponse(player, objectid, 0);

	for (int i = 0; i < size; i++) {
		uint8 index = pack->parseByte();
		uint8 parentid = pack->parseByte();
		uint8 radialid = pack->parseByte();
		uint8 callback = pack->parseByte();

		//if (radialid == 20)
		callback = 3;

		pack->shiftOffset(4); // shift UnicodeString command

		omr->addRadialParent(radialid, callback, "");
	}

	//TODO: This may be uneeded...
	uint8 counter = pack->parseByte();
	omr->setCounter(counter);

	//Privileged players always have permission to pickup items.
	//Players can pickup items in buildings that they have admin rights on.
	//if (player->isInBuilding() || player->isPrivileged()) {
		//BuildingObject* building = (BuildingObject*) player->getBuilding();

		//if (player->isPrivileged() || (building != NULL && building->isOnAdminList(player)))
		//	omr->addRadialParent(10, 3, "@ui_radial:item_pickup");
	//}

	return omr;
}

void RadialManager::sendDefaultRadialResponse(PlayerObject* player, ObjectMenuResponse* omr) {
	omr->finish();

	player->sendMessage(omr);
}
