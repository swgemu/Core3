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

#include "../../packets/object/ObjectMenuResponse.h"
#include "../../packets/trade/BeginTradeMessage.h"
#include "../../packets/installation/ResourceHarvesterActivatePageMessage.h"

#include "../../Zone.h"
#include "../../objects.h"

#include "../../objects/player/sui/listbox/SuiListBoxImplementation.h"
#include "../../objects/player/sui/colorpicker/SuiColorPickerImplementation.h"
#include "../../objects/player/sui/inputbox/SuiInputBoxImplementation.h"

#include "../bazaar/BazaarManager.h"
#include "../bazaar/BazaarManagerImplementation.h"
#include "../bank/BankManager.h"
#include "../bank/BankManagerImplementation.h"

#include "../guild/GuildManagerImplementation.h"

RadialManager::RadialManager() {
}

/**
 * This method is fired when the server receives a packet requesting radial options for an object.
 * In response, an ObjectMenuResponse packet is sent to the client, containing the radial options.
 * \param player The player that has requested the radial options.
 * \param pack The packet that was sent from the client to the server.
 */
void RadialManager::handleRadialRequest(Player* player, Packet* pack) {
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

	ManagedReference<SceneObject> object = zone->lookupObject(objectid);

	//System::out << "Radial Request ObjectID: " << dec << objectid << "\n";
	if (object == NULL)
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
	}
}

void RadialManager::handleRadialSelect(Player* player, Packet* pack) {
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

		//TODO: Get a bazaar object to pass to the next functions
		BazaarManager* bazaarManager = zone->getZoneServer()->getBazaarManager();

		if (bazaarManager->isBazaarTerminal(objectID)) {
			sendRadialResponseForBazaar(objectID, player);

			player->unlock();
			return;
		}

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
	}
}

