/*
 * StructureObjectImplementation.cpp
 *
 *  Created on: Aug 15, 2010
 *      Author: crush
 */

#include "StructureObject.h"
#include "server/zone/templates/tangible/SharedStructureObjectTemplate.h"
#include "server/zone/objects/structure/events/StructureMaintenanceTask.h"
#include "server/zone/managers/player/PlayerManager.h"

void StructureObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	SharedStructureObjectTemplate* structureTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateData);

	lotSize = structureTemplate->getLotSize();

	baseMaintenanceRate = structureTemplate->getBaseMaintenanceRate();

	basePowerRate = structureTemplate->getBasePowerRate();

	length = structureTemplate->getLength();

	width = structureTemplate->getWidth();
}

bool StructureObjectImplementation::addPermission(PlayerCreature* player, PlayerCreature* targetPlayer, const String& listName) {
	if (player == NULL || targetPlayer == NULL)
		return false;

	if ((listName == "ENTRY" || listName =="ADMIN") && isOnBanList(targetPlayer)) {
		player->sendSystemMessage("@player_structure:no_banned"); //You cannot add a banned player to the entry list.
		return false;
	}

	if (listName != "BAN" && isOnBanList(targetPlayer)) {
		ParameterizedStringId params;
		params.setStringId("@player_structure:cannot_add_banned"); //%NO must first be removed from the banned list.
		params.setTO(targetPlayer);
		player->sendSystemMessage(params);
		return false;
	}

	if (listName == "ENTRY" && isOnAdminList(targetPlayer)) {
		player->sendSystemMessage("@player_structure:no_remove_admin"); //You cannot remove an admin from the entry list.
		return false;
	}

	return structurePermissionList.addPermission(targetPlayer->getObjectID(), structurePermissionList.getPermissionFromListName(listName));
}

bool StructureObjectImplementation::addPermission(PlayerCreature* player, const String& targetPlayerName, const String& listName) {
	PlayerManager* playerManager = server->getPlayerManager();

	if (playerManager == NULL)
		return false;

	ManagedReference<PlayerCreature*> targetPlayer = playerManager->getPlayer(targetPlayerName);

	if (player == NULL || targetPlayer == NULL)
		return false;

	if ((listName == "ENTRY" || listName =="ADMIN") && isOnBanList(targetPlayer)) {
		player->sendSystemMessage("@player_structure:no_banned"); //You cannot add a banned player to the entry list.
		return false;
	}

	if (listName != "BAN" && isOnBanList(targetPlayer)) {
		ParameterizedStringId params;
		params.setStringId("@player_structure:cannot_add_banned"); //%NO must first be removed from the banned list.
		params.setTO(targetPlayer);
		player->sendSystemMessage(params);
		return false;
	}

	if (listName == "ENTRY" && isOnAdminList(targetPlayer)) {
		player->sendSystemMessage("@player_structure:no_remove_admin"); //You cannot remove an admin from the entry list.
		return false;
	}

	return structurePermissionList.addPermission(targetPlayer->getObjectID(), structurePermissionList.getPermissionFromListName(listName));
}

bool StructureObjectImplementation::removePermission(PlayerCreature* player, PlayerCreature* targetPlayer, const String& listName) {
	if (player == NULL || targetPlayer == NULL)
		return false;

	if (targetPlayer == player) {
		player->sendSystemMessage("@player_structure:cannot_remove_self"); //You cannot remove yourself from the admin list.
		return false;
	}

	if (isOwnerOf(targetPlayer)) {
		player->sendSystemMessage("@player_structure:cannot_remove_owner"); //You cannot remove the owner from the admin list.
		return false;
	}

	return structurePermissionList.removePermission(targetPlayer->getObjectID(), structurePermissionList.getPermissionFromListName(listName));
}

bool StructureObjectImplementation::removePermission(PlayerCreature* player, const String& targetPlayerName, const String& listName) {
	PlayerManager* playerManager = server->getPlayerManager();

	if (playerManager == NULL)
		return false;

	ManagedReference<PlayerCreature*> targetPlayer = playerManager->getPlayer(targetPlayerName);

	if (player == NULL || targetPlayer == NULL)
		return false;

	if (targetPlayer == player) {
		player->sendSystemMessage("@player_structure:cannot_remove_self"); //You cannot remove yourself from the admin list.
		return false;
	}

	if (isOwnerOf(targetPlayer)) {
		player->sendSystemMessage("@player_structure:cannot_remove_owner"); //You cannot remove the owner from the admin list.
		return false;
	}

	return structurePermissionList.removePermission(targetPlayer->getObjectID(), structurePermissionList.getPermissionFromListName(listName));

}

void StructureObjectImplementation::scheduleMaintenanceExpirationEvent() {
	float timeRemaining = surplusMaintenance / baseMaintenanceRate / 3600000;

	maintenanceExpires.updateToCurrentTime();
	maintenanceExpires.addMiliTime(timeRemaining);

	if (structureMaintenanceTask == NULL)
		structureMaintenanceTask = new StructureMaintenanceTask(_this);

	if (structureMaintenanceTask->isScheduled())
		structureMaintenanceTask->reschedule();
	else
		structureMaintenanceTask->schedule(timeRemaining);
}
