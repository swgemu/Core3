/*
 * GuildTerminalImplementation.cpp
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */


#include "GuildTerminal.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/building/BuildingObject.h"

void GuildTerminalImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (guildObject == NULL) {
		ManagedReference<BuildingObject*> building = cast<BuildingObject*>( getParentRecursively(SceneObject::BUILDING));

		if (building != NULL && building->isOwnerOf(player)) {
			if (!player->isInGuild()) {
				menuResponse->addRadialMenuItem(185, 3, "@guild:menu_create"); //Create Guild
				return;
			}

			//If the owner is already in a guild, and this guild terminal doesn't have a guild assigned yet,
			//then use the owner's guild.
			guildObject = player->getGuildObject();
		} else {
			//They don't have permission to create a guild.
			return;
		}
	}

	uint64 playerID = player->getObjectID();

	//Only members have access.
	if (!guildObject->hasMember(playerID))
		return;

	//Guild exists -> display these functions.
	menuResponse->addRadialMenuItem(193, 3, "@guild:menu_guild_management"); //Guild Management
	menuResponse->addRadialMenuItemToRadialID(193, 186, 3, "@guild:menu_info"); //Guild Information
	menuResponse->addRadialMenuItemToRadialID(193, 189, 3, "@guild:menu_enemies"); //Guild Enemies

	if (guildObject->hasDisbandPermission(playerID))
		menuResponse->addRadialMenuItemToRadialID(193, 191, 3, "@guild:menu_disband"); //Disband Guild

	if (guildObject->hasNamePermission(playerID))
		menuResponse->addRadialMenuItemToRadialID(193, 192, 3, "@guild:menu_namechange"); //Change Guild Name

	menuResponse->addRadialMenuItemToRadialID(193, 68, 3, "@guild:menu_enable_elections"); //Enable/Disable Elections

	menuResponse->addRadialMenuItem(194, 3, "@guild:menu_member_management"); //Member Management
	menuResponse->addRadialMenuItemToRadialID(194, 187, 3, "@guild:menu_members"); //Guild Members

	if (guildObject->getSponsoredPlayerCount() > 0)
		menuResponse->addRadialMenuItemToRadialID(194, 188, 3, "@guild:menu_sponsored"); //Sponsored for Membership

	menuResponse->addRadialMenuItemToRadialID(194, 190, 3, "@guild:menu_sponsor"); //Sponsor for Membership

	if (guildObject->getGuildLeaderID() == playerID)
		menuResponse->addRadialMenuItemToRadialID(194, 69, 3, "@guild:menu_leader_change"); //Transfer PA Leadership

	return;
}

int GuildTerminalImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	Locker _lock(_this);

	ManagedReference<GuildManager*> guildManager = server->getZoneServer()->getGuildManager();

	if (guildManager == NULL)
		return TerminalImplementation::handleObjectMenuSelect(player, selectedID);

	switch (selectedID) {
	case 185:
		guildManager->sendGuildCreateNameTo(player, _this);
		break;
	case 193:
	case 186:
		guildManager->sendGuildInformationTo(player, guildObject, _this);
		break;
	case 191:
		guildManager->sendGuildDisbandConfirmTo(player, guildObject, _this);
		break;
	case 194:
	case 187:
		guildManager->sendGuildMemberListTo(player, guildObject, _this);
		break;
	case 188:
		guildManager->sendGuildSponsoredListTo(player, guildObject, _this);
		break;
	case 190:
		guildManager->sendGuildSponsorTo(player, guildObject, _this);
	default:
		TerminalImplementation::handleObjectMenuSelect(player, selectedID);
	}
	return 0;
}
