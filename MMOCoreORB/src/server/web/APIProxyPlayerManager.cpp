/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : APIProxyPlayerManager.cpp
 * @created     : Sun Jan  5 11:26:18 UTC 2020
 */

#ifdef WITH_REST_API

#include "engine/engine.h"
#include "server/ServerCore.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"

#include "APIProxyPlayerManager.h"
#include "APIRequest.h"

namespace server {
 namespace web3 {

server::zone::managers::player::PlayerManager* APIProxyPlayerManager::getPlayerManager() {
	auto server = getZoneServer();

	if (server == nullptr) {
		return nullptr;
	}

	return server->getPlayerManager();
}

void APIProxyPlayerManager::handle(APIRequest& apiRequest) {
	if (!apiRequest.isMethodPOST()) {
		apiRequest.fail("Only supports POST");
		return;
	}

	if (!apiRequest.parseRequestJSON())
		return;

	auto command = apiRequest.getRequestFieldString("command", true);

	if (command.isEmpty()) {
		apiRequest.fail("Invalid request, command is empty.");
		return;
	}

	if (command != "kick") {
		apiRequest.fail("Invalid command: [" + command + "]");
		return;
	}

	uint64_t accountID = apiRequest.getPathFieldUnsignedLong("accountID", true);

	uint32_t galaxyID = apiRequest.getPathFieldUnsignedLong("galaxyID", false, 0ull);

	uint64_t characterID = apiRequest.getPathFieldUnsignedLong("characterID", false, 0ull);

	if (galaxyID == 0 || characterID == 0) {
		apiRequest.fail("Currently account kick is not implemented");
		return;
	}

	uint64_t adminID = apiRequest.getRequestFieldUnsignedLong("admin", true);

	if (adminID == 0) {
		apiRequest.fail("Invalid request, admin is 0");
		return;
	}

	auto reason = apiRequest.getRequestFieldString("reason", true);

	if (reason.isEmpty()) {
		apiRequest.fail("Invalid request, reason is empty.");
		return;
	}

	int expires = apiRequest.getRequestFieldUnsignedLong("expires", false, 0);

	auto playerManager = getPlayerManager();

	if (playerManager == nullptr) {
		apiRequest.fail("Unable to get playerManager");
		return;
	}

	auto adminName = playerManager->getPlayerName(adminID);

	if (adminName.isEmpty()) {
		apiRequest.fail("admin [" + String::valueOf(adminID) + "] not found");
		return;
	}

	auto characterName = playerManager->getPlayerName(characterID);

	if (characterName.isEmpty()) {
		apiRequest.fail("character [" + String::valueOf(characterID) + "] not found");
		return;
	}

	// TODO - This only works if the admin is online, need to check if admin is online, if not need to bring them in first
	if (!playerManager->kickUser(characterName, adminName, reason, expires > 0 ? true : false)) {
		apiRequest.fail("kickUser failed");
		return;
	}

	JSONSerializationType result;

	result["request"] = apiRequest.getRequestJSON();
	result["adminName"] = adminName;
	result["characterName"] = characterName;

	apiRequest.success(result);
}
}
}

#endif // WITH_REST_API
