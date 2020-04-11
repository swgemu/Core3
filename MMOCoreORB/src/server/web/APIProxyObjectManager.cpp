/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : APIProxyObjectManager.cpp
 * @created     : Sat Apr 11 10:32:31 UTC 2020
 */

#ifdef WITH_REST_API

#include "engine/engine.h"
#include "server/ServerCore.h"
#include "server/zone/objects/scene/SceneObject.h"

#include "APIProxyObjectManager.h"
#include "APIRequest.h"

namespace server {
 namespace web3 {

int APIProxyObjectManager::writeObjectJSON(uint64 oid, bool recursive, bool parents, JSONSerializationType& objects, int maxDepth) {
	int countFound = 0;

	auto obj = Core::lookupObject(oid).castTo<ManagedObject*>();

	if (obj != nullptr) {
		ReadLocker lock(obj);

		auto scno = dynamic_cast<SceneObject*>(obj.get());

		if (scno != nullptr) {
			if (!recursive) {
				maxDepth = 1;
			}

			if (parents) {
				auto rootObj = scno->getRootParent();

				if (rootObj != nullptr) {
					scno = rootObj;
				}
			}

			countFound += scno->writeRecursiveJSON(objects, maxDepth);
		} else {
			JSONSerializationType jsonData;
			obj->writeJSON(jsonData);
			countFound++;
			jsonData["_depth"] = 0;
			jsonData["_oid"] = oid;
			jsonData["_className"] = obj->_getClassName();
			jsonData["_oidPath"] = JSONSerializationType::array();
			jsonData["_oidPath"].push_back(oid);
			objects[String::valueOf(oid)] = jsonData;
		}
	}

	return countFound;
}

void APIProxyObjectManager::handleGET(APIRequest& apiRequest) {
	auto parents = apiRequest.getQueryFieldBool("parents", false, false);
	auto recursive = apiRequest.getQueryFieldBool("recursive", false, false);
	int maxDepth = apiRequest.getQueryFieldUnsignedLong("maxdepth", false, 1000);

	int countFound = 0;
	auto objects = JSONSerializationType::object();

	auto oid = apiRequest.getPathFieldUnsignedLong("oid", false, 0);

	if (oid == 0 && !apiRequest.hasQueryField("oids")) {
		apiRequest.fail("missing oid or query field 'oids'");
		return;
	}

	if (oid != 0) {
		try {
			apiRequest.debug() << countFound << ") Lookup oid " << oid;

			countFound += writeObjectJSON(oid, recursive, parents, objects, maxDepth);
		} catch (const Exception& e) {
			apiRequest.fail("Exception looking up object", "Exception: " + e.getMessage());
			return;
		}
	}

	if (apiRequest.hasQueryField("oids")) {
		StringTokenizer oidStrList(apiRequest.getQueryFieldString("oids"));
		oidStrList.setDelimeter(",");

		while(oidStrList.hasMoreTokens()) {
			try {
				uint64 oid = oidStrList.getUnsignedLongToken();

				apiRequest.debug() << countFound << ") Lookup oid " << oid;

				countFound += writeObjectJSON(oid, recursive, parents, objects, maxDepth);
			} catch (const Exception& e) {
				apiRequest.fail("Exception looking up objects", "Exception: " + e.getMessage());
				return;
			}
		}
	}

	apiRequest.debug() << "Found " << countFound << " object(s)";

	if (countFound == 0) {
		apiRequest.fail("Nothing found");
	} else {
		JSONSerializationType metadata;

		Time now;
		metadata["exportTime"] = now.getFormattedTimeFull();
		metadata["objectCount"] = countFound;
		metadata["maxDepth"] = maxDepth;
		metadata["recursive"] = recursive;
		metadata["parents"] = parents;

		if (apiRequest.hasQueryField("oids")) {
			metadata["query_oids"] = apiRequest.getQueryFieldString("oids");
		} else {
			metadata["query_oids"] = String::valueOf(oid);
		}

		JSONSerializationType result;
		result["objects"] = objects;
		result["metadata"] = metadata;

		apiRequest.success(result);
	}
}

void APIProxyObjectManager::handle(APIRequest& apiRequest) {
	if (apiRequest.isMethodGET()) {
		handleGET(apiRequest);
		return;
	}

	apiRequest.fail("Unsupported method");
}

}
}

#endif // WITH_REST_API
