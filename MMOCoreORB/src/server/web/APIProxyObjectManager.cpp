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
#include "server/zone/objects/tangible/tool/antidecay/AntiDecayKit.h"
#include "server/zone/managers/auction/AuctionManager.h"
#include "server/zone/managers/auction/AuctionsMap.h"
#include "conf/ConfigManager.h"

#include "APIProxyObjectManager.h"
#include "APIRequest.h"

#include <iomanip>

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

			lock.release();
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

int APIProxyObjectManager::deleteObject(APIRequest& apiRequest, uint64 oid, bool refundADK, String& resultMessage) {
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

	lock.release();
	result << "DELETED; Exported to " << exportJSON(obj.get(), exportMsg.toString());

	if (scno != nullptr) {
		Locker lock(scno);

		auto auctionManager = getZoneServer()->getAuctionManager();
		auto auctionOwnerID = 0ull;

		if (auctionManager != nullptr) {
			auto auctionsMap = auctionManager->getAuctionMap();

			if (auctionsMap != nullptr) {
				if (auctionsMap->containsItem(oid)) {
					Reference<AuctionItem*> aitem = auctionsMap->getItem(oid);

					if (aitem != nullptr) {
						auctionOwnerID = aitem->getOwnerID();
						result << "; item was for sale on AuctionItem(" << aitem->getObjectID();
						result << ") by player " << auctionOwnerID << ", auction deleted and exported to ";
						result << exportJSON(aitem, exportMsg.toString());
						auctionManager->deleteExpiredSale(aitem, false);
					}
				}
			}
		}

		auto tano = scno->asTangibleObject();

		if (tano != nullptr && tano->hasAntiDecayKit() && refundADK) {
			Reference<SceneObject*> dest = scno->getParent().get();

			if (dest == nullptr && auctionOwnerID > 0) {
				dest = getZoneServer()->getObject(auctionOwnerID);
			}

			if (dest != nullptr && dest->isCreatureObject()) {
				Locker lock(dest);

				auto inventory = dest->getSlottedObject("inventory");

				if (inventory == nullptr && dest->isPlayerObject()) {
					result << "; Failed to find inventory for " << dest->_getClassName() << "(" << dest->getObjectID() << ")";
				}

				dest = inventory;
			}

			if (dest != nullptr) {
				Reference<AntiDecayKit*> adk = dynamic_cast<AntiDecayKit*>(tano->removeAntiDecayKit());

				if (adk != nullptr) {
					Reference<SceneObject*> where = dest->isPlayerCreature() ? dest : dest->getParentRecursively(SceneObjectType::PLAYERCREATURE);

					if (where == nullptr) {
						where = dest->getParentRecursively(SceneObjectType::BUILDING);
					}

					if (where != nullptr) {
						Locker lock(dest);
						Locker cLock(adk, dest);

						adk->setUsed(false);
						adk->initializePosition(scno->getPositionX(), scno->getPositionZ(), scno->getPositionY());
						adk->setDirection(Math::deg2rad(scno->getDirectionAngle()));
						dest->transferObject(adk, -1, true, true);
						dest->broadcastObject(adk, true);

						result << "; refunded AntiDecayKit(" << adk->getObjectID() << ") to ";
						result << where->_getClassName() << "(" << where->getObjectID() << ")";
						result << " into " << dest->_getClassName() << "(" << dest->getObjectID() << ")";
					} else {
						Locker lock(adk);

						result << "; will not refund AntiDecayKit(" << adk->getObjectID() << ") to ";
						result << dest->_getClassName() << "(" << dest->getObjectID() << ")";

						adk->destroyObjectFromWorld(true);
						adk->destroyObjectFromDatabase(true);
					}
				}
			} else {
				result << "; failed to find destination to refund AntiDecayKit(" << tano->getAntiDecayKitObjectID() << ")";
			}
		}

		Reference<CreatureObject*> creo = scno->getParentRecursively(SceneObjectType::PLAYERCREATURE).castTo<CreatureObject*>();

		if (creo != nullptr) {
			Locker lock(creo);
			creo->removeWearableObject(scno->asTangibleObject(), true);
			scno->destroyObjectFromWorld(true);
			scno->destroyObjectFromDatabase(true);
		} else {
			scno->destroyObjectFromWorld(true);
			scno->destroyObjectFromDatabase(true);
		}
	} else {
		Locker lock(obj);

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
		Locker lock(obj);
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

	auto exportBasedir = ConfigManager::instance()->getString("Core3.RESTServer.exportDir", "log/exports/api/%Y-%m-%d/%H/");

	// Save to file...
	StringBuffer fileNameBuf;

	fileNameBuf << now.getFormattedTime(exportBasedir) << oid << "/";

	String dirName = fileNameBuf.toString();

	if (File::directorySeparator() != '/') {
		dirName.replaceAll("/", String().concat(File::directorySeparator()));
	}

	File::mkpath(dirName, 0755);

	fileNameBuf << oid << "-" << now.getMiliTime() << ".json";

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

	auto refundADK = apiRequest.getQueryFieldBool("refundADK", false, false);

	if (oid != 0) {
		try {
			apiRequest.debug() << countDeleted << ") Lookup oid " << oid;

			String resultMessage;

			countDeleted += deleteObject(apiRequest, oid, refundADK, resultMessage);

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

				countDeleted += deleteObject(apiRequest, oid, refundADK, resultMessage);

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

bool APIProxyObjectManager::updateObject(APIRequest& apiRequest, uint64 oid, String& resultMessage) {
	auto className = apiRequest.getPathFieldString("class");

	if (className != "SceneObject") {
		resultMessage = "Updates to " + className + " not supported";
		return false;
	}

	auto obj = Core::lookupObject(oid).castTo<ManagedObject*>();

	if (obj == nullptr) {
		resultMessage = "Object not found";
		return false;
	}

	Locker lock(obj);

	Reference<SceneObject*> scno = dynamic_cast<SceneObject*>(obj.get());

	if (scno == nullptr) {
		resultMessage = "Updates only supported for SceneObject's";
		return false;
	}

	auto propertyName = apiRequest.getPathFieldString("property");
	auto value = apiRequest.getQueryFieldBool("value");

	StringBuffer exportMsg;

	exportMsg << "Updating " << propertyName << "=" << value << " via API, trxId: " << apiRequest.getTrxId();

	resultMessage = "UPDATED; Exported original to " + exportJSON(obj.get(), exportMsg.toString());

	// TODO this should be more generic to support more properties

	if (propertyName == "forceNoTrade") {
		scno->setForceNoTrade(value);
	} else {
		resultMessage = "Updates to " + className + "." + propertyName + " not supported.";
		return false;
	}

	return true;
}

void APIProxyObjectManager::handlePUT(APIRequest& apiRequest) {
	auto oid = apiRequest.getPathFieldUnsignedLong("oid", false, 0);

	if (oid == 0) {
		apiRequest.fail("missing oid in uri");
		return;
	}

	int countUpdated = 0;
	auto results = JSONSerializationType::object();

	try {
		apiRequest.debug() << "Update oid " << oid;

		String resultMessage;

		if (!updateObject(apiRequest, oid, resultMessage)) {
			apiRequest.fail(resultMessage);
			return;
		}

		results[String::valueOf(oid)] = resultMessage;
		countUpdated += 1;
	} catch (const Exception& e) {
		apiRequest.fail("Exception updating object", "Exception: " + e.getMessage());
		return;
	}

	apiRequest.debug() << "Updated " << countUpdated << " object(s)";

	if (countUpdated == 0) {
		apiRequest.fail("Nothing found to update.");
	} else {
		JSONSerializationType metadata;

		Time now;
		metadata["exportTime"] = now.getFormattedTimeFull();
		metadata["objectCount"] = countUpdated;
		metadata["maxDepth"] = 1;
		metadata["recursive"] = false;
		metadata["parents"] = false;
		metadata["query_oids"] = String::valueOf(oid);

		JSONSerializationType result;
		result["results"] = results;
		result["metadata"] = metadata;

		apiRequest.success(result);
	}
}

void APIProxyObjectManager::handle(APIRequest& apiRequest) {
	auto zoneServer = getZoneServer();

	if (zoneServer == nullptr) {
		apiRequest.fail("zoneServer not found.");
		return;
	}

	if (zoneServer->isServerLoading()) {
		apiRequest.fail("zoneServer is loading.");
		return;
	}

	if (apiRequest.isMethodGET()) {
		handleGET(apiRequest);
		return;
	}

	if (apiRequest.isMethodDELETE()) {
		handleDELETE(apiRequest);
		return;
	}

	if (apiRequest.isMethodPUT()) {
		handlePUT(apiRequest);
		return;
	}

	apiRequest.fail("Unsupported method");
}

}
}

#endif // WITH_REST_API
