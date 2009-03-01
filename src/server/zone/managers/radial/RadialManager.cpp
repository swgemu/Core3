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
		case 41: //GROUP_DISBAND
		case 42: //GROUP_DECLINE
		case 43: //EXTRACT_OBJECT
		case 44: //PET_CALL
			break;
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
			handleSetName(player, obj);
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
			//player->storePet(obj);
			break;
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
			handleStructureAddEnergy(player, obj);
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
		case 88: //SERVER_HEAL_WOUND_HEALTH
		case 89: //SERVER_HEAL_WOUND_ACTION
		case 90: //SERVER_HEAL_WOUND_STRENGTH
		case 91: //SERVER_HEAL_WOUND_CONSTITUTION
		case 92: //SERVER_HEAL_WOUND_QUICKNESS
		case 93: //SERVER_HEAL_WOUND_STAMINA
		case 94: //SERVER_HEAL_DAMAGE
		case 95: //SERVER_HEAL_STATE
		case 96: //SERVER_HEAL_STATE_STUNNED
		case 97: //SERVER_HEAL_STATE_BLINDED
		case 98: //SERVER_HEAL_STATE_DIZZY
		case 99: //SERVER_HEAL_STATE_INTIMIDATED
		case 100: //SERVER_HEAL_ENHANCE
		case 101: //SERVER_HEAL_ENHANCE_HEALTH
		case 102: //SERVER_HEAL_ENHANCE_ACTION
		case 103: //SERVER_HEAL_ENHANCE_STRENGTH
		case 104: //SERVER_HEAL_ENHANCE_CONSTITUTION
		case 105: //SERVER_HEAL_ENHANCE_QUICKNESS
		case 106: //SERVER_HEAL_ENHANCE_STAMINA
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
			handleStructurePermissionList(player, obj, StructurePermissionList::ENTRYLIST);
			break;
		case 120: //SERVER_TERMINAL_PERMISSIONS_BANNED
			handleStructurePermissionList(player, obj, StructurePermissionList::BANLIST);
			break;
		case 121: //SERVER_TERMINAL_PERMISSIONS_ADMIN
			handleStructurePermissionList(player, obj, StructurePermissionList::ADMINLIST);
			break;
		case 122: //SERVER_TERMINAL_PERMISSIONS_VENDOR
			handleStructurePermissionList(player, obj, StructurePermissionList::VENDORLIST);
			break;
		case 123: //SERVER_TERMINAL_PERMISSIONS_HOPPER
			handleStructurePermissionList(player, obj, StructurePermissionList::HOPPERLIST);
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
		case 142: //PET_FOLLOW
		case 143: //PET_STAY
		case 144: //PET_GUARD
		case 145: //PET_FRIEND
		case 146: //PET_ATTACK
		case 147: //PET_PATROL
		case 148: //PET_GET_PATROL_POINT
		case 149: //PET_CLEAR_PATROL_POINTS
		case 150: //PET_ASSUME_FORMATION_1
		case 151: //PET_ASSUME_FORMATION_2
		case 152: //PET_TRANSFER
		case 153: //PET_RELEASE
		case 154: //PET_TRICK_1
		case 155: //PET_TRICK_2
		case 156: //PET_TRICK_3
		case 157: //PET_TRICK_4
		case 158: //PET_GROUP
		case 159: //PET_TAME
		case 160: //PET_FEED
		case 161: //PET_SPECIAL_ATTACK_ONE
		case 162: //PET_SPECIAL_ATTACK_TWO
		case 163: //PET_RANGED_ATTACK
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
		case 196: //SERVER_MANF_HOPPER_OUTPUT
		case 197: //SERVER_MANF_STATION_SCHEMATIC
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

		omr->addRadialItem(parentid, radialid, callback);
	}

	uint8 counter = pack->parseByte();
	omr->setCounter(counter);

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
		if (mount == NULL)
			return;

		if (!mount->isNonPlayerCreature())
			return;

		if (!((Creature*)mount)->isMount())
			return;

		try {
			mount->wlock();

			((MountCreature*)mount)->store();

			mount->unlock();
		} catch (...) {
			mount->unlock();
		}

		return;
	}

	if (!obj->isNonPlayerCreature())
		return;

	if (!((Creature*)obj)->isMount())
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

	if (mount == NULL)
		return;

	if (!mount->isNonPlayerCreature())
		return;

	if (!((Creature*)mount)->isMount())
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
			Player* target = (Player*)obj;

			StringBuffer msg;
			msg << player->getCharacterName().toString() << " requested a trade.";
			target->sendSystemMessage(msg.toString());
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

void RadialManager::handleManageHarvester(Player* player, SceneObject* obj) {
	try {
		if (!obj->isTangible())
			return;

		TangibleObject* tano = (TangibleObject*) obj;

		if (tano->getObjectSubType() != TangibleObjectImplementation::HARVESTER)
			return;

		InstallationObject* inso = (InstallationObject*) tano;

		// Update Hopper
		inso->updateHopper();

		ResourceHarvesterActivatePageMessage* rhapm = new ResourceHarvesterActivatePageMessage(obj->getObjectID());
		player->sendMessage(rhapm);
	}
	catch(...){
		System::out << "Unreported exception in RadialManager::handleManageHarvester\n";
	}
}



void RadialManager::handleStructureDestroy(Player* player, SceneObject* obj) {
	try{
		InstallationObject * inso = (InstallationObject *) obj;

		if (inso!= NULL)
			inso->handleStructureRedeed(player);
		/*else {
				BuildingObject * buio = (BuildingObject * ) obj;

				if (buio!= NULL)
					buio->undeploy();
			}
		}*/
	}
	catch(...){
		System::out << "Unreported exception in RadialManager::handleStructureDestroy\n";
	}
}

