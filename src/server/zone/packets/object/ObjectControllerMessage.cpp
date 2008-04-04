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
#include "../../managers/combat/CombatManager.h"
#include "../../managers/player/ProfessionManager.h"
#include "../../managers/radial/RadialManager.h"
#include "../../managers/group/GroupManager.h"
#include "../../managers/resource/ResourceManager.h"

#include "../../managers/combat/CombatManager.h"
#include "../../../chat/ChatManager.h"

#include "../../objects.h"

#include "../../objects/player/sui/messagebox/SuiMessageBoxImplementation.h"

#include "../../managers/combat/CommandQueueAction.h"

#include "ObjectControllerMessage.h"
#include "CommandQueueRemove.h"

#include "../../packets.h"

ObjectControllerMessage::ObjectControllerMessage(uint64 objid, uint32 header1, uint32 header2, bool comp) : BaseMessage() {
	insertShort(0x05);
	insertInt(0x80CE5E46);  // CRC
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
	
	float dx = pack->parseFloat();
	float dz = pack->parseFloat();
	float dy = pack->parseFloat();
	float dw = pack->parseFloat();
	
	//cout << "dir vector x:" << dx << " dz:" << dz << " dy:" << dy << " dw:" << dw << "\n";

	float x = pack->parseFloat();
	float z = pack->parseFloat();
	float y = pack->parseFloat();
	
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
			
		if (serverStamp + 250 < (uint64)deltaStamp) {
			stringstream deltas;
			deltas << "speed hack detected " << "deltaStamp:[" << deltaStamp << "] serversStamp:[" << serverStamp << "]";
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

			float dist = sqrt(((x - lastPosX) * (x - lastPosX)) + ((y - lastPosY) * (y - lastPosY)));

			float speed = dist * 1000 / (float)deltaStamp;
			
			if (speed > player->getSpeed() * 1.5) {
				stringstream msg;
				msg << "SpeedHack detected on player: [" << player->getFirstName() << "]\n";
				msg << "Player Speed:" << player->getSpeed() << " caught speed:" << speed << "\n";
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

uint64 ObjectControllerMessage::parseDataTransformWithParent(Player* player, Message* pack) {
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
	float dz = pack->parseFloat();
	float dy = pack->parseFloat();
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
			
		if (serverStamp + 250 < (uint64)deltaStamp) {
			stringstream deltas;
			deltas << "speed hack detected " << "deltaStamp:[" << deltaStamp << "] serversStamp:[" << serverStamp << "]";
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

			float dist = sqrt(((x - lastPosX) * (x - lastPosX)) + ((y - lastPosY) * (y - lastPosY)));

			float speed = dist * 1000 / (float)deltaStamp;
			
			if (speed > player->getSpeed() * 1.5) {
				stringstream msg;
				msg << "SpeedHack detected on player: [" << player->getFirstName() << "]\n";
				msg << "Player Speed:" << player->getSpeed() << " caught speed:" << speed << "\n";
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
	
	player->setDirection(dx, dz, dy , dw);
	player->setPosition(x, z, y);
	player->setLastMovementUpdateStamp(movementStamp);
	
	return parent;
	
	/*cout << "Player [" << player->getObjectID() << "] with Parent [" << parent << "] - Counter [" << player->getMovementCounter() << "]" 
			<< " - Position (" << (int) x << "," << (int) z << "," << (int) y << ")\n";*/
}
	
void ObjectControllerMessage::parseObjectTargetUpdate(Player* player, Message* pack) {
	pack->shiftOffset(12); // skip ObjectID and size

	uint64 target = pack->parseLong();
	player->updateTarget(target);
}

void ObjectControllerMessage::parseCommandQueueEnqueue(Player* player, Message* pack, ZoneProcessServerImplementation* serv) {
	pack->shiftOffset(12); // skip ObjectID and size

	uint32 actioncntr = pack->parseInt();
	uint32 actionCRC = pack->parseInt();
	uint64 target;
	unicode name;

	if (player->isIncapacitated() || player->isDead()) {
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
	case 0x82f75977: // equip, unequip, change clothes.  unequip weapon, unequip armor.
		target = pack->parseLong();
		player->changeCloth(target);
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
	case (0x7B1DCBE0): //startdance
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		parseStartDance(player, pack);
		break;
	case (0xDDD1E8F1): //startmusic
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		parseStartMusic(player, pack);
		break;
	case (0xC8998CE9): //flourish
		if (player->isMounted()) {
			player->clearQueueAction(actioncntr, 0, 1, 16);
			return;
		}
		parseFlourish(player, pack);
		break;
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
		break;
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
		parseWaypointCreate(player, pack);
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
	case (0x5FD21EB0):  // Schematic Resources
		//parseRequestDraftSlotsBatch(player, pack);
		break;
	case (0x9A8B385C): // Schematic Experimental Properties
		//parseRequestResourceWeightsBatch(player, pack);
		break;
	case (0x094AC516): // Request Crafting Session
		//parseRequestCraftingSession(player, pack);
		break;
	case (0x89242E02): // Select Draft Schematic
		//parseSelectDraftSchematic(player, pack);
		break;
	case (0x83250E2A): // Cancel Crafting Session
		//parseCancelCraftingSession(player, pack);
		break;
	case (0x6AD8ED4D): // Next crafting stage
		//parseNextCraftingStage(player, pack);
		break;
	case (0xD61FF415): // Create Prototype
		//parseCreatePrototype(player, pack);
		break;
		
	default:
		target = pack->parseLong();
		
	    string actionModifier = "";
	    
	    // fancy if statement
	    switch (actionCRC) // modifier for entertainer-type commands /dazzle 2 vs /dazzle 1
	    { // they're dumb and all have the same action crc
	    	case (0xB008CBFA): //colorlights
	    	case (0x9C7713A5): //dazzle
	    	case (0xED4AA746): //spotlight
	    	case (0xD536B419): //smokebomb
	    	case (0x2434AC3A): //distract
	    	case (0x6CB6978F): //ventriloquism
	    	case (0x35ED32BE): //firejet
	    		unicode option = unicode("");
	    	    pack->parseUnicode(option);
	    	    actionModifier = option.c_str();
			    //if(skillOptionID <=0 ) skillOptionID = 1; // default to level 1
	    }

	    /*stringstream opc;
		opc << "Opc: " << hex << actionCRC << " modifier: " << dec << actionModifier;
		player->sendSystemMessage(opc.str());*/
		
		player->queueAction(player, target, actionCRC, actioncntr, actionModifier.c_str());

		return;
	}
	
	player->clearQueueAction(actioncntr);
}

void ObjectControllerMessage::parseAttachmentDragDrop(Player* player, Message* pack) {
	if (player->getTradeSize() != 0) {
		player->sendSystemMessage("You cant move objects while trading..");
		return;
	}
	
	uint64 attachmentID = pack->parseLong();
	unicode unicodeID;
	
	pack->parseUnicode(unicodeID);
	StringTokenizer tokenizer(unicodeID.c_str());
	
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

void ObjectControllerMessage::parseCommandQueueClear(Player* player, Message* pack) {
	pack->shiftOffset(12); // skip ObjectID and size

	uint32 actioncntr = pack->parseInt();
	uint32 actionCRC = pack->parseInt();
	uint64 target;

	player->deleteQueueAction(actioncntr);
}

void ObjectControllerMessage::parseSurrenderSkillBox(Player* player, Message* pack) {
	try {

		pack->shiftOffset(8); 
		unicode skillBox;
		pack->parseUnicode(skillBox);

		player->surrenderSkillBox(skillBox.c_str().c_str());
	} catch (...) {
		cout << "unreported parseSurrenderSkillBox(Player* player, Message* pack) exception\n";
	}
}

void ObjectControllerMessage::parseNpcStartConversation(Player* player, Message* pack) {
	uint64 target = pack->parseLong();
	
	SceneObject* object = player->getZone()->lookupObject(target);
	if (object != NULL) {
		player->setConversatingCreature((CreatureObject*)object);
		object->sendConversationStartTo(player);
	}
}

void ObjectControllerMessage::parseNpcStopConversation(Player* player, Message* pack) {
	uint64 target = pack->parseLong();
	
	CreatureObject* npc = player->getConversatingCreature();
	
	if (npc != NULL) {
		StopNpcConversation* conv = new StopNpcConversation(player, npc->getObjectID());
		player->setConversatingCreature(NULL);
	
		player->sendMessage(conv);
	}
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

	// create ticket item 
	TicketImplementation* ticketImpl = new TicketImplementation(player, 0xDAA0DE83, unicode("Travel Ticket"), "travel_ticket", 
    	departurePlanet, departurePoint, arrivalPlanet, arrivalPoint);
    	
    stringstream Name;
    Name << "Ticket" << ticketImpl->getObjectID();
    
    Ticket* ticket = (Ticket*) ObjectRequestBroker::instance()->deploy(Name.str(), ticketImpl);
	
	player->addInventoryItem(ticket);
    ticket->sendTo(player, true);
    
    SuiMessageBoxImplementation* sui = new SuiMessageBoxImplementation(player, 0xDAAD);
    sui->setPromptTitle("@base_player:swg");
    sui->setPromptText("@travel:ticket_purchase_complete");
    
    player->addSuiBox(sui->deploy());
    player->sendMessage(sui->generateMessage());
}

void ObjectControllerMessage::parseNpcConversationSelect(Player* player, Message* pack) {
	pack->shiftOffset(8);
	
	SceneObject* object = player->getConversatingCreature();

	if (object != NULL) {
		unicode opt;
		pack->parseUnicode(opt);
			
		int option = atoi(opt.c_str().c_str());
		object->selectConversationOption(option, player);
	}
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
				
				if (target != NULL && target != player && target->isPlayer()) {
					Player* targetPlayer = (Player*) target;
					
					try {
						targetPlayer->wlock(player);

						object = targetPlayer->getPlayerItem(objid);

						targetPlayer->unlock();
					} catch (...) {
						targetPlayer->unlock();
					}
				}
			}
		}

		if (object != NULL)
			object->generateAttributes(player);
		else {
			AttributeListMessage* msg = new AttributeListMessage(objid);
			player->sendMessage(msg);
		}
	}
}

void ObjectControllerMessage::parseRadialRequest(Player* player, Message* pack, RadialManager* radialManager) {
	radialManager->handleRadialRequest(player, pack);
}

void ObjectControllerMessage::parseSetCurrentSkillTitle(Player* player, Message* pack) {
	pack->shiftOffset(8); //shift past the blank id.
	unicode title;
	pack->parseUnicode(title);
	string newTitle = title.c_str();
    
    PlayerObject* object = player->getPlayerObject();
    object->setCurrentTitle(newTitle, true);
}

void ObjectControllerMessage::parseShowPvpRating(Player* player, Message* pack) {
	stringstream msg;
	msg << "Your player vs. player combat rating is " << player->getPvpRating();
	
	player->sendSystemMessage(msg.str());
}

void ObjectControllerMessage::parseStartDance(Player* player, Message* pack) {
	pack->shiftOffset(8); //shift past the blank long.
	
	unicode anim;
	pack->parseUnicode(anim);
	
	player->startDancing(anim.c_str());
}

void ObjectControllerMessage::parseStartMusic(Player* player, Message* pack) {
	pack->shiftOffset(8); //shift past the blank long.
	
	unicode music;
	pack->parseUnicode(music);
	
	player->startPlayingMusic(music.c_str());
}

void ObjectControllerMessage::parseFlourish(Player* player, Message* pack) {

	//player->getSkill()
	pack->shiftOffset(8);

    unicode flourishID;
    pack->parseUnicode(flourishID);
    
    int fid = atoi(flourishID.c_str().c_str());
    
    //now we need to determine whether its a music or a dance flourish.
    
	string skillbox = "social_entertainer_novice";
	
	if (!player->getSkillBoxesSize() || !player->hasSkillBox(skillbox)) {
		player->sendSystemMessage("You do not have sufficient abilities to Flourish.");
		return;
	}
	
	if (!player->isDancing() && !player->isPlayingMusic()) {
		player->sendSystemMessage("You must be playing music or dancing to Flourish..");
		return;		
	}

	float baseActionDrain = -40 + (player->getQuickness() / 37.5);
	float flourishActionDrain = baseActionDrain / 2.0;
	
	int actionDrain = (int)round((flourishActionDrain * 10+ 0.5) / 10.0); // Round to nearest dec for actual int cost

    /*stringstream opc;
	opc << "ActionDrain: " << dec << ActionDrain;
	player->sendSystemMessage(opc.str());*/
	
	if (player->changeActionBar(actionDrain, false) ) {		
		player->activateRecovery();
		
		if (player->isDancing()) {
	    	stringstream msg;
			msg << "skill_action_" << fid;
	    	player->doAnimation(msg.str());
	    } else if (player->isPlayingMusic()) {
	    	Flourish* flourish = new Flourish(player, fid);
			player->broadcastMessage(flourish);
	    }
		
	} else {
		player->sendSystemMessage("You do not have enough action to do that.");
	}	
}

void ObjectControllerMessage::parseStopMusic(Player* player, Message* pack) {
	    player->stopPlayingMusic();
}

void ObjectControllerMessage::parseStopDance(Player* player, Message* pack) {
		player->stopDancing();
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

			if (x < -8192 || x > 8192)
				x = 0;
			if (y < -8192 || y > 8192)
				y = 0;
			if (z < -8192 || z > 8192)
				z = 0;

			player->setPosture(CreatureObjectImplementation::SITTING_POSTURE, false, true, x, y, z);
		} catch (...) {
			cout << "Unreported exception in ObjectControllerMessage::parseServerSit\n";
		}
	}
}

void ObjectControllerMessage::parseWaypointCreate(Player* player, Message* pack) {
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
		
		if (x < -8192 || x > 8192)
			x = 0;
		if (y < -8192 || y > 8192)
			y = 0;
		if (z < -8192 || z > 8192)
			z = 0;
		
		WaypointObjectImplementation* wayImpl = new WaypointObjectImplementation(player, player->getNewItemID());
		wayImpl->setPlanetName(planet);
		wayImpl->setPosition(x, z, y);
		stringstream Name;
		Name << "Waypoint" << wayImpl->getObjectID();
		WaypointObject* waypoint = (WaypointObject*)ObjectRequestBroker::instance()->deploy(Name.str(), wayImpl);
		
		player->addWaypoint(waypoint);
		
	} catch (...) {
		cout << "Unreported exception in ObjectControllerMessage::parseWaypointCreate\n";
	}
}

