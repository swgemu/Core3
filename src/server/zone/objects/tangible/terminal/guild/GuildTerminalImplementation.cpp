/*
 * GuildTerminalImplementation.cpp
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */


#include "GuildTerminal.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/building/BuildingObject.h"

void GuildTerminalImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	ManagedReference<BuildingObject*> building = (BuildingObject*) getParentRecursively(SceneObject::BUILDING);

	if (guildObject == NULL) {
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

	//Guild exists -> display these functions.
	menuResponse->addRadialMenuItem(193, 3, "@guild:menu_guild_management"); //Guild Management
	menuResponse->addRadialMenuItemToRadialID(193, 186, 3, "@guild:menu_info"); //Guild Information
	menuResponse->addRadialMenuItemToRadialID(193, 189, 3, "@guild:menu_enemies"); //Guild Enemies
	menuResponse->addRadialMenuItemToRadialID(193, 191, 3, "@guild:menu_disband"); //Disband Guild
	menuResponse->addRadialMenuItemToRadialID(193, 192, 3, "@guild:menu_namechange"); //Change Guild Name
	menuResponse->addRadialMenuItemToRadialID(193, 68, 3, "@guild:menu_enable_elections"); //Enable/Disable Elections

	menuResponse->addRadialMenuItem(194, 3, "@guild:menu_member_management"); //Member Management
	menuResponse->addRadialMenuItemToRadialID(194, 187, 3, "@guild:menu_members"); //Guild Members
	menuResponse->addRadialMenuItemToRadialID(194, 188, 3, "@guild:menu_sponsored"); //Sponsored for Membership
	menuResponse->addRadialMenuItemToRadialID(194, 190, 3, "@guild:menu_sponsor"); //Sponsor for Membership
	menuResponse->addRadialMenuItemToRadialID(194, 69, 3, "@guild:menu_leader_change"); //Transfer PA Leadership

	return;
}

int GuildTerminalImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	ManagedReference<GuildManager*> guildManager = server->getZoneServer()->getGuildManager();

	if (guildManager == NULL)
		return TerminalImplementation::handleObjectMenuSelect(player, selectedID);

	switch (selectedID) {
	case 185:
		guildManager->sendGuildCreateNameTo(player, _this);
		break;
	case 193:
	case 186: //Guild Information
		guildManager->sendGuildInformationTo(player, _this);
		break;
	default:
		TerminalImplementation::handleObjectMenuSelect(player, selectedID);
	}
	return 0;
}