void RadialManager::handleStructureStatus(Player* player, SceneObject* obj) {
	try{
		if (obj != NULL && obj->isTangible() && ((TangibleObject*)obj)->isInstallation()) {
			InstallationObject * inso = (InstallationObject *) obj;

			inso->handleStructureStatus(player);
			/*else {
				BuildingObject * buio = (BuildingObject * ) obj;

				if (buio!= NULL)
					buio->handleStructureStatus(player);
				}
			}*/
		}
	}
	catch(...){
		System::out << "Unreported exception in RadialManager::handleStructureStatus\n";
	}
}

void RadialManager::handleSetName(Player* player, SceneObject* obj) {
	try{
		TangibleObject * tano = (TangibleObject*) obj;

		if (tano!= NULL)

			tano->setObjectName(player);

		/*else {
			BuildingObject * buio = (BuildingObject * ) obj;

			if (buio!= NULL)
				buio->setName(player);
		}
		*/

	}
	catch(...){
		System::out << "Unreported exception RadialManager::handleSetName\n";
	}
}

void RadialManager::handleStructureManageMaintenance(Player* player, SceneObject* obj) {
	try{
		if(!obj->isTangible())
			return;

		TangibleObject* tano = (TangibleObject*) obj;

		if(!tano->isInstallation())
			return;

		InstallationObject * inso = (InstallationObject*) tano;

		if (inso!= NULL)
			inso->handleStructureManageMaintenance(player);

		/*else {
			BuildingObject * buio = (BuildingObject * ) obj;

			if (buio!= NULL)
				buio->setName(player);
		}
		*/

	}
	catch(...){
		System::out << "Unreported exception in RadialManager::handleStructureManageMaintenance\n";
	}
}
void RadialManager::handleStructureAddEnergy(Player* player, SceneObject* obj) {
	try{
		if(!obj->isTangible())
			return;

		TangibleObject* tano = (TangibleObject*) obj;

		if(!tano->isInstallation())
			return;

		InstallationObject * inso = (InstallationObject*) tano;

		if (inso!= NULL)
			inso->handleStructureAddEnergy(player);

		/*else {
			BuildingObject * buio = (BuildingObject * ) obj;

			if (buio!= NULL)
				buio->setName(player);
		}
		*/

	}
	catch(...){
		System::out << "Unreported exception in RadialManager::handleStructureAddEnergy\n";
	}
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
	omr->addRadialItem(0, 136, 3, "@sui:tool_options");
	omr->addRadialItem(4, 137, 3, "@sui:survey_range");
	omr->finish();

	player->sendMessage(omr);
}

void RadialManager::sendRadialResponseForSurveyToolRange(Player* player, SceneObject* obj) {
	String skillBox = "crafting_artisan_novice";

	if (!player->hasSkillBox(skillBox)) {
		player->sendSystemMessage("error_message", "insufficient_skill");
		return;
	}

	String surveying = "surveying";

	int surveyMod = player->getSkillMod(surveying);

	SuiListBox* suiToolRangeBox = new SuiListBox(player, SuiWindowType::SURVEY_TOOL_RANGE);
	suiToolRangeBox->setPromptTitle("@base_player:swg");
	suiToolRangeBox->setPromptText("@survey:select_range");

	if (surveyMod >= 0)
		suiToolRangeBox->addMenuItem("64m x 3pts");

	if (surveyMod > 20)
		suiToolRangeBox->addMenuItem("128m x 4pts");

	if (surveyMod > 40)
		suiToolRangeBox->addMenuItem("192m x 4pts");

	if (surveyMod > 60)
		suiToolRangeBox->addMenuItem("256m x 5pts");

	if (surveyMod > 80)
		suiToolRangeBox->addMenuItem("320m x 5pts");

	player->addSuiBox(suiToolRangeBox);
	player->sendMessage(suiToolRangeBox->generateMessage());

	player->setSurveyTool((SurveyTool*) obj);
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
	suiInpBox->setCancelButton(true);
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
	suiInpBox->setCancelButton(true);
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
	suiInpBox->setCancelButton(true);
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
	camp->disbandCamp();

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
 * This method makes sure that the object used was in fact a player structure terminal, it then passes execution to the terminal.
 * \param player The player using the radial.
 * \param obj The object that the radial originated from.
 * \param listtype The type of the list, referencing StructurePermissionList
 */
void RadialManager::handleStructurePermissionList(Player* player, SceneObject* obj, uint8 listtype) {
	if (obj == NULL || !obj->isTangible() || !((TangibleObject*)obj)->isTerminal() || !((Terminal*)obj)->isPlayerStructureTerminal())
		return;

	PlayerStructureTerminal* terminal = (PlayerStructureTerminal*) obj;
	terminal->sendPermissionListTo(player, listtype);
}

void RadialManager::handleStructurePrivacy(Player* player, SceneObject* obj) {

}
void RadialManager::handleStructureTransferRequest(Player* player, SceneObject* obj) {

}
void RadialManager::handleStructureDeclareResidence(Player* player, SceneObject* obj) {

}
void RadialManager::handleStructurePayMaintenance(Player* player, SceneObject* obj) {

}
void RadialManager::handleStructureCreateVendor(Player* player, SceneObject* obj) {

}

void RadialManager::handleGiveVendorMaintenance(Player* player, SceneObject* obj) {

}