void ObjectControllerMessage::parseWaypointCommand(Player* player, Message* pack) {
	pack->shiftOffset(8);
	
	unicode waypoint;
	pack->parseUnicode(waypoint);
	
	try {
		float x = 0, y = 0;
	
		if (waypoint.size() > 1) {
			StringTokenizer tokenizer(waypoint.c_str());
			if (tokenizer.hasMoreTokens())
				x = tokenizer.getFloatToken();
			
			if (tokenizer.hasMoreTokens())
				y = tokenizer.getFloatToken();			
		} else {
			x = player->getPositionX();
			y = player->getPositionY();
		}

		if (x < -8192 || x > 8192)
			x = 0;
		if (y < -8192 || y > 8192)
			y = 0;

		WaypointObjectImplementation* wayImpl = new WaypointObjectImplementation(player, player->getNewItemID());
		wayImpl->setPosition(x, 0, y);
		stringstream Name;
		Name << "Waypoint" << wayImpl->getObjectID();
		WaypointObject* waypoint = (WaypointObject*)ObjectRequestBroker::instance()->deploy(Name.str(), wayImpl);

		player->addWaypoint(waypoint);

	} catch (...) {
		cout << "Unreported exception in ObjectControllerMessage::parseWaypointCommand\n";
	}
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

void ObjectControllerMessage::parseServerDestroyObject(Player* player, Message* pack) {
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
	
	TangibleObject* item = (TangibleObject*) player->getInventoryItem(objid);
	if (item != NULL) {
		if (item->isEquipped()) {
			//player->changeCloth(objid);
			player->sendSystemMessage("You must unequip the item before destroying it.");
			return;
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
		if (player->removeWaypoint(waypoint));
			waypoint->finalize();
	}
}

void ObjectControllerMessage::parseSetWaypointActiveStatus(Player* player, Message* pack) {
	uint64 wpId = pack->parseLong();
	
	WaypointObject* wp = player->getWaypoint(wpId);
	
	if (wp == NULL)
		return;
		
	wp->switchStatus();
}

void ObjectControllerMessage::parseRequestCharacterMatch(Player* player, Message* pack) {
	//pack->shiftOffset(8); //Shift past the blank long. Eventually parse stuff here. Not yet. lols.
	player->getPlayersNearYou();
}

void ObjectControllerMessage::parseGroupInvite(Player* player, Message* pack, GroupManager* groupManager) {
	uint64 objectID = pack->parseLong();
	SceneObject* object = player->getZone()->lookupObject(objectID);
	
	if (object == NULL || !object->isPlayer() || object == player)
		return;

	Player* invitePlayer = (Player*)object;
	groupManager->inviteToGroup(player, invitePlayer);
}

void ObjectControllerMessage::parseGroupJoin(Player* player, Message* pack, GroupManager* groupManager) {	
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

void ObjectControllerMessage::parseGroupLeave(Player* player, Message* pack, GroupManager* groupManager) {
	GroupObject* group = player->getGroupObject();
	
	if (group == NULL)
		return;

	groupManager->leaveGroup(group, player);
}

void ObjectControllerMessage::parseGroupDisband(Player* player, Message* pack, GroupManager* groupManager) {
	GroupObject* group = player->getGroupObject();
	if (group == NULL)
		return;

	groupManager->disbandGroup(group, player);
}

void ObjectControllerMessage::parseGroupKick(Player* player, Message* pack, GroupManager* groupManager) {
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

void ObjectControllerMessage::parseGroupMakeLeader(Player* player, Message* pack, GroupManager* groupManager) {
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

void ObjectControllerMessage::parseTip(Player* player, Message* pack, PlayerManager* playerManager) {
	uint64 tipToId = pack->parseLong();

	unicode tipParams;
	pack->parseUnicode(tipParams);

	StringTokenizer tokenizer(tipParams.c_str());
	tokenizer.setDelimeter(" ");

	int tipAmount;

	if (tipToId == 0) {
		//either player not in range. Or not online. So lets do a bank tip.

		string tipToName;
		tokenizer.getStringToken(tipToName);

		//Ok so now we have the name. Lets verify they exist first before doing anything else.
		if (!playerManager->validateName(tipToName)) {
			//Ok so the player exists. So lets parse the rest of the packet now.

			string tips; 
			tokenizer.getStringToken(tips);

			tipAmount = atoi(tips.c_str());

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
				playerManager->modifyOfflineBank(player, tipToName, tipAmount);
				player->sendSystemMessage("Player not online. Credits should be transferred.");
				return;
			} else {
				//Player is online. Tip their stuff and send mail etc;
				//make sure they have the proper credits first.
				playerManager->doBankTip(player, tiptoPlayer, tipAmount, true);
			}

		} else {
			//Invalid Player Name
			player->sendSystemMessage(tipToName + " is not a valid player name.");
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

			string tipToName;
			tokenizer.getStringToken(tipToName);

			//Before we go any further we should validate the player name.
			if (!playerManager->validateName(tipToName)) {
				//They exist at least. Now lets grab the tip amount.
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
						Player* tiptoPlayer = playerManager->getPlayer(tipToName);
						if (tiptoPlayer == NULL) {
							//The player exists but they are offline. So Still do the tip.
							//Do stuff like altering the db here since they arent online.	
							playerManager->modifyOfflineBank(player, tipToName, tipAmount);
							player->sendSystemMessage("Player not online. Add Altering the DB in later.");
							return;
						} else {
							//Player is online. Tip their stuff and send mail etc;
							//make sure they have the proper credits first.
							playerManager->doBankTip(player, tiptoPlayer, tipAmount, true);
						}
					} else {
						//They typed something else other than bank.
						player->sendSystemMessage("Invalid Tip parameter. (Bank Parameter)");
						return;
					}
				}
			} else {
				//Invalid Player Name
				player->sendSystemMessage(tipToName + " is not a valid player name.");
				return;	
			}
		}
	}
}

void ObjectControllerMessage::handleDeathblow(Player* player, Message* packet, CombatManager* combatManager) {
	uint64 targetID = packet->parseLong();

	SceneObject* object = player->getZone()->lookupObject(targetID);

	if (object == NULL || !object->isPlayer() || object == player)
		return;
	
	Player* target = (Player*) object;
	
	try {
		target->wlock(player);
		
		if (combatManager->canAttack(player, target) && target->isIncapacitated()
				&& target->isInRange(player, 5)) {
			target->kill();
				
			player->sendSystemMessage("base_player", "prose_target_dead", target->getObjectID());
		}
		
		target->unlock();
	} catch (...) {
		cout << "Unreported exception caught in ObjectControllerMessage::handleDeathblow(Player* player, Message* packet)\n";
		target->unlock();
	}
}

void ObjectControllerMessage::parseSurveySlashRequest(Player* player, Message* packet) {
	player->setSurveyErrorMessage();
}

void ObjectControllerMessage::parseSampleSlashRequest(Player* player, Message* packet) {
	player->setSampleErrorMessage();
}

void ObjectControllerMessage::parseSurveyRequest(Player* player, Message* packet) {
	uint64 targetID = packet->parseLong();
	
	unicode resourceName;
	packet->parseUnicode(resourceName);
	
	string skillBox = "crafting_artisan_novice";
	
	if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox)) {
		if (player->getSurveyTool() == NULL) {
			player->sendSystemMessage("You must use a survey tool once from the Inventory before you can do this.");
			return;
		}
		player->getSurveyTool()->surveyRequest(player, resourceName);
	} else {
		if (player->getSurveyErrorMessage())
			player->sendSystemMessage("You do not have sufficient abilities to Survey Resources.");
	}
}

