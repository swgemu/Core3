/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : APIProxyStatisticsManager.cpp
 * @created     : Sun Feb 20 18:25:48 UTC 2022
 */

#ifdef WITH_REST_API

#include "engine/engine.h"
#include "server/zone/managers/statistics/StatisticsManager.h"
#include "APIProxyStatisticsManager.h"
#include "APIRequest.h"

namespace server {
 namespace web3 {

void APIProxyStatisticsManager::handleGET(APIRequest& apiRequest) {
	JSONSerializationType metadata;

	Time now;
	metadata["asOfTime"] = now.getFormattedTimeFull();

	JSONSerializationType result;

	result["metadata"] = metadata;
	result["result"] = StatisticsManager::instance()->getAsJSON();

	apiRequest.success(result);
}

void APIProxyStatisticsManager::handlePUT(APIRequest& apiRequest) {
	auto reset = apiRequest.getQueryFieldBool("reset", false, false);

	if (reset) {
		StatisticsManager::instance()->reset();
	}

	handleGET(apiRequest);
}

void APIProxyStatisticsManager::handle(APIRequest& apiRequest) {
	if (apiRequest.isMethodGET()) {
		handleGET(apiRequest);
		return;
	}

	if (apiRequest.isMethodPUT()) {
		handlePUT(apiRequest);
		return;
	}

	apiRequest.fail("Unsupported method.");
}

}
}

#endif // WITH_REST_API
