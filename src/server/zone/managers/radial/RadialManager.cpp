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

#include "../../Zone.h"
#include "../../objects.h"

#include "../bazaar/BazaarManager.h"
#include "../bazaar/BazaarManagerImplementation.h"

RadialManager::RadialManager() {
}

void RadialManager::handleRadialRequest(Player* player, Packet* pack) {
	pack->shiftOffset(12); // skip ObjectID and size

	uint64 objectid = pack->parseLong();
	uint64 playerid = pack->parseLong();
		
	ObjectMenuResponse* omr;
	omr = parseDefaults(player, objectid, pack);
	
	Zone* zone = player->getZone();
	if (zone == NULL)
		return;
	
	SceneObject* object = zone->lookupObject(objectid); 
	
	if (object == NULL) {
		object = player->getInventoryItem(objectid);
		if (object == NULL)
			object = player->getDatapadItem(objectid);
	}
	
	if (object == NULL) {
		sendDefaultRadialResponse(player, omr);
		return;
	}
	
	switch (object->getObjectType()) {
	case SceneObjectImplementation::NONPLAYERCREATURE:
		Creature* creature = (Creature*)object;
		
		if (creature->isMount() && (player->getMount() == (MountCreature*)creature)) {
			sendRadialResponseForMounts(player, (MountCreature*)creature, omr);
			return;
		}
		
		break;
	case SceneObjectImplementation::TANGIBLE:
		TangibleObject* tano = (TangibleObject*) object;
		
		switch (tano->getObjectSubType()) {
		case TangibleObjectImplementation::TERMINAL:
			Terminal* terminal = (Terminal*) tano;
			
			switch (terminal->getTerminalType()) {
			case TerminalImplementation::GUILD:
				GuildTerminal* guildTerminal = (GuildTerminal*) terminal;
				sendRadialResponseForGuildTerminals(player, guildTerminal, omr);
				return;
			}
			break;		
		case TangibleObjectImplementation::SURVEYTOOL:
			SurveyTool* surveyTool = (SurveyTool*) tano;
			sendRadialResponseForSurveyTools(player, surveyTool, omr);
			return;
		}
		break;
	}
	
	sendDefaultRadialResponse(player, omr);
}

void RadialManager::handleRadialSelect(Player* player, Packet* pack) {
    SceneObject* obj = NULL;
        
	try {
		player->wlock();

		uint64 objectID = pack->parseLong();
		uint8 radialID = pack->parseByte();
		
		Zone* zone = player->getZone();
		if (zone == NULL) {
			player->unlock();
			return;
		}

		obj = zone->lookupObject(objectID);
		
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

		handleSelection(radialID, player, obj);
		
	} catch (...) {
		cout << "unreported exception on ZonePacketHandler:::handleUseItem(Message* pack)\n";
		player->unlock();
	}
}

