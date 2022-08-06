#include "server/zone/objects/creature/ai/GuildManagementDroid.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/managers/guild/GuildManager.h"

void GuildManagementDroidImplementation::initializeTransientMembers() {
	AiAgentImplementation::initializeTransientMembers();
}

void GuildManagementDroidImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
}

void GuildManagementDroidImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (player == nullptr)
		return;

	ManagedReference<CreatureObject*> owner = getLinkedCreature().get();

	if (owner == nullptr || !owner->isPlayerCreature()) {
		return;
	}

	if (owner == player) {
		// Droid Options
		menuResponse->addRadialMenuItem(132, 3, "@pet/pet_menu:droid_options");
		menuResponse->addRadialMenuItemToRadialID(132, 59, 3, "@pet/pet_menu:menu_store"); // Store

		if (!ConfigManager::instance()->useGuildEnhancements() || isDead())
			return;

		ManagedReference<PlayerObject*> ownerGhost = owner->getPlayerObject().get();
		ManagedReference<PlayerObject*> playerGhost = player->getPlayerObject().get();

		if (ownerGhost == nullptr || playerGhost == nullptr)
			return;

		ManagedReference<GuildObject*> guildObject = player->getGuildObject().get();

		if (guildObject == nullptr) {
			if (!player->isInGuild()) {
				menuResponse->addRadialMenuItem(185, 3, "@guild:menu_create"); // Create Guild
			}

			return;
		}

		// Guild Options
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

		return;
	}

	return;

}

int GuildManagementDroidImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (player == nullptr)
		return 1;

	ManagedReference<GuildManager*> guildManager = getZoneServer()->getGuildManager();

	if (guildManager == nullptr)
		return 1;

	ManagedReference<CreatureObject*> owner = getLinkedCreature().get();

	if (owner == nullptr || !owner->isPlayerCreature()) {
		return 1;
	}

	ManagedReference<PlayerObject*> ownerGhost = owner->getPlayerObject().get();
	ManagedReference<PlayerObject*> playerGhost = player->getPlayerObject().get();

	if (ownerGhost == nullptr || playerGhost == nullptr)
		return 1;

	ManagedReference<GuildObject*> guildObject = owner->getGuildObject().get();

	uint64 playerID = player->getObjectID();
	bool isMember = false, isLeader = false;

	if (guildObject != nullptr && guildObject->hasMember(playerID))
		isMember = true;

	if (guildObject != nullptr && guildObject->getGuildLeaderID() == playerID)
		isLeader = true;

	switch (selectedID) {
	case 70:
		if (isLeader && !guildObject->isElectionEnabled()) {
			guildManager->toggleElection(guildObject, player);
		} else if (guildObject != nullptr && guildObject->isElectionEnabled()) {
			guildManager->viewElectionStandings(guildObject, player, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 71:
		if (guildObject != nullptr && guildObject->isElectionEnabled()) {
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
	case 185:
		if (guildObject == nullptr && player == owner) {
			guildManager->sendGuildCreateNameTo(player, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 189:
		if (guildObject != nullptr && (isMember || playerGhost->isPrivileged())) {
			guildManager->sendGuildWarStatusTo(player, guildObject, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 193:
	case 186:
		if (guildObject != nullptr && (isMember || playerGhost->isPrivileged())) {
			guildManager->sendGuildInformationTo(player, guildObject, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 191:
		if (guildObject != nullptr) {
			guildManager->sendGuildDisbandConfirmTo(player, guildObject, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 194:
	case 187:
		if (guildObject != nullptr && (isMember || playerGhost->isPrivileged())) {
			guildManager->sendGuildMemberListTo(player, guildObject, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 188:
		if (guildObject != nullptr && (isMember || playerGhost->isPrivileged())) {
			guildManager->sendGuildSponsoredListTo(player, guildObject, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 190:
		if (guildObject != nullptr && (isMember || playerGhost->isPrivileged())) {
			guildManager->sendGuildSponsorTo(player, guildObject, _this.getReferenceUnsafeStaticCast());
		}
		break;
	case 192:
		if (guildObject != nullptr) {
			guildManager->sendGuildChangeNameTo(player, guildObject);
		}
		break;
	default:
		return SceneObjectImplementation::handleObjectMenuSelect(player, selectedID); // PetMenuComponent
	}

	return 0;
}