void ObjectControllerMessage::parseSampleRequest(Player* player, Message* packet) {
	uint64 targetID = packet->parseLong();
	
	unicode resourceName;
	packet->parseUnicode(resourceName);
	
	string skillBox = "crafting_artisan_novice";
	
	if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox)) {
		if (player->getSurveyTool() == NULL) {
			player->sendSystemMessage("You must use a survey tool once from the Inventory before you can do this.");
			return;
		}
		player->getSurveyTool()->sampleRequest(player, resourceName);
	} else {
		if (player->getSampleErrorMessage())
			player->sendSystemMessage("You do not have sufficient abilities to Sample Resource.");
	}
}

void ObjectControllerMessage::parseResourceContainerSplit(Player* player, Message* packet) {
	if (player->getTradeSize() != 0) {
		player->sendSystemMessage("You cant move objects while trading..");
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
	
	ResourceContainer* rco = (ResourceContainer*)player->getInventoryItem(objectID);
	if (rco != NULL)
		rco->splitContainer(player, newQuantity);
}

void ObjectControllerMessage::parseResourceContainerTransfer(Player* player, Message* packet) {
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
    
    if (object1 != NULL && object2 != NULL && object1->isTangible() && object2->isTangible()) {
    	TangibleObject* resCof = (TangibleObject*) object1;
    	TangibleObject* resCot = (TangibleObject*) object2;
    	if (resCof->isResource() && resCot->isResource()) {
    		ResourceContainer* rcof = (ResourceContainer*)resCof;
    		ResourceContainer* rcot = (ResourceContainer*) resCot;
			rcot->transferContents(player, rcof);
    	}
    }
}

void ObjectControllerMessage::parseRequestDraftSlotsBatch(Player* player, Message* packet) {
	packet->shiftOffset(8);
	
	unicode crcAndID;
	packet->parseUnicode(crcAndID);
	
	StringTokenizer tokenizer(crcAndID.c_str());
		
	uint32 schematicID;
	uint32 schematicCRC;
	// CHANGE THIS WHEN .getIntToken WORKS RIGHT
	if(tokenizer.hasMoreTokens())
		schematicID = tokenizer.getLongToken();
	if(tokenizer.hasMoreTokens())
		schematicCRC = tokenizer.getLongToken();
		
	//Check to see if the correct obj id is in the players vector of draft schematics
	DraftSchematic* ds = player->getDraftSchematic(schematicID);
	if(ds != NULL) {
		ds->sendIngredientsToPlayer(player);
	}
}	 


void ObjectControllerMessage::parseRequestResourceWeightsBatch(Player* player, Message* packet) {
	packet->shiftOffset(8);
	
	unicode id;
	packet->parseUnicode(id);
	
	StringTokenizer tokenizer(id.c_str());
	
	uint32 schematicID;
	if(tokenizer.hasMoreTokens())
		schematicID = tokenizer.getIntToken();
		
	//Check to see if the correct obj id is in the players vector of draft schematics
	DraftSchematic* ds = player->getDraftSchematic(schematicID);
	if(ds != NULL) {
		ds->sendExperimentalPropertiesToPlayer(player);
	}
}

void ObjectControllerMessage::parseRequestCraftingSession(Player* player, Message* packet) {
	uint64 ctSceneObjID = packet->parseLong();
	
	//Check to see if the correct obj id is in the player's datapad
	CraftingTool* ct = (CraftingTool*)player->getInventoryItem(ctSceneObjID);
	if(ct != NULL) {
		ct->sendToolStart(player);
	} else {
		// This eles should never execute
		player->sendSystemMessage("Crafting Tool Not Found.  Please inform Link of this error.");
	}	
}

void ObjectControllerMessage::parseCancelCraftingSession(Player* player, Message* packet) {
	
	//TODO: Try to find a Cancel Crafting Session server->client packet in live for researching

	// This is just a guess as to what the client wants when it sends a Cancel Crafting Session packet
	
	// DPlay9
	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player->getPlayerObject());
	dplay9->setCraftingState(0);
	dplay9->close();
	player->sendMessage(dplay9);
	
	// Clean up crafting here, delete, sceneremove unneeded objects
	//CraftingTool * ct = player->getCurrentCraftingTool();
	
	//cout << "Crafting Closed!\n";
}

