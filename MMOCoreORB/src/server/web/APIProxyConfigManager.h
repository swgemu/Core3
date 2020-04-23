/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : APIProxyConfigManager.h
 * @created     : Wed Apr 22 10:23:57 UTC 2020
 */

#pragma once

#include "BaseAPIProxy.h"

namespace server {
 namespace web3 {
	class APIRequest;

	class APIProxyConfigManager : public BaseAPIProxy {
	public:
		APIProxyConfigManager() : BaseAPIProxy("ConfigManager")  {
		}

		void handle(APIRequest& apiRequest);
	private:
		void handlePOST(APIRequest& apiRequest);
		void handleGET(APIRequest& apiRequest);
		void handlePUT(APIRequest& apiRequest);
	};
 }
}
