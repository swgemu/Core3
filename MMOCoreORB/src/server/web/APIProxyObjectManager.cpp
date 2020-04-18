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
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/auction/AuctionItem.h"
#include "server/zone/managers/auction/AuctionManager.h"
#include "server/zone/managers/auction/AuctionsMap.h"

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

int APIProxyObjectManager::deleteObject(APIRequest& apiRequest, uint64 oid, String& resultMessage) {
	auto obj = Core::lookupObject(oid).castTo<ManagedObject*>();

	if (obj == nullptr) {
		return 0;
	}

	Locker lock(obj);

	Reference<SceneObject*> scno = dynamic_cast<SceneObject*>(obj.get());

	if (scno != nullptr && scno->isPlayerObject()) {
		resultMessage = "FAILED; Can not delete player objects via API.";
		return 0;
	}

	StringBuffer exportMsg;

	exportMsg << "Deleted via API, trxId: " << apiRequest.getTrxId();

	StringBuffer result;

	result << "DELETED; Exported to " << exportJSON(obj.get(), exportMsg.toString());

	if (scno != nullptr) {
		auto auctionManager = getZoneServer()->getAuctionManager();

		if (auctionManager != nullptr) {
			auto auctionsMap = auctionManager->getAuctionMap();

			if (auctionsMap != nullptr) {
				if (auctionsMap->containsItem(oid)) {
					Reference<AuctionItem*> aitem = auctionsMap->getItem(oid);

					if (aitem != nullptr) {
						result << "; item was for sale on AuctionItem(" << aitem->getObjectID();
						result << "), auction deleted and exported to " << exportJSON(aitem, exportMsg.toString());
						auctionManager->deleteExpiredSale(aitem, false);
					}
				}
			}
		}

		scno->destroyObjectFromWorld(true);
		scno->destroyObjectFromDatabase(true);
	} else {
		Reference<AuctionItem*> aitem = dynamic_cast<AuctionItem*>(obj.get());

		if (aitem != nullptr) {
			auto auctionManager = getZoneServer()->getAuctionManager();

			if (auctionManager != nullptr) {
				auctionManager->expireSale(aitem);
			}
		} else {
			auto server = getZoneServer();
			server->destroyObjectFromDatabase(oid);
		}
	}

	resultMessage = result.toString();

	return 1;
}

String APIProxyObjectManager::exportJSON(ManagedObject* obj, const String& exportNote) {
	if (obj == nullptr) {
		return "Can't export nullptr object.";
	}

	int count = 0;
	int maxDepth = 1000;

	uint64 oid = obj->_getObjectID();

	JSONSerializationType exportedObjects = JSONSerializationType::object();

	auto scno = dynamic_cast<SceneObject*>(obj);

	if (scno != nullptr) {
		count = scno->writeRecursiveJSON(exportedObjects, maxDepth);
	} else {
		JSONSerializationType jsonData;
		obj->writeJSON(jsonData);
		jsonData["_depth"] = 0;
		jsonData["_oid"] = oid;
		jsonData["_className"] = obj->_getClassName();
		jsonData["_oidPath"] = JSONSerializationType::array();
		jsonData["_oidPath"].push_back(oid);
		exportedObjects[String::valueOf(oid)] = jsonData;
	}

	// Metadata
	Time now;
	JSONSerializationType metaData = JSONSerializationType::object();
	metaData["exportTime"] = now.getFormattedTimeFull();
	metaData["exportNote"] = exportNote;
	metaData["rootObjectID"] = oid;
	metaData["rootObjectClassName"] = obj->_getClassName();
	metaData["objectCount"] = count;
	metaData["maxDepth"] = maxDepth;

	// Root object is meta "exportObject"
	JSONSerializationType exportObject;
	exportObject["metadata"] = metaData;
	exportObject["objects"] = exportedObjects;

	// Save to file...
	StringBuffer fileNameBuf;

	// Spread the files out across directories
	fileNameBuf << "exports";
	if (!File::doMkdir(fileNameBuf.toString().toCharArray(), 0770)) {
		Logger::console.warning() << "could not create " << fileNameBuf << " directory";
	}

	fileNameBuf << File::directorySeparator() << "api";
	if (!File::doMkdir(fileNameBuf.toString().toCharArray(), 0770)) {
		Logger::console.warning() << "could not create " << fileNameBuf << " directory";
	}

	fileNameBuf << File::directorySeparator() << String::hexvalueOf((int64)((oid & 0xFFFF000000000000) >> 48));
	if (!File::doMkdir(fileNameBuf.toString().toCharArray(), 0770)) {
		Logger::console.warning() << "could not create " << fileNameBuf << " directory";
	}

	fileNameBuf << File::directorySeparator() << String::hexvalueOf((int64)((oid & 0x0000FFFFFF000000) >> 24));
	if (!File::doMkdir(fileNameBuf.toString().toCharArray(), 0770)) {
		Logger::console.warning() << "could not create " << fileNameBuf << " directory";
	}

	fileNameBuf << File::directorySeparator() << oid << "-" << now.getMiliTime() << ".json";

	String fileName = fileNameBuf.toString();

	std::ofstream jsonFile(fileName.toCharArray());
	jsonFile << std::setw(4) << exportObject << std::endl;
	jsonFile.close();

	return fileName;
}

void APIProxyObjectManager::handleDELETE(APIRequest& apiRequest) {
	int countDeleted = 0;
	auto results = JSONSerializationType::object();

	auto oid = apiRequest.getPathFieldUnsignedLong("oid", false, 0);

	if (oid == 0 && !apiRequest.hasQueryField("oids")) {
		apiRequest.fail("missing oid or query field 'oids'");
		return;
	}

	if (oid != 0) {
		try {
			apiRequest.debug() << countDeleted << ") Lookup oid " << oid;

			String resultMessage;

			countDeleted += deleteObject(apiRequest, oid, resultMessage);

			results[String::valueOf(oid)] = resultMessage;
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

				apiRequest.debug() << countDeleted << ") Lookup oid " << oid;

				String resultMessage;

				countDeleted += deleteObject(apiRequest, oid, resultMessage);

				results[String::valueOf(oid)] = resultMessage;
			} catch (const Exception& e) {
				apiRequest.fail("Exception looking up objects", "Exception: " + e.getMessage());
				return;
			}
		}
	}

	apiRequest.debug() << "Deleted " << countDeleted << " object(s)";

	if (countDeleted == 0) {
		apiRequest.fail("Nothing found");
	} else {
		JSONSerializationType metadata;

		Time now;
		metadata["deleteTime"] = now.getFormattedTimeFull();
		metadata["deleteCount"] = countDeleted;

		if (apiRequest.hasQueryField("oids")) {
			metadata["query_oids"] = apiRequest.getQueryFieldString("oids");
		} else {
			metadata["query_oids"] = String::valueOf(oid);
		}

		JSONSerializationType result;
		result["results"] = results;
		result["metadata"] = metadata;

		apiRequest.success(result);
	}
}

void APIProxyObjectManager::handle(APIRequest& apiRequest) {
	if (apiRequest.isMethodGET()) {
		handleGET(apiRequest);
		return;
	}

	if (apiRequest.isMethodDELETE()) {
		handleDELETE(apiRequest);
		return;
	}

	apiRequest.fail("Unsupported method");
}

}
}

#endif // WITH_REST_API
