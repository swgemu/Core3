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
#include "server/login/account/AccountManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/credits/CreditObject.h"
#include "server/zone/objects/guild/GuildObject.h"

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

void APIProxyPlayerManager::lookupCharacter(APIRequest& apiRequest) {
	if (!apiRequest.isMethodGET()) {
		apiRequest.fail("Only supports GET");
		return;
	}

	auto server = getZoneServer();

	if (server == nullptr) {
		apiRequest.fail("Failed to getZoneServer");
		return;
	}

	if (server->isServerLoading()) {
		apiRequest.fail("zoneServer is loading.");
		return;
	}

	auto qName = apiRequest.getQueryFieldString("name", false);
	auto qNames = apiRequest.getQueryFieldString("names", false);
    auto qSearch = apiRequest.getQueryFieldString("search", false, "").toLowerCase();
	auto qRecursive = apiRequest.getQueryFieldBool("recursive", false, false);
	auto qMaxDepth = apiRequest.getQueryFieldUnsignedLong("maxdepth", false, 3);
    auto qLimit = apiRequest.getQueryFieldUnsignedLong("limit", false, 20);
    auto qOffset = apiRequest.getQueryFieldUnsignedLong("offset", false, 0);
	bool findMode = apiRequest.getPathFieldString("mode", true) == "find";

	if (qName.isEmpty() && qNames.isEmpty() && qSearch.isEmpty()) {
		apiRequest.fail("Invalid request, must specify one of: name, names, search");
		return;
	}

	if (!qSearch.isEmpty() && qSearch.length() < 3) {
		apiRequest.fail("Invalid request, search much be at least 3 characters in length.");
		return;
	}

	if (findMode && qLimit > 100) {
		apiRequest.fail("Invalid request, limit must not be more than 100 for find");
		return;
	}

	if (qLimit > 1000) {
		apiRequest.fail("Invalid request, limit must not be more than 1000 for lookup");
		return;
	}

	Vector<String> names;

	if (!qName.isEmpty()) {
		names.add(qName);
	}

	if (!qNames.isEmpty()) {
		StringTokenizer nameList(qNames);
		nameList.setDelimeter(",");

		while (nameList.hasMoreTokens()) {
			String name;
			nameList.getStringToken(name);

			if (!name.isEmpty()) {
				names.add(name);
			}
		}
	}

	auto playerManager = getPlayerManager();

	if (playerManager == nullptr) {
		apiRequest.fail("Unable to get playerManager");
		return;
	}

	Timer msSearch, msExport;
	int countFound = 0;
	auto found = JSONSerializationType::object();
	auto objects = JSONSerializationType::object();
	SortedVector<uint64> hits;

	hits.setAllowOverwriteInsertPlan();

	msSearch.start();

	for (auto name : names) {
		auto oid = playerManager->getObjectID(name);

		if (oid != 0) {
			hits.put(oid);
		}
	}

	if (!qSearch.isEmpty()) {
		playerManager->iteratePlayerNames([&](String name, uint64 oid) -> void {
			if (name.beginsWith(qSearch)) {
				hits.put(oid);
			}
		});
	}

	msSearch.stop();

	msExport.start();

	auto stop = qOffset + qLimit > hits.size() ? hits.size() : qOffset + qLimit;

	for (int i = qOffset; i < stop; ++i) {
		auto oid = hits.get(i);

		found[playerManager->getPlayerName(oid)] = oid;

		if (!findMode) {
			countFound++;
			continue;
		}

		Reference<CreatureObject*> creo = server->getObject(hits.get(i)).castTo<CreatureObject*>();

		if (creo == nullptr) {
			continue;
		}

		if (qRecursive) {
			countFound += creo->writeRecursiveJSON(objects, qMaxDepth);
		} else {
			countFound += creo->writeRecursiveJSON(objects, 1);

			Locker wLock(creo);
			auto ghost = creo->getPlayerObject();
			auto crobj = creo->getCreditObject();
			wLock.release();

			if (ghost != nullptr) {
				auto oidPath = new Vector<uint64>;
				oidPath->add(creo->getObjectID());
				countFound += ghost->writeRecursiveJSON(objects, 1, oidPath);
				delete oidPath;
			}

			if (crobj != nullptr) {
				ReadLocker crLock(crobj);
				auto oid = crobj->_getObjectID();
				JSONSerializationType jsonData;
				crobj->writeJSON(jsonData);
				countFound++;
				jsonData["_depth"] = 1;
				jsonData["_oid"] = oid;
				jsonData["_className"] = crobj->_getClassName();
				jsonData["_oidPath"] = JSONSerializationType::array();
				jsonData["_oidPath"].push_back(creo->getObjectID());
				jsonData["_oidPath"].push_back(oid);
				objects[String::valueOf(oid)] = jsonData;
			}
		}

		auto guild = creo->getGuildObject().get();

		if (guild != nullptr) {
			auto oidPath = new Vector<uint64>;
			oidPath->add(creo->getObjectID());
			countFound += guild->writeRecursiveJSON(objects, qRecursive ? qMaxDepth : 1, oidPath);
			delete oidPath;
		}
	}

	msExport.stop();

	JSONSerializationType metadata;

	Time now;
	metadata["exportTime"] = now.getFormattedTimeFull();
	metadata["objectCount"] = countFound;
	metadata["maxDepth"] = qMaxDepth;
	metadata["recursive"] = qRecursive;
	metadata["msSearch"] = msSearch.getElapsedTimeMs();
	metadata["msExport"] = msExport.getElapsedTimeMs();

    // Pagination data
    metadata["offset"] = qOffset;
    metadata["limit"] = qLimit;
    metadata["total"] = hits.size();

    if (hits.size() > qOffset + qLimit) {
        metadata["resultsRemaining"] = hits.size() - (qOffset + qLimit);
    } else {
        metadata["resultsRemaining"] = 0;
    }

	JSONSerializationType result;

	result["metadata"] = metadata;
	result["names"] = found;

	if (findMode) {
		result["objects"] = objects;
	}

	apiRequest.success(result);
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

	if (command != "kick" && command != "ban") {
		apiRequest.fail("Invalid command: [" + command + "]");
		return;
	}

	uint64_t accountID = apiRequest.getPathFieldUnsignedLong("accountID", true);

	uint32_t galaxyID = apiRequest.getPathFieldUnsignedLong("galaxyID", false, 0ull);

	uint64_t characterID = apiRequest.getPathFieldUnsignedLong("characterID", false, 0ull);

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

	JSONSerializationType result;

	result["request"] = apiRequest.getRequestJSON();
	result["admin_name"] = adminName;

	if (command == "kick") {
		if (galaxyID == 0 || characterID == 0) {
			apiRequest.fail("Currently account kick is not implemented");
			return;
		}

		auto characterName = playerManager->getPlayerName(characterID);

		if (characterName.isEmpty()) {
			apiRequest.fail("character [" + String::valueOf(characterID) + "] not found");
			return;
		}

		result["action"] = expires > 0 ? "kickbanned player" : "kicked player";
		result["target"] = characterName;

		if (!playerManager->kickUser(characterName, adminName, reason, expires > 0 ? true : false)) {
			apiRequest.fail("kickUser failed");
			return;
		}

		result["action_result"] = "SUCCESS";
	} else if (command == "ban") {
		Reference<CreatureObject*> adminCreo = playerManager->getPlayer(adminName);

		if (adminCreo == nullptr) {
			apiRequest.fail("failed to get admin creature object");
			return;
		}

		Reference<PlayerObject*> adminGhost = adminCreo->getPlayerObject();

		if (adminGhost == nullptr) {
			apiRequest.fail("failed to get admin player object");
			return;
		}

		Reference<Account*> account = AccountManager::getAccount(accountID);

		if (account == nullptr) {
			apiRequest.fail("Account not found (accountID: " + String::valueOf(accountID) + ")");
			return;
		}

		result["username"] = account->getUsername();

		String banResult;

		if (galaxyID == 0 || characterID == 0) {
			result["action"] = "banned account";
			result["target"] = account->getUsername();
			result["action_result"] = playerManager->banAccount(adminGhost, account, expires, reason);
		} else {
			auto characterName = playerManager->getPlayerName(characterID);

			if (characterName.isEmpty()) {
				apiRequest.fail("character [" + String::valueOf(characterID) + "] not found");
				return;
			}

			result["action"] = "banned player";
			result["target"] = characterName;
			result["action_result"] = playerManager->banCharacter(adminGhost, account, characterName, galaxyID, expires, reason);
		}

		adminCreo->sendSystemMessage("API command ban: " + String(result["action_result"]));
	}

	apiRequest.info(true)
		<< adminName << " "
		<< result["action"].get<std::string>() << " "
		<< result["target"].get<std::string>() << " "
		<< "for '" << reason << "' "
		<< "expires = " << expires << ", "
		<< "result = " << result["action_result"].get<std::string>();

	apiRequest.success(result);
}
}
}

#endif // WITH_REST_API
