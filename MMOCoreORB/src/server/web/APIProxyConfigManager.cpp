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
	apiRequest.fail("Not implemented");
}

void APIProxyConfigManager::handlePOST(APIRequest& apiRequest) {
	apiRequest.fail("Not implemented");
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
