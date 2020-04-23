/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : APIProxyConfigManager.cpp
 * @created     : Wed Apr 22 10:23:57 UTC 2020
 */

#ifdef WITH_REST_API

#include "engine/engine.h"
#include "conf/ConfigManager.h"

#include "APIProxyConfigManager.h"
#include "APIRequest.h"

namespace server {
 namespace web3 {

void APIProxyConfigManager::handleGET(APIRequest& apiRequest) {
	auto key = apiRequest.getPathFieldString("key").replaceAll("/", ".");

	JSONSerializationType found;

	if (!ConfigManager::instance()->getAsJSON(key, found)) {
		apiRequest.fail(key + " not found.", key + " not found.", APIRequestStatus::NotFound);
		return;
	}

	JSONSerializationType metadata;

	Time now;
	metadata["exportTime"] = now.getFormattedTimeFull();

	JSONSerializationType result;

	result["metadata"] = metadata;
	result["result"] = found;

	apiRequest.success(result);
}

void APIProxyConfigManager::handlePUT(APIRequest& apiRequest) {
	auto key = apiRequest.getPathFieldString("key").replaceAll("/", ".");

	auto value = apiRequest.getQueryFieldString("value");

	if (!ConfigManager::instance()->contains(key)) {
		apiRequest.fail(key + " not found.", key + " not found.", APIRequestStatus::NotFound);
	}

	if (!ConfigManager::instance()->setString(key, value)) {
		apiRequest.fail("Failed to update " + key, "Failed to update " + key, APIRequestStatus::NotModified);
		return;
	}

	JSONSerializationType metadata;

	Time now;
	metadata["exportTime"] = now.getFormattedTimeFull();

	JSONSerializationType result;

	result["metadata"] = metadata;

	JSONSerializationType jsonData;

	ConfigManager::instance()->getAsJSON(key, jsonData);

	result["result"] = jsonData;

	apiRequest.success(result);
}

void APIProxyConfigManager::handlePOST(APIRequest& apiRequest) {
	auto key = apiRequest.getPathFieldString("key");

	if (!key.isEmpty()) {
		apiRequest.fail("Invalid request, key cannot be specified for POST operations");
		return;
	}

	apiRequest.parseRequestJSON();

	String errMsg;
	auto jsonData = apiRequest.getRequestJSON();

	if (!ConfigManager::instance()->parseConfigJSON(apiRequest.getRequestJSON(), errMsg, true)) {
		apiRequest.fail("Update failed: " + errMsg, "Update failed: " + errMsg, APIRequestStatus::NotModified);
		return;
	}

	JSONSerializationType metadata;

	Time now;
	metadata["exportTime"] = now.getFormattedTimeFull();

	JSONSerializationType result;

	result["metadata"] = metadata;

	apiRequest.success(result);
}

void APIProxyConfigManager::handle(APIRequest& apiRequest) {
	if (apiRequest.isMethodGET()) {
		handleGET(apiRequest);
		return;
	}

	if (apiRequest.isMethodPUT()) {
		handlePUT(apiRequest);
		return;
	}

	if (apiRequest.isMethodPOST()) {
		handlePOST(apiRequest);
		return;
	}

	apiRequest.fail("Unsupported method.");
}

}
}

#endif // WITH_REST_API
