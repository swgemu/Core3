/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : APIProxyGuildManager.cpp
 * @created     : Sun Jan  5 11:26:18 UTC 2020
 */

#ifdef WITH_REST_API

#include "engine/engine.h"
#include "server/ServerCore.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/managers/guild/GuildManager.h"

#include "APIProxyGuildManager.h"
#include "APIRequest.h"

namespace server {
 namespace web3 {

server::zone::managers::guild::GuildManager* APIProxyGuildManager::getGuildManager() {
	auto server = getZoneServer();

	if (server == nullptr) {
		return nullptr;
	}

	return server->getGuildManager();
}

void APIProxyGuildManager::lookupGuild(APIRequest& apiRequest) {
	if (!apiRequest.isMethodGET()) {
		apiRequest.fail("Only supports GET");
		return;
	}

	auto qName = apiRequest.getQueryFieldString("name", false);
	auto qNames = apiRequest.getQueryFieldString("names", false);
	auto qRecursive = apiRequest.getQueryFieldBool("recursive", false, false);
	auto qCaseInsensitive = apiRequest.getQueryFieldBool("ignorecase", false, false);
	auto qSearch = apiRequest.getQueryFieldString("search", false, "");
	int qMaxDepth = apiRequest.getQueryFieldUnsignedLong("maxdepth", false, 1000);

	if (qName.isEmpty() && qNames.isEmpty() && qSearch.isEmpty()) {
		apiRequest.fail("Invalid request, must specify one of: name, names, search");
		return;
	}

	if (!qSearch.isEmpty() && qCaseInsensitive) {
		qSearch = qSearch.toLowerCase();
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
				if (qCaseInsensitive) {
					name = name.toLowerCase();
				}

				names.add(name);
			}
		}
	}

	auto guildManager = getGuildManager();

	if (guildManager == nullptr) {
		apiRequest.fail("Unable to get guildManager");
		return;
	}

	int countFound = 0;

	JSONSerializationType result, found, objects;
	Vector<Reference<GuildObject*>> hits;

	guildManager->iterateGuilds([&](GuildObject* guild) -> void {
		if (guild == nullptr) {
			return;
		}

		auto guildAbbr = qCaseInsensitive ? guild->getGuildAbbrev().toLowerCase() : guild->getGuildAbbrev();
		auto guildName = qCaseInsensitive ? guild->getGuildName().toLowerCase() : guild->getGuildName();

		if (!qSearch.isEmpty() && (guildAbbr.contains(qSearch) || guildName.contains(qSearch))) {
			hits.add(guild);
		} else {
			for (auto name: names) {
				if (name == guildAbbr || (qCaseInsensitive && name.toLowerCase() == guildAbbr)) {
					hits.add(guild);
					break;
				}
			}
		}
	});

	auto mode = apiRequest.getPathFieldString("mode", true);

	// Handle matched guilds
	for (int i = 0; i < hits.size(); ++i) {
		auto guild = hits.get(i);

		if (guild == nullptr) {
			continue;
		}

		found[guild->getGuildAbbrev()] = guild->getObjectID();

		if (mode == "find") {
			Locker lock(guild);
			countFound += guild->writeRecursiveJSON(objects, qRecursive ? qMaxDepth : 1);
		} else {
			countFound++;
		}
	}

	if (countFound == 0) {
		apiRequest.fail("Nothing found");
	} else {
		JSONSerializationType metadata;

		Time now;
		metadata["exportTime"] = now.getFormattedTimeFull();
		metadata["objectCount"] = countFound;
		metadata["maxDepth"] = qMaxDepth;
		metadata["recursive"] = qRecursive;

		if (apiRequest.hasQueryField("name")) {
			metadata["query_names"] = apiRequest.getQueryFieldString("name");
		} else if (apiRequest.hasQueryField("names")) {
			metadata["query_names"] = apiRequest.getQueryFieldString("names");
		}

		if (apiRequest.hasQueryField("search")) {
			metadata["query_search"] = apiRequest.getQueryFieldString("search");
		}

		JSONSerializationType result;

		result["metadata"] = metadata;
		result["names"] = found;

		if (mode == "find") {
			result["objects"] = objects;
		}

		apiRequest.success(result);
	}
}

void APIProxyGuildManager::handle(APIRequest& apiRequest) {
	apiRequest.fail("Unsupported method");
}

}
}

#endif // WITH_REST_API
