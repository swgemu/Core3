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
	auto qRecursive = apiRequest.getQueryFieldBool("recursive", false, false);
	auto qCaseInsensitive = apiRequest.getQueryFieldBool("ignorecase", false, false);
	auto qSearch = apiRequest.getQueryFieldString("search", false, "");
	int qMaxDepth = apiRequest.getQueryFieldUnsignedLong("maxdepth", false, 2);
	auto qLimit = apiRequest.getQueryFieldUnsignedLong("limit", false, 20);
	auto qOffset = apiRequest.getQueryFieldUnsignedLong("offset", false, 0);

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

	Time startSearchTime;
	int countFound = 0;
	auto objects = JSONSerializationType::object();
	auto found = JSONSerializationType::object();
	SortedVector<uint64> hits;

	hits.setAllowOverwriteInsertPlan();

	guildManager->iterateGuilds([&](GuildObject* guild) -> void {
		if (guild == nullptr) {
			return;
		}

		auto guildAbbr = qCaseInsensitive ? guild->getGuildAbbrev().toLowerCase() : guild->getGuildAbbrev();
		auto guildName = qCaseInsensitive ? guild->getGuildName().toLowerCase() : guild->getGuildName();

		if (!qSearch.isEmpty() && (guildAbbr.contains(qSearch) || guildName.contains(qSearch))) {
			hits.put(guild->getObjectID());
		} else {
			for (auto name: names) {
				if (name == guildAbbr || (qCaseInsensitive && name.toLowerCase() == guildAbbr)) {
					hits.put(guild->getObjectID());
					break;
				}
			}
		}
	});

	Time startExportTime;
	auto msSearch = startSearchTime.miliDifference();
	auto mode = apiRequest.getPathFieldString("mode", true);

	// Handle matched guilds
	auto stop = qOffset + qLimit > hits.size() ? hits.size() : qOffset + qLimit;

	for (int i = qOffset; i < stop; ++i) {
		Reference<GuildObject*> guild = server->getObject(hits.get(i)).castTo<GuildObject*>();

		if (guild == nullptr) {
			continue;
		}

		found[guild->getGuildAbbrev()] = guild->getObjectID();

		if (mode == "find") {
			countFound += guild->writeRecursiveJSON(objects, qRecursive ? qMaxDepth : 1);
		} else {
			countFound++;
		}
	}

	auto msExport = startExportTime.miliDifference();

	JSONSerializationType metadata;

	Time now;
	metadata["exportTime"] = now.getFormattedTimeFull();
	metadata["objectCount"] = countFound;
	metadata["maxDepth"] = qMaxDepth;
	metadata["recursive"] = qRecursive;
	metadata["msSearch"] = msSearch;
	metadata["msExport"] = msExport;

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

	if (mode == "find") {
		result["objects"] = objects;
	}

	apiRequest.success(result);
}

void APIProxyGuildManager::handle(APIRequest& apiRequest) {
	apiRequest.fail("Unsupported method");
}

}
}

#endif // WITH_REST_API
