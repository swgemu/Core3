/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : APIProxyStatisticsManager.h
 * @created     : Sun Feb 20 18:25:48 UTC 2022
 */

#pragma once

#include "BaseAPIProxy.h"

namespace server {
 namespace web3 {
	class APIRequest;

	class APIProxyStatisticsManager : public BaseAPIProxy {
	public:
		APIProxyStatisticsManager() : BaseAPIProxy("StatisticsManager")  {
		}

		void handle(APIRequest& apiRequest);
	private:
		void handleGET(APIRequest& apiRequest);
		void handlePUT(APIRequest& apiRequest);
	};
 }
}
