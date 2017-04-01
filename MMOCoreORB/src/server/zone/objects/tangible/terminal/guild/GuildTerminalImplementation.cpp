/*
 * GuildTerminalImplementation.cpp
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */


#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/building/BuildingObject.h"


void GuildTerminalImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	ManagedReference<BuildingObject*> building = getParentRecursively(SceneObjectType::BUILDING).castTo<BuildingObject*>();
	if (building == NULL) {
		return;
	}

	ManagedReference<CreatureObject*> owner = building->getOwnerCreatureObject();
	if (owner == NULL || !owner->isPlayerCreature()) {
		return;
	}

	ManagedReference<PlayerObject*> ownerGhost = owner->getPlayerObject().get();
	ManagedReference<PlayerObject*> playerGhost = player->getPlayerObject().get();

	if (ownerGhost == NULL || playerGhost == NULL)
		return;

	ManagedReference<GuildObject*> guildObject = owner->getGuildObject().get();

	if (guildObject == NULL) {

		if (player == owner) {
			if (!player->isInGuild()) {
				menuResponse->addRadialMenuItem(185, 3, "@guild:menu_create"); // Create Guild
			}

		}

		return;
	}

	uint64 playerID = player->getObjectID();

	//Only members have access.
	if (!guildObject->hasMember(playerID) && !playerGhost->isPrivileged())
		return;

	bool isLeader = false;

	if (guildObject->getGuildLeaderID() == playerID)
		isLeader = true;

	//Guild exists -> display these functions.
	menuResponse->addRadialMenuItem(193, 3, "@guild:menu_guild_management"); // Guild Management
	menuResponse->addRadialMenuItemToRadialID(193, 186, 3, "@guild:menu_info"); // Guild Information
	menuResponse->addRadialMenuItemToRadialID(193, 189, 3, "@guild:menu_enemies"); // Guild Enemies

	if (guildObject->hasDisbandPermission(playerID))
		menuResponse->addRadialMenuItemToRadialID(193, 191, 3, "@guild:menu_disband"); // Disband Guild

	if (guildObject->hasNamePermission(playerID) || playerGhost->isPrivileged())
		menuResponse->addRadialMenuItemToRadialID(193, 192, 3, "@guild:menu_namechange"); // Change Guild Name

	menuResponse->addRadialMenuItem(194, 3, "@guild:menu_member_management"); // Member Management
	menuResponse->addRadialMenuItemToRadialID(194, 187, 3, "@guild:menu_members"); // Guild Members

	if (guildObject->getSponsoredPlayerCount() > 0)
		menuResponse->addRadialMenuItemToRadialID(194, 188, 3, "@guild:menu_sponsored"); // Sponsored for Membership

	if (guildObject->hasMember(playerID))
		menuResponse->addRadialMenuItemToRadialID(194, 190, 3, "@guild:menu_sponsor"); // Sponsor for Membership

	if ((isLeader && player == owner) || playerGhost->isPrivileged())
		menuResponse->addRadialMenuItemToRadialID(194, 68, 3, "@guild:menu_leader_change"); // Transfer PA Leadership

	if (isLeader && !ownerGhost->isOnline() && ownerGhost->getDaysSinceLastLogout() >= 28)
		menuResponse->addRadialMenuItemToRadialID(194, 69, 3, "@guild:accept_hall"); // Transfer PA Hall Lots to Myself

	if (guildObject->isElectionEnabled()) {
		menuResponse->addRadialMenuItem(70, 3, "@guild:menu_leader_race"); // Guild Leader Elections
		menuResponse->addRadialMenuItemToRadialID(70, 71, 3, "@guild:menu_leader_standings"); // View Standings

		if (guildObject->hasMember(playerID)) {
			menuResponse->addRadialMenuItemToRadialID(70, 72, 3, "@guild:menu_leader_vote"); // Cast a Vote

			if (guildObject->isCandidate(playerID))
				menuResponse->addRadialMenuItemToRadialID(70, 73, 3, "@guild:menu_leader_unregister"); // Unregister from Race
			else
				menuResponse->addRadialMenuItemToRadialID(70, 73, 3, "@guild:menu_leader_register"); // Register to Run
		}

		if (isLeader) {
			menuResponse->addRadialMenuItemToRadialID(70, 74, 3, "@guild:menu_leader_reset_vote"); // Reset Elections
			menuResponse->addRadialMenuItemToRadialID(70, 75, 3, "@guild:menu_disable_elections"); // Disable Elections
		}

	} else if (isLeader) {
		menuResponse->addRadialMenuItem(70, 3, "@guild:menu_leader_race"); // Guild Leader Elections
		menuResponse->addRadialMenuItemToRadialID(70, 75, 3, "@guild:menu_enable_elections"); // Enable Elections
	}

	if (playerGhost->isPrivileged())
		menuResponse->addRadialMenuItemToRadialID(193, 76, 3, "Process Guild Update"); //TODO: Remove this temporary ability

	return;
}

int GuildTerminalImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	Locker _lock(_this.getReferenceUnsafeStaticCast());

	ManagedReference<GuildManager*> guildManager = getZoneServer()->getGuildManager();

	if (guildManager == NULL)
		return TerminalImplementation::handleObjectMenuSelect(player, selectedID);

	ManagedReference<BuildingObject*> building = getParentRecursively(SceneObjectType::BUILDING).castTo<BuildingObject*>();
	if (building == NULL) {
		return 1;
	}

	ManagedReference<CreatureObject*> owner = building->getOwnerCreatureObject();
	if (owner == NULL || !owner->isPlayerCreature()) {
		return 1;
	}

	ManagedReference<PlayerObject*> ownerGhost = owner->getPlayerObject().get();
	ManagedReference<PlayerObject*> playerGhost = player->getPlayerObject().get();

	if (ownerGhost == NULL || playerGhost == NULL)
		return 1;

	ManagedReference<GuildObject*> guildObject = owner->getGuildObject().get();

	uint64 playerID = player->getObjectID();
	bool isMember = false, isLeader = false;

	if (guildObject != NULL && guildObject->hasMember(playerID))
		isMember = true;

	if (guildObject != NULL && guildObject->getGuildLeaderID() == playerID)
		isLeader = true;

	switch (selectedID) {
	case 68:
		if (guildObject != NULL && ((isLeader && player == owner) || playerGhost->isPrivileged())) {
			guildManager->sendGuildTransferTo(player, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 69:
		if (isLeader && !ownerGhost->isOnline() && ownerGhost->getDaysSinceLastLogout() >= 28) {
			guildManager->sendAcceptLotsTo(player, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 70:
		if (isLeader && !guildObject->isElectionEnabled()) {
			guildManager->toggleElection(guildObject, player);
		} else if (guildObject != NULL && guildObject->isElectionEnabled()) {
			guildManager->viewElectionStandings(guildObject, player, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 71:
		if (guildObject != NULL && guildObject->isElectionEnabled()) {
			guildManager->viewElectionStandings(guildObject, player, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 72:
		if (isMember && guildObject->isElectionEnabled()) {
			guildManager->promptCastVote(guildObject, player, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 73:
		if (isMember && guildObject->isElectionEnabled()) {
			if (guildObject->isCandidate(playerID)) {
				guildManager->unregisterFromElection(guildObject, player);
			} else {
				guildManager->registerForElection(guildObject, player);
			}
		}
		break;
	case 74:
		if (isLeader && guildObject->isElectionEnabled()) {
			guildManager->resetElection(guildObject, player);
		}
		break;
	case 75:
		if (isLeader) {
			guildManager->toggleElection(guildObject, player);
		}
		break;
	case 76:
		if (playerGhost->isPrivileged()) {
			Locker locker(guildObject);
			guildManager->processGuildUpdate(guildObject);
		}
		break;
	case 185:
		if (guildObject == NULL && player == owner) {
			guildManager->sendGuildCreateNameTo(player, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 189:
		if (guildObject != NULL && (isMember || playerGhost->isPrivileged())) {
			guildManager->sendGuildWarStatusTo(player, guildObject, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 193:
	case 186:
		if (guildObject != NULL && (isMember || playerGhost->isPrivileged())) {
			guildManager->sendGuildInformationTo(player, guildObject, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 191:
		if (guildObject != NULL) {
			guildManager->sendGuildDisbandConfirmTo(player, guildObject, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 194:
	case 187:
		if (guildObject != NULL && (isMember || playerGhost->isPrivileged())) {
			guildManager->sendGuildMemberListTo(player, guildObject, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 188:
		if (guildObject != NULL && (isMember || playerGhost->isPrivileged())) {
			guildManager->sendGuildSponsoredListTo(player, guildObject, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 190:
		if (guildObject != NULL && (isMember || playerGhost->isPrivileged())) {
			guildManager->sendGuildSponsorTo(player, guildObject, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 192:
		if (guildObject != NULL) {
			guildManager->sendGuildChangeNameTo(player, guildObject);
		}
		break;
	default:
		return TerminalImplementation::handleObjectMenuSelect(player, selectedID);
	}

	return 0;
}


