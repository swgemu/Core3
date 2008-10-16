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

#ifndef OBJECTCONTROLLERMESSAGE_H_
#define OBJECTCONTROLLERMESSAGE_H_

#include "engine/engine.h"

class ZoneProcessServerImplementation;
class GroupManager;
class RadialManager;
class PlayerManager;
class Player;
class CombatManager;
class ItemManager;
class PlanetManager;

class ObjectControllerMessage : public BaseMessage {
public:
	ObjectControllerMessage(uint64 objid, uint32 header1, uint32 header2, bool comp = true);

	static void parseAttachmentDragDrop(Player* player, Message* pack);
	static void parsePowerupDragDrop(Player* player, Message* pack);

	static bool parseDataTransform(Player* player, Message* pack);
	static uint64 parseDataTransformWithParent(Player* player, Message* pack);

	static void parseCommandQueueEnqueue(Player* player, Message* pack, ZoneProcessServerImplementation* serv);
	static void parseCommandQueueClear(Player* player, Message* pack);

	static void parseObjectTargetUpdate(Player* player, Message* pack);

	static void parseSurrenderSkillBox(Player* player, Message* pack);

	static void parseNpcStartConversation(Player* player, Message* pack);
	static void parseNpcStopConversation(Player* player, Message* pack);
    static void parseNpcConversationSelect(Player* player, Message* pack);

    static void parseStatMigrationDataRequest(Player* player, Message* pack);
    static void parseSetStatMigrationDataRequest(Player* player, Message* pack);
	static void parseCharacterSheetInfoRequest(Player* player, Message* pack);
    static void parseBiographyRequest(Player* player, Message* pack);
    static void parseSetBiography(Player* player, Message* pack);
    static void parseBadgesRequest(Player* player, Message* pack);

    static void parsePurchaseTicket(Player* player, Message* pack);
    static void parseGetAttributes(Player* player, Message* pack);

    static void parseRadialRequest(Player* player, Message* pack, RadialManager* radialManager);

    static void parseImageDesignChange(Player* player, Message* pack, ZoneProcessServerImplementation* serv);
    static void parseImageDesignCancel(Player* player, Message* pack);

    static void parseSetCurrentSkillTitle(Player* player, Message* pack);

    static void parseShowPvpRating(Player* player, Message* pack);


    static void parseFlourish(Player* player, Message* pack, uint32 actionCntr);
    static void parseImageDesign(Player* player, Message* pack);
    static void parseWatch(Player* player, Message* pack);
    static void parseListen(Player* player, Message* pack);
   	static void parseStopWatch(Player* player, Message* pack);
    static void parseStopListen(Player* player, Message* pack);
    static void parseFlourish(Player* player, Message* pack);
    static void parseChangeMusic(Player* player, Message* pack);
    static void parseChangeDance(Player* player, Message* pack);

    static void parseServerSit(Player* player, Message* pack);

    static void parseServerDestroyObject(Player* player, Message* pack);

    static void parseWaypointCreate(Player* player, Message* pack);
    static void parseWaypointCommand(Player* player, Message* pack);
    static void parseSetWaypointName(Player* player, Message* pack);

    static void parseRequestCharacterMatch(Player* player, Message* pack);

    static void parseSetWaypointActiveStatus(Player* player, Message* pack);

    static void handleDeathblow(Player* player, Message* packet, CombatManager* combatManager);

    static void parseSurveySlashRequest(Player* player, Message* pack);
    static void parseSampleSlashRequest(Player* player, Message* pack);
    static void parseSurveyRequest(Player* player, Message* pack);
    static void parseSampleRequest(Player* player, Message* pack);

    static void parseResourceContainerSplit(Player* player, Message* pack);
    static void parseResourceContainerTransfer(Player* player, Message* pack);

    // mission
    static void parseMissionListRequest(Player* player, Message* pack);
    static void parseMissionAccept(Player* player, Message* pack);
    static void parseMissionAbort(Player* player, Message* pack);

    // group
    static void parseGroupInvite(Player* player, Message* pack, GroupManager* groupManager);
    static void parseGroupUninvite(Player* player, Message* pack);
    static void parseGroupJoin(Player* player, Message* pack, GroupManager* groupManager);
    static void parseGroupLeave(Player* player, Message* pack, GroupManager* groupManager);
    static void parseGroupKick(Player* player, Message* pack, GroupManager* groupManager);
	static void parseGroupDisband(Player* player, Message* pack, GroupManager* groupManager);
	static void parseGroupMakeLeader(Player* player, Message* pack, GroupManager* groupManager);
	static void parseGroupDecline(Player* player, Message* pack);

	//Mounts
	static void parseMount(Player* player, Message* pack);
	static void parseDismount(Player* player, Message* pack);

	//Tip
	static void parseTip(Player* player, Message* pack, PlayerManager* playerManager);

	//Structures
	static void parsePlaceStructure(Player* player, Message* pack);

	// Schematics
	static void parseRequestDraftSlotsBatch(Player* player, Message* pack);
	static void parseRequestResourceWeightsBatch(Player* player, Message* pack);

	// Crafting
	static void parseRequestCraftingSession(Player* player, Message* pack);
	static void parseCancelCraftingSession(Player* player, Message* packet);
	static void parseSelectDraftSchematic(Player* player, Message* pack);
	static void parseAddCraftingResource(Player* player, Message* packet);
	static void parseRemoveCraftingResource(Player* player, Message* packet);
	static void parseNextCraftingStage(Player* player, Message* packet);
	static void parseCraftCustomization(Player* player, Message* packet);
	static void parseCreatePrototype(Player* player, Message* packet);
	static void parseCreateSchematic(Player* player, Message* packet);
	static void parseExperimentation(Player* player, Message* packet);


	static void parsePickup(Player* player, Message* pack);

	static void parseTransferItemMisc(Player* player, Message* pack);

	static void parseAddFriend(Player* player, Message* pack);
	static void parseRemoveFriend(Player* player, Message* pack);
	static void parseFindFriend(Player* player, Message* pack, PlayerManager* playerManager);

	static void parseAddIgnore(Player* player, Message* pack);
	static void parseRemoveIgnore(Player* player, Message* pack);
	static void parseRotateItem(Player* player, Message* pack);

	static void parseGiveConsentRequest(Player* player, Message* pack);
	static void parseRevokeConsentRequest(Player* player, Message* pack);
	static void parseHaveConsentRequest(Player* player, Message* pack);

	static void parseHarvestOrganics(Player* packet, Message* pack);

	static void handleRemoveFromGuild(Player* player, Message* pack, ZoneProcessServerImplementation* serv);

	static void parseMeditation(Player* player);

	static void parseDelFactionPoints(Player* player, Message* pack);
};

#endif /*OBJECTCONTROLLERMESSAGE_H_*/