void RadialManager::handleSelection(int radialID, Player* player, SceneObject* obj) {
	// Pre: player is wlocked, obj is unlocked
	// Post: player and obj unlocked
	
	switch (radialID) {
	case 7: // EXAMINE
		break;
	case 8: // TRADE
		handleTrade(player, obj);
		break;
	case 14: // DESTROY
		break;
	case 20: // ITEM_USE
		obj->useObject(player);
		break;
	case 35:  // LOOT 
		player->lootCorpse(); 
		break; 
	case 36:  // LOOT_ALL 
		player->lootCorpse(); 
		break; 
	case 45: // Open vendor
		sendRadialResponseForBazaar(obj->getObjectID(), player);
		break;
	case 60: // VEHICLE_GENERATE
		player->unlock();
		
		handleVehicleGenerate(obj);
		return;
	case 61: // VEHICLE_STORE
		player->unlock();
		
		handleVehicleStore(obj);
		return;
	case 136: // SURVEY_TOOL_OPTIONS
		break;
	case 137: // SURVEY_TOOL_SET_RANGE
		sendRadialResponseForSurveyToolRange(player, obj);
	case 187: // SERVER_GUILD_INFO
		break;
	case 188: // SERVER_GUILD_MEMBERS
		break;
	case 190: // SERVER_GUILD_ENEMIES
		break;
	case 194: // SERVER_GUILD_GUILD_MANAGEMENT
		break;
	case 195: // SERVER_GUILD_MEMBER_MANAGEMENT
		break;
	default:
		//cout << "Unkown radial selection recieved:" << radialID << "\n";
		break;
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
		
		pack->shiftOffset(4); // shift unicode command

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

void RadialManager::sendRadialResponseForMounts(Player* player, MountCreature* mount, ObjectMenuResponse* omr) {
	omr->addRadialItem(0,205,1, "@pet/pet_menu:menu_enter_exit");
	omr->addRadialItem(0,61,3);

	omr->finish();

	player->sendMessage(omr);
}

void RadialManager::sendRadialResponseForGuildTerminals(Player* player, GuildTerminal* guildTerm, ObjectMenuResponse* omr) {
	Guild* guild = player->getGuild();
	if (guild == NULL) {
		//send create guild, etc.. options
	} else {
		// check if if player has privilegies
	}
	// First root options
	omr->addRadialItem(0,194,3, "@guild:menu_guild_management");
	omr->addRadialItem(0,195,3, "@guild:menu_member_management");
	
	// Suboptions
	omr->addRadialItem(2,190,3, "@guild:menu_enemies");
	omr->addRadialItem(2,187,3, "@guild:menu_info");
	
	
	omr->addRadialItem(3,188,3, "@guild:menu_members");

	omr->finish();

	player->sendMessage(omr);
}

void RadialManager::sendRadialResponseForBazaar(long objectId, Player* player) {
	Zone* zone = player->getZone();
	
	BazaarManager* bazaarManager = zone->getZoneServer()->getBazaarManager();
	bazaarManager->newBazaarRequest(objectId, player, player->getZoneID());
	
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
		cout << "Unreported exception caught in RadialManager::handleVehicleStore(Player* player, SceneObject* obj)\n";
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
		cout << "Unreported exception caught in RadialManager::handleVehicleGenerate\n";
		mount->unlock();
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

			stringstream msg;
			msg << player->getCharacterName().c_str() << " requested a trade.";
			target->sendSystemMessage(msg.str());
		}
		
		target->unlock();
	} catch (Exception& e) {
		target->unlock();
		cout << e.getMessage() << "caught in RadialManager::handleTrade(Player* player, SceneObject* obj)\n";
	} catch (...) {
		target->unlock();
		cout << "Unreported exception caught in RadialManager::handleTrade(Player* player, SceneObject* obj)\n";
	}
}

void RadialManager::sendRadialResponseForSurveyTools(Player* player, SurveyTool* surveyTool, ObjectMenuResponse* omr) {
	omr->addRadialItem(0, 136, 3, "@sui:tool_options");
	omr->addRadialItem(4, 137, 3, "@sui:survey_range");
	omr->finish();
	
	player->sendMessage(omr);
}

void RadialManager::sendRadialResponseForSurveyToolRange(Player* player, SceneObject* obj) {
	if (!player->hasSkillMod("surveying")) {
		player->sendSystemMessage("You are confused by this device.");
		return;
	}
	
	string boxTitle = "@base_player:swg";
	string boxText = "@survey:select_range";
	
	string range64 = "64m x 3pts";
	string range128 = "128m x 4pts";
	string range192 = "192m x 4pts";
	string range256 = "256m x 5pts";
	string range320 = "320m x 5pts";
	string surveying = "surveying";
	
	int surveyMod = player->getSkillMod(surveying);
	
	ListBox* suiToolRangeBox = new ListBox(0xD44B7259, boxTitle, boxText, false);
	
	if (surveyMod >= 0)
		suiToolRangeBox->addItem(range64);
	
	if (surveyMod > 20)
		suiToolRangeBox->addItem(range128);
	
	if (surveyMod > 40)
		suiToolRangeBox->addItem(range192);
	
	if (surveyMod > 60)
		suiToolRangeBox->addItem(range256);

	if (surveyMod > 80)
		suiToolRangeBox->addItem(range320);
	
	suiToolRangeBox->generateMessage();
	
	player->sendMessage(suiToolRangeBox);
	
	player->setSurveyTool((SurveyTool*)obj);
}