void ObjectControllerMessage::parseSelectDraftSchematic(Player* player, Message* packet) {

	packet->shiftOffset(8);
		
	unicode uniIndexOfSelectedSchematic;
	packet->parseUnicode(uniIndexOfSelectedSchematic);
		
	StringTokenizer tokenizer(uniIndexOfSelectedSchematic.c_str());
		
	int indexOfSelectedSchematic;
		
	if(tokenizer.hasMoreTokens())
		indexOfSelectedSchematic = tokenizer.getIntToken();
	
	// Find the selected schematic
	DraftSchematic* ds = player->getDraftSchematic(indexOfSelectedSchematic); 
	
	if(ds != NULL) {
		CraftingTool * ct = player->getCurrentCraftingTool();
		player->prepareCraftingSession(ct, ds);
	} else {
		// This eles should never execute
		player->sendSystemMessage("Selected Draft Schematic was invalid.  Please inform Link of this error.");
	}

}
void ObjectControllerMessage::parseAddCraftingResource(Player* player, Message* packet) {

	packet->shiftOffset(12);
	
	uint64 resourceObjectID = packet->parseLong();
	
	int slot = packet->parseInt();
	
	packet->shiftOffset(4);
	
	int counter = packet->parseByte();

	ResourceContainer * rnco = (ResourceContainer*)player->getInventoryItem(resourceObjectID);
	if(rnco != NULL) {
		player->addResourceToCraft(rnco, slot, counter);
	} else {
		// This eles should never execute
		player->sendSystemMessage("Add resource invalid, contact kyle");
	}
}
void ObjectControllerMessage::parseRemoveCraftingResource(Player* player, Message* packet) {

	packet->shiftOffset(12);
	
	int slot = packet->parseInt();
	
	uint64 resID = packet->parseLong();
	
	//packet->shiftOffset(4);
	
	int counter = packet->parseByte();

	player->removeResourceFromCraft(resID, slot, counter);

}
void ObjectControllerMessage::parseNextCraftingStage(Player* player, Message* packet) {

	packet->shiftOffset(8);
	
	unicode test;
	packet->parseUnicode(test);
	
	string test2 = test.c_str();
	
	player->nextCraftingStage(test2);
	
}
void ObjectControllerMessage::parseCraftCustomization(Player* player, Message* packet){
	
	packet->shiftOffset(12);
	
	unicode n;
	packet->parseUnicode(n);
	
	string name = n.c_str();
	
	packet->shiftOffset(1);
	
    int condition = packet->parseInt();
    
    player->craftingCustomization(name, condition);
}
void ObjectControllerMessage::parseCreatePrototype(Player* player, Message* packet){
	
	packet->shiftOffset(8);
	
	unicode test;
	packet->parseUnicode(test);
	
	string test2 = test.c_str();
	
	player->createPrototype(test2);
}