void RadialManager::handleSelection(int radialID, Player* player, SceneObject* obj) {
	// Pre: player is wlocked, obj is unlocked
	// Post: player and obj unlocked


	//System::out << "Radial ID = " << dec << radialID << endl;
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
			handleTrade(player, obj);
			break;
		case 9: //TRADE_ACCEPT
			break;
		case 10: //ITEM_PICKUP
		case 11: //ITEM_EQUIP
			break;
		case 12: //ITEM_UNEQUIP
			break;
		case 13: //ITEM_DROP
			handleItemDrop(player, obj);
			break;
		case 14: //ITEM_DESTROY
			break;
		case 15: //ITEM_TOKEN
			break;
		case 16: //ITEM_OPEN
			break;
		case 17: //ITEM_OPEN_NEW_WINDOW
			break;
		case 18: //ITEM_ACTIVATE
		case 19: //ITEM_DEACTIVATE
			break;
		case 20: //ITEM_USE
			obj->useObject(player);
			break;
		case 21: //ITEM_USE_SELF
		case 22: //ITEM_USE_OTHER
		case 23: //ITEM_SIT
		case 24: //ITEM_MAIL
		case 25: //CONVERSE_START
		case 26: //CONVERSE_RESPOND
		case 27: //CONVERSE_RESPONSE
		case 28: //CONVERSE_STOP
			break;
		case 29: //CRAFT_OPTIONS
			break;
		case 30: //CRAFT_START
			break;
		case 31: //CRAFT_HOPPER_INPUT
			break;
		case 32: //CRAFT_HOPPER_OUTPUT
			handleOpenCraftingToolHopper(player, obj);
			break;
		case 33: //MISSION_TERMINAL_LIST
			break;
		case 34: //MISSION_DETAILS
			break;
		case 35: //LOOT
			player->lootCorpse();
			break;
		case 36: //LOOT_ALL
			player->lootCorpse(true);
			break;
		case 37: //GROUP_INVITE
			break;
		case 38: //GROUP_JOIN
		case 39: //GROUP_LEAVE
		case 40: //GROUP_KICK
			break;
		case 41: //GROUP_DISBAND
			break;
		case 42: //GROUP_DECLINE
		case 43: //EXTRACT_OBJECT
			break;
		case 44: //PET_CALL
			player->sendSystemMessage("Sorry, Creature Handler has been temporarily disabled.");
			break;

			//player->unlock();
			//handlePetCall(obj);
			return;
		case 45: //TERMINAL_AUCTION_USE
			sendRadialResponseForBazaar(obj->getObjectID(), player);
			break;
		case 46: //CREATURE_FOLLOW
		case 47: //CREATURE_STOP_FOLLOW
			break;
		case 48: //SPLIT
			break;
		case 49: //IMAGEDESIGN
			break;
		case 50: //SET_NAME
			handleSetObjectName(player, obj);
			break;
		case 51: //ITEM_ROTATE - MENU ROOT
			break;
		case 52: //ITEM_ROTATE_RIGHT
			//obj->rotate(right);
			break;
		case 53: //ITEM_ROTATE_LEFT
			//obj->rotate(left);
			break;
		case 54: //ITEM_MOVE - MENU ROOT
			break;
		case 55: //ITEM_MOVE_FORWARD
			//obj->move(forward, amount);
			break;
		case 56: //ITEM_MOVE_BACK
			//obj->move(back, amount);
			break;
		case 57: //ITEM_MOVE_UP
			//obj->move(up, amount);
			break;
		case 58: //ITEM_MOVE_DOWN
			//obj->move(down, amount);
			break;
		case 59: //PET_STORE
			player->sendSystemMessage("Sorry, Creature Handler has been temporarily disabled.");
			break;

			//player->unlock();
			//handlePetStore(obj);
			return;
		case 60: // VEHICLE_GENERATE
			player->unlock();
			handleVehicleGenerate(obj);
			return;
		case 61: // VEHICLE_STORE
			player->unlock();
			handleVehicleStore(obj);
			return;
		//case 62: //MISSION_ABORT
		case 62: // VEHICLE_REPAIR
			player->unlock();
			handleVehicleRepair(obj);
			return;
		case 63: //MISSION_END_DUTY
			break;
		case 64: //SHIP_MANAGE_COMPONENTS
		case 65: //WAYPOINT_AUTOPILOT
		case 66: //PROGRAM_DROID
		case 67: //SERVER_DIVIDER
			break;
		case 68: // SERVER_MENU1 TODO:using to change color on wearables (temporary)
			handleWearableColorChange(player, obj);
			break;
		//case 69: //SERVER_MENU2
		//case 70: //SERVER_MENU3
		//case 71: //SERVER_MENU4
		//case 72: //SERVER_MENU5
		//case 73: //SERVER_MENU6
		//case 74: //SERVER_MENU7
		//case 75: //SERVER_MENU8
		//case 76: //SERVER_MENU9
		//case 77: //SERVER_MENU10
		case 69: // SLICING
			handleSlicing(player, obj);
			break;
		case 70: // REPAIR
			handleRepair(player, obj);
			break;
		case 71: // REMOVE POWERUP
			handleRemovePowerup(player, obj);
			break;
		case 77: // Add Energy
			handleStructureDepositPower(player, obj);
			break;
		case 78: //SERVER_HARVESTER_MANAGE
			handleManageHarvester(player, obj);
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
			handleHealWound(player, obj);
			break;
		case 88: //SERVER_HEAL_WOUND_HEALTH
			handleHealWound(player, obj, CreatureAttribute::HEALTH);
			break;
		case 89: //SERVER_HEAL_WOUND_ACTION
			handleHealWound(player, obj, CreatureAttribute::ACTION);
			break;
		case 90: //SERVER_HEAL_WOUND_STRENGTH
			handleHealWound(player, obj, CreatureAttribute::STRENGTH);
			break;
		case 91: //SERVER_HEAL_WOUND_CONSTITUTION
			handleHealWound(player, obj, CreatureAttribute::CONSTITUTION);
			break;
		case 92: //SERVER_HEAL_WOUND_QUICKNESS
			handleHealWound(player, obj, CreatureAttribute::QUICKNESS);
			break;
		case 93: //SERVER_HEAL_WOUND_STAMINA
			handleHealWound(player, obj, CreatureAttribute::STAMINA);
			break;
		case 94: //SERVER_HEAL_DAMAGE
		case 95: //SERVER_HEAL_STATE
		case 96: //SERVER_HEAL_STATE_STUNNED
		case 97: //SERVER_HEAL_STATE_BLINDED
		case 98: //SERVER_HEAL_STATE_DIZZY
		case 99: //SERVER_HEAL_STATE_INTIMIDATED
		case 100: //SERVER_HEAL_ENHANCE
			handleHealEnhance(player, obj);
			break;
		case 101: //SERVER_HEAL_ENHANCE_HEALTH
			handleHealEnhance(player, obj, CreatureAttribute::HEALTH);
			break;
		case 102: //SERVER_HEAL_ENHANCE_ACTION
			handleHealEnhance(player, obj, CreatureAttribute::ACTION);
			break;
		case 103: //SERVER_HEAL_ENHANCE_STRENGTH
			handleHealEnhance(player, obj, CreatureAttribute::STRENGTH);
			break;
		case 104: //SERVER_HEAL_ENHANCE_CONSTITUTION
			handleHealEnhance(player, obj, CreatureAttribute::CONSTITUTION);
			break;
		case 105: //SERVER_HEAL_ENHANCE_QUICKNESS
			handleHealEnhance(player, obj, CreatureAttribute::QUICKNESS);
			break;
		case 106: //SERVER_HEAL_ENHANCE_STAMINA
			handleHealEnhance(player, obj, CreatureAttribute::STAMINA);
			break;
		case 107: //SERVER_HEAL_FIRSTAID
		case 108: //SERVER_HEAL_CURE_POISON
		case 109: //SERVER_HEAL_CURE_DISEASE
		case 110: //SERVER_HEAL_APPLY_POISON
		case 111: //SERVER_HEAL_APPLY_DISEASE
			break;
		case 112: //SERVER_HARVEST_CORPSE
			handleHarvest(player, obj, 0);
		case 113: //SERVER_PERFORMANCE_LISTEN
		case 114: //SERVER_PERFORMANCE_WATCH
		case 115: //SERVER_PERFORMANCE_LISTEN_STOP
		case 116: //SERVER_PERFORMANCE_WATCH_STOP
			handleEntertainerActions(player, obj);
			break;
		case 117: //SERVER_TERMINAL_PERMISSIONS
		case 118: //SERVER_TERMINAL_MANAGEMENT
			break;
		case 119: //SERVER_TERMINAL_PERMISSIONS_ENTER
			handleStructurePermissionList(player, obj, "ENTRY");
			break;
		case 120: //SERVER_TERMINAL_PERMISSIONS_BANNED
			handleStructurePermissionList(player, obj, "BAN");
			break;
		case 121: //SERVER_TERMINAL_PERMISSIONS_ADMIN
			handleStructurePermissionList(player, obj, "ADMIN");
			break;
		case 122: //SERVER_TERMINAL_PERMISSIONS_VENDOR
			handleStructurePermissionList(player, obj, "VENDOR");
			break;
		case 123: //SERVER_TERMINAL_PERMISSIONS_HOPPER
			handleStructurePermissionList(player, obj, "HOPPER");
			break;
		case 124: //SERVER_TERMINAL_MANAGEMENT_STATUS
			handleStructureStatus(player, obj);
			break;
		case 125: //SERVER_TERMINAL_MANAGEMENT_PRIVACY
			handleStructurePrivacy(player, obj);
			break;
		case 126: //SERVER_TERMINAL_MANAGEMENT_TRANSFER
			handleStructureTransferRequest(player, obj);
			break;
		case 127: //SERVER_TERMINAL_MANAGEMENT_RESIDENCE
			handleStructureDeclareResidence(player, obj);
			break;
		case 128: //SERVER_TERMINAL_MANAGEMENT_DESTROY
			handleStructureDestroy(player, obj);
			break;
		case 129: //SERVER_TERMINAL_MANAGEMENT_PAY
			handleStructurePayMaintenance(player, obj);
			break;
		case 130: //SERVER_TERMINAL_CREATE_VENDOR
			handleStructureCreateVendor(player, obj);
			break;
		case 131: //SERVER_GIVE_VENDOR_MAINTENANCE
			handleGiveVendorMaintenance(player, obj);
			break;
		case 132: //SERVER_ITEM_OPTIONS
			break;
		case 133: //SERVER_SURVEY_TOOL_RANGE
			sendRadialResponseForSurveyToolRange(player, obj);
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
			handleTeach(obj, player);
			break;
		case 141: //PET_COMMAND
			break;
		case 142: //PET_FOLLOW
			handlePetTraining(obj,PetCommandHelper::PETFOLLOW);
			break;
		case 143: //PET_STAY
			handlePetTraining(obj,PetCommandHelper::PETSTAY);
			break;
		case 144: //PET_GUARD
			handlePetTraining(obj,PetCommandHelper::PETGUARD);
			break;
		case 145: //PET_FRIEND
			handlePetTraining(obj,PetCommandHelper::PETFRIEND);
			break;
		case 146: //PET_ATTACK
			handlePetTraining(obj,PetCommandHelper::PETATTACK);
			break;
		case 147: //PET_PATROL
			handlePetTraining(obj,PetCommandHelper::PETPATROL);
			break;
		case 148: //PET_GET_PATROL_POINT
			handlePetTraining(obj,PetCommandHelper::PETPATROLPOINTADD);
			break;
		case 149: //PET_CLEAR_PATROL_POINTS
			handlePetTraining(obj,PetCommandHelper::PETPATROLPOINTCLEAR);
			break;
		case 150: //PET_ASSUME_FORMATION_1
			handlePetTraining(obj,PetCommandHelper::PETFORMATION1);
			break;
		case 151: //PET_ASSUME_FORMATION_2
			handlePetTraining(obj,PetCommandHelper::PETFORMATION2);
			break;
		case 152: //PET_TRANSFER
			handlePetTraining(obj,PetCommandHelper::PETTRANSFER);
			break;
		case 153: //PET_RELEASE
			handlePetTraining(obj,PetCommandHelper::PETRELEASE);
			break;
		case 154: //PET_TRICK_1
			handlePetTraining(obj,PetCommandHelper::PETTRICK1);
			break;
		case 155: //PET_TRICK_2
			handlePetTraining(obj,PetCommandHelper::PETTRICK2);
			break;
		case 156: //FOLLOW_OTHER
			handlePetTraining(obj,PetCommandHelper::PETFOLLOWOTHER);
			break;
		case 157: //TRAIN MOUNT
			handlePetTrainMount(obj);
			break;
		case 158: //PET_GROUP
			handlePetTraining(obj,PetCommandHelper::PETGROUP);
			break;
		case 159: //PET_TRANSFER
			handlePetTraining(obj,PetCommandHelper::PETTRANSFER);
			break;
		case 160: //PET_STORE
			handlePetTraining(obj,PetCommandHelper::PETSTORE);
			break;
		case 161: //PET_SPECIAL_ATTACK_ONE
			handlePetTraining(obj,PetCommandHelper::PETSPECIALATTACK1);
			break;
		case 162: //PET_SPECIAL_ATTACK_TWO
			handlePetTraining(obj,PetCommandHelper::PETSPECIALATTACK2);
			break;
		case 163: //PET_RANGED_ATTACK
			handlePetTraining(obj,PetCommandHelper::PETRANGEDATTACK);
			break;
		case 164: // ROLL_DICE (Configure)
			// nothing here, has sub-members
			break;
		case 165: // DICE_TWO_FACE
			handleDiceConfigure(player, obj, 2);
			break;
		case 166: // DICE_THREE_FACE
			handleDiceConfigure(player, obj, 3);
			break;
		case 167: // DICE_FOUR_FACE
			handleDiceConfigure(player, obj, 4);
			break;
		case 168: // DICE_FIVE_FACE
			handleDiceConfigure(player, obj, 5);
			break;
		case 169: // DICE_SIX_FACE
			handleDiceConfigure(player, obj, 6);
			break;
		case 170: // DICE_SEVEN_FACE
			handleDiceConfigure(player, obj, 7);
			break;
		case 171: // DICE_EIGHT_FACE
			handleDiceConfigure(player, obj, 8);
			break;
		case 172: // DICE_COUNT_ONE
			handleDiceRoll(player, obj, 1);
			break;
		case 173: // DICE_COUNT_TWO
			handleDiceRoll(player, obj, 2);
			break;
		case 174: // DICE_COUNT_THREE
			handleDiceRoll(player, obj, 3);
			break;
		case 175: // DICE_COUNT_FOUR
			handleDiceRoll(player, obj, 4);
			break;
		case 176: //CREATE_BALLOT
		case 177: //VOTE
		case 178: //BOMBING_RUN
		case 179: //SELF_DESTRUCT
		case 180: //THIRTY_SEC
		case 181: //FIFTEEN_SEC
		case 182: //SERVER_CAMP_DISBAND
			handleDisbandCamp(player,obj);
			break;
		case 183: //SERVER_CAMP_ASSUME_OWNERSHIP
		case 184: //SERVER_PROBE_DROID_PROGRAM
		case 185: //SERVER_GUILD_CREATE
			player->unlock();
			handleGuildCreationTag(player);
			return;
		case 186: //SERVER_GUILD_INFO
			player->unlock();
			handleGuildInformation(player);
			return;
		case 187: // SERVER_GUILD_MEMBERS
			player->unlock();
			handleGuildInformationMembers(player);
			return;
		case 188: //SERVER_GUILD_SPONSORED
			player->unlock();
			handleGuildSponsored(player);
			return;
		case 189: //SERVER_GUILD_ENEMIES
			player->unlock();
			return;
		case 190: //SERVER_GUILD_SPONSOR
			player->unlock();
			handleGuildSponsor(player);
			return;
		case 191: //SERVER_GUILD_DISBAND
			player->unlock();
			handleGuildDisband(player);
			return;
		case 192: //SERVER_GUILD_NAMECHANGE
			player->unlock();
			handleGuildNameChange(player);
			return;
		case 193: //SERVER_GUILD_GUILD_MANAGEMENT
		case 194: //SERVER_GUILD_MEMBER_MANAGEMENT
			break;
		case 195: //SERVER_MANF_HOPPER_INPUT
			handleViewFactoryInput(player, obj);
			break;
		case 196: //SERVER_MANF_HOPPER_OUTPUT
			handleViewFactoryOutput(player, obj);
			break;
		case 197: //SERVER_MANF_STATION_SCHEMATIC
			handleInsertFactorySchematic(player, obj);
			break;
		case 198: //ELEVATOR_UP
		case 199: //ELEVATOR_DOWN
		case 200: //SERVER_PET_OPEN
		case 201: //SERVER_PET_DPAD
		case 202: //SERVER_MED_TOOL_DIAGNOSE
		case 203: //SERVER_MED_TOOL_TENDWOUND
		case 204: //SERVER_MED_TOOL_TENDDAMAGE
		case 205: //SERVER_PET_MOUNT
		case 206: //SERVER_PET_DISMOUNT
		case 207: //SERVER_PET_TRAIN_MOUNT
		case 208: //SERVER_VEHICLE_ENTER
		case 209: //SERVER_VEHICLE_EXIT
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
		case 234: //HARVEST_MEAT
			handleHarvest(player, obj, 1);
			break;
		case 235: //HARVEST_HIDE
			handleHarvest(player, obj, 2);
			break;
		case 236: //HARVEST_BONE
			handleHarvest(player, obj, 3);
			break;
		case 240: //INSURE_ALL
			player->unlock();
			handleInsureAllItems(player, obj);
			return;
		case 245: //BANK_STORAGE
			handleBankStorage(player);
			break;
		case 246: //BANK_REGISTER
		case 247: //BANK_UNREGISTER
			break;
		case 250: // SERVER_GUILD_TOGGLE_ELECTIONS
			player->sendSystemMessage("This feature is not in yet. Thank you for choosing SWGEmu(c).");
			break;
		case 251: // SERVER_GUILD_TRANSFER_LEADERSHIP
			player->unlock();
			handleGuildTransferLeader(player);
			return;
		case 252: // CAMP_INFO
			player->unlock();
			handleCampInfo(player, obj);
			return;
		case 253: // FACTORY VIEW SCHEM INGREDIENTS
			handleViewFactoryIngredients(player, obj);
			break;
		case 254: // FACTORY ACTIVATE/DEACTIVATE
			handleFactoryRun(player, obj);
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

ObjectMenuResponse* RadialManager::parseDefaults(Player* player, uint64 objectid, Packet* pack) {
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
	if (player->isInBuilding() || player->isPrivileged()) {
		BuildingObject* building = (BuildingObject*) player->getBuilding();

		if (player->isPrivileged() || (building != NULL && building->isOnAdminList(player)))
			omr->addRadialParent(10, 3, "@ui_radial:item_pickup");
	}

	return omr;
}

void RadialManager::sendDefaultRadialResponse(Player* player, ObjectMenuResponse* omr) {
	omr->finish();

	player->sendMessage(omr);
}

void RadialManager::sendRadialResponseForBazaar(uint64 objectId, Player* player) {
	Zone* zone = player->getZone();

	BazaarManager* bazaarManager = zone->getZoneServer()->getBazaarManager();

	RegionBazaar* bazaar = bazaarManager->getBazaar(objectId);

	if (bazaar != NULL)
		bazaar->newBazaarRequest(objectId, player, player->getZoneID());
}

void RadialManager::handleVehicleStore(SceneObject* obj) {
	if (obj->isIntangible()) {
		SceneObject* mount = ((IntangibleObject*)obj)->getWorldObject();

		if (!mount->isNonPlayerCreature())
			return;

		if (!((CreatureObject*)mount)->isVehicle())
			return;

		try {
			mount->wlock();
			((MountCreature*)mount)->store();
			mount->unlock();
		} catch (...) {
			obj->unlock();
		}
		return;
	}

	if (!obj->isNonPlayerCreature())
		return;

	if (!((CreatureObject*)obj)->isVehicle())
		return;

	try {
		obj->wlock();
		((MountCreature*)obj)->store();
		obj->unlock();
	} catch (...) {
		System::out << "Unreported exception caught in RadialManager::handleVehicleStore(Player* player, SceneObject* obj)\n";
		obj->unlock();
	}
}

void RadialManager::handleVehicleGenerate(SceneObject* obj) {
	if (!obj->isIntangible())
		return;

	SceneObject* mount = ((IntangibleObject*)obj)->getWorldObject();

	if (!mount->isNonPlayerCreature())
		return;

	if (!((CreatureObject*)mount)->isMount())
		return;

	try {
		mount->wlock();
		((MountCreature*)mount)->call();
		mount->unlock();
	} catch (...) {
		System::out << "Unreported exception caught in RadialManager::handleVehicleGenerate\n";
		mount->unlock();
	}
}

void RadialManager::handleVehicleRepair(SceneObject* obj) {
	if (!obj->isNonPlayerCreature())
		return;

	if (!((Creature*)obj)->isMount())
		return;

	try {
		obj->wlock();

		((MountCreature*)obj)->repair();

		obj->unlock();

	} catch (...) {
		System::out << "Unreported exception caught in RadialManager::handleVehicleRepair(SceneObject* obj)\n";
		obj->unlock();
	}
}

void RadialManager::handleTrade(Player* player, SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* target = (Player*)obj;

	try {
		target->wlock(player);

		uint64 requestedID = target->getTradeRequestedPlayer();
		player->setTradeRequestedPlayer(obj->getObjectID());

		if (requestedID == player->getObjectID()) {
			BeginTradeMessage* msg = new BeginTradeMessage(target->getObjectID());
			player->sendMessage(msg);

			BeginTradeMessage* msg2 = new BeginTradeMessage(player->getObjectID());
			target->sendMessage(msg2);

		} else {
			Player* receiver = (Player*)obj;

			StfParameter* params = new StfParameter();
			params->addTU(player->getCharacterName().toString());

			receiver->sendSystemMessage("ui_trade", "requested_prose", params);

			delete params;
		}

		target->unlock();
	} catch (Exception& e) {
		target->unlock();
		System::out << e.getMessage() << "caught in RadialManager::handleTrade(Player* player, SceneObject* obj)\n";
	} catch (...) {
		target->unlock();
		System::out << "Unreported exception caught in RadialManager::handleTrade(Player* player, SceneObject* obj)\n";
	}
}

void RadialManager::handleWearableColorChange(Player* player, SceneObject* obj) {
	if (!obj->isTangible())
		return;

	if (player->getTradeSize() != 0)
		return;

	TangibleObject* tano = (TangibleObject*) obj;

	if (!tano->isArmor())
		return;

	Armor* wearable = (Armor*) tano;

	if (player->getInventoryItem(wearable->getObjectID()) == NULL)
		return;

	SuiColorPicker* sui = new SuiColorPicker(player, wearable->getObjectID(), SuiWindowType::COLOR_PICKER2);

	player->addSuiBox(sui);
	player->sendMessage(sui->generateMessage());
}

void RadialManager::handleSetObjectName(Player* player, SceneObject* obj) {
	if (obj != NULL)
		obj->sendCustomNamePromptTo(player);
}

void RadialManager::handleSlicing(Player* player, SceneObject* obj) {
	if (!obj->isTangible())
		return;

	if (player->getTradeSize() != 0)
		return;

	TangibleObject* tano = (TangibleObject*) obj;

	if (!tano->isSlicable())
		return;

	if (tano->isSliced()) {
		player->sendSystemMessage("slicing/slicing", "already_sliced"); //That item has already been sliced.
		return;
	}

	if (tano->isBeingSliced()) {
		if (tano->getSlicerID() == player->getObjectID())
			player->sendSystemMessage("slicing/slicing", "already_being_sliced"); //That item is already being sliced.
		else
			player->sendSystemMessage("slicing/slicing", "slicing_underway"); //Someone is already slicing that device.

		return;
	}

	player->sendSlicingMenu(tano);
}

void RadialManager::handleRepair(Player* player, SceneObject* obj) {
	if (!obj->isTangible())
		return;

	if (player->getTradeSize() != 0)
		return;

	TangibleObject* tano = (TangibleObject*) obj;

	try {
		tano->wlock();

		tano->repairItem(player);

		tano->unlock();
	} catch (...) {
		System::out << "unreported exception caught in RadialManager::handleRepair\n";
		tano->unlock();
	}
}

void RadialManager::handleRemovePowerup(Player* player, SceneObject* obj) {
	if (obj == NULL || !obj->isTangible())
		return;

	if (player->getTradeSize() != 0)
		return;

	TangibleObject* tano = (TangibleObject*) obj;

	if (!tano->isWeapon())
		return;

	Weapon* weapon = (Weapon*) tano;

	try {
		weapon->wlock();

		if (weapon->hasPowerup())
			weapon->removePowerup(player, false);

		weapon->unlock();
	} catch (...) {
		System::out << "unreported exception caught in RadialManager::handleRemovePowerup\n";
		weapon->unlock();
	}
}


void RadialManager::sendRadialResponseForSurveyTools(Player* player, SurveyTool* surveyTool, ObjectMenuResponse* omr) {
	RadialMenuParent* toolOptions = new RadialMenuParent(136, 3, "@sui:tool_options");

	toolOptions->addRadialMenuItem(137, 3, "@sui:survey_range");
	omr->addRadialParent(toolOptions);

	omr->finish();
	player->sendMessage(omr);
}

void RadialManager::sendRadialResponseForSurveyToolRange(Player* player, SceneObject* obj) {
	if(obj->isTangible()) {

		TangibleObject* tano = (TangibleObject*) obj;

		if(tano->isSurveyTool())
			((SurveyTool*)tano)->setRangeFromRadial(player);
	}
}

void RadialManager::handleOpenCraftingToolHopper(Player* player, SceneObject* obj) {
	if (obj == NULL || !obj->isTangible())
		return;

	TangibleObject* tano = (TangibleObject*)obj;

	if (!tano->isCraftingTool())
		return;

	CraftingTool* craftingTool = (CraftingTool*) tano;

	try {
		craftingTool->wlock();

		craftingTool->retriveHopperItem(player);

		craftingTool->unlock();
	} catch (...) {
		System::out << "unreported exception caught in RadialManager::handleOpenCraftingToolHopper\n";
		craftingTool->unlock();
	}
}

void RadialManager::handleHarvest(Player* player, SceneObject* obj, int type) {
	if (obj == NULL)
		return;

	if (!obj->isNonPlayerCreature())
		return;

	Creature* creature = (Creature*)obj;

	ResourceManager* resourceManager = player->getZone()->getZoneServer()->getResourceManager();

	if (resourceManager == NULL)
		return;

	resourceManager->harvestOrganics(player, creature, type);
}

void RadialManager::handleGuildCreationTag(Player* player) {
	if (player->hasSuiBoxWindowType(SuiWindowType::GUILD_CREATION_INPUT_FOR_TAG) || player->hasSuiBoxWindowType(SuiWindowType::GUILD_CREATION_INPUT_FOR_NAME))
		return;

	player->setInputBoxReturnBuffer("");

	SuiInputBox* suiInpBox = new SuiInputBox(player, SuiWindowType::GUILD_CREATION_INPUT_FOR_TAG, 0);

	suiInpBox->setPromptTitle("@guild:create_abbrev_title");
	suiInpBox->setPromptText("@guild:create_abbrev_prompt");
	suiInpBox->setCancelButton(true, "");
	suiInpBox->setMaxInputSize(5);

	player->addSuiBox(suiInpBox);
	player->sendMessage(suiInpBox->generateMessage());

}

void RadialManager::handleGuildSponsor(Player* player) {
	if (player->hasSuiBoxWindowType(SuiWindowType::GUILD_SPONSORING_MEMBER_INPUT_FOR_NAME))
		return;

	if ( ! ( ( player->getGuildPermissions() ) & (PlayerImplementation::GUILDSPONSOR) ) ) {
		player->sendSystemMessage("@guild:generic_fail_no_permission");
		return;
	}

	player->setInputBoxReturnBuffer("");

	SuiInputBox* suiInpBox = new SuiInputBox(player, SuiWindowType::GUILD_SPONSORING_MEMBER_INPUT_FOR_NAME, 0);

	suiInpBox->setPromptTitle("@guild:sponsor_title");
	suiInpBox->setPromptText("@guild:sponsor_prompt");
	suiInpBox->setCancelButton(true, "");
	suiInpBox->setMaxInputSize(25);

	player->addSuiBox(suiInpBox);
	player->sendMessage(suiInpBox->generateMessage());
}

void RadialManager::handleGuildSponsored(Player* player) {

	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	GuildManager* gm = zone->getZoneServer()->getGuildManager();

	if (gm == NULL)
		return;

	gm->handleGuildSponsoring(player);
}

void RadialManager::handleGuildInformation(Player* player) {

	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	GuildManager* gm = zone->getZoneServer()->getGuildManager();
	if (gm == NULL)
		return;

	gm->handleGuildInfo(player);
}

void RadialManager::handleGuildDisband(Player* player) {

	if ( ! ( ( player->getGuildPermissions() ) & (PlayerImplementation::GUILDDISBAND) ) ) {
		player->sendSystemMessage("@guild:generic_fail_no_permission");
		return;
	}

	SuiInputBox* suiInpBox = new SuiInputBox(player, SuiWindowType::GUILD_DISBAND, 0);

	StringBuffer prompt;
	prompt << "@guild:disband_prompt " << endl << endl << "To confirm the disbanding of your guild, "
	<< "please type the following in the area below, then press Ok:" << endl << endl << "disband guild" << endl;

	suiInpBox->setPromptTitle("@guild:disband_title");
	suiInpBox->setPromptText(prompt.toString());
	suiInpBox->setCancelButton(true, "");
	suiInpBox->setMaxInputSize(15);

	player->addSuiBox(suiInpBox);
	player->sendMessage(suiInpBox->generateMessage());
}

void RadialManager::handleGuildNameChange(Player* player) {

	if ( ! ( ( player->getGuildPermissions() ) & (PlayerImplementation::GUILDCHANGENAME) ) ) {
		player->sendSystemMessage("@guild:generic_fail_no_permission");
		return;
	}

	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	GuildManager* gm = zone->getZoneServer()->getGuildManager();

	if (gm == NULL)
		return;

	gm->handleGuildRenaming(player);

}

void RadialManager::handleGuildInformationMembers(Player* player) {
	Zone* zone = player->getZone();

	if (zone == NULL)
		return;

	GuildManager* pGuild = zone->getZoneServer()->getGuildManager();

	if (pGuild == NULL)
		return;

	pGuild->handleGuildInformationMembers(player);
}

void RadialManager::handleGuildTransferLeader(Player* player) {
	Zone* zone = player->getZone();

	if (zone == NULL)
		return;

	GuildManager* pGuild = zone->getZoneServer()->getGuildManager();

	if (pGuild == NULL)
		return;

	pGuild->handleGuildTransferLeader(player);

}

void RadialManager::handleEntertainerActions(Player* player, SceneObject* obj) {
	//i am not sure, but i don't think OBJ can be anything else then a player?
	if (!obj->isPlayer())
		return;

	Player* target = (Player*)obj;

	try {

		target->wlock(player);

		//we need to request the getter's with the just applied cross lock
		//because startWatch/listen and stopWatch/listen are cross-locking on their own (->deadlock)

		bool dancing = target->isDancing();
		bool noising = target->isPlayingMusic();
		uint64 targetID = target->getObjectID();

		target->unlock();


		if (dancing) {
			if (!player->isWatching())
				player->startWatch(targetID);
			else
				player->stopWatch(player->getWatchID());

			return;
		}

		if (noising) {
			if (!player->isListening())
				player->startListen(targetID);
			else
				player->stopListen(player->getListenID());

			return;
		}

	} catch (...) {
		target->unlock();

		return;
	}
}

void RadialManager::handleDiceRoll(Player* player, SceneObject* obj, int dnum) {
    if (!obj->isTangible())
        return;

    TangibleObject* tano = (TangibleObject*) obj;

    if (tano->isGenericItem()) {
        GenericItem* geni = (GenericItem*) tano;
        if (geni->isDice()) {
	        Dice* dice = (Dice*) geni;
	        dice->rollDice(player, dnum);
        }
    }
}

void RadialManager::handleDiceConfigure(Player* player, SceneObject* obj, int dsides) {
    if (!obj->isTangible())
        return;

    TangibleObject* tano = (TangibleObject*) obj;

    if (tano->isGenericItem()) {
	    GenericItem* geni = (GenericItem*) tano;
        if (geni->isDice()) {
		    Dice* dice = (Dice*) geni;
            dice->setConfigurableDice(dsides);
        }
    }
}


void RadialManager::handleItemDrop(Player* player, SceneObject* obj) {
	//Leave in plz, i still need it
}

void RadialManager::handleTeach(SceneObject* obj, Player* trainer) {
	if (obj == NULL) {
		trainer->sendSystemMessage("teaching","no_target");
		return;
	} else if (!obj->isPlayer()) {
		trainer->sendSystemMessage("teaching","no_target");
		return;
	}

	Player* trainee = (Player*)obj;

	StfParameter *params = new StfParameter();
	params->addTT(trainee->getFirstNameProper());

	if (trainer == trainee) {
		trainer->sendSystemMessage("teaching","no_teach_self");
		delete params;
		return;
	} else if (trainee->isDead() || trainee->isIncapacitated()) {
		trainer->sendSystemMessage("teaching","student_dead",params);
		delete params;
		return;
	} else if (!trainer->isInRange(trainee, 128)) {
		trainer->sendSystemMessage("teaching","student_too_far_target",params);
		delete params;
		return;
	} else if (!trainer->isInAGroup() || !trainee->isInAGroup() || (trainer->getGroupObject() != trainee->getGroupObject())) {
		trainer->sendSystemMessage("teaching","not_in_same_group");
		delete params;
		return;
	}  else if (trainee->getTeacher() != NULL) {
		trainer->sendSystemMessage("teaching","student_has_offer_to_learn",params);
		delete params;
		return;
	}

	delete params;

	trainer->teachPlayer(trainee);
}

void RadialManager::handleDisbandCamp(Player* player,SceneObject* obj) {
	if (!obj->isTangible())
		return;
	CampTerminal* terminal = (CampTerminal*) obj;
	CampSite* camp = terminal->getCampSite();

	if (camp != NULL)
		camp->disbandCamp();

}

void RadialManager::handleCampInfo(Player* player,SceneObject* obj) {
	if (!obj->isTangible())
		return;
	CampTerminal* terminal = (CampTerminal*) obj;
	CampSite* camp = terminal->getCampSite();
	camp->sendCampInfo(player);

}


void RadialManager::handleInsureAllItems(Player* player, SceneObject* obj) {
	if (obj->isTangible()) {
		TangibleObject* tangibleObj = (TangibleObject*) obj;
		if (tangibleObj->isTerminal()) {
			Terminal* terminal = (Terminal*) tangibleObj;
			if (terminal->isInsuranceTerminal()) {
				InsuranceTerminal* insterm = (InsuranceTerminal*) terminal;
				player->sendItemInsureAllConfirm(insterm);
				return;
			}
		}
	}

	player->sendSystemMessage("The insurance terminal used was invalid.");
}

void RadialManager::handleBankStorage(Player* player) {
	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	BankManager* bankmanager = zone->getZoneServer()->getBankManager();
	if (bankmanager == NULL)
		return;

	bankmanager->handleBankStorage(player);
}





/**
 * Sends the manage harvester screen to the player and sets them as an operator.
 * \param player Player to manager harvester.
 * \param obj The harvester that was used to summon the radial.
 */
void RadialManager::handleManageHarvester(Player* player, SceneObject* obj) {
	if (obj != NULL && obj->isTangible() && ((TangibleObject*)obj)->isInstallation()) {
		InstallationObject* installation = (InstallationObject*) obj;

		if (installation->isHarvester() || installation->isGenerator()) {
			//TODO: Handle manage harvester screen.
			ResourceHarvesterActivatePageMessage* rhapm = new ResourceHarvesterActivatePageMessage(installation->getObjectID());
			player->sendMessage(rhapm);
		}
	}
}


/**
 * This method makes sure that the object used was in fact a player structure terminal, it then passes execution to the terminal.
 * \param player The player using the radial.
 * \param obj The object that the radial originated from.
 * \param listtype The type of the list, referencing StructurePermissionList
 */
void RadialManager::handleStructurePermissionList(Player* player, SceneObject* obj, const String& listname) {
	if (obj == NULL || !obj->isTangible())
		return;

	TangibleObject* tangible = (TangibleObject*) obj;

	if (tangible->isTerminal() && ((Terminal*) tangible)->isPlayerStructureTerminal()) {
		PlayerStructureTerminal* terminal = (PlayerStructureTerminal*) obj;
		terminal->sendPermissionListTo(player, listname);
	} else if (tangible->isInstallation()) {
		InstallationObject* installation = (InstallationObject*) tangible;
		installation->sendPermissionListTo(player, listname);
	}
}

/**
 * Starts the structures destroy process.
 * \param player The player requesting that the structure be destroyed.
 * \param obj The terminal used to invoke structure destruction.
 */
void RadialManager::handleStructureDestroy(Player* player, SceneObject* obj) {
	if (obj != NULL) {
		if (obj->isTangible() && ((TangibleObject*)obj)->isInstallation())
			((InstallationObject*)obj)->sendConfirmDestroyTo(player);
		else if (obj->isBuilding())
			((BuildingObject*)obj)->sendConfirmDestroyTo(player);
	}
}

/**
 * Sends the interface for depositing power to the player.
 * \param player The player whom has requested the power deposit interface.
 * \param obj The installation used to invoke the command.
 */
void RadialManager::handleStructureDepositPower(Player* player, SceneObject* obj) {
	if (obj->isTangible() && ((TangibleObject*)obj)->isInstallation()) {
		InstallationObject* installation = (InstallationObject*) obj;

		if (installation->isOnAdminList(player))
			installation->sendManagePowerTo(player);
		else
			player->sendSystemMessage("@player_structure:not_admin"); //You must be an admin to do that.
	}
}

/**
 * Toggles the privacy mode for the structure.
 * \param player The player setting the privacy.
 * \param obj The terminal being used to toggle the privacy?
 */
void RadialManager::handleStructurePrivacy(Player* player, SceneObject* obj) {

}

void RadialManager::handleStructureStatus(Player* player, SceneObject* obj) {
	if (obj->isTangible() && ((TangibleObject*)obj)->isInstallation()) {
		InstallationObject* installation = (InstallationObject*) obj;

		if (installation->isOnAdminList(player))
			installation->sendStatusTo(player);
		else
			player->sendSystemMessage("@player_structure:not_admin"); //You must be an admin to do that.
	} else if (obj->isBuilding()) {
		BuildingObject* building = (BuildingObject*) obj;

		//if (building->isOnEntryList(player))
		//	building->sendStatusTo(player);
	}
}

/**
 * Attempts to transfer a structure to another player. The target should be player's target.
 * \param player The player that is transfering the structure.
 * \param obj The terminal that was used to transfer the structure?
 */
void RadialManager::handleStructureTransferRequest(Player* player, SceneObject* obj) {

}

/**
 * Declares residence at the structure
 * \param player The player that is attempting to declare residence.
 * \param obj The playerstructureterminal that was used to declare with.
 */
void RadialManager::handleStructureDeclareResidence(Player* player, SceneObject* obj) {

}

/**
 * Pays maintenance to a structure
 * \param player The player that is paying the maintenance
 * \param obj The terminal that was summoned to pay maintenance with.
 */
void RadialManager::handleStructurePayMaintenance(Player* player, SceneObject* obj) {
	if (obj->isTangible() && ((TangibleObject*)obj)->isInstallation()) {
		InstallationObject* installation = (InstallationObject*) obj;

		if (installation->isOnAdminList(player))
			installation->sendManageMaintenanceTo(player);
		else
			player->sendSystemMessage("@player_structure:not_admin"); //You must be an admin to do that.
	} else if (obj->isBuilding()) {
		BuildingObject* building = (BuildingObject*) obj;

		//if (building->isOnAdminList(player))
		//	building->sendManageMaintenanceTo(player);
	}
}

/**
 * Creates a new vendor from a player structure terminal. Player must be on the Vendor List
 * \param player The player that is attempting to create the vendor.
 * \param obj The terminal that is being used to create the vendor.
 */
void RadialManager::handleStructureCreateVendor(Player* player, SceneObject* obj) {

}

/**
 * Gives a vendor maintenance
 * \param player The player that is giving the maintenance.
 * \param obj The vendor that is receiving the maintenance.
 */
void RadialManager::handleGiveVendorMaintenance(Player* player, SceneObject* obj) {

}


//Healing
/**
 * Enhances the specified attribute of the object passed in.
 * \param player The player that is doing the enhancing.
 * \param obj The target of the enhancement.
 * \param attribute Which attribute should be enhanced? Defaults to unknown which will result in the first sequential available attribute.
 */
void RadialManager::handleHealEnhance(Player* player, SceneObject* obj, uint8 attribute) {
	//if (!obj->isPlayer() || !obj->isNonPlayerCreature())
	//	return;

	if (attribute == 9)
		attribute = CreatureAttribute::HEALTH;

	uint32 actionCRC = 0xEEE029CF; //healenhance
	String actionModifier = CreatureAttribute::getName(attribute);
	player->setActionCounter(player->getActionCounter() + 1);
	player->queueAction(player, obj->getObjectID(), actionCRC, player->getActionCounter(), actionModifier.toCharArray());
}

/**
 * Heals a wound of a specified attribute on the object passed.
 * \param player The player that is doing the wound healing.
 * \param obj The wounded player that is receiving the healing.
 * \param attribute The attribute that is being healed. Defaults to unknown which will result in the first sequential available attribute.
 */
void RadialManager::handleHealWound(Player* player, SceneObject* obj, uint8 attribute) {
	//if (!obj->isPlayer() || !obj->isNonPlayerCreature())
	//	return;

	CreatureObject* creature = (CreatureObject*) obj;

	if (attribute == 9)
		attribute = creature->getNextWoundedAttribute(true, true, false);

	uint32 actionCRC = 0x2087CE04; //healwound
	String actionModifier = CreatureAttribute::getName(attribute);
	player->setActionCounter(player->getActionCounter() + 1);
	player->queueAction(player, obj->getObjectID(), actionCRC, player->getActionCounter(), actionModifier.toCharArray());
}

void RadialManager::handleInsertFactorySchematic(Player* player, SceneObject* obj){

	if(!obj->isTangible())
		return;

	TangibleObject* tano = (TangibleObject*) obj;

	if(!tano->isInstallation())
		return;

	InstallationObject* inst = (InstallationObject*) obj;
	if(!inst->isFactory())
		return;

	FactoryObject* fact = (FactoryObject*) obj;

	//fact->sendInsertManSchemTo(player);
}
void RadialManager::handleViewFactoryIngredients(Player* player, SceneObject* obj){

	if(!obj->isTangible())
		return;

	TangibleObject* tano = (TangibleObject*) obj;

	if(!tano->isInstallation())
			return;

	InstallationObject* inst = (InstallationObject*) obj;
	if(!inst->isFactory())
		return;

	FactoryObject* fact = (FactoryObject*) obj;

	//fact->sendViewIngredientsTo(player);
}
void RadialManager::handleViewFactoryInput(Player* player, SceneObject* obj){
	//open an inventory window with the factory input container
	//Zone* zone = player->getZone();

	if(!obj->isTangible())
		return;

	TangibleObject* tano = (TangibleObject*) obj;

	if(!tano->isInstallation())
		return;

	InstallationObject* inst = (InstallationObject*) obj;
	if(!inst->isFactory())
		return;

	FactoryObject* fact = (FactoryObject*) obj;

	if(fact->isOwner(player->getCharacterID())) {
		//fact->sendInputHopperTo(player);
	}
}
void RadialManager::handleViewFactoryOutput(Player* player, SceneObject* obj){
	//open an inventory window with the factory output container
	//Zone* zone = player->getZone();

	if(!obj->isTangible())
		return;

	TangibleObject* tano = (TangibleObject*) obj;

	if(!tano->isInstallation())
		return;

	InstallationObject* inst = (InstallationObject*) obj;
	if(!inst->isFactory())
		return;

	FactoryObject* fact = (FactoryObject*) obj;

	if(fact->isOwner(player->getCharacterID())) {
		//fact->sendOutputHopperTo(player);
	}
}
void RadialManager::handleFactoryRun(Player* player, SceneObject* obj){
	//if factory is on, turn it off
	//else turn it on
	if(!obj->isTangible())
		return;

	TangibleObject* tano = (TangibleObject*) obj;

	if(!tano->isInstallation())
		return;

	InstallationObject* inst = (InstallationObject*) obj;
	if(!inst->isFactory())
		return;

	FactoryObject* fact = (FactoryObject*) obj;

	if(fact->isOperating())
		fact->setOperating(false);
	else
		fact->setOperating(true);
}


void RadialManager::handlePetCall(SceneObject* obj) {
	if (!obj->isIntangible())
		return;

	SceneObject* pet = ((IntangibleObject*)obj)->getWorldObject();

	if (pet == NULL)
		return;

	if (!pet->isNonPlayerCreature())
		return;

	try {
		pet->wlock();
		((CreaturePet*)pet)->call();
		pet->unlock();
	} catch (...) {
		System::out << "Unreported exception caught in RadialManager::handlePetCall\n";
		pet->unlock();
	}
}

void RadialManager::handlePetStore(SceneObject* obj) {
	if (obj->isIntangible()) {

		SceneObject* pet = ((IntangibleObject*)obj)->getWorldObject();

		if (pet == NULL)
			return;

		if (!pet->isNonPlayerCreature())
			return;


		try {
			pet->wlock();
			((CreaturePet*)pet)->store();
			pet->unlock();
		} catch (...) {
			System::out << "Unreported exception caught in RadialManager::handlePetStore\n";
			pet->unlock();
		}

		return;
	}
	if (!obj->isNonPlayerCreature())
		return;
	if (!((CreatureObject*)obj)->isPet())
		return;
	try {
		obj->wlock();
		((CreaturePet*)obj)->store();
		obj->unlock();
	} catch (...) {
		System::out << "Unreported exception caught in RadialManager::handleVehicleStore(Player* player, SceneObject* obj)\n";
		obj->unlock();
	}
}

void RadialManager::handlePetTraining(SceneObject* obj,int command) {
	if (!obj->isNonPlayerCreature())
			return;

		if (!((CreatureObject*)obj)->isPet())
			return;

		try {
			obj->wlock();
			((CreaturePet*)obj)->initTrainingState(command);
			obj->unlock();
		} catch (...) {
			System::out << "Unreported exception caught in RadialManager::handleVehicleStore(Player* player, SceneObject* obj)\n";
			obj->unlock();
		}
}
void RadialManager::handlePetTrainMount(SceneObject* obj) {
	if (!obj->isNonPlayerCreature())
			return;

		if (!((CreatureObject*)obj)->isPet())
			return;

		try {
			obj->wlock();
			((CreaturePet*)obj)->trainMount();
			((CreaturePet*)obj)->getDatapadItem()->setUpdated(true);
			obj->unlock();
		} catch (...) {
			System::out << "Unreported exception caught in RadialManager::handleVehicleStore(Player* player, SceneObject* obj)\n";
			obj->unlock();
		}
}